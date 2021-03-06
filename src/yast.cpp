/* 
 * Copyright (c) 2010-2011 SUSE LINUX Products GmbH.
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation either version 2 of the 
 * license or version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, contact SUSE LINUX Products GmbH.
 *
 * To contact SUSE about this file by physical or electronic mail,
 * you may find current contact information at www.suse.com 
 *
 */

#include <QtGui>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QDesktopServices>
#include <QDebug>
#include <QFile>
#include "yast.h"
#include "constants.h"


Yast::Yast()
{

	// create context menu
	QMenu *menu = new QMenu;
	enableYastAction = new QAction("Enable WebYaST", menu);
	enableYastAction->setCheckable(true); menu->addAction(enableYastAction);
	connect(enableYastAction, SIGNAL(triggered()), this, SLOT( slotEnableYast()));

	runBrowserAction = new QAction("Start WebYaST Browser", menu);
  	connect(runBrowserAction, SIGNAL(triggered()), this, SLOT( slotRunBrowser()));
	menu->addAction(runBrowserAction);
	menu->addAction("&Quit", qApp, SLOT( quit () ));
	
	// create system tray 
	tray = new QSystemTrayIcon();
	tray->setContextMenu(menu);
	tray->setIcon(QIcon::fromTheme(QString(WEBYAST_DOWN_ICON), QIcon(QString(WEBYAST_ICON_PATH) + QString(WEBYAST_DOWN_ICON))));
	tray->show();

	// create status updater
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(slotUpdateStatus()));
	timer->start(UPDATE_INTERVAL);

	connect (tray, SIGNAL (activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slotTrayActivated ( QSystemTrayIcon::ActivationReason)));

	QHBoxLayout *layout = new QHBoxLayout;
	this->setLayout(layout);
	setWindowTitle("WebYaST");
	setWindowIcon(QIcon::fromTheme((WEBYAST_UP_ICON), QIcon(QString(WEBYAST_ICON_PATH) + QString(WEBYAST_UP_ICON))));

	slotUpdateStatus();
	hide();
}


void Yast::slotTrayActivated ( QSystemTrayIcon::ActivationReason reason )
{
	if ( ( QSystemTrayIcon::Trigger == reason ) && enableYastAction->isChecked() )
		slotRunBrowser();
}


void Yast::slotUpdateStatus()
{
	if ( isYastRunning() )
	{
		tray->setIcon(QIcon::fromTheme((WEBYAST_UP_ICON), QIcon(QString(WEBYAST_ICON_PATH) + QString(WEBYAST_UP_ICON)))); 
		enableYastAction->setChecked(true);
		runBrowserAction->setEnabled(true);
	}
	else
	{
		tray->setIcon(QIcon::fromTheme((WEBYAST_DOWN_ICON), QIcon(QString(WEBYAST_ICON_PATH) + QString(WEBYAST_DOWN_ICON))));
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
	QString cmd;
	
	// figure out which browser is available and pick one 
	if ( isChromeAvailable() )
		cmd = CHROME_CMD;
	else if ( isChromeiumAvailable() )
		cmd = CHROMIUM_CMD;
	else if ( isFirefoxAvailable() )
		cmd = FIREFOX_CMD;

	if (!cmd.isEmpty())
	{
		QProcess* helperprocess = new QProcess(this);
	        connect( helperprocess, SIGNAL(finished(int, QProcess::ExitStatus)), SLOT(slotHelperFinished(int, QProcess::ExitStatus)));
	        connect( helperprocess, SIGNAL(error(QProcess::ProcessError)), SLOT(slotHelperError( QProcess::ProcessError )));
		helperprocess->start(cmd);
	}
	else
	{
		QDesktopServices::openUrl ( QUrl(BROWSER_URL) );
	}
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

        //qDebug() << ". helper process finished:";
        //qDebug() << "  helper exit code: " << exitCode;
        //qDebug() << "  helper exit status: " << exitStatus;
}


void Yast::slotHelperError( QProcess::ProcessError error  )
{
	QString reason;
	if ( QProcess::FailedToStart == error )
		reason = "The process failed to start.";
		
	QMessageBox::critical(this,"Error running process.", "An error happend while running a helper process. " + reason);
}


bool Yast::isApplicationAvailable(QString location)
{
	QFile file(location);
	return file.exists();
}

bool Yast::isFirefoxAvailable()
{
	return isApplicationAvailable(FIREFOX_BIN);

}

bool Yast::isChromeAvailable()
{
	return isApplicationAvailable(CHROME_BIN);

}

bool Yast::isChromeiumAvailable()
{
	return isApplicationAvailable(CHROMIUM_BIN);

}





#include "yast.moc"
