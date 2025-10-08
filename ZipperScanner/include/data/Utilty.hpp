#pragma once

#include <QString>

#include "imgPro_ImageProcessUtilty.hpp"
#include "ZipperScanner.h"

QImage cvMatToQImage(const cv::Mat& mat);

QPixmap cvMatToQPixmap(const cv::Mat& mat);

using Time = std::chrono::system_clock::time_point;

struct Utility
{
	static QString cameraIp1;
	static QString cameraIp2;
	static QString zmotionIp;
};

struct WarningId
{
	static constexpr int cairPressureAlarm = 0;
	static constexpr int ccameraDisconnectAlarm1 = 1;
	static constexpr int ccameraDisconnectAlarm2 = 2;
	static constexpr int cworkTrigger1 = 3;
	static constexpr int cworkTrigger2 = 4;
	static constexpr int csportControlAlarm = 5;
	static constexpr int clongTermIdleOperationAlarm = 6;
	static constexpr int cwork1AndWork2EmptyAlarm = 7;
};

struct ControlLines
{
public:
	static size_t qidonganniuIn ;
	static size_t jitingIn ;
	static size_t lalianlawanIn ;
	static size_t guanjiIn;
public:
	static size_t chongkongOUT ;
	static size_t tuojiOut ;
	static size_t xiangjichufaOut1;
	static size_t xiangjichufaOut2;
};

struct ClassId
{
	static constexpr int minNum = 0;
	static constexpr int Queya = 0;
	static constexpr int Tangshang = 1;
	static constexpr int Zangwu = 2;
	static constexpr int Suoxiao = 3;
	static constexpr int Huawen = 4;
	static constexpr int Yuan = 5;
	static constexpr int Huapo = 6;
	static constexpr int Duanxian = 7;
	static constexpr int maxNum = 7;
	static constexpr int indexCount = 8;
	static std::unordered_map<rw::imgPro::ClassId, rw::imgPro::ClassIdName> classIdNameMap;
	static std::vector<rw::imgPro::ClassId> classids;


	static constexpr int Extra5 = 8;
	static constexpr int Extra6 = 9;
	static constexpr int Extra7 = 10;
	static constexpr int Extra8 = 11;
};

inline struct GlobalPath
{
public:
	QString projectHome = R"(D:\zfkjData\ZipperScanner\)";
public:
	QString configRootPath = projectHome + R"(config\)";
	QString modelRootPath = projectHome + R"(model\)";
	QString generalConfigPath = configRootPath + R"(generalConfig.xml)";
	QString scoreConfigPath = configRootPath + R"(scoreConfig.xml)";
	QString setConfigPath = configRootPath + R"(setConfig.xml)";
	QString dlgExposureTimeSetFilePath = configRootPath + R"(dlgExposureTimeSet.xml)";
	QString modelPath = modelRootPath + R"(lalian.engine)";
public:
	QString imageSaveRootPath = projectHome + R"(SavedImages\)";
	QString testImgDirPath= R"(D:\zfkjDevelopment\ImgStorage\lalian\20250607)";
}globalPath;
