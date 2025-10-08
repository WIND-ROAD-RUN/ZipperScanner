#include "ImageProcessorModule.h"

#include <qcolor.h>
#include <QPainter>

#include "GlobalStruct.hpp"
#include "ime_ModelEngineFactory.h"
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
	auto maskImg = imgPro.getMaskImg(frame.image);
	auto defectResult = imgPro.getDefectResultInfo();

	emit imageReady(QPixmap::fromImage(maskImg), frame.index, defectResult.isBad);
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

	emit imageReady(QPixmap::fromImage(rw::rqw::cvMatToQImage(frame.image)),frame.index,false);
}

void ImageProcessorZipper::run_OpenRemoveFunc(MatInfo& frame)
{
	leftLocationX = 0;
	auto& imgPro = *_imgProcess;
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	imgPro(frame.image);
	auto maskImg = imgPro.getMaskImg(frame.image);
	auto defectResult = imgPro.getDefectResultInfo();

	auto& context = imgPro.context();

	auto tempLeftLocationX = 0;
	if (context.customFields.find("leftLocationX") != context.customFields.end())
	{
		tempLeftLocationX = std::any_cast<int>(context.customFields.at("leftLocationX"));
	}

	if (tempLeftLocationX != 0)
	{
		leftLocationX = tempLeftLocationX;
	}

	if (1 == imageProcessingModuleIndex)
	{
		tifeijuli = setConfig.tifeijuli1;
	}
	else if (2 == imageProcessingModuleIndex)
	{
		tifeijuli = setConfig.tifeijuli2;
	}

	if (leftLocationX > 0)
	{
		leftLocationX = frame.location - leftLocationX * pixToWorld + tifeijuli;
	}
	if (defectResult.isBad) {
		std::cout << "tifeijuli" << tifeijuli << std::endl;
		std::cout << "leftLocationX" << leftLocationX << " frame.location:" << frame.location << std::endl;
	}

	run_OpenRemoveFunc_emitErrorInfo(defectResult.isBad);

	emit imageReady(QPixmap::fromImage(maskImg), frame.index, defectResult.isBad);

	rw::rqw::ImageInfo imageInfo(maskImg);

	save_image(imageInfo, rw::rqw::cvMatToQImage(frame.image));
}

void ImageProcessorZipper::run_OpenRemoveFunc_emitErrorInfo(bool isbad) const
{
	auto& priorityQueue = Modules::getInstance().eliminateModule.priorityQueue;

	if (isbad)
	{
		priorityQueue->push(leftLocationX);
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
	auto& imageSaveEngine = Modules::getInstance().imgSaveModule.imageSaveEngine;
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	if (_isbad) {
		if (setConfig.saveNGImg)
		{
			rw::rqw::ImageInfo NG(image);
			NG.classify = "NG";
			imageSaveEngine->pushImage(NG);
		}
		if (setConfig.saveMaskImg)
		{
			imageInfo.classify = "Mask";
			imageSaveEngine->pushImage(imageInfo);
		}
	}
	else {
		if (setConfig.saveOKImg)
		{
			rw::rqw::ImageInfo Ok(image);
			Ok.classify = "OK";
			imageSaveEngine->pushImage(Ok);
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
	_imgProcess->context() = Modules::getInstance().imgProModule.imageProcessContext_Main;
	_imgProcess->context().customFields["ImgProcessIndex"] = static_cast<int>(imageProcessingModuleIndex);
	_imgProcess->context().customFields["stationIdx"] = static_cast<int>(_workIndex);
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
	auto& imgRotateCount1 = Modules::getInstance().configManagerModule.setConfig.imgRotateCount1;
	auto& imgRotateCount2 = Modules::getInstance().configManagerModule.setConfig.imgRotateCount2;
	QMutexLocker locker(&_mutex);
	MatInfo mat;

	if (index == 1)
	{
		switch (imgRotateCount1) {
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
		switch (imgRotateCount2) {
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

	mat.location = std::any_cast<float>(matInfo.customField.at("LocCallBack"));
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
		connect(this, &ImageProcessingModule::shibiekaungChanged, processor, &ImageProcessorZipper::updateDrawRec, Qt::QueuedConnection);
		connect(this, &ImageProcessingModule::wenziChanged, processor, &ImageProcessorZipper::updateDrawText, Qt::QueuedConnection);
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
