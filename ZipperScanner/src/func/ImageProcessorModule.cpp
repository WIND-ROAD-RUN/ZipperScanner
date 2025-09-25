#include "ImageProcessorModule.h"

#include <qcolor.h>
#include <QPainter>

#include "GlobalStruct.hpp"
#include"imgPro_ImagePainter.hpp"
#include "Modules.hpp"
#include "Utilty.hpp"

ImageProcessorZipper::ImageProcessorZipper(QQueue<MatInfo>& queue, QMutex& mutex, QWaitCondition& condition, int workIndex, QObject* parent)
	: QThread(parent), _queue(queue), _mutex(mutex), _condition(condition), _workIndex(workIndex) {

}

void ImageProcessorZipper::run()
{
	while (!QThread::currentThread()->isInterruptionRequested()) {
		MatInfo frame;
		{
			QMutexLocker locker(&_mutex);
			if (_queue.isEmpty()) {
				_condition.wait(&_mutex);
				if (QThread::currentThread()->isInterruptionRequested()) {
					break;
				}
			}
			if (!_queue.isEmpty()) {
				frame = _queue.dequeue();
			}
			else {
				continue; // 如果队列仍为空，跳过本次循环
			}
		}

		// 检查 frame 是否有效
		if (frame.image.empty()) {
			continue; // 跳过空帧
		}

		auto& runningState = Modules::getInstance().runtimeInfoModule.runningState;

		// 获取当前时间点
		auto now = std::chrono::system_clock::now();
		// 转换为time_t格式
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);
		// 转换为本地时间
		std::tm* local_time = std::localtime(&now_time);

		auto currentRunningState = runningState.load();
		switch (currentRunningState)
		{
		case RunningState::Debug:
			run_debug(frame);
			break;
		case RunningState::OpenRemoveFunc:
			run_OpenRemoveFunc(frame);
			break;
		case RunningState::Stop:
			run_stop(frame);
			break;
		default:
			break;
		}
	}
}

void ImageProcessorZipper::run_debug(MatInfo& frame)
{
	auto& imgPro = *_imgProcess;
	imgPro(frame.image);
	// 更新屏蔽线
	updateShieldWires();
	auto maskImg = imgPro.getMaskImg(frame.image);
	auto defectResult = imgPro.getDefectResultInfo();

	drawBoundariesLines(maskImg);

	emit imageReady(QPixmap::fromImage(maskImg));
}

void ImageProcessorZipper::run_stop(MatInfo& frame)
{
	//auto& imgPro = *_imgProcess;
	//imgPro(frame.image);
	//// 更新屏蔽线
	//updateShieldWires();
	//auto maskImg = imgPro.getMaskImg(frame.image);
	//auto defectResult = imgPro.getDefectResultInfo();

	//drawBoundariesLines(maskImg);

	emit imageReady(QPixmap::fromImage(rw::rqw::cvMatToQImage(frame.image)));
}

void ImageProcessorZipper::run_OpenRemoveFunc(MatInfo& frame)
{
	leftLocationX = 0;
	auto& imgPro = *_imgProcess;
	imgPro(frame.image);
	// 更新屏蔽线
	updateShieldWires();
	auto maskImg = imgPro.getMaskImg(frame.image);
	auto defectResult = imgPro.getDefectResultInfo();


	if (leftLocationX > 0)
	{
		auto& globalStruct = GlobalData::getInstance();
		//globalStruct.zmotion.stopAllAxis();
		//std::cout << "leftLocationX" << leftLocationX << std::endl;

		leftLocationX = frame.location - leftLocationX * pixToWorld + tifeijuli;
		//std::cout << " frame.location" << frame.location << std::endl;
		//std::cout << "leftLocationX1" << leftLocationX << std::endl;


	}
	

	run_OpenRemoveFunc_emitErrorInfo(defectResult.isBad);

	drawBoundariesLines(maskImg);

	emit imageNGReady(QPixmap::fromImage(maskImg), frame.index, defectResult.isBad);

	rw::rqw::ImageInfo imageInfo(maskImg);

	save_image(imageInfo, rw::rqw::cvMatToQImage(frame.image));
}

void ImageProcessorZipper::run_OpenRemoveFunc_emitErrorInfo(bool isbad) const
{
	auto& globalStruct = GlobalData::getInstance();

	if (isbad)
	{
		globalStruct.priorityQueue->push(leftLocationX);
	}
}

void ImageProcessorZipper::save_image(rw::rqw::ImageInfo& imageInfo, const QImage& image)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	auto& isTakePictures = Modules::getInstance().runtimeInfoModule.isTakePictures;

	if (!isTakePictures)
	{
		return;
	}

	if (imageProcessingModuleIndex == 1 && setConfig.takeWork1Pictures)
	{
		save_image_work(imageInfo, image);
	}
	else if (imageProcessingModuleIndex == 2 && setConfig.takeWork2Pictures)
	{
		save_image_work(imageInfo, image);
	}
}

void ImageProcessorZipper::save_image_work(rw::rqw::ImageInfo& imageInfo, const QImage& image)
{
	auto& globalData = GlobalData::getInstance();
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	if (_isbad) {
		if (setConfig.saveNGImg)
		{
			rw::rqw::ImageInfo NG(image);
			NG.classify = "NG";
			globalData.imageSaveEngine->pushImage(NG);
		}
		if (setConfig.saveMaskImg)
		{
			imageInfo.classify = "Mask";
			globalData.imageSaveEngine->pushImage(imageInfo);
		}
	}
	else {
		if (setConfig.saveOKImg)
		{
			rw::rqw::ImageInfo Ok(image);
			Ok.classify = "OK";
			globalData.imageSaveEngine->pushImage(Ok);
		}
	}
}

void ImageProcessorZipper::buildSegModelEngine(const QString& enginePath)
{
	rw::ModelEngineConfig modelEngineConfig;
	modelEngineConfig.conf_threshold = 0.1f;
	modelEngineConfig.nms_threshold = 0.1f;
	modelEngineConfig.imagePretreatmentPolicy = rw::ImagePretreatmentPolicy::LetterBox;
	modelEngineConfig.letterBoxColor = cv::Scalar(114, 114, 114);
	modelEngineConfig.modelPath = enginePath.toStdString();
	auto engine = rw::ModelEngineFactory::createModelEngine(modelEngineConfig, rw::ModelType::Yolov11_Seg, rw::ModelEngineDeployType::TensorRT);

	_imgProcess = std::make_unique<rw::imgPro::ImageProcess>(engine);

	iniIndexGetContext();
	iniEliminationInfoFunc();
	iniEliminationInfoGetContext();
	iniDefectResultInfoFunc();
	iniDefectResultGetContext();
	iniDefectDrawConfig();
	iniRunTextConfig();
}

void ImageProcessorZipper::iniIndexGetContext()
{
	auto& context = _imgProcess->context();

	context.indexGetContext.removeIndicesIfByInfo = [this](const rw::DetectionRectangleInfo& info,const rw::imgPro::ImageProcessContext& imageProcessContext) {
		bool isInShieldWires = false;
		if (-1 == leftShieldWire || -1 == rightShieldWire || -1 == topShieldWire || -1 == bottomShieldWire)
		{
			return false;
		}
		if (info.center_x < rightShieldWire && info.center_x > leftShieldWire)
		{
			if (info.center_y > topShieldWire && info.center_y < bottomShieldWire)
			{
				isInShieldWires = true;
			}
		}
		return !isInShieldWires;
		};
}

void ImageProcessorZipper::iniEliminationInfoFunc()
{
	updateParamMapsFromGlobalStruct();
}

void ImageProcessorZipper::iniEliminationInfoGetContext()
{
	auto& context = _imgProcess->context();

	context.eliminationInfoGetContext.getEliminationItemFuncSpecialOperator = [this](rw::imgPro::EliminationItem& item,
		const rw::DetectionRectangleInfo& info,
		const rw::imgPro::EliminationInfoGetConfig& cfg) {
			item.customFields["LocationX"] = static_cast<int>(info.center_x);
		};
}

void ImageProcessorZipper::iniDefectResultInfoFunc()
{
	auto& context = _imgProcess->context();

	rw::imgPro::DefectResultInfoFunc::Config defectConfig;
	rw::imgPro::DefectResultInfoFunc::ClassIdWithConfigMap defectConfigs;
	defectConfig.isEnable = queyaMap["enable"];
	defectConfigs[ClassId::Queya] = defectConfig;
	defectConfig.isEnable = tangshangMap["enable"];
	defectConfigs[ClassId::Tangshang] = defectConfig;
	defectConfig.isEnable = zangwuMap["enable"];
	defectConfigs[ClassId::Zangwu] = defectConfig;
	defectConfig.isEnable = suoxiaoMap["enable"];
	defectConfigs[ClassId::Suoxiao] = defectConfig;
	defectConfig.isEnable = huawenMap["enable"];
	defectConfigs[ClassId::Huawen] = defectConfig;
	defectConfig.isEnable = yuanMap["enable"];
	defectConfigs[ClassId::Yuan] = defectConfig;
	defectConfig.isEnable = huapoMap["enable"];
	defectConfigs[ClassId::Huapo] = defectConfig;
	defectConfig.isEnable = duanxianMap["enable"];
	defectConfigs[ClassId::Duanxian] = defectConfig;
	defectConfig.isEnable = extra5Map["enable"];
	defectConfigs[ClassId::Extra5] = defectConfig;
	defectConfig.isEnable = extra6Map["enable"];
	defectConfigs[ClassId::Extra6] = defectConfig;
	defectConfig.isEnable = extra7Map["enable"];
	defectConfigs[ClassId::Extra7] = defectConfig;
	defectConfig.isEnable = extra8Map["enable"];
	defectConfigs[ClassId::Extra8] = defectConfig;
	context.defectCfg = defectConfigs;
}

void ImageProcessorZipper::iniDefectResultGetContext()
{
	auto& context = _imgProcess->context();
	context.defectResultGetContext.getDefectResultExtraOperate = 
		[this](const rw::imgPro::EliminationItem& item,
			const rw::DetectionRectangleInfo& info) {
		auto find = item.customFields.find("LocationX");
		if (find != item.customFields.end())
		{
			leftLocationX = (std::max)(leftLocationX, std::any_cast<int>(find->second));
		}
		};
}

void ImageProcessorZipper::iniDefectDrawConfig()
{
	auto& context = _imgProcess->context();

	rw::imgPro::DefectDrawFunc::ConfigDefectDraw drawConfig;
	updateDrawRec();
	drawConfig.setAllIdsWithSameColor({ 0,1,2 }, rw::rqw::RQWColor::Green, true);
	drawConfig.setAllIdsWithSameColor({ 0,1,2 }, rw::rqw::RQWColor::Red, false);
	drawConfig.classIdNameMap[ClassId::Queya] = "缺牙";
	drawConfig.classIdNameMap[ClassId::Tangshang] = "烫伤";
	drawConfig.classIdNameMap[ClassId::Zangwu] = "脏污";
	drawConfig.classIdNameMap[ClassId::Suoxiao] = "缩小";
	drawConfig.classIdNameMap[ClassId::Huawen] = "花纹";
	drawConfig.classIdNameMap[ClassId::Yuan] = "圆";
	drawConfig.classIdNameMap[ClassId::Huapo] = "划破";
	context.defectDrawCfg = drawConfig;
}

void ImageProcessorZipper::iniRunTextConfig()
{
	updateDrawText();
}

void ImageProcessorZipper::updateParamMapsFromGlobalStruct()
{
	auto& context = _imgProcess->context();
	auto& scoreConfig = Modules::getInstance().configManagerModule.scoreConfig;
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;

	queyaMap["classId"] = ClassId::Queya;
	queyaMap["maxArea"] = scoreConfig.queYaArea;
	queyaMap["maxScore"] = scoreConfig.queYaScore;
	queyaMap["enable"] = scoreConfig.queYa;
	if (1 == imageProcessingModuleIndex)
	{
		queyaMap["pixToWorld"] = setConfig.xiangSuDangLiang1;
	}
	else
	{
		queyaMap["pixToWorld"] = setConfig.xiangSuDangLiang2;
	}

	tangshangMap["classId"] = ClassId::Tangshang;
	tangshangMap["maxArea"] = scoreConfig.tangShangArea;
	tangshangMap["maxScore"] = scoreConfig.tangShangScore;
	tangshangMap["enable"] = scoreConfig.tangShang;
	if (1 == imageProcessingModuleIndex)
	{
		tangshangMap["pixToWorld"] = setConfig.xiangSuDangLiang1;
	}
	else
	{
		tangshangMap["pixToWorld"] = setConfig.xiangSuDangLiang2;
	}

	zangwuMap["classId"] = ClassId::Zangwu;
	zangwuMap["maxArea"] = scoreConfig.zangWuArea;
	zangwuMap["maxScore"] = scoreConfig.zangWuScore;
	zangwuMap["enable"] = scoreConfig.zangWu;
	if (1 == imageProcessingModuleIndex)
	{
		zangwuMap["pixToWorld"] = setConfig.xiangSuDangLiang1;
	}
	else
	{
		zangwuMap["pixToWorld"] = setConfig.xiangSuDangLiang2;
	}

	suoxiaoMap["classId"] = ClassId::Suoxiao;
	suoxiaoMap["maxArea"] = scoreConfig.suoXiaoArea;
	suoxiaoMap["maxScore"] = scoreConfig.suoXiaoScore;
	suoxiaoMap["enable"] = scoreConfig.suoXiao;
	if (1 == imageProcessingModuleIndex)
	{
		suoxiaoMap["pixToWorld"] = setConfig.xiangSuDangLiang1;
	}
	else
	{
		suoxiaoMap["pixToWorld"] = setConfig.xiangSuDangLiang2;
	}

	huawenMap["classId"] = ClassId::Huawen;
	huawenMap["maxArea"] = scoreConfig.huaWenArea;
	huawenMap["maxScore"] = scoreConfig.huaWenScore;
	huawenMap["enable"] = scoreConfig.huaWen;
	if (1 == imageProcessingModuleIndex)
	{
		huawenMap["pixToWorld"] = setConfig.xiangSuDangLiang1;
	}
	else
	{
		huawenMap["pixToWorld"] = setConfig.xiangSuDangLiang2;
	}

	yuanMap["classId"] = ClassId::Yuan;
	yuanMap["maxArea"] = scoreConfig.yuanArea;
	yuanMap["maxScore"] = scoreConfig.yuanScore;
	yuanMap["enable"] = scoreConfig.yuan;
	if (1 == imageProcessingModuleIndex)
	{
		yuanMap["pixToWorld"] = setConfig.xiangSuDangLiang1;
	}
	else
	{
		yuanMap["pixToWorld"] = setConfig.xiangSuDangLiang2;
	}

	huapoMap["classId"] = ClassId::Huapo;
	huapoMap["maxArea"] = scoreConfig.huaPoArea;
	huapoMap["maxScore"] = scoreConfig.huaPoScore;
	huapoMap["enable"] = scoreConfig.huaPo;
	if (1 == imageProcessingModuleIndex)
	{
		huapoMap["pixToWorld"] = setConfig.xiangSuDangLiang1;
	}
	else
	{
		huapoMap["pixToWorld"] = setConfig.xiangSuDangLiang2;
	}

	duanxianMap["classId"] = ClassId::Duanxian;
	duanxianMap["maxArea"] = scoreConfig.duanXianArea;
	duanxianMap["maxScore"] = scoreConfig.duanXianScore;
	duanxianMap["enable"] = scoreConfig.duanXian;
	if (1 == imageProcessingModuleIndex)
	{
		duanxianMap["pixToWorld"] = setConfig.xiangSuDangLiang1;
	}
	else
	{
		duanxianMap["pixToWorld"] = setConfig.xiangSuDangLiang2;
	}

	extra5Map["classId"] = ClassId::Extra5;
	extra5Map["maxArea"] = scoreConfig.extra5Area;
	extra5Map["maxScore"] = scoreConfig.extra5Score;
	extra5Map["enable"] = scoreConfig.extra5;
	if (1 == imageProcessingModuleIndex)
	{
		extra5Map["pixToWorld"] = setConfig.xiangSuDangLiang1;
	}
	else
	{
		extra5Map["pixToWorld"] = setConfig.xiangSuDangLiang2;
	}

	extra6Map["classId"] = ClassId::Extra6;
	extra6Map["maxArea"] = scoreConfig.extra6Area;
	extra6Map["maxScore"] = scoreConfig.extra6Score;
	extra6Map["enable"] = scoreConfig.extra6;
	if (1 == imageProcessingModuleIndex)
	{
		extra6Map["pixToWorld"] = setConfig.xiangSuDangLiang1;
	}
	else
	{
		extra6Map["pixToWorld"] = setConfig.xiangSuDangLiang2;
	}

	extra7Map["classId"] = ClassId::Extra7;
	extra7Map["maxArea"] = scoreConfig.extra7Area;
	extra7Map["maxScore"] = scoreConfig.extra7Score;
	extra7Map["enable"] = scoreConfig.extra7;
	if (1 == imageProcessingModuleIndex)
	{
		extra7Map["pixToWorld"] = setConfig.xiangSuDangLiang1;
	}
	else
	{
		extra7Map["pixToWorld"] = setConfig.xiangSuDangLiang2;
	}

	extra8Map["classId"] = ClassId::Extra8;
	extra8Map["maxArea"] = scoreConfig.extra8Area;
	extra8Map["maxScore"] = scoreConfig.extra8Score;
	extra8Map["enable"] = scoreConfig.extra8;
	if (1 == imageProcessingModuleIndex)
	{
		extra8Map["pixToWorld"] = setConfig.xiangSuDangLiang1;
	}
	else
	{
		extra8Map["pixToWorld"] = setConfig.xiangSuDangLiang2;
	}

	rw::imgPro::EliminationInfoFunc::ClassIdWithConfigMap eliminationInfoGetConfigs;
	rw::imgPro::EliminationInfoGetConfig queyaEliminationInfoGetConfig;
	rw::imgPro::EliminationInfoGetConfig tangshangEliminationInfoGetConfig;
	rw::imgPro::EliminationInfoGetConfig zangwuEliminationInfoGetConfig;
	rw::imgPro::EliminationInfoGetConfig suoxiaoEliminationInfoGetConfig;
	rw::imgPro::EliminationInfoGetConfig huawenEliminationInfoGetConfig;
	rw::imgPro::EliminationInfoGetConfig yuanEliminationInfoGetConfig;
	rw::imgPro::EliminationInfoGetConfig huapoEliminationInfoGetConfig;
	rw::imgPro::EliminationInfoGetConfig duanxianEliminationInfoGetConfig;
	rw::imgPro::EliminationInfoGetConfig extra5EliminationInfoGetConfig;
	rw::imgPro::EliminationInfoGetConfig extra6EliminationInfoGetConfig;
	rw::imgPro::EliminationInfoGetConfig extra7EliminationInfoGetConfig;
	rw::imgPro::EliminationInfoGetConfig extra8EliminationInfoGetConfig;

	queyaEliminationInfoGetConfig.areaFactor = queyaMap["pixToWorld"];
	queyaEliminationInfoGetConfig.scoreFactor = 100;
	queyaEliminationInfoGetConfig.isUsingArea = true;
	queyaEliminationInfoGetConfig.isUsingScore = true;
	queyaEliminationInfoGetConfig.scoreRange = { 0, queyaMap["maxScore"] };
	queyaEliminationInfoGetConfig.areaRange = { 0, queyaMap["maxArea"] };
	queyaEliminationInfoGetConfig.scoreIsUsingComplementarySet = false;
	eliminationInfoGetConfigs[ClassId::Queya] = queyaEliminationInfoGetConfig;

	tangshangEliminationInfoGetConfig.areaFactor = tangshangMap["pixToWorld"];
	tangshangEliminationInfoGetConfig.scoreFactor = 100;
	tangshangEliminationInfoGetConfig.isUsingArea = true;
	tangshangEliminationInfoGetConfig.isUsingScore = true;
	tangshangEliminationInfoGetConfig.scoreRange = { 0, tangshangMap["maxScore"] };
	tangshangEliminationInfoGetConfig.areaRange = { 0, tangshangMap["maxArea"] };
	tangshangEliminationInfoGetConfig.scoreIsUsingComplementarySet = false;
	eliminationInfoGetConfigs[ClassId::Tangshang] = tangshangEliminationInfoGetConfig;

	zangwuEliminationInfoGetConfig.areaFactor = zangwuMap["pixToWorld"];
	zangwuEliminationInfoGetConfig.scoreFactor = 100;
	zangwuEliminationInfoGetConfig.isUsingArea = true;
	zangwuEliminationInfoGetConfig.isUsingScore = true;
	zangwuEliminationInfoGetConfig.scoreRange = { 0, zangwuMap["maxScore"] };
	zangwuEliminationInfoGetConfig.areaRange = { 0, zangwuMap["maxArea"] };
	zangwuEliminationInfoGetConfig.scoreIsUsingComplementarySet = false;
	eliminationInfoGetConfigs[ClassId::Zangwu] = zangwuEliminationInfoGetConfig;

	suoxiaoEliminationInfoGetConfig.areaFactor = suoxiaoMap["pixToWorld"];
	suoxiaoEliminationInfoGetConfig.scoreFactor = 100;
	suoxiaoEliminationInfoGetConfig.isUsingArea = true;
	suoxiaoEliminationInfoGetConfig.isUsingScore = true;
	suoxiaoEliminationInfoGetConfig.scoreRange = { 0, suoxiaoMap["maxScore"] };
	suoxiaoEliminationInfoGetConfig.areaRange = { 0, suoxiaoMap["maxArea"] };
	suoxiaoEliminationInfoGetConfig.scoreIsUsingComplementarySet = false;
	eliminationInfoGetConfigs[ClassId::Suoxiao] = suoxiaoEliminationInfoGetConfig;

	huawenEliminationInfoGetConfig.areaFactor = huawenMap["pixToWorld"];
	huawenEliminationInfoGetConfig.scoreFactor = 100;
	huawenEliminationInfoGetConfig.isUsingArea = true;
	huawenEliminationInfoGetConfig.isUsingScore = true;
	huawenEliminationInfoGetConfig.scoreRange = { 0, huawenMap["maxScore"] };
	huawenEliminationInfoGetConfig.areaRange = { 0, huawenMap["maxArea"] };
	huawenEliminationInfoGetConfig.scoreIsUsingComplementarySet = false;
	eliminationInfoGetConfigs[ClassId::Huawen] = huawenEliminationInfoGetConfig;

	yuanEliminationInfoGetConfig.areaFactor = yuanMap["pixToWorld"];
	yuanEliminationInfoGetConfig.scoreFactor = 100;
	yuanEliminationInfoGetConfig.isUsingArea = true;
	yuanEliminationInfoGetConfig.isUsingScore = true;
	yuanEliminationInfoGetConfig.scoreRange = { 0, yuanMap["maxScore"] };
	yuanEliminationInfoGetConfig.areaRange = { 0, yuanMap["maxArea"] };
	yuanEliminationInfoGetConfig.scoreIsUsingComplementarySet = false;
	eliminationInfoGetConfigs[ClassId::Yuan] = yuanEliminationInfoGetConfig;

	huapoEliminationInfoGetConfig.areaFactor = huapoMap["pixToWorld"];
	huapoEliminationInfoGetConfig.scoreFactor = 100;
	huapoEliminationInfoGetConfig.isUsingArea = true;
	huapoEliminationInfoGetConfig.isUsingScore = true;
	huapoEliminationInfoGetConfig.scoreRange = { 0, huapoMap["maxScore"] };
	huapoEliminationInfoGetConfig.areaRange = { 0, huapoMap["maxArea"] };
	huapoEliminationInfoGetConfig.scoreIsUsingComplementarySet = false;
	eliminationInfoGetConfigs[ClassId::Huapo] = huapoEliminationInfoGetConfig;

	duanxianEliminationInfoGetConfig.areaFactor = duanxianMap["pixToWorld"];
	duanxianEliminationInfoGetConfig.scoreFactor = 100;
	duanxianEliminationInfoGetConfig.isUsingArea = true;
	duanxianEliminationInfoGetConfig.isUsingScore = true;
	duanxianEliminationInfoGetConfig.scoreRange = { 0, duanxianMap["maxScore"] };
	duanxianEliminationInfoGetConfig.areaRange = { 0, duanxianMap["maxArea"] };
	duanxianEliminationInfoGetConfig.scoreIsUsingComplementarySet = false;
	eliminationInfoGetConfigs[ClassId::Duanxian] = duanxianEliminationInfoGetConfig;

	extra5EliminationInfoGetConfig.areaFactor = extra5Map["pixToWorld"];
	extra5EliminationInfoGetConfig.scoreFactor = 100;
	extra5EliminationInfoGetConfig.isUsingArea = true;
	extra5EliminationInfoGetConfig.isUsingScore = true;
	extra5EliminationInfoGetConfig.scoreRange = { 0, extra5Map["maxScore"] };
	extra5EliminationInfoGetConfig.areaRange = { 0, extra5Map["maxArea"] };
	extra5EliminationInfoGetConfig.scoreIsUsingComplementarySet = false;
	eliminationInfoGetConfigs[ClassId::Extra5] = extra5EliminationInfoGetConfig;

	extra6EliminationInfoGetConfig.areaFactor = extra6Map["pixToWorld"];
	extra6EliminationInfoGetConfig.scoreFactor = 100;
	extra6EliminationInfoGetConfig.isUsingArea = true;
	extra6EliminationInfoGetConfig.isUsingScore = true;
	extra6EliminationInfoGetConfig.scoreRange = { 0, extra6Map["maxScore"] };
	extra6EliminationInfoGetConfig.areaRange = { 0, extra6Map["maxArea"] };
	extra6EliminationInfoGetConfig.scoreIsUsingComplementarySet = false;
	eliminationInfoGetConfigs[ClassId::Extra6] = extra6EliminationInfoGetConfig;

	extra7EliminationInfoGetConfig.areaFactor = extra7Map["pixToWorld"];
	extra7EliminationInfoGetConfig.scoreFactor = 100;
	extra7EliminationInfoGetConfig.isUsingArea = true;
	extra7EliminationInfoGetConfig.isUsingScore = true;
	extra7EliminationInfoGetConfig.scoreRange = { 0, extra7Map["maxScore"] };
	extra7EliminationInfoGetConfig.areaRange = { 0, extra7Map["maxArea"] };
	extra7EliminationInfoGetConfig.scoreIsUsingComplementarySet = false;
	eliminationInfoGetConfigs[ClassId::Extra7] = extra7EliminationInfoGetConfig;

	extra8EliminationInfoGetConfig.areaFactor = extra8Map["pixToWorld"];
	extra8EliminationInfoGetConfig.scoreFactor = 100;
	extra8EliminationInfoGetConfig.isUsingArea = true;
	extra8EliminationInfoGetConfig.isUsingScore = true;
	extra8EliminationInfoGetConfig.scoreRange = { 0, extra8Map["maxScore"] };
	extra8EliminationInfoGetConfig.areaRange = { 0, extra8Map["maxArea"] };
	extra8EliminationInfoGetConfig.scoreIsUsingComplementarySet = false;
	eliminationInfoGetConfigs[ClassId::Extra8] = extra8EliminationInfoGetConfig;

	context.eliminationCfg = eliminationInfoGetConfigs;

	iniDefectResultInfoFunc();
}

void ImageProcessorZipper::drawBoundariesLines(QImage& image)
{
	auto& index = imageProcessingModuleIndex;
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	rw::imgPro::ConfigDrawLine configDrawLine;
	configDrawLine.color = rw::imgPro::Color::Orange;
	configDrawLine.thickness = 3;
	if (index == 1)
	{
		configDrawLine.position = setConfig.shangXianWei1;
		rw::imgPro::ImagePainter::drawHorizontalLine(image, configDrawLine);
		configDrawLine.position = setConfig.xiaXianWei1;
		rw::imgPro::ImagePainter::drawHorizontalLine(image, configDrawLine);
		configDrawLine.position = setConfig.zuoXianWei1;
		rw::imgPro::ImagePainter::drawVerticalLine(image, configDrawLine);
		configDrawLine.position = setConfig.youXianWei1;
		rw::imgPro::ImagePainter::drawVerticalLine(image, configDrawLine);
	}
	else if (index == 2)
	{
		configDrawLine.position = setConfig.shangXianWei2;
		rw::imgPro::ImagePainter::drawHorizontalLine(image, configDrawLine);
		configDrawLine.position = setConfig.xiaXianWei2;
		rw::imgPro::ImagePainter::drawHorizontalLine(image, configDrawLine);
		configDrawLine.position = setConfig.zuoXianWei2;
		rw::imgPro::ImagePainter::drawVerticalLine(image, configDrawLine);
		configDrawLine.position = setConfig.youXianWei2;
		rw::imgPro::ImagePainter::drawVerticalLine(image, configDrawLine);
	}
}

void ImageProcessorZipper::updateShieldWires()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;

	if (1 == imageProcessingModuleIndex)
	{
		leftShieldWire = setConfig.zuoXianWei1;
		rightShieldWire = setConfig.youXianWei1;
		topShieldWire = setConfig.shangXianWei1;
		bottomShieldWire = setConfig.xiaXianWei1;
		pixToWorld = setConfig.xiangSuDangLiang1;
		tifeijuli = setConfig.tifeijuli1;
	}
	else if (2 == imageProcessingModuleIndex)
	{
		leftShieldWire = setConfig.zuoXianWei2;
		rightShieldWire = setConfig.youXianWei2;
		topShieldWire = setConfig.shangXianWei2;
		bottomShieldWire = setConfig.xiaXianWei2;
		pixToWorld = setConfig.xiangSuDangLiang2;
		tifeijuli = setConfig.tifeijuli2;
	}
}

void ImageProcessorZipper::updateDrawRec()
{
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	auto& context = _imgProcess->context();
	if (generalConfig.isshibiekuang)
	{
		context.defectDrawCfg.isDrawDefects = true;
		context.defectDrawCfg.isDrawDisableDefects = true;
	}
	else
	{
		context.defectDrawCfg.isDrawDefects = false;
		context.defectDrawCfg.isDrawDisableDefects = false;
	}
}

void ImageProcessorZipper::updateDrawText()
{
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	auto& context = _imgProcess->context();
	context.runTextCfg.isDisOperatorTime = false;
	context.runTextCfg.processImgTimeTextColor = rw::rqw::RQWColor::Green;
	if (generalConfig.iswenzi)
	{
		context.runTextCfg.isDrawExtraText = true;
	}
	else
	{
		context.runTextCfg.isDrawExtraText = false;
	}
}

void ImageProcessingModule::onFrameCaptured(rw::rqw::MatInfo matInfo, size_t index)
{
	auto& globalStruct = GlobalData::getInstance();

	QMutexLocker locker(&_mutex);
	MatInfo mat;

	if (index == 1)
	{
		switch (globalStruct.imgRotateCount1) {
		case 1:
			cv::rotate(matInfo.mat, matInfo.mat, cv::ROTATE_90_CLOCKWISE);
			break;
		case 2:
			cv::rotate(matInfo.mat, matInfo.mat, cv::ROTATE_180);
			break;
		case 3:
			cv::rotate(matInfo.mat, matInfo.mat, cv::ROTATE_90_COUNTERCLOCKWISE);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (globalStruct.imgRotateCount2) {
		case 1:
			cv::rotate(matInfo.mat, matInfo.mat, cv::ROTATE_90_CLOCKWISE);
			break;
		case 2:
			cv::rotate(matInfo.mat, matInfo.mat, cv::ROTATE_180);
			break;
		case 3:
			cv::rotate(matInfo.mat, matInfo.mat, cv::ROTATE_90_COUNTERCLOCKWISE);
			break;
		default:
			break;
		}
	}

	
	mat.image = matInfo.mat;
	mat.index = index;
	if (index==1)
	{
		mat.location = globalStruct.zmotion.getModbus(2, 1);	// 获取拍照的位置

	}
	else
	{
		mat.location = globalStruct.zmotion.getModbus(6, 1);	// 获取拍照的位置

	}
	_queue.enqueue(mat);
	_condition.wakeOne();
}

void ImageProcessingModule::BuildModule()
{
	for (int i = 0; i < _numConsumers; ++i) {
		static size_t workIndexCount = 0;
		ImageProcessorZipper* processor = new ImageProcessorZipper(_queue, _mutex, _condition, workIndexCount, this);
		workIndexCount++;
		processor->imageProcessingModuleIndex = index;
		processor->buildSegModelEngine(modelEnginePath);
		connect(processor, &ImageProcessorZipper::imageReady, this, &ImageProcessingModule::imageReady, Qt::QueuedConnection);
		connect(processor, &ImageProcessorZipper::imageNGReady, this, &ImageProcessingModule::imageNGReady, Qt::QueuedConnection);
		connect(this, &ImageProcessingModule::shibiekaungChanged, processor, &ImageProcessorZipper::updateDrawRec, Qt::QueuedConnection);
		connect(this, &ImageProcessingModule::wenziChanged, processor, &ImageProcessorZipper::updateDrawText, Qt::QueuedConnection);
		connect(this, &ImageProcessingModule::paramMapsChanged, processor, &ImageProcessorZipper::updateParamMapsFromGlobalStruct, Qt::QueuedConnection);
		_processors.push_back(processor);
		processor->start();
	}
}

ImageProcessingModule::ImageProcessingModule(int numConsumers, QObject* parent)
	: QObject(parent), _numConsumers(numConsumers) {

}

ImageProcessingModule::~ImageProcessingModule()
{
	// 通知所有线程退出
	for (auto processor : _processors) {
		processor->requestInterruption();
	}

	// 唤醒所有等待的线程
	{
		QMutexLocker locker(&_mutex);
		_condition.wakeAll();
	}

	// 等待所有线程退出
	for (auto processor : _processors) {
		if (processor->isRunning()) {
			processor->wait(1000); // 使用超时机制，等待1秒
		}
		delete processor;
	}
}
