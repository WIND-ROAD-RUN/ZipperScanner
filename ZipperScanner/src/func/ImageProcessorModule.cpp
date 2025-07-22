#include "ImageProcessorModule.h"

#include <qcolor.h>
#include <QPainter>

#include "GlobalStruct.hpp"
#include"rqw_ImagePainter.h"
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
	imgPro.getContext().indexGetContext.removeIndicesIfByInfo = [this](const rw::DetectionRectangleInfo& info) -> bool {
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
	auto& imgPro = *_imgProcess;
	imgPro(frame.image);
	// 更新屏蔽线
	updateShieldWires();
	imgPro.getContext().indexGetContext.removeIndicesIfByInfo = [this](const rw::DetectionRectangleInfo& info) -> bool {
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
	auto maskImg = imgPro.getMaskImg(frame.image);
	auto defectResult = imgPro.getDefectResultInfo();

	drawBoundariesLines(maskImg);

	emit imageNGReady(QPixmap::fromImage(maskImg), frame.index, defectResult.isBad);
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
	auto engine = rw::ModelEngineFactory::createModelEngine(modelEngineConfig, rw::ModelType::Yolov11_Seg, rw::ModelEngineDeployType::TensorRT);

	_imgProcess = std::make_unique<rw::imgPro::ImageProcess>(engine);
	auto& context = _imgProcess->getContext();

	rw::imgPro::EliminationInfoFunc::ClassIdWithConfigMap eliminationInfoGetConfigs;
	rw::imgPro::EliminationInfoFunc::EliminationInfoGetConfig eliminationInfoGetConfig;

	eliminationInfoGetConfig.areaFactor = 1;//这里设置为像素当量
	eliminationInfoGetConfig.scoreFactor = 100;//这里设置为百分比当量
	eliminationInfoGetConfig.isUsingArea = false;//这里设置为不使用面积
	eliminationInfoGetConfig.isUsingScore = true;//这里设置为使用分数
	eliminationInfoGetConfig.scoreRange = { 0,100 };
	eliminationInfoGetConfig.areaRange = { 0,100 };
	eliminationInfoGetConfig.scoreIsUsingComplementarySet = false;//这里设置为不使用补集
	eliminationInfoGetConfigs[ClassId::Queya] = eliminationInfoGetConfig;
	eliminationInfoGetConfigs[ClassId::Tangshang] = eliminationInfoGetConfig;
	eliminationInfoGetConfigs[ClassId::Zangwu] = eliminationInfoGetConfig;
	context.eliminationCfg = eliminationInfoGetConfigs;

	rw::imgPro::DefectResultInfoFunc::DefectResultGetConfig defectConfig;
	rw::imgPro::DefectResultInfoFunc::ClassIdWithConfigMap defectConfigs;
	defectConfig.isEnable = true;
	defectConfigs[ClassId::Queya] = defectConfig;
	defectConfig.isEnable = true;
	defectConfigs[ClassId::Tangshang] = defectConfig;
	defectConfig.isEnable = true;
	defectConfigs[ClassId::Zangwu] = defectConfig;
	context.defectCfg = defectConfigs;

	rw::imgPro::DefectDrawFunc::DefectDrawConfig drawConfig;
	drawConfig.isDrawDefects = true;
	drawConfig.isDrawDisableDefects = true;
	context.defectDrawCfg = drawConfig;
}

void ImageProcessorZipper::drawBoundariesLines(QImage& image)
{
	auto& index = imageProcessingModuleIndex;
	auto& setConfig = GlobalStructDataZipper::getInstance().setConfig;
	rw::rqw::ImagePainter::PainterConfig painterConfig;
	painterConfig.color = rw::rqw::ImagePainter::toQColor(rw::rqw::ImagePainter::BasicColor::Red);
	if (index == 1)
	{
		rw::rqw::ImagePainter::drawHorizontalLine(image, setConfig.shangXianWei1, painterConfig);
		rw::rqw::ImagePainter::drawHorizontalLine(image, setConfig.xiaXianWei1, painterConfig);
		rw::rqw::ImagePainter::drawVerticalLine(image, setConfig.zuoXianWei1, painterConfig);
		rw::rqw::ImagePainter::drawVerticalLine(image, setConfig.youXianWei1, painterConfig);
	}
	else if (index == 2)
	{
		rw::rqw::ImagePainter::drawHorizontalLine(image, setConfig.shangXianWei2, painterConfig);
		rw::rqw::ImagePainter::drawHorizontalLine(image, setConfig.xiaXianWei2, painterConfig);
		rw::rqw::ImagePainter::drawVerticalLine(image, setConfig.zuoXianWei2, painterConfig);
		rw::rqw::ImagePainter::drawVerticalLine(image, setConfig.youXianWei2, painterConfig);
	}
}

void ImageProcessorZipper::updateShieldWires()
{
	auto& globalStructSetConfig = GlobalStructDataZipper::getInstance().setConfig;

	leftShieldWire = globalStructSetConfig.zuoXianWei1;
	rightShieldWire = globalStructSetConfig.youXianWei1;
	topShieldWire = globalStructSetConfig.shangXianWei1;
	bottomShieldWire = globalStructSetConfig.xiaXianWei1;
}

void ImageProcessingModuleZipper::onFrameCaptured(cv::Mat frame, size_t index)
{
	// 手动读取本地图片
	std::string imagePath = "C:\\Users\\zzw\\Desktop\\saveimage\\123.jpg"; // 替换为你的图片路径
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
	mat.location = globalStruct.zmotion.getModbus(2, 1);	// 获取拍照的位置
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
