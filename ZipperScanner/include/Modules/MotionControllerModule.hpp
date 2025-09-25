#pragma once

#include <QObject>

#include"IModule.hpp"
#include"rqw_ZMotion.hpp"
#include"rqw_MonitorMotionIO.hpp"

class MotionControllerModule
	:public QObject, public IModule<bool>
{
	Q_OBJECT
private:
	static constexpr int cmonitorMotionFrequency = 20;
public:
	MotionControllerModule() = default;
	~MotionControllerModule() override = default;
public:
	bool build() override;
	void destroy() override;
	void start() override;
	void stop() override;
public:
	std::shared_ptr<rw::rqw::ZMotion> zmotion{ nullptr };
	std::unique_ptr<rw::rqw::MonitorZMotionIOStateThread> monitorMotionIoStateThread{ nullptr };
signals:
	void DIState(size_t index, bool state);
	void DOState(size_t index, bool state);
public:
	bool isConnectMotion{ false };

	// 是否开启IO监控
	std::atomic_bool _isUpdateMonitorInfo{ false };
public slots:
	void getStopSignal();
};