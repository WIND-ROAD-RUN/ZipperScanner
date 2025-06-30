#include "DetachDefectThread.h"

DetachDefectThreadZipper::DetachDefectThreadZipper(QObject* parent)
{

}

DetachDefectThreadZipper::~DetachDefectThreadZipper()
{
	stopThread();
	wait(); // 等待线程安全退出
}

void DetachDefectThreadZipper::startThread()
{
	running = true;
	if (!isRunning()) {
		start(); // 启动线程
	}
}

void DetachDefectThreadZipper::stopThread()
{
	running = false; // 停止线程
}

void DetachDefectThreadZipper::processQueue1(std::unique_ptr<rw::dsl::ThreadSafeDHeap<float, float>>& queue, float minDefectLocation)
{
	auto& globalStruct = GlobalStructDataZipper::getInstance();
	auto& setConfig = globalStruct.setConfig;

	try
	{
		float nowLocation = queue->peek();
		if (nowLocation > 0)
		{
			queue->top();
		}
		auto tifeijuli1 = setConfig.tifeijuli1;
		auto tifeichixushijian1 = setConfig.tiFeiChiXuShiJian1;
		minDefectLocation = minDefectLocation * globalStruct.setConfig.xiangSuDangLiang1;
		if (abs(nowLocation - minDefectLocation) > tifeijuli1)
		{
			// 停止电机
			bool isStop = globalStruct.zmotion.stopAllAxis();

			if (!isStop)
			{
				//QMessageBox::warning(this, "警告", "停止电机失败!");
			}
			//冲孔
			bool isSuccess = globalStruct.zmotion.setIOOut(ControlLines::chongkongOUT,true);

			emit findIsBad(1);

			// 等待冲孔完毕
			QThread::msleep(tifeichixushijian1);

			// 启动电机
			auto isAxisRun = globalStruct.zmotion.setAxisRun(0, -1);
			if (!isAxisRun)
			{
				//QMessageBox::warning(this, "警告", "启动电机失败!");
			}
		}
	}
	catch (const std::runtime_error&)
	{
		return;
	}
}

void DetachDefectThreadZipper::processQueue2(std::unique_ptr<rw::dsl::ThreadSafeDHeap<float, float>>& queue, float minDefectLocation)
{
	auto& globalStruct = GlobalStructDataZipper::getInstance();
	auto& setConfig = globalStruct.setConfig;

	try
	{
		float nowLocation = queue->peek();
		if (nowLocation > 0)
		{
			queue->top();
		}
		auto tifeijuli2 = setConfig.tifeijuli2;
		auto tifeichixushijian2 = setConfig.tiFeiChiXuShiJian2;
		minDefectLocation = minDefectLocation * globalStruct.setConfig.xiangSuDangLiang2;
		if (abs(nowLocation - minDefectLocation) > tifeijuli2)
		{
			// 停止电机
			bool isStop = globalStruct.zmotion.stopAllAxis();

			if (!isStop)
			{
				//QMessageBox::warning(this, "警告", "停止电机失败!");
			}
			//冲孔
			bool isSuccess = globalStruct.zmotion.setIOOut(ControlLines::chongkongOUT, true);

			emit findIsBad(2);

			// 等待冲孔完毕
			QThread::msleep(tifeichixushijian2);

			// 启动电机
			auto isAxisRun = globalStruct.zmotion.setAxisRun(0, -1);
			if (!isAxisRun)
			{
				//QMessageBox::warning(this, "警告", "启动电机失败!");
			}
		}
	}
	catch (const std::runtime_error&)
	{
		return;
	}
}

void DetachDefectThreadZipper::run()
{
	auto& globalStruct = GlobalStructDataZipper::getInstance();
	auto& priorityQueue1 = globalStruct.priorityQueue1;
	auto& priorityQueue2 = globalStruct.priorityQueue2;

	while (running) {
		QThread::msleep(10);
		processQueue1(priorityQueue1,globalStruct.minDefectLocation1);
		processQueue2(priorityQueue2,globalStruct.minDefectLocation2);
	}
}
