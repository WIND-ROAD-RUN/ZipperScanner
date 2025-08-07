#include "ImageProcessorModule.h"

#include <qcolor.h>
#include <QPainter>

#include "GlobalStruct.hpp"
#include"imgPro_ImagePainter.hpp"
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

		auto& globalData = GlobalStructDataZipper::getInstance();

		// 获取当前时间点
		auto now = std::chrono::system_clock::now();
		// 转换为time_t格式
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);
		// 转换为本地时间
		std::tm* local_time = std::localtime(&now_time);

		auto currentRunningState = globalData.runningState.load();
		switch (currentRunningState)
		{
		case RunningState::Debug:
			run_debug(frame);
			break;
		case RunningState::OpenRemoveFunc:
			run_OpenRemoveFunc(frame);
			break;
			/*case RunningState::Monitor:
				run_monitor(frame);
				break;*/
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

void ImageProcessorZipper::run_monitor(MatInfo& frame)
{

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

	if (1 == imageProcessingModuleIndex)
	{
		leftLocationX = leftLocationX * pixToWorld + tifeijuli;
	}

	run_OpenRemoveFunc_emitErrorInfo(defectResult.isBad);

	drawBoundariesLines(maskImg);

	emit imageNGReady(QPixmap::fromImage(maskImg), frame.index, defectResult.isBad);

	rw::rqw::ImageInfo imageInfo(maskImg);

	save_image(imageInfo, rw::rqw::cvMatToQImage(frame.image));
}

void ImageProcessorZipper::run_OpenRemoveFunc_emitErrorInfo(bool isbad) const
{
	auto& globalStruct = GlobalStructDataZipper::getInstance();

	if (isbad)
	{
		++globalStruct.statisticalInfo.wasteCount;
	}

	if (imageProcessingModuleIndex == 1 || imageProcessingModuleIndex == 2)
	{
		++globalStruct.statisticalInfo.produceCount;
	}

	if (imageProcessingModuleIndex == 1)
	{
		++globalStruct.statisticalInfo.produceCount1;
	}
	else if (imageProcessingModuleIndex == 2)
	{
		++globalStruct.statisticalInfo.produceCount2;
	}

	if (isbad)
	{
		globalStruct.priorityQueue->push(leftLocationX);
	}
}

void ImageProcessorZipper::save_image(rw::rqw::ImageInfo& imageInfo, const QImage& image)
{
	auto& globalStruct = GlobalStructDataZipper::getInstance();
	auto& setConfig = globalStruct.setConfig;

	if (!globalStruct.isTakePictures)
	{
		return;
	}

	if (imageProcessingModuleIndex == 1 && setConfig.takeWork1Pictures)
	{
		if (globalStruct.isTakePictures) {
			save_image_work(imageInfo, image);
		}
	}
	else if (imageProcessingModuleIndex == 2 && setConfig.takeWork2Pictures)
	{
		if (globalStruct.isTakePictures) {
			save_image_work(imageInfo, image);
		}
	}
}

void ImageProcessorZipper::save_image_work(rw::rqw::ImageInfo& imageInfo, const QImage& image)
{
	auto& globalData = GlobalStructDataZipper::getInstance();
	auto& setConfig = globalData.setConfig;
	if (_isbad) {
		if (setConfig.saveNGImg)
		{
			imageInfo.classify = "NG";
			globalData.imageSaveEngine->pushImage(imageInfo);
		}
		if (setConfig.saveMaskImg)
		{
			rw::rqw::ImageInfo mask(image);
			mask.classify = "Mask";
			globalData.imageSaveEngine->pushImage(mask);
		}
	}
	else {
		if (setConfig.saveOKImg)
		{
			imageInfo.classify = "OK";
			globalData.imageSaveEngine->pushImage(imageInfo);
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
	auto engine = rw::ModelEngineFactory::createModelEngine(modelEngineConfig, rw::ModelType::Yolov11_Seg_CudaAcc, rw::ModelEngineDeployType::TensorRT);

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

	context.indexGetContext.removeIndicesIfByInfo = [this](const rw::DetectionRectangleInfo& info) {
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
	context.defectCfg = defectConfigs;
}

void ImageProcessorZipper::iniDefectResultGetContext()
{
	auto& context = _imgProcess->context();
	context.defectResultGetContext.getDefectResultExtraOperate = [this](const rw::imgPro::EliminationItem& item) {
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
	drawConfig.classIdNameMap[0] = "缺牙";
	drawConfig.classIdNameMap[1] = "烫伤";
	drawConfig.classIdNameMap[2] = "脏污";
	context.defectDrawCfg = drawConfig;
}

void ImageProcessorZipper::iniRunTextConfig()
{
	updateDrawText();
}

void ImageProcessorZipper::updateParamMapsFromGlobalStruct()
{
	auto& context = _imgProcess->context();
	auto& globalStruct = GlobalStructDataZipper::getInstance();

	queyaMap["classId"] = 0;
	queyaMap["maxArea"] = globalStruct.scoreConfig.queYaArea;
	queyaMap["maxScore"] = globalStruct.scoreConfig.queYaScore;
	queyaMap["enable"] = globalStruct.scoreConfig.queYa;
	if (1 == imageProcessingModuleIndex)
	{
		queyaMap["pixToWorld"] = globalStruct.setConfig.xiangSuDangLiang1;
	}
	else
	{
		queyaMap["pixToWorld"] = globalStruct.setConfig.xiangSuDangLiang2;
	}

	tangshangMap["classId"] = 1;
	tangshangMap["maxArea"] = globalStruct.scoreConfig.tangShangArea;
	tangshangMap["maxScore"] = globalStruct.scoreConfig.tangShangScore;
	tangshangMap["enable"] = globalStruct.scoreConfig.tangShang;
	if (1 == imageProcessingModuleIndex)
	{
		tangshangMap["pixToWorld"] = globalStruct.setConfig.xiangSuDangLiang1;
	}
	else
	{
		tangshangMap["pixToWorld"] = globalStruct.setConfig.xiangSuDangLiang2;
	}

	zangwuMap["classId"] = 2;
	zangwuMap["maxArea"] = globalStruct.scoreConfig.zangWuArea;
	zangwuMap["maxScore"] = globalStruct.scoreConfig.zangWuScore;
	zangwuMap["enable"] = globalStruct.scoreConfig.zangWu;
	if (1 == imageProcessingModuleIndex)
	{
		zangwuMap["pixToWorld"] = globalStruct.setConfig.xiangSuDangLiang1;
	}
	else
	{
		zangwuMap["pixToWorld"] = globalStruct.setConfig.xiangSuDangLiang2;
	}

	rw::imgPro::EliminationInfoFunc::ClassIdWithConfigMap eliminationInfoGetConfigs;
	rw::imgPro::EliminationInfoGetConfig queyaEliminationInfoGetConfig;
	rw::imgPro::EliminationInfoGetConfig tangshangEliminationInfoGetConfig;
	rw::imgPro::EliminationInfoGetConfig zangwuEliminationInfoGetConfig;

	queyaEliminationInfoGetConfig.areaFactor = queyaMap["pixToWorld"];//这里设置为像素当量
	queyaEliminationInfoGetConfig.scoreFactor = 100;//这里设置为百分比当量
	queyaEliminationInfoGetConfig.isUsingArea = true;//这里设置为使用面积
	queyaEliminationInfoGetConfig.isUsingScore = true;//这里设置为使用分数
	queyaEliminationInfoGetConfig.scoreRange = { 0,queyaMap["maxScore"] };
	queyaEliminationInfoGetConfig.areaRange = { 0,queyaMap["maxArea"] };
	queyaEliminationInfoGetConfig.scoreIsUsingComplementarySet = false;//这里设置为不使用补集
	eliminationInfoGetConfigs[ClassId::Queya] = queyaEliminationInfoGetConfig;

	tangshangEliminationInfoGetConfig.areaFactor = tangshangMap["pixToWorld"];//这里设置为像素当量
	tangshangEliminationInfoGetConfig.scoreFactor = 100;//这里设置为百分比当量
	tangshangEliminationInfoGetConfig.isUsingArea = true;//这里设置为使用面积
	tangshangEliminationInfoGetConfig.isUsingScore = true;//这里设置为使用分数
	tangshangEliminationInfoGetConfig.scoreRange = { 0,tangshangMap["maxScore"] };
	tangshangEliminationInfoGetConfig.areaRange = { 0,tangshangMap["maxArea"] };
	tangshangEliminationInfoGetConfig.scoreIsUsingComplementarySet = false;//这里设置为不使用补集
	eliminationInfoGetConfigs[ClassId::Tangshang] = tangshangEliminationInfoGetConfig;

	zangwuEliminationInfoGetConfig.areaFactor = zangwuMap["pixToWorld"];//这里设置为像素当量
	zangwuEliminationInfoGetConfig.scoreFactor = 100;//这里设置为百分比当量
	zangwuEliminationInfoGetConfig.isUsingArea = true;//这里设置为使用面积
	zangwuEliminationInfoGetConfig.isUsingScore = true;//这里设置为使用分数
	zangwuEliminationInfoGetConfig.scoreRange = { 0,zangwuMap["maxScore"] };
	zangwuEliminationInfoGetConfig.areaRange = { 0,zangwuMap["maxArea"] };
	zangwuEliminationInfoGetConfig.scoreIsUsingComplementarySet = false;//这里设置为不使用补集
	eliminationInfoGetConfigs[ClassId::Zangwu] = zangwuEliminationInfoGetConfig;

	context.eliminationCfg = eliminationInfoGetConfigs;

	iniDefectResultInfoFunc();
}

void ImageProcessorZipper::drawBoundariesLines(QImage& image)
{
	auto& index = imageProcessingModuleIndex;
	auto& setConfig = GlobalStructDataZipper::getInstance().setConfig;
	rw::imgPro::ConfigDrawLine configDrawLine;
	configDrawLine.color = rw::imgPro::Color::Red;
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
	auto& globalStructSetConfig = GlobalStructDataZipper::getInstance().setConfig;

	if (1 == imageProcessingModuleIndex)
	{
		leftShieldWire = globalStructSetConfig.zuoXianWei1;
		rightShieldWire = globalStructSetConfig.youXianWei1;
		topShieldWire = globalStructSetConfig.shangXianWei1;
		bottomShieldWire = globalStructSetConfig.xiaXianWei1;
		pixToWorld = globalStructSetConfig.xiangSuDangLiang1;
		tifeijuli = globalStructSetConfig.tifeijuli1;
	}
	else if (2 == imageProcessingModuleIndex)
	{
		leftShieldWire = globalStructSetConfig.zuoXianWei2;
		rightShieldWire = globalStructSetConfig.youXianWei2;
		topShieldWire = globalStructSetConfig.shangXianWei2;
		bottomShieldWire = globalStructSetConfig.xiaXianWei2;
		pixToWorld = globalStructSetConfig.xiangSuDangLiang2;
		tifeijuli = globalStructSetConfig.tifeijuli2;
	}
}

void ImageProcessorZipper::updateDrawRec()
{
	auto& globalStruct = GlobalStructDataZipper::getInstance();
	auto& context = _imgProcess->context();
	if (globalStruct.generalConfig.isshibiekuang)
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
	auto& globalStruct = GlobalStructDataZipper::getInstance();
	auto& context = _imgProcess->context();
	if (globalStruct.generalConfig.iswenzi)
	{
		context.runTextCfg.isDrawExtraText = true;
	}
	else
	{
		context.runTextCfg.isDrawExtraText = false;
	}
}

void ImageProcessingModuleZipper::onFrameCaptured(cv::Mat frame, size_t index)
{
	// 手动读取本地图片
	std::string imagePath = R"(C:\Users\zfkj4090\Desktop\TestImg\lalian\Image_20250411152145599.jpg)"; // 替换为你的图片路径
	cv::Mat frame1 = cv::imread(imagePath, cv::IMREAD_COLOR);
	frame = frame1.clone();
	if (frame.channels() == 4) {
		cv::cvtColor(frame, frame, cv::COLOR_BGRA2BGR);
	}
	if (frame.type() != CV_8UC3) {
		frame.convertTo(frame, CV_8UC3);
	}

	if (frame.empty()) {
		return; // 跳过空帧
	}

	auto& globalStruct = GlobalStructDataZipper::getInstance();

	QMutexLocker locker(&_mutex);
	MatInfo mat;
	mat.image = frame;
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

void ImageProcessingModuleZipper::BuildModule()
{
	for (int i = 0; i < _numConsumers; ++i) {
		static size_t workIndexCount = 0;
		ImageProcessorZipper* processor = new ImageProcessorZipper(_queue, _mutex, _condition, workIndexCount, this);
		workIndexCount++;
		processor->buildSegModelEngine(modelEnginePath);
		processor->imageProcessingModuleIndex = index;
		connect(processor, &ImageProcessorZipper::imageReady, this, &ImageProcessingModuleZipper::imageReady, Qt::QueuedConnection);
		connect(processor, &ImageProcessorZipper::imageNGReady, this, &ImageProcessingModuleZipper::imageNGReady, Qt::QueuedConnection);
		connect(this, &ImageProcessingModuleZipper::shibiekaungChanged, processor, &ImageProcessorZipper::updateDrawRec, Qt::QueuedConnection);
		connect(this, &ImageProcessingModuleZipper::wenziChanged, processor, &ImageProcessorZipper::updateDrawText, Qt::QueuedConnection);
		connect(this, &ImageProcessingModuleZipper::paramMapsChanged, processor, &ImageProcessorZipper::updateParamMapsFromGlobalStruct, Qt::QueuedConnection);
		_processors.push_back(processor);
		processor->start();
	}
}

ImageProcessingModuleZipper::ImageProcessingModuleZipper(int numConsumers, QObject* parent)
	: QObject(parent), _numConsumers(numConsumers) {

}

ImageProcessingModuleZipper::~ImageProcessingModuleZipper()
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
