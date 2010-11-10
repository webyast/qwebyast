#include <QApplication>
#include <QSystemTrayIcon>
#include <QtGui>
#include "yast.h"

int main(int argc, char *argv[])
{

	QApplication app(argc, argv);
	QApplication::setQuitOnLastWindowClosed(false);

	Yast yast;
	yast.hide();

	return app.exec();
}
