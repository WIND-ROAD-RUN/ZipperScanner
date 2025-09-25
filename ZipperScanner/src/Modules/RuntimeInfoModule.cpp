#include "RuntimeInfoModule.hpp"

#include "Modules.hpp"

bool RuntimeInfoModule::build()
{
	detachUtiltyThread = std::make_unique<DetachUtiltyThread>(this);
	return true;
}

void RuntimeInfoModule::destroy()
{
	if (detachUtiltyThread)
	{
		detachUtiltyThread.reset();
	}
}

void RuntimeInfoModule::start()
{
	if (detachUtiltyThread)
	{
		detachUtiltyThread->startThread();
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
