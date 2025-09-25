#include "Modules.hpp"

#include <QApplication>
#include <QMessageBox>
#include "LoadingDialog.h"
#include "DlgProductScore.h"
#include "DlgProductSet.h"
#include "ZipperScanner.h"
#include "rqw_RunEnvCheck.hpp"

Modules::Modules()
{

}

Modules::~Modules()
{

}

bool Modules::build()
{
	LoadingDialog dlg;
	dlg.show();

	// 读取配置
	dlg.updateMessage("读取配置中...");
	QApplication::processEvents();
	auto configManagerBuild = configManagerModule.build();

	// 构建相机
	dlg.updateMessage("构建相机中...");
	QApplication::processEvents();
	auto cameraBuild = cameraModule.build();

	// 构建显示信息模块
	dlg.updateMessage("构建处理模块中...");
	QApplication::processEvents();
	auto runtimeInfoModuleBuild = runtimeInfoModule.build();

	// 构建图像处理模块
	dlg.updateMessage("构建识别模块中...");
	QApplication::processEvents();
	auto imgProModuleBuild = imgProModule.build();

	// 构建UI模块
	uiModule.build();

	// 构建重连模块
	//reconnectModule.build();

	// 构建消除模块
	//auto eliminateModuleBuild = eliminateModule.build();

	// 构建图像保存模块
	//imgSaveModule.build();

	// 构建运动控制模块
	//auto motionControllerModuleBuild = motionControllerModule.build();

	// 构建报警模块
	//warningModule.build();


#ifdef BUILD_WITHOUT_HARDWARE
	test_module.build();
#endif
	

	return true;
}

void Modules::destroy()
{
	LoadingDialog dlg;
	dlg.show();

	dlg.updateMessage("等待销毁工作完成...");
	QApplication::processEvents();

#ifdef BUILD_WITHOUT_HARDWARE
	test_module.destroy();
#endif
	runtimeInfoModule.destroy();
	imgProModule.destroy();
	cameraModule.destroy();
	configManagerModule.destroy();
	uiModule.destroy();
	//reconnectModule.destroy();
	//eliminateModule.destroy();
	//imgSaveModule.destroy();
	//motionControllerModule.destroy();
	//warningModule.destroy();
}

void Modules::start()
{
	uiModule.start();
	configManagerModule.start();
	//motionControllerModule.start();
	runtimeInfoModule.start();
	//warningModule.start();
	//imgSaveModule.start();
	//eliminateModule.start();
	imgProModule.start();
	cameraModule.start();
	//reconnectModule.start();


#ifdef BUILD_WITHOUT_HARDWARE
	test_module.start();
#endif
}

void Modules::stop()
{
#ifdef BUILD_WITHOUT_HARDWARE
	test_module.stop();
#endif
	//reconnectModule.stop();
	cameraModule.stop();
	imgProModule.stop();
	//eliminateModule.stop();
	//imgSaveModule.stop();
	//warningModule.stop();
	runtimeInfoModule.stop();
	//motionControllerModule.stop();
	configManagerModule.stop();
	uiModule.stop();
}

void Modules::connect()
{
#pragma region connect camera and imgProModule

	QObject::connect(&cameraModule, &CameraModule::frameCaptured1,
		imgProModule.imageProcessingModule1.get(), &ImageProcessingModule::onFrameCaptured, Qt::DirectConnection);
	QObject::connect(&cameraModule, &CameraModule::frameCaptured2,
		imgProModule.imageProcessingModule2.get(), &ImageProcessingModule::onFrameCaptured, Qt::DirectConnection);


#pragma endregion

#pragma region connect UIModule and imgProModule
	QObject::connect(imgProModule.imageProcessingModule1.get(), &ImageProcessingModule::imageReady, uiModule._zipperScanner, &ZipperScanner::onCameraDisplay);
	QObject::connect(imgProModule.imageProcessingModule2.get(), &ImageProcessingModule::imageReady, uiModule._zipperScanner, &ZipperScanner::onCameraDisplay);

	QObject::connect(uiModule._zipperScanner, &ZipperScanner::shibiekuangChanged, &imgProModule, &ImgProModule::onUpdateImgProContext);
	QObject::connect(uiModule._zipperScanner, &ZipperScanner::wenziChanged, &imgProModule, &ImgProModule::onUpdateImgProContext);
	QObject::connect(uiModule._dlgProductScore, &DlgProductScore::scoreFormClosed, &imgProModule, &ImgProModule::onUpdateImgProContext);
#pragma endregion

#pragma region connect UIModule and ReconnectModule
	//// 更新UI界面
	//QObject::connect(reconnectModule.monitorCameraAndCardStateThread.get(), &CameraAndCardStateThreadHandleScanner::updateCameraLabelState,
	//	uiModule._handleScanner, &HandleScanner::updateCameraLabelState, Qt::QueuedConnection);
	//// 相机重连
	//QObject::connect(reconnectModule.monitorCameraAndCardStateThread.get(), &CameraAndCardStateThreadHandleScanner::buildCamera,
	//	&cameraModule, &CameraModule::onBuildCamera, Qt::QueuedConnection);
	//QObject::connect(reconnectModule.monitorCameraAndCardStateThread.get(), &CameraAndCardStateThreadHandleScanner::startMonitor,
	//	&cameraModule, &CameraModule::onStartCamera, Qt::QueuedConnection);
	//// 相机销毁
	//QObject::connect(reconnectModule.monitorCameraAndCardStateThread.get(), &CameraAndCardStateThreadHandleScanner::destroyCamera,
	//	&cameraModule, &CameraModule::onDestroyCamera, Qt::QueuedConnection);

#pragma endregion

#pragma region connect UIModule and MotionControllerModule
	/*QObject::connect(motionControllerModule.monitorMotionIoStateThread.get(), &rw::rqw::MonitorZMotionIOStateThread::DIState,
		uiModule._dlgProductSet, &DlgProductSet::monitorInPutSignal, Qt::QueuedConnection);
	QObject::connect(motionControllerModule.monitorMotionIoStateThread.get(), &rw::rqw::MonitorZMotionIOStateThread::DOState,
		uiModule._dlgProductSet, &DlgProductSet::monitorOutPutSignal, Qt::QueuedConnection);*/
#pragma endregion

#ifdef BUILD_WITHOUT_HARDWARE
	/*QObject::connect(test_module.testImgPushThread.get(), &TestImgPushThread::imgReady,
			imgProModule.imageProcessingModule1.get(), &ImageProcessingModuleHandleScanner::onFrameCaptured, Qt::DirectConnection);*/
	/*QObject::connect(test_module.testImgPushThread.get(), &TestImgPushThread::imgReady,
		imgProModule.imageProcessingModule2.get(), &ImageProcessingModuleHandleScanner::onFrameCaptured, Qt::DirectConnection);*/
#endif

#pragma region connect UIModule and RuntimeInfoModule
	QObject::connect(runtimeInfoModule.detachUtiltyThread.get(), &DetachUtiltyThread::updateStatisticalInfo,
		uiModule._zipperScanner, &ZipperScanner::onUpdateStatisticalInfo, Qt::QueuedConnection);
#pragma endregion

#pragma region connect MotionControllerModule and RuntimeInfoModule
	/*QObject::connect(runtimeInfoModule.detachUtiltyThread.get(), &DetachUtiltyThread::produceCountReachingTheSetValue,
		&motionControllerModule, &MotionControllerModule::getStopSignal, Qt::QueuedConnection);*/
#pragma endregion

}

bool Modules::check()
{
#pragma region check single instance
	if (!rw::rqw::RunEnvCheck::isSingleInstance("ZipperScanner.exe"))
	{
		QMessageBox::warning(nullptr, "错误", "已经有程序在运行，请勿多次打开");
		return false;
	}
#pragma endregion

#pragma region check run env
	if (rw::rqw::RunEnvCheck::isProcessRunning("MVS.exe"))
	{
		QMessageBox::warning(nullptr, "错误", "检测到海康威视软件正在运行，请先关闭后再启动本程序。");
		return false;
	}

	if (rw::rqw::RunEnvCheck::isProcessRunning("BasedCam3.exe"))
	{
		QMessageBox::warning(nullptr, "错误", "检测到度申相机平台软件正在运行，请先关闭后再启动本程序。");
		return false;
	}

#pragma endregion

#pragma region check directory exist
	/*EnsureDirectoryExists(globalPath.projectHome);
	EnsureDirectoryExists(globalPath.configRootPath);
	EnsureDirectoryExists(globalPath.modelRootPath);
	EnsureDirectoryExists(globalPath.txtPath);
	EnsureDirectoryExists(globalPath.imageSaveRootPath);*/
#pragma endregion

#pragma region check model exist
	/*if (!rw::rqw::RunEnvCheck::isFileExist(globalPath.modelPath))
	{
		QMessageBox::warning(nullptr, "错误", "模型文件缺失");
		return false;
	}*/
#pragma endregion

#pragma region check config format and exist
	/*rw::oso::StorageContext storageContext(rw::oso::StorageType::Xml);

	checkFileExistAndFormat<cdm::HandleScannerConfig>(globalPath.HandleScannerConfigPath, storageContext);
	checkFileExistAndFormat<cdm::SetConfig>(globalPath.DlgProductSetConfigPath, storageContext);
	checkFileExistAndFormat<cdm::ScoreConfig>(globalPath.DlgProductScoreConfigPath, storageContext);*/
#pragma endregion

	return true;
}

bool Modules::EnsureDirectoryExists(const QString& dirPath)
{
	QDir dir(dirPath);
	if (!dir.exists()) {
		return dir.mkpath(".");
	}
	return true;
}
