#include "EliminateModule.hpp"

bool EliminateModule::build()
{
	priorityQueue = std::make_unique<ThreadSafeMinHeap>();
	detachDefectThread = std::make_unique<DetachDefectThreadZipper>(this);
	return true;
}

void EliminateModule::destroy()
{
	if (detachDefectThread)
	{
		detachDefectThread.reset();
	}
	if (priorityQueue)
	{
		priorityQueue.reset();
	}
}

void EliminateModule::start()
{
	if (detachDefectThread)
	{
		detachDefectThread->startThread();
	}
}

void EliminateModule::stop()
{
	if (detachDefectThread)
	{
		detachDefectThread->stopThread();
		detachDefectThread->wait();
	}
}
