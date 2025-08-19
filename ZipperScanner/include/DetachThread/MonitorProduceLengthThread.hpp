#pragma once

#include <QThread>
#include <atomic>

#include<Utilty.hpp>

#include "ime_ModelEngine.h"

class MonitorProduceLengthThread : public QThread
{
	Q_OBJECT
public:
	std::atomic_bool isProcessing{ false };
	std::atomic_bool isProcessFinish{ false };
private:
	std::atomic<bool> running;
public:
	explicit MonitorProduceLengthThread(QObject* parent = nullptr);

	~MonitorProduceLengthThread() override;

	void startThread();

	void stopThread();

protected:
	void run() override;
public:
	std::atomic<double> currentPulse;
signals:
	void finishProduce();
};


