#pragma once

#include"IModule.hpp"
#include <QObject>
#include "DetachDefectThread.h"

class EliminateModule
	: public QObject, public IModule<bool>
{
	Q_OBJECT
public:
	bool build() override;
	void destroy() override;
	void start() override;
	void stop() override;
public:
	//std::unique_ptr<rw::dsl::ThreadSafeHeap<DefectInfoForPriorityQueue>> productPriorityQueue1;
	//std::unique_ptr<rw::dsl::ThreadSafeHeap<DefectInfoForPriorityQueue>> productPriorityQueue2;
public:
	//std::unique_ptr<DetachDefectThreadHandleScanner> detachDefectThread{ nullptr };

public:
	float lastLocation1{ 0.0f };
	float lastLocation2{ 0.0f };
};