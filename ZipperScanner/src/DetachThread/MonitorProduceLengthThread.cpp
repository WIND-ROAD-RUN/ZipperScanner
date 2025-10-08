#include"MonitorProduceLengthThread.hpp"

#include "GlobalStruct.hpp"
#include "Modules.hpp"

MonitorProduceLengthThread::MonitorProduceLengthThread(QObject* parent)
	: QThread(parent), running(false)
{
}

MonitorProduceLengthThread::~MonitorProduceLengthThread()
{
	stopThread();
	wait();
}

void MonitorProduceLengthThread::startThread()
{
	running = true;
	if (!isRunning()) {
		start();
	}
}

void MonitorProduceLengthThread::stopThread()
{
	running = false;
}

void MonitorProduceLengthThread::run()
{
	static size_t s = 0;
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	auto& globalData = GlobalData::getInstance();
	auto& statisticalInfo = Modules::getInstance().runtimeInfoModule.statisticalInfo;
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;


	while (running) {
		QThread::msleep(10);

		bool isGet{ false };
		auto isConnect = zmotion->getConnectState(isGet);
		if (!(isConnect && isGet)) {
			continue;
		}
		bool isGetLocation{ false };
		auto location = zmotion->getAxisLocation(0, isGetLocation);
		if (!isGetLocation)
		{
			continue;
		}

		if (globalData.goToGetStartLocation)
		{
			globalData.startLocation = location;
			globalData.goToGetStartLocation = false;
			globalData.isMonitorProduceLocation = true;
		}

		if (globalData.goToGetStopLocation)
		{
			globalData.stopLocation = location;
			globalData.goToGetStopLocation = false;
			globalData.isMonitorProduceLocation = false;
			statisticalInfo.produceLength = statisticalInfo.produceLength + statisticalInfo.produceLengthBeforeStart.load();
			statisticalInfo.produceLengthBeforeStart = 0;
		}

		if (globalData.isMonitorProduceLocation)
		{
			globalData.currentProducePulse = location - globalData.startLocation;
			statisticalInfo.produceLengthBeforeStart = globalData.currentProducePulse.load() / 1000;//转换为米
		}

		if (statisticalInfo.produceLength + statisticalInfo.produceLengthBeforeStart.load() > generalConfig.shedingladaichangdu)
		{
			emit finishProduce();
		}
	}
}
