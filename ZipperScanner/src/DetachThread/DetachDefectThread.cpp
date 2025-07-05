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

void DetachDefectThreadZipper::processQueue1(std::unique_ptr<ThreadSafeMinHeap>& queue, float minDefectLocation)
{
	auto& globalStruct = GlobalStructDataZipper::getInstance();
	auto& setConfig = globalStruct.setConfig;

	try
	{
		float nowLocation = 0;
		bool isget = false;
		nowLocation = globalStruct.zmotion.getAxisLocation(0, isget);

		float minlocation = 0;

		queue->tryGetMin(minlocation);
		if (!minlocation)
		{
			return;
		}

		//如果有瑕疵直接降速
		//std::cout << "jiansulocation" << globalStruct.zmotion.getAxisLocation(0, isget) << std::endl;
		
		auto isshoudongsudu = globalStruct.zmotion.setAxisRunSpeed(0,globalStruct.setConfig.shoudongsudu);
		

		auto tifeijuli1 = setConfig.tifeijuli1;
		auto tifeichixushijian1 = setConfig.tiFeiChiXuShiJian1;
		if (abs(abs(nowLocation)-  abs(minlocation )) > tifeijuli1)
		{
			//std::cout << "stopsendlocation" << globalStruct.zmotion.getAxisLocation(0, isget) << std::endl;

			// 停止电机
			bool isStop = globalStruct.zmotion.stopAllAxis();

			if (!isStop)
			{
				//QMessageBox::warning(this, "警告", "停止电机失败!");
			}
			//冲孔
			bool isSuccess = globalStruct.zmotion.setIOOut(ControlLines::chongkongOUT, true);

			queue->tryPopMin(nowLocation);

			emit findIsBad(1);

			// 等待冲孔完毕
			QThread::msleep(tifeichixushijian1);

			isSuccess = globalStruct.zmotion.setIOOut(ControlLines::chongkongOUT, false);
			QThread::msleep(1000);
			//std::cout << "stoplocation" << globalStruct.zmotion.getAxisLocation(0, isget) << std::endl;

			//删除重复location
			for (size_t i = 0; i < queue->size(); i++)
			{
				float location = 0;
				queue->tryGetMin(location);
				float nowlocation = globalStruct.zmotion.getAxisLocation(0, isget);
				//std::cout << "nowlocation" << nowlocation << std::endl;
				//std::cout << "location" << location << std::endl;

				if (abs(location+ tifeijuli1 - nowlocation) <30)
				{

					queue->tryPopMin(location);
				}


			}



			if (globalStruct.generalConfig.isStart == true)
			{
				// 启动电机
				auto iszidongladaisudu = globalStruct.zmotion.setAxisRunSpeed(0, globalStruct.setConfig.zidongladaisudu);

				auto isAxisRun = globalStruct.zmotion.setAxisRun(0, -1);
				if (!isAxisRun)
				{
					//QMessageBox::warning(this, "警告", "启动电机失败!");
				}
			}
			else
			{
				isStop = globalStruct.zmotion.stopAllAxis();
			}
		}
	}
	catch (const std::runtime_error&)
	{
		return;
	}
}

void DetachDefectThreadZipper::processQueue2(std::unique_ptr<ThreadSafeMinHeap>& queue, float minDefectLocation)
{
	auto& globalStruct = GlobalStructDataZipper::getInstance();
	auto& setConfig = globalStruct.setConfig;

	try
	{
		float nowLocation = 0;
		queue->tryGetMin(nowLocation);
		if (nowLocation > 0)
		{
			queue->tryPopMin(nowLocation);
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
		QThread::msleep(0);
		processQueue1(priorityQueue1, globalStruct.maxDefectLocation1);
		processQueue2(priorityQueue2, globalStruct.maxDefectLocation2);
	}
}
