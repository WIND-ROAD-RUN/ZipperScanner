#include"WarningModule.hpp"

#include "Utilty.hpp"
#include "DlgWarn.h"
#include "Modules.hpp"
#include "rqw_LabelWarning.h"

void WarningModule::build()
{
	dlgWarn = new DlgWarn();
	labelWarning = new rw::rqw::LabelWarning();
	warningInfoProcessThread = std::make_unique<WarningInfoProcessThread>(this);
}

void WarningModule::destroy()
{
	delete dlgWarn;
	delete labelWarning;
	warningInfoProcessThread.reset();
}

void WarningModule::start()
{
	warningInfoProcessThread->startThread();
}

void WarningModule::stop()
{
	warningInfoProcessThread->stopThread();
}

void WarningModule::addWarning(const rw::rqw::WarningInfo& message, int redDuration)
{
	labelWarning->addWarning(message, redDuration);
}

void WarningModule::addWarning(const rw::rqw::WarningInfo& message, bool updateTimestampIfSame, int redDuration,
	int time)
{
	labelWarning->addWarning(message, updateTimestampIfSame, redDuration, time);
}

void WarningModule::onShowDlgWarn(rw::rqw::WarningInfo info)
{
#ifndef BUILD_WITHOUT_HARDWARE

	QString timeStr = info.timestamp.toString("hh时mm分ss秒");
	dlgWarn->setTime(timeStr);
	dlgWarn->setText(info.message);
	switch (info.type)
	{
	case rw::rqw::WarningType::Error:
		dlgWarn->setTitle("错误");
		break;
	case rw::rqw::WarningType::Warning:
		dlgWarn->setTitle("警告");
		break;
	case rw::rqw::WarningType::Info:
		dlgWarn->setTitle("信息");
		break;
	default:
		dlgWarn->setTitle("未知");
		break;
	}


	dlgWarn->show();
#endif
}

void WarningModule::onDlgWarningAccept()
{
	warningInfoProcessThread->isProcessingWarn = false;
	warningInfoProcessThread->isProcessFinishWarn = true;
}
