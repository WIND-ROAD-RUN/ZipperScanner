#include "DetachUtiltyThread.h"

#include "GlobalStruct.hpp"
#include "rqw_CameraObjectZMotion.hpp"
#include <Utilty.hpp>

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
	auto& globalStruct = GlobalData::getInstance();
	auto& statisticalInfo = globalStruct.statisticalInfo;


	static size_t s = 0;
	while (running) {
		QThread::sleep(1);
		CalculateRealtimeInformation(s);
		processWarningInfo(s);
		processTrigger(s);
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
		processOneWarnFinsh(warningInfo);
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

void DetachUtiltyThread::processOneWarnFinsh(rw::rqw::WarningInfo& info)
{
	/*closeWarnAlarm(info);
	info = warningLabel->popWarningListThreadSafe();
	isProcessFinish = false;
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
		openWarnAlarm(info);
	}
	else
	{
		isProcessing = false;
		warningLabel->popWarningListThreadSafe();
	}*/
}

//void DetachUtiltyThreadZipper::openWarnAlarm(const rw::rqw::WarningInfo& info)
//{
//	auto& motion = zwy::scc::GlobalMotion::getInstance().motionPtr;
//	motion->SetIOOut(ControlLines::warnRedOut, true);
//	motion->SetIOOut(ControlLines::warnGreenOut, false);
//}
//
//void DetachUtiltyThreadZipper::closeWarnAlarm(const rw::rqw::WarningInfo& info)
//{
//	auto& motion = zwy::scc::GlobalMotion::getInstance().motionPtr;
//	motion->SetIOOut(ControlLines::warnRedOut, false);
//	motion->SetIOOut(ControlLines::warnGreenOut, true);
//}

void DetachUtiltyThread::processTrigger(size_t s)
{
	/*if (s % 180 == 0)
	{
		auto& globalStruct = GlobalData::getInstance();
		auto& statisticalInfo = globalStruct.statisticalInfo;
		auto& runningState = globalStruct.runningState;
		bool isRun = runningState.load() == RunningState::OpenRemoveFunc;

		if (isRun)
		{
			if (isStopOnce)
			{
				isStopOnce = false;
				return;
			}
			auto newWork1Count = statisticalInfo.produceCount1.load();
			auto newWork2Count = statisticalInfo.produceCount2.load();

			if (newWork1Count == lastWork1Count)
			{
				emit workTriggerError(1);
			}
			if (newWork2Count == lastWork2Count)
			{
				emit workTriggerError(2);
			}

			lastWork1Count = newWork1Count;
			lastWork2Count = newWork2Count;
		}
		else
		{
			isStopOnce = true;
		}
	}*/
}

void DetachUtiltyThread::processShutdownIO(size_t s)
{
	/*if (s % 1 == 0)
	{
		auto& motion = zwy::scc::GlobalMotion::getInstance().motionPtr;
		auto isShutdown = motion->GetIOIn(ControlLines::shutdownComputerIn);

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
	}*/
}
