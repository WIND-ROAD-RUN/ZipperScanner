#pragma once

#include"IModule.hpp"

#include<QObject>

#include "DetachUtiltyThread.h"

enum class RunningState
{
	Debug,
	OpenRemoveFunc,
	Stop
};

class RuntimeInfoModule : public QObject, public IModule<bool>
{
	Q_OBJECT
public:
	bool build() override;
	void destroy() override;
	void start() override;
	void stop() override;
public:
	struct StatisticalInfo
	{
		std::atomic_int punchCount{ 0 };
		std::atomic<double> produceLengthBeforeStart{ 0 };
		std::atomic<double> produceLength{ 0 };
	} statisticalInfo;
public:
	std::atomic_bool isTakePictures{ false };
	std::atomic<RunningState> runningState{ RunningState::Stop };
public:
	std::unique_ptr<DetachUtiltyThread> detachUtiltyThread{ nullptr };
};

