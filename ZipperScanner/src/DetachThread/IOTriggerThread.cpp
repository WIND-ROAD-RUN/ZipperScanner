#include"IOTriggerThread.hpp"
#include "Modules.hpp"

IOTriggerThread::IOTriggerThread(QObject* parent)
	: QThread(parent), running(false) {
}

IOTriggerThread::~IOTriggerThread()
{
	stopThread();
	wait();
}

void IOTriggerThread::startThread()
{
	running = true;
	if (!isRunning()) {
		start();
	}
}

void IOTriggerThread::stopThread()
{
	running = false;
}

void IOTriggerThread::run()
{
	auto& motionControllerModule = Modules::getInstance().motionControllerModule;

	while (running) {

		auto qiya = motionControllerModule.zmotion->getIOIn(ControlLines::lalianlawanIn);
		if (qiya == true) {
			QMetaObject::invokeMethod(qApp, [this]
				{
					rw::rqw::WarningInfo info;
					info.message = "拉链拉完了!";
					info.type = rw::rqw::WarningType::Error;
					info.warningId = WarningId::clalianlawanAlarm;
					Modules::getInstance().warningModule.addWarning(info, true);
				});
		}

		QThread::sleep(1);

	}
}
