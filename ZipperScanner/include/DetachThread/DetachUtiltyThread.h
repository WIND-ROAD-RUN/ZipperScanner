#pragma once

#include <QThread>
#include <atomic>
#include"rqw_LabelWarning.h"

class DetachUtiltyThread : public QThread
{
	Q_OBJECT
public:
	std::atomic_bool isProcessing{ false };
	std::atomic_bool isProcessFinish{ false };
public:
	explicit DetachUtiltyThread(QObject* parent = nullptr);

	~DetachUtiltyThread() override;

	void startThread();

	void stopThread();
protected:
	void run() override;
private:
	void CalculateRealtimeInformation(size_t s);
private:
	void processShutdownIO(size_t s);
private:
	bool lastIsShutDown{ false };
	int shutdownCount{ 0 };
signals:
	void updateStatisticalInfo();
signals:
	void shutdownComputer(int time);
private:
	std::atomic<bool> running; // 使用原子变量保证线程安全
};
