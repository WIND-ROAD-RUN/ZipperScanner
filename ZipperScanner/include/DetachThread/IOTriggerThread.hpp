#pragma once

#include <QThread>

class IOTriggerThread : public QThread
{
	Q_OBJECT
public:
	std::atomic_bool isProcessing{ false };
	std::atomic_bool isProcessFinish{ false };
public:
	explicit IOTriggerThread(QObject* parent = nullptr);

	~IOTriggerThread() override;

	void startThread();

	void stopThread();
protected:
	void run() override;
public:
	std::atomic<bool> running; 
};
