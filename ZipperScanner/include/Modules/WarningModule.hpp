#pragma once

#include"IModule.hpp"
#include<QObject>

#include "WarningInfoProcessThread.hpp"
#include "WarnUtilty.hpp"

namespace rw::rqw
{
	class LabelWarning;
}

class DlgWarn;

class WarningModule
	:public QObject,public IModule<void>
{
	Q_OBJECT
public:
	void build() override;
	void destroy() override;
	void start() override;
	void stop() override;
public:
	DlgWarn* dlgWarn = nullptr;
	rw::rqw::LabelWarning* labelWarning = nullptr;
public:
	std::unique_ptr<WarningInfoProcessThread> warningInfoProcessThread = nullptr;
public:
	void addWarning(const rw::rqw::WarningInfo& message, int redDuration);
	void addWarning(const rw::rqw::WarningInfo& message, bool updateTimestampIfSame = true, int redDuration = 5000, int time = 10000);
public slots:
	void onShowDlgWarn(rw::rqw::WarningInfo info);
	void onDlgWarningAccept();
};
