#include <QMessageBox>

#include "ZipperScanner.h"
#include <QtWidgets/QApplication>
#include "rqw_RunEnvCheck.hpp"
#include "Utilty.hpp"
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	ZipperScanner w;
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
#ifdef NDEBUG
	w.showFullScreen();
#else
	w.show();
#endif

	return a.exec();
}