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
		processWarningInfo(s);
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

void DetachUtiltyThread::processWarningInfo(size_t s)
{
	static rw::rqw::WarningInfo warningInfo;
	if (isProcessFinish)
	{
		isProcessFinish = false;
		//processOneWarnFinsh(warningInfo);
	}
	if (s % 2 == 0 && !isProcessing)
	{
		processOneWarnGet(warningInfo);
	}
}

void DetachUtiltyThread::processOneWarnGet(rw::rqw::WarningInfo& info)
{
	/*isProcessFinish = false;
	auto isEmpty = warningLabel->isEmptyWarningListThreadSafe();
	if (isEmpty)
	{
		return;
	}
	isProcessing = true;
	info = warningLabel->topWarningListThreadSafe();
	auto& config = GlobalData::getInstance().dlgWarningManagerConfig;
	auto isOpenWarn = config.findIsOpen(info.warningId);
	if (isOpenWarn)
	{
		emit showDlgWarn(info);
		openWarnAlarm(info);;
	}
	else
	{
		isProcessing = false;
		warningLabel->popWarningListThreadSafe();
	}*/
}



void DetachUtiltyThread::processShutdownIO(size_t s)
{
	if (s % 1 == 0)
	{
		auto& motion = GlobalData::getInstance().zmotion;
		auto isShutdown = motion.getIOIn(ControlLines::guanjiIn);

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
