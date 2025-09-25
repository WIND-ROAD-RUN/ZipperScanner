#pragma once

#include <memory>
#include "rqw_CameraObjectCore.hpp"
#include "rqw_CameraObjectThread.hpp"
#include "ImageProcessorModule.h"
#include "dsl_ThreadSafeMinHeap.h"
#include "Utilty.hpp"
#include "CameraAndCardStateThread.h"
#include <chrono>

#include "DetachUtiltyThread.h"
#include "MonitorProduceLengthThread.hpp"
#include "rqw_ZMotion.hpp"
#include "rqw_MonitorMotionIO.hpp"
#include "RuntimeInfoModule.hpp"
#include "TestImgPushThread.hpp"


class DetachDefectThreadZipper;


enum class LightLevel {
	StrongLight,
	MediumLight,
	WeakLight
};

class GlobalThread
	:public QObject
{
	Q_OBJECT
public:
	static GlobalThread& getInstance()
	{
		static GlobalThread instance;
		return instance;
	}

	GlobalThread(const GlobalThread&) = delete;
	GlobalThread& operator=(const GlobalThread&) = delete;
private:
	GlobalThread() = default;
	~GlobalThread() = default;
public:
	void buildDetachThread();
	void destroyDetachThread();
	void startDetachThread();
public:
	std::unique_ptr<MonitorProduceLengthThread> monitorProduceLengthThread{ nullptr };

#ifdef BUILD_WITHOUT_HARDWARE
public:
	std::unique_ptr<TestImgPushThread> testImgPushThread{ nullptr };
	std::atomic_bool testImgPush{ false };
#endif
public:
	std::atomic_bool goToGetStartLocation{false};
	std::atomic_bool goToGetStopLocation{ false };
	std::atomic_bool isMonitorProduceLocation{false};
	std::atomic<double> startLocation{ 0.0 };
	std::atomic<double> stopLocation{ 0.0 };
	std::atomic<double> currentProducePulse { 0.0 };
};

class GlobalData
	:public QObject
{
	Q_OBJECT
public:
	std::atomic_int imgRotateCount1{0};
	std::atomic_int imgRotateCount2{ 0 };
public:
	rw::rqw::ZMotion  zmotion;
	void destory_motion();

public:
	// 监控所有IO
	rw::rqw::MonitorZMotionIOStateThread monitorZMotionMonitorThread;
public:
	void build_MonitorZMotionIOStateThread();
	void destroy_MonitorZMotionIOStateThread();

	void getInPutSignal(size_t index, bool state);
	void getOutPutSignal(size_t index, bool state);

public:
	// 监控启停按钮
	rw::rqw::MonitorZMotionIOStateThread monitorStartOrStopThread;
public:
	void build_monitorStartOrStopThread();
	void destroy_monitorStartOrStopThread();

	void getStartOrStopSignal(size_t index, bool state);
	
signals:
	// 监控启停IO
	void emit_StartOrStopSignal(size_t index, bool state);
	// 监控所有IO
	void emit_InPutSignal(size_t index, bool state);
	void emit_OutPutSignal(size_t index, bool state);
public:
	std::unique_ptr<ThreadSafeMinHeap> priorityQueue;

	float startLocation = 0;
public:
	void build_PriorityQueue();
	void destroy_PriorityQueue();
public:
	DetachDefectThreadZipper* detachDefectThreadZipper;
public:
	void build_DetachDefectThreadZipper();
	void destroy_DetachDefectThreadZipper();
public:
	CameraAndCardStateThreadZipper* cameraAndCardStateThreadZipper;
public:
	void build_CameraAndCardStateThreadZipper();
signals:
	// 更新UI
	void emit_updateUiLabels(int index, bool isConnected);

public:
	std::atomic<bool> debug_isDisplayRec{ true };
	std::atomic<bool> debug_isDisplayText{ true };

	std::atomic_bool _isUpdateMonitorInfo{ false };

public:
	static GlobalData& getInstance()
	{
		static GlobalData instance;
		return instance;
	}

	GlobalData(const GlobalData&) = delete;
	GlobalData& operator=(const GlobalData&) = delete;
private:
	GlobalData();
	~GlobalData() = default;
public:
	void setLightLevel(const LightLevel& level);
public:
	void buildImageProcessorModules(const QString& path);
	void destroyImageProcessingModule();

	// 图像处理模块
	std::unique_ptr<ImageProcessingModule> imageProcessingModule1 = nullptr;
	std::unique_ptr<ImageProcessingModule> imageProcessingModule2 = nullptr;


public:
	void buildImageSaveEngine();
	void destroyImageSaveEngine();
	std::unique_ptr<rw::rqw::ImageSaveEngine> imageSaveEngine{ nullptr };
};
