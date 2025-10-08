#pragma once

#include <memory>
#include "rqw_CameraObjectCore.hpp"
#include "rqw_CameraObjectThread.hpp"
#include "ImageProcessorModule.h"
#include "Utilty.hpp"
#include "CameraAndCardStateThread.h"
#include <chrono>
#include "rqw_MonitorMotionIO.hpp"
#include "TestImgPushThread.hpp"


class DetachDefectThreadZipper;

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

#ifdef BUILD_WITHOUT_HARDWARE
public:
	std::unique_ptr<TestImgPushThread> testImgPushThread{ nullptr };
	std::atomic_bool testImgPush{ false };
#endif

};

class GlobalData
	:public QObject
{
	Q_OBJECT
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
	std::atomic_bool goToGetStartLocation{ false };
	std::atomic_bool goToGetStopLocation{ false };
	std::atomic_bool isMonitorProduceLocation{ false };
	std::atomic<double> startLocation{ 0.0 };
	std::atomic<double> stopLocation{ 0.0 };
	std::atomic<double> currentProducePulse{ 0.0 };
};
