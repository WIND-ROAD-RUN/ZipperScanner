#include "CameraModule.hpp"

#include <QRegularExpression>

#include "GlobalStruct.hpp"
#include "Modules.hpp"
#include"rqw_CameraObjectThread.hpp"


CameraModule::CameraModule()
{
}

CameraModule::~CameraModule()
{
}

std::vector<BuildError> CameraModule::build()
{
	std::vector<BuildError> errorList;
	if (!build_camera1())
	{
		errorList.emplace_back(Camera1Error);
	}
	if (!build_camera2())
	{
		errorList.emplace_back(Camera2Error);
	}
	_buildResults = errorList;
	return std::vector<BuildError>();
}

void CameraModule::destroy()
{
	destroy_camera1();
	destroy_camera2();
}

void CameraModule::start()
{
	if (camera1)
	{
		camera1->startMonitor();
	}
	if (camera2)
	{
		camera2->startMonitor();
	}
}

void CameraModule::stop()
{
	if (camera1)
	{
		camera1->stopMonitor();
	}
	if (camera2)
	{
		camera2->stopMonitor();
	}
}

bool CameraModule::build_camera1()
{
	auto& zipperScannerConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;

	auto cameraList = rw::rqw::CheckCameraList();
	auto cameraMetaData1 = cameraMetaDataCheck(Utility::cameraIp1, cameraList);

	auto& globalDataGeneralConfig = zipperScannerConfig;
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;

	if (cameraMetaData1.ip != "0")
	{
		try
		{
			camera1 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
			// 相机触发回调
			camera1->callBackForImgReadyBefore = [](rw::rqw::MatInfo& matInfo){
				auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
				matInfo.customField["LocCallBack"]= static_cast<float>(zmotion->getModbus(2, 1));
				};
			camera1->initCamera(cameraMetaData1, rw::rqw::CameraObjectTrigger::Hardware);
			camera1->setTriggerState(true);
			camera1->cameraIndex = 1;
			camera1->setFrameRate(50);
			camera1->setHeartbeatTime(5000);
			if (globalDataGeneralConfig.qiangGuang)
			{
				camera1->setExposureTime(static_cast<size_t>(setConfig.qiangBaoGuang1));
				camera1->setGain(static_cast<size_t>(setConfig.qiangZengYi1));
			}
			else if (globalDataGeneralConfig.zhongGuang)
			{
				camera1->setExposureTime(static_cast<size_t>(setConfig.zhongBaoGuang1));
				camera1->setGain(static_cast<size_t>(setConfig.zhongZengYi1));
			}
			else if (globalDataGeneralConfig.ruoGuang)
			{
				camera1->setExposureTime(static_cast<size_t>(setConfig.ruoBaoGuang1));
				camera1->setGain(static_cast<size_t>(setConfig.ruoZengYi1));
			}
			QObject::connect(camera1.get(), &rw::rqw::CameraPassiveThread::frameCaptured,
				this, &CameraModule::onFrameCaptured);
			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}

	return false;
}

bool CameraModule::build_camera2()
{
	auto& zipperScannerConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;

	auto cameraList = rw::rqw::CheckCameraList();
	auto cameraMetaData2 = cameraMetaDataCheck(Utility::cameraIp2, cameraList);
	auto& globalDataGeneralConfig = zipperScannerConfig;
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	if (cameraMetaData2.ip != "0")
	{
		try
		{
			camera2 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
			// 相机触发回调
			camera2->callBackForImgReadyBefore = [](rw::rqw::MatInfo& matInfo) {
				auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
				matInfo.customField["LocCallBack"] = static_cast<float>(zmotion->getModbus(6, 1));
				};
			camera2->initCamera(cameraMetaData2, rw::rqw::CameraObjectTrigger::Hardware);
			camera2->setTriggerState(true);
			camera2->cameraIndex = 2;
			camera2->setFrameRate(50);
			camera2->setHeartbeatTime(5000);
			if (globalDataGeneralConfig.qiangGuang)
			{
				camera2->setExposureTime(static_cast<size_t>(setConfig.qiangBaoGuang2));
				camera2->setGain(static_cast<size_t>(setConfig.qiangZengYi2));
			}
			else if (globalDataGeneralConfig.zhongGuang)
			{
				camera2->setExposureTime(static_cast<size_t>(setConfig.zhongBaoGuang2));
				camera2->setGain(static_cast<size_t>(setConfig.zhongZengYi2));
			}
			else if (globalDataGeneralConfig.ruoGuang)
			{
				camera2->setExposureTime(static_cast<size_t>(setConfig.ruoBaoGuang2));
				camera2->setGain(static_cast<size_t>(setConfig.ruoZengYi2));
			}
			QObject::connect(camera2.get(), &rw::rqw::CameraPassiveThread::frameCaptured,
				this, &CameraModule::onFrameCaptured);
			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}
	return false;
}

void CameraModule::destroy_camera1()
{
	camera1.reset();
}

void CameraModule::destroy_camera2()
{
	camera2.reset();
}

bool CameraModule::isTargetCamera(const QString& cameraIndex, const QString& targetName)
{
	QRegularExpression regex(R"((\d+)\.(\d+)\.(\d+)\.(\d+))");
	QRegularExpressionMatch match = regex.match(targetName);

	if (match.hasMatch()) {
		auto matchString = match.captured(3);

		return cameraIndex == matchString;
	}

	return false;
}

rw::rqw::CameraMetaData CameraModule::cameraMetaDataCheck(const QString& cameraIndex,
	const QVector<rw::rqw::CameraMetaData>& cameraInfo)
{
	for (const auto& cameraMetaData : cameraInfo) {
		if (isTargetCamera(cameraIndex, cameraMetaData.ip)) {
			return cameraMetaData;
		}
	}
	rw::rqw::CameraMetaData error;
	error.ip = "0";
	return error;
}

bool CameraModule::onBuildCamera(int index)
{
	switch (index)
	{
	case 1:
		return build_camera1();
	case 2:
		return build_camera2();
	default:
		return false;
	}
}

void CameraModule::onDestroyCamera(int index)
{
	switch (index)
	{
	case 1:
		destroy_camera1();
		break;
	case 2:
		destroy_camera2();
		break;
	default:
		break;
	}
}

void CameraModule::onStartCamera(int index)
{
	switch (index)
	{
	case 1:
		if (camera1)
		{
			camera1->startMonitor();
		}
		break;
	case 2:
		if (camera2)
		{
			camera2->startMonitor();
		}
		break;
	default:
		break;
	}
}

void CameraModule::onFrameCaptured(rw::rqw::MatInfo frame, size_t index)
{
	switch (index)
	{
		case 1:
			emit frameCaptured1(frame, index);
			break;
		case 2:
			emit frameCaptured2(frame, index);
			break;
		default:
			break;
	}
}
