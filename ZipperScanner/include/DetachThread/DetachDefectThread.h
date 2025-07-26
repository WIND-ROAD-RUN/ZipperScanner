#pragma once

#include <atomic>
#include<QThread>

#include"rqw_LabelWarning.h"
#include"dsl_PriorityQueue.hpp"

#include"Utilty.hpp"
#include"GlobalStruct.hpp"


class DetachDefectThreadZipper : public QThread
{
	Q_OBJECT
public:
	std::atomic_bool isProcessing{ false };
	std::atomic_bool isProcessFinish{ false };
public:
	explicit DetachDefectThreadZipper(QObject* parent = nullptr);

	~DetachDefectThreadZipper() override;

	void startThread();

	void stopThread();

	void processQueue(std::unique_ptr<ThreadSafeMinHeap>& queue);

protected:
	void run() override;
private:
	std::atomic<bool> running; // 使用原子变量保证线程安全
};
