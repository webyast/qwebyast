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

#ifndef APP_H
#define APP_H

#include <QApplication>
#include <QSessionManager>



class App : public QApplication
{
	Q_OBJECT
public:
	App ( int & argc, char ** argv );
	void saveState( QSessionManager & manager );


};


#endif
