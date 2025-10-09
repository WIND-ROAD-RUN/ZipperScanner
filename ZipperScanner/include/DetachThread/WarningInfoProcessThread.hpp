#pragma once

#include <QThread>
#include <atomic>

#include "rqw_LabelWarning.h"
#include "WarnUtilty.hpp"

class WarningInfoProcessThread : public QThread
{
	Q_OBJECT
public:
	WarningInfoProcessThread(QObject* parent);
	~WarningInfoProcessThread();
public:
	rw::rqw::LabelWarning* warningLabel{ nullptr };
public:
	std::atomic_bool isProcessingWarn{ false };
	std::atomic_bool isProcessFinishWarn{ false };

	void startThread();

	void stopThread();

protected:
	void run() override;
private:
	void processWarningInfo(size_t s);
	void processOneWarnGet(rw::rqw::WarningInfo& info);
	void processOneWarnFinsh(rw::rqw::WarningInfo& info);
	void openWarnAlarm(const rw::rqw::WarningInfo& info);
	void closeWarnAlarm(const rw::rqw::WarningInfo& info);
signals:
	void showDlgWarn(rw::rqw::WarningInfo info);
private:
	std::atomic<bool> running;
};
