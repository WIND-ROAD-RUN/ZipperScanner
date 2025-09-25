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
    auto& globalStruct = GlobalData::getInstance();
    auto& globalThread = GlobalThread::getInstance();
    auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
    double lastValidPulse = 0.0;
    bool firstRun = true;


    while (running) {
        QThread::msleep(10);

        bool isGet{false};
        auto isConnect = globalStruct.zmotion.getConnectState(isGet);
        if (!(isConnect&& isGet)) {
            continue;
        }
        bool isGetLocation{false};
		auto location=globalStruct.zmotion.getAxisLocation(0, isGetLocation);
        if (!isGetLocation)
        {
			continue;
        }

        if (globalThread.goToGetStartLocation)
        {
			globalThread.startLocation = location;
            globalThread.goToGetStartLocation = false;
			globalThread.isMonitorProduceLocation = true;
        }

        if (globalThread.goToGetStopLocation)
		{
            globalThread.stopLocation = location;
            globalThread.goToGetStopLocation = false;
			globalThread.isMonitorProduceLocation = false;
            globalStruct.statisticalInfo.produceLength = globalStruct.statisticalInfo.produceLength+globalStruct.statisticalInfo.produceLengthBeforeStart.load();
            globalStruct.statisticalInfo.produceLengthBeforeStart = 0;
        }

        if (globalThread.isMonitorProduceLocation)
        {
			globalThread.currentProducePulse = location - globalThread.startLocation;
            globalStruct.statisticalInfo.produceLengthBeforeStart = globalThread.currentProducePulse.load() / 1000;//转换为米
        }

        if (globalStruct.statisticalInfo.produceLength + globalStruct.statisticalInfo.produceLengthBeforeStart.load() > generalConfig.shedingladaichangdu)
        {
            emit finishProduce();
        }
    }
}
