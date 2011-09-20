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


#ifndef YAST_H
#define YAST_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QProcess>



class Yast : public QDialog
{
	Q_OBJECT
public:
	Yast();

private:
	QSystemTrayIcon *tray;
	QAction *enableYastAction;
	QAction *runBrowserAction;

	bool isYastRunning();
	bool isApplicationAvailable(QString location);
	bool isFirefoxAvailable();
	bool isChromeAvailable();
	bool isChromeiumAvailable();


private slots:
	void slotEnableYast();
	void slotRunBrowser();
	void slotHelperFinished( int exitCode, QProcess::ExitStatus exitStatus );
	void slotHelperError( QProcess::ProcessError error );
	void slotUpdateStatus();
	void slotTrayActivated ( QSystemTrayIcon::ActivationReason reason );

};


#endif
