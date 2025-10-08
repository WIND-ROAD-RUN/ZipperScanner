#include "DetachUtiltyThread.h"

#include "GlobalStruct.hpp"
#include "rqw_CameraObjectZMotion.hpp"
#include <Utilty.hpp>

#include "Modules.hpp"

DetachUtiltyThread::DetachUtiltyThread(QObject* parent)
	: QThread(parent), running(false) {

}

DetachUtiltyThread::~DetachUtiltyThread()
{
	stopThread();
	wait(); // 等待线程安全退出
}

void DetachUtiltyThread::startThread()
{
	running = true;
	if (!isRunning()) {
		start(); // 启动线程
	}
}

void DetachUtiltyThread::stopThread()
{
	running = false; // 停止线程
}

void DetachUtiltyThread::run()
{
	static size_t s = 0;
	while (running) {
		QThread::sleep(1);
		CalculateRealtimeInformation(s);
		processShutdownIO(s);
		++s;
		if (s == 300)
		{
			s = 0;
		}
	}
}

void DetachUtiltyThread::CalculateRealtimeInformation(size_t s)
{
	emit updateStatisticalInfo();
}


void DetachUtiltyThread::processShutdownIO(size_t s)
{
	if (s % 1 == 0)
	{
		auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
		auto isShutdown = zmotion->getIOIn(ControlLines::guanjiIn);

		if (lastIsShutDown)
		{
			shutdownCount++;
			emit shutdownComputer(shutdownCount);
		}
		else
		{
			if (isShutdown)
			{
				emit shutdownComputer(shutdownCount);
			}
			else
			{
				shutdownCount = 0;
				emit shutdownComputer(-1);
			}
		}
		lastIsShutDown = isShutdown;
	}
}
