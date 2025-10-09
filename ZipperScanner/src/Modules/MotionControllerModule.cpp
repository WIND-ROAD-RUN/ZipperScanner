#include "MotionControllerModule.hpp"

#include "Modules.hpp"

bool MotionControllerModule::build()
{
#pragma region build zmotion
	zmotion = std::make_shared<rw::rqw::ZMotion>(Utility::zmotionIp);
	zmotion->setIp(Utility::zmotionIp);
	bool isConnected = zmotion->connect();
	isConnectMotion = isConnected;
	if (isConnected)
	{
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;

		auto meizhuanmaichongshu = setConfig.meizhuanmaichongshu;
		auto shedingzhouchang = setConfig.shedingzhouchang;
		auto value = meizhuanmaichongshu / shedingzhouchang;

		bool isLocationZero = zmotion->setLocationZero(0);
		bool isAxisType = zmotion->setAxisType(0,1);
		bool isAxisPulse = zmotion->setAxisPulse(0, value);

		bool isSetXiangJiChuFaChangDu = zmotion->setModbus(4, 1, setConfig.xiangjichufachangdu);
		bool isSetdangqianweizhi = zmotion->setModbus(2, 1, 0);
		isSetdangqianweizhi = zmotion->setModbus(6, 1, 0);

		bool isOK = true;
		for (int i = 0; i < 13; i++)
		{
			isOK&& zmotion->setIOOut(i, false);
		}
	}
#pragma endregion

#pragma region build monitorMotionIoStateThread
	monitorMotionIoStateThread = std::make_unique<rw::rqw::MonitorZMotionIOStateThread>();

	monitorMotionIoStateThread->setMonitorObject(*zmotion);
	QVector<size_t> monitorIList = {
		ControlLines::qidonganniuIn,ControlLines::jitingIn,
		ControlLines::lalianlawanIn, ControlLines::guanjiIn };

	QVector<size_t> monitorOList = {
		ControlLines::chongkongOUT,ControlLines::tuojiOut,
		ControlLines::xiangjichufaOut1,ControlLines::xiangjichufaOut2,
		ControlLines::DOWarnRed,ControlLines::DOWarnGreen};

	monitorMotionIoStateThread->setMonitorIList(monitorIList);
	monitorMotionIoStateThread->setMonitorOList(monitorOList);
	monitorMotionIoStateThread->setMonitorFrequency(20);
	monitorMotionIoStateThread->setRunning(false);
#pragma endregion

#pragma region build monitorMotionIoStateThread
	monitorStartOrStopThread = std::make_unique<rw::rqw::MonitorZMotionIOStateThread>();
	monitorStartOrStopThread->setMonitorObject(*zmotion);

	monitorIList = { ControlLines::qidonganniuIn,ControlLines::jitingIn };

	monitorStartOrStopThread->setMonitorIList(monitorIList);
	monitorStartOrStopThread->setMonitorFrequency(20);
	monitorStartOrStopThread->setRunning(false);
#pragma endregion

#pragma region build ioTriggerThread
	ioTriggerThread = std::make_unique<IOTriggerThread>();
#pragma endregion

	return isConnected;
}

void MotionControllerModule::destroy()
{
	if (monitorStartOrStopThread)
	{
		monitorStartOrStopThread->destroyThread();
	}
	if (monitorMotionIoStateThread)
	{
		monitorMotionIoStateThread->destroyThread();
	}
	if (zmotion)
	{
		bool isDisconnect = zmotion->disConnect();
		zmotion.reset();
	}
	if (ioTriggerThread)
	{
		ioTriggerThread.reset();
	}
}

void MotionControllerModule::start()
{
	if (monitorMotionIoStateThread)
	{
		monitorMotionIoStateThread->setRunning(true);
		monitorMotionIoStateThread->start();
	}
	if (monitorStartOrStopThread)
	{
		monitorStartOrStopThread->setRunning(true);
		monitorStartOrStopThread->start();
	}
	if (ioTriggerThread)
	{
		ioTriggerThread->startThread();
	}
}

void MotionControllerModule::stop()
{
	if (monitorStartOrStopThread)
	{
		monitorStartOrStopThread->setRunning(false);
	}
	if (monitorMotionIoStateThread)
	{
		monitorMotionIoStateThread->setRunning(false);
	}
	if (zmotion)
	{
		zmotion->stopAllAxis();
	}
	if (ioTriggerThread)
	{
		ioTriggerThread->stopThread();
	}
}

void MotionControllerModule::getStopSignal()
{
	if (zmotion)
	{
		zmotion->stopAllAxis();
	}
}
