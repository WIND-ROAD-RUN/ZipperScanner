#include <QMessageBox>

#include "ZipperScanner.h"
#include <QtWidgets/QApplication>
#include "Modules.hpp"
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	Modules::check();
	Modules::getInstance().build(); 
	ZipperScanner w;
	Modules::getInstance().uiModule._zipperScanner = &w;
	Modules::getInstance().connect();
	Modules::getInstance().start();
	
#ifdef NDEBUG
	w.showFullScreen();
#else
	w.show();
#endif

	return a.exec();
}