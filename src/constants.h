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

#define WEBYAST_UP_ICON		"qwebyast-enabled.png"
#define WEBYAST_DOWN_ICON	"qwebyast-disabled.png"
#define WEBYAST_ICON_PATH	"/usr/share/icons/hicolor/32x32/apps/qwebyast/pics/"
#define WEBYAST_CHECK_CMD	"/usr/bin/webyast.sh status"
#define WEBYAST_UP_CMD		"kdesu /usr/bin/webyast.sh start"
#define WEBYAST_DOWN_CMD	"kdesu /usr/bin/webyast.sh stop"
#define BROWSER_URL		"https://localhost:4984"
#define UPDATE_INTERVAL		15000
#define USE_EXTERNAL_BROWSER	1
#define IGNORE_SSL_ERRORS	1
#define CHROME_BIN		"/usr/bin/google-chrome"
#define CHROMIUM_BIN		"/usr/bin/chromium"
#define FIREFOX_BIN		"/usr/bin/firefox"
#define CHROME_CMD		"/usr/bin/env xdg-open /usr/share/applications/chrome-webyast.desktop"
#define CHROMIUM_CMD		"/usr/bin/env xdg-open /usr/share/applications/chromium-webyast.desktop"
#define FIREFOX_CMD		"/usr/bin/firefox https://localhost:4984"
