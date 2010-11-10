#include <QtGui>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include "yast.h"
#include "constants.h"


Yast::Yast()
{

	// create context menu
	QMenu *menu = new QMenu;
	enableYastAction = new QAction("Enable WebYaST", menu);
	enableYastAction->setCheckable(true);
	menu->addAction(enableYastAction);
	connect(enableYastAction, SIGNAL(triggered()), this, SLOT( slotEnableYast()));

	runBrowserAction = new QAction("Start WebYaST Browser", menu);
  	connect(runBrowserAction, SIGNAL(triggered()), this, SLOT( slotRunBrowser()));

	if ( isFirefoxAvailable() )
		menu->addAction(runBrowserAction);

	menu->addAction("&Quit", qApp, SLOT( quit () ));
	
	// create system tray 
	tray = new QSystemTrayIcon();
	tray->setContextMenu(menu);
	tray->setIcon(QIcon(WEBYAST_DOWN_ICON));
	tray->show();


	// create status updater
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(slotUpdateStatus()));
	timer->start(UPDATE_INTERVAL);


	slotUpdateStatus();
}


void Yast::slotUpdateStatus()
{
	if ( isYastRunning() )
	{
		tray->setIcon(QIcon(WEBYAST_UP_ICON)); 
		enableYastAction->setChecked(true);
		runBrowserAction->setEnabled(true);
	}
	else
	{
		tray->setIcon(QIcon(WEBYAST_DOWN_ICON));
		enableYastAction->setChecked(false);
		runBrowserAction->setEnabled(false);
	}
}


bool Yast::isYastRunning()
{
	return ( 0 == system( WEBYAST_CHECK_CMD ) ); 
}


void Yast::slotRunBrowser()
{
	QProcess* helperprocess = new QProcess(this);
        connect( helperprocess, SIGNAL(finished(int, QProcess::ExitStatus)), SLOT(slotHelperFinished(int, QProcess::ExitStatus)));
        connect( helperprocess, SIGNAL(error(QProcess::ProcessError)), SLOT(slotHelperError( QProcess::ProcessError )));
	helperprocess->start(QString(BROWSER_CMD) + QString(" ") + QString(BROWSER_URL) );
}


void Yast::slotEnableYast()
{
	QProcess* helperprocess = new QProcess(this);
        connect( helperprocess, SIGNAL(finished(int, QProcess::ExitStatus)), SLOT(slotHelperFinished(int, QProcess::ExitStatus)));
        connect( helperprocess, SIGNAL(error(QProcess::ProcessError)), SLOT(slotHelperError( QProcess::ProcessError )));

	if (enableYastAction->isChecked())
        	helperprocess->start(WEBYAST_UP_CMD);
	else
	        helperprocess->start(WEBYAST_DOWN_CMD);

	slotUpdateStatus();
}



void Yast::slotHelperFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	if ( QProcess::CrashExit == exitStatus )
	{
		QMessageBox::critical(this,"Error running process.", "The helper process crashed.");
		return;
	}

        qDebug() << ". helper process finished:";
        qDebug() << "  helper exit code: " << exitCode;
        qDebug() << "  helper exit status: " << exitStatus;
}


void Yast::slotHelperError( QProcess::ProcessError error  )
{
	QString reason;
	if ( QProcess::FailedToStart == error )
		reason = "The process failed to start.";
		
	QMessageBox::critical(this,"Error running process.", "An error happend while running a helper process. " + reason);
}

bool Yast::isFirefoxAvailable()
{
	QFile file(BROWSER_CMD);
	return file.exists();

}


#include "yast.moc"