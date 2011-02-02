#include <QApplication>
#include <QSystemTrayIcon>
#include <QtGui>
#include <QSessionManager>
#include "yast.h"
#include "app.h"

int main(int argc, char *argv[])
{

	//QSessionManager manager;
	//manager.setRestartHint(QSessionManager::RestartNever)


	App app(argc, argv);
	App::setQuitOnLastWindowClosed(false);
	Yast yast;

	return app.exec();
}

