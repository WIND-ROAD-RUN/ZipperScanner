#include "RuntimeInfoModule.hpp"

#include "Modules.hpp"

bool RuntimeInfoModule::build()
{
	detachUtiltyThread = std::make_unique<DetachUtiltyThread>(this);
	monitorProduceLengthThread = std::make_unique<MonitorProduceLengthThread>(this);
	return true;
}

void RuntimeInfoModule::destroy()
{
	if (detachUtiltyThread)
	{
		detachUtiltyThread.reset();
	}
	if (monitorProduceLengthThread)
	{
		monitorProduceLengthThread.reset();
	}
}

void RuntimeInfoModule::start()
{
	if (detachUtiltyThread)
	{
		detachUtiltyThread->startThread();
	}
	if (monitorProduceLengthThread)
	{
		monitorProduceLengthThread->startThread();
	}
}

void RuntimeInfoModule::stop()
{
	if (detachUtiltyThread)
	{
		detachUtiltyThread->stopThread();
		detachUtiltyThread->wait();
	}
}
