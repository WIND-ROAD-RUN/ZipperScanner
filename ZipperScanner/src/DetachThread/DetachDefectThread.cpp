#include "DetachDefectThread.h"

#include "Modules.hpp"

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

void DetachDefectThreadZipper::processQueue(std::unique_ptr<ThreadSafeMinHeap>& queue)
{
	auto& globalStruct = GlobalData::getInstance();
	auto& statisticalInfo = Modules::getInstance().runtimeInfoModule.statisticalInfo;
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;

	try
	{
		float nowLocation = 0;
		bool isget = false;
		nowLocation = globalStruct.zmotion.getAxisLocation(0, isget);

		float minlocation = 0;

		//如果拉带长度超过设定值则停机
		/*if (abs(globalStruct.startLocation- nowLocation)> globalStruct.setConfig.shedingladaichangdu*1000)
		{
			globalStruct.zmotion.stopAllAxis();

		}*/



		queue->tryGetMin(minlocation);
		if (!minlocation)
		{
			return;
		}

		//如果有瑕疵直接降速
		//std::cout << "jiansulocation" << globalStruct.zmotion.getAxisLocation(0, isget) << std::endl;
		
		auto isshoudongsudu = globalStruct.zmotion.setAxisRunSpeed(0,setConfig.shoudongsudu);
		

		auto chongkongshijian = setConfig.chongkongshijian*1000;
		auto yanshiziqi = setConfig.yanshiziqi * 1000;
		auto yanshichongkong = setConfig.yanshichongkong * 1000;
		if (nowLocation - minlocation > 0)
		{
			std::cout << "|---------BEGIN----------|" << std::endl;
			// 停止电机
			bool isStop = globalStruct.zmotion.stopAllAxis();

			QThread::msleep(yanshichongkong);
			if (!isStop)
			{
				//QMessageBox::warning(this, "警告", "停止电机失败!");
			}
			//冲孔
			bool isSuccess = globalStruct.zmotion.setIOOut(ControlLines::chongkongOUT, true);

			queue->tryPopMin(minlocation);

			// 等待冲孔完毕
			QThread::msleep(chongkongshijian);

			isSuccess = globalStruct.zmotion.setIOOut(ControlLines::chongkongOUT, false);
			QThread::msleep(yanshiziqi);
			++statisticalInfo.punchCount;
			std::cout << "stoplocation:" << minlocation << std::endl;

			std::cout << "queue->size() before delete:" << queue->size() << std::endl;
			auto queueSize = queue->size();
			for (size_t i = 0; i < queueSize; i++)
			{
				float location = 0;
				queue->tryGetMin(location);
				float nowlocation = globalStruct.zmotion.getAxisLocation(0, isget);

				if (abs(location - nowlocation) <30)
				{
					queue->tryPopMin(location);
					std::cout << "delete location:"  <<location <<std::endl;
				}


			}

			std::cout << "queue->size() after delete:" << queue->size() << std::endl;



			if (generalConfig.isStart == true)
			{
				// 启动电机
				auto iszidongladaisudu = globalStruct.zmotion.setAxisRunSpeed(0, setConfig.zidongladaisudu);

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

			std::cout << "|----------END-----------|" << std::endl;
		}
	
	
	
	
	
	}
	catch (const std::runtime_error&)
	{
		return;
	}
}

void DetachDefectThreadZipper::run()
{
	auto& globalStruct = GlobalData::getInstance();
	auto& priorityQueue = globalStruct.priorityQueue;

	while (running) {
		QThread::msleep(1);

		processQueue(priorityQueue);
	}
}
