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

