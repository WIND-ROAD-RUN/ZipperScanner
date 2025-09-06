#include <QMessageBox>

#include "ZipperScanner.h"
#include <QtWidgets/QApplication>
#include "rqw_RunEnvCheck.hpp"
#include "Utilty.hpp"
#include "GlobalStruct.hpp"
#include "oso_func.hpp"
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

#pragma region running software check
	// 运行前检查
	if (!rw::rqw::RunEnvCheck::isSingleInstance("WetPapers.exe"))
	{
		QMessageBox::warning(nullptr, "提示", "请勿重复开启软件。");
		return -1;
	}
	if (rw::rqw::RunEnvCheck::isProcessRunning("MVS.exe"))
	{
		QMessageBox::warning(nullptr, "提示", "检测到海康威视软件正在运行，请先关闭后再启动本程序。");
		return -2;
	}
	if (rw::rqw::RunEnvCheck::isProcessRunning("BasedCam3.exe"))
	{
		QMessageBox::warning(nullptr, "提示", "检测到度申相机平台软件正在运行，请先关闭后再启动本程序。");
		return -3;
	}
	if (!rw::rqw::RunEnvCheck::isFileExist(globalPath.configRootPath))
	{
		QDir dir;
		dir.mkpath(globalPath.configRootPath);
	}
#pragma endregion

#pragma region check config file if format is error
	rw::oso::StorageContext storageContext(rw::oso::StorageType::Xml);

	{
		std::shared_ptr<rw::oso::ObjectStoreAssembly> loadData = nullptr;
		auto path = globalPath.generalConfigPath;
		try
		{
			if (QFile::exists(path)) {
				loadData = storageContext.loadSafe(path.toStdString());
				if (!loadData)
				{
					QFile::remove(path);
				}

				cdm::GeneralConfig config = *loadData;
			}
		}
		catch (std::runtime_error& e)
		{
			rw::oso::ObjectStoreAssembly newAssembly = cdm::GeneralConfig();
			if (loadData)
			{
				rw::oso::AssemblyMergeTool::Merge(newAssembly, *loadData);
				auto isSuccess = storageContext.saveSafe(newAssembly, path.toStdString());
				if (isSuccess)
				{
					qDebug() << "GeneralConfig.xml update success";
				}
			}
		}
	}

	{
		std::shared_ptr<rw::oso::ObjectStoreAssembly> loadData = nullptr;
		auto path = globalPath.scoreConfigPath;
		try
		{
			if (QFile::exists(path)) {
				loadData = storageContext.loadSafe(path.toStdString());
				if (!loadData)
				{
					QFile::remove(path);
				}

				cdm::ScoreConfig config = *loadData;
			}
		}
		catch (std::runtime_error& e)
		{
			rw::oso::ObjectStoreAssembly newAssembly = cdm::ScoreConfig();
			if (loadData)
			{
				rw::oso::AssemblyMergeTool::Merge(newAssembly, *loadData);
				auto isSuccess = storageContext.saveSafe(newAssembly, path.toStdString());
				if (isSuccess)
				{
					qDebug() << "ScoreConfig.xml update success";
				}
			}
		}
	}

	{
		std::shared_ptr<rw::oso::ObjectStoreAssembly> loadData = nullptr;
		auto path = globalPath.setConfigPath;
		try
		{
			if (QFile::exists(path)) {
				loadData = storageContext.loadSafe(path.toStdString());
				if (!loadData)
				{
					QFile::remove(path);
				}

				cdm::SetConfig config = *loadData;
			}
		}
		catch (std::runtime_error& e)
		{
			rw::oso::ObjectStoreAssembly newAssembly = cdm::SetConfig();
			if (loadData)
			{
				rw::oso::AssemblyMergeTool::Merge(newAssembly, *loadData);
				auto isSuccess = storageContext.saveSafe(newAssembly, path.toStdString());
				if (isSuccess)
				{
					qDebug() << "SetConfig.xml update success";
				}
			}
		}
	}

	{
		std::shared_ptr<rw::oso::ObjectStoreAssembly> loadData = nullptr;
		auto path = globalPath.dlgExposureTimeSetFilePath;
		try
		{
			if (QFile::exists(path)) {
				loadData = storageContext.loadSafe(path.toStdString());
				if (!loadData)
				{
					QFile::remove(path);
				}

				cdm::ZipperScannerDlgExposureTimeSet config = *loadData;
			}
		}
		catch (std::runtime_error& e)
		{
			rw::oso::ObjectStoreAssembly newAssembly = cdm::ZipperScannerDlgExposureTimeSet();
			if (loadData)
			{
				rw::oso::AssemblyMergeTool::Merge(newAssembly, *loadData);
				auto isSuccess = storageContext.saveSafe(newAssembly, path.toStdString());
				if (isSuccess)
				{
					qDebug() << "ZipperScannerDlgExposureTimeSetConfig.xml update success";
				}
			}
		}
	}
#pragma endregion

	ZipperScanner w;
	
#ifdef NDEBUG
	w.showFullScreen();
#else
	w.show();
#endif

	return a.exec();
}