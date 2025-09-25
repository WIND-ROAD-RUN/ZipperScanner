#include"GlobalStruct.hpp"

#include <qregularexpression.h>

#include "hoec_Camera.hpp"
#include "rqw_CameraObjectCore.hpp"
#include "Utilty.hpp"
#include "DetachDefectThread.h"
#include "Modules.hpp"
#include "rqw_CameraObjectThreadZMotion.hpp"


void GlobalThread::buildDetachThread()
{
	monitorProduceLengthThread = std::make_unique<MonitorProduceLengthThread>(this);
}

void GlobalThread::destroyDetachThread()
{
	monitorProduceLengthThread.reset();
}

void GlobalThread::startDetachThread()
{
	if (monitorProduceLengthThread)
	{
		monitorProduceLengthThread->startThread();
	}
}

void GlobalData::destory_motion()
{
	bool isDisconnect = zmotion.disConnect();
}

void GlobalData::build_MonitorZMotionIOStateThread()
{
	monitorZMotionMonitorThread.setMonitorObject(zmotion);
	QVector<size_t> monitorIList = {ControlLines::qidonganniuIn,ControlLines::lalianlawanIn,ControlLines::jitingIn,ControlLines::guanjiIn};
	QVector<size_t> monitorOList = {ControlLines::chongkongOUT,ControlLines::tuojiOut,ControlLines::xiangjichufaOut1 ,ControlLines::xiangjichufaOut2 };
	monitorZMotionMonitorThread.setMonitorIList(monitorIList);
	monitorZMotionMonitorThread.setMonitorOList(monitorOList);
	monitorZMotionMonitorThread.setMonitorFrequency(20);
	monitorZMotionMonitorThread.setRunning(false);
	monitorZMotionMonitorThread.start();
	QObject::connect(&monitorZMotionMonitorThread, &rw::rqw::MonitorZMotionIOStateThread::DIState,
		this, &GlobalData::getInPutSignal,Qt::QueuedConnection);
	QObject::connect(&monitorZMotionMonitorThread, &rw::rqw::MonitorZMotionIOStateThread::DOState,
		this, &GlobalData::getOutPutSignal, Qt::QueuedConnection);
}

void GlobalData::destroy_MonitorZMotionIOStateThread()
{
	monitorZMotionMonitorThread.setRunning(false);
	monitorZMotionMonitorThread.destroyThread();
}

void GlobalData::getStartOrStopSignal(size_t index, bool state)
{
	emit emit_StartOrStopSignal(index, state);
}

void GlobalData::build_monitorStartOrStopThread()
{
	monitorStartOrStopThread.setMonitorObject(zmotion);

	QVector<size_t> monitorIList = { ControlLines::qidonganniuIn,ControlLines::jitingIn };
	monitorStartOrStopThread.setMonitorIList(monitorIList);
	monitorStartOrStopThread.setMonitorFrequency(20);
	monitorStartOrStopThread.setRunning(true);
	monitorStartOrStopThread.start();

	QObject::connect(&monitorStartOrStopThread, &rw::rqw::MonitorZMotionIOStateThread::DIState,
		this, &GlobalData::getStartOrStopSignal, Qt::QueuedConnection);
}

void GlobalData::destroy_monitorStartOrStopThread()
{
	monitorStartOrStopThread.setRunning(false);
	monitorStartOrStopThread.destroyThread();
}

void GlobalData::getInPutSignal(size_t index, bool state)
{
	emit emit_InPutSignal(index, state);
}

void GlobalData::getOutPutSignal(size_t index, bool state)
{
	emit emit_OutPutSignal(index, state);
}

void GlobalData::build_PriorityQueue()
{
	auto compareNodeEqual = [](const float& a, const float& b) {
		return a == b;
		};
	auto compareNodePriority = [](const float& a, const float& b) {
		return a < b;
		};

	priorityQueue = std::make_unique<ThreadSafeMinHeap >();
}

void GlobalData::destroy_PriorityQueue()
{
	priorityQueue.reset();
}

void GlobalData::build_DetachDefectThreadZipper()
{
	detachDefectThreadZipper = new DetachDefectThreadZipper(this);
}

void GlobalData::destroy_DetachDefectThreadZipper()
{
	if (detachDefectThreadZipper)
	{
		delete detachDefectThreadZipper;
	}
}

void GlobalData::build_CameraAndCardStateThreadZipper()
{
	cameraAndCardStateThreadZipper = new CameraAndCardStateThreadZipper(this);
	// 更新UI界面
	QObject::connect(cameraAndCardStateThreadZipper, &CameraAndCardStateThreadZipper::updateCameraLabelState,
		this, &GlobalData::emit_updateUiLabels, Qt::QueuedConnection);
	////相机重连
	//QObject::connect(cameraAndCardStateThreadZipper, &CameraAndCardStateThreadZipper::buildCamera1,
	//	this, &GlobalData::rebuild_Camera1, Qt::QueuedConnection);
	//QObject::connect(cameraAndCardStateThreadZipper, &CameraAndCardStateThreadZipper::buildCamera2,
	//	this, &GlobalData::rebuild_Camera2, Qt::QueuedConnection);
	//// 相机销毁
	//QObject::connect(cameraAndCardStateThreadZipper, &CameraAndCardStateThreadZipper::destroyCamera1,
	//	this, &GlobalData::destroy_Camera1, Qt::QueuedConnection);
	//QObject::connect(cameraAndCardStateThreadZipper, &CameraAndCardStateThreadZipper::destroyCamera2,
	//	this, &GlobalData::destroy_Camera2, Qt::QueuedConnection);
}

GlobalData::GlobalData()
{

}

void GlobalData::setLightLevel(const LightLevel& level)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	auto& camera1 = Modules::getInstance().cameraModule.camera1;
	auto& camera2 = Modules::getInstance().cameraModule.camera2;
	switch (level)
	{
	case LightLevel::StrongLight :
		if (camera1) {
			camera1->setExposureTime(setConfig.qiangBaoGuang);
			camera1->setGain(setConfig.qiangZengYi);
		}
		if (camera2) {
			camera2->setExposureTime(setConfig.qiangBaoGuang);
			camera2->setGain(setConfig.qiangZengYi);
		}
		break;
	case LightLevel::MediumLight:
		if (camera1) {
			camera1->setExposureTime(setConfig.zhongBaoGuang);
			camera1->setGain(setConfig.zhongZengYi);
		}
		if (camera2) {
			camera2->setExposureTime(setConfig.zhongBaoGuang);
			camera2->setGain(setConfig.zhongZengYi);
		}
		break;
	case LightLevel::WeakLight:
		if (camera1) {
			camera1->setExposureTime(setConfig.ruoBaoGuang);
			camera1->setGain(setConfig.ruoZengYi);
		}
		if (camera2) {
			camera2->setExposureTime(setConfig.ruoBaoGuang);
			camera2->setGain(setConfig.ruoZengYi);
		}
		break;
	default:
		break;
	}
}

void GlobalData::buildImageSaveEngine()
{
	imageSaveEngine = std::make_unique<rw::rqw::ImageSaveEngine>(this, 2);
}

void GlobalData::destroyImageSaveEngine()
{
	imageSaveEngine->stop();
	imageSaveEngine.reset();
}