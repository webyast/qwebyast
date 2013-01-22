#!/bin/bash

case "$1" in
    start)
	/usr/sbin/rcwebyast start && /usr/sbin/rccollectd start
	RETVAL=$?
   ;;
    stop)
	/usr/sbin/rcwebyast stop && /usr/sbin/rccollectd stop
	RETVAL=$?
    ;;
    status)

	WS=`ps -ef | grep -E "(/usr/sbin/lighttpd -f /etc/yastws/|/usr/sbin/nginx -c /etc/yastws/nginx.conf)" | grep -v grep | wc -l`
	WC=`ps -ef | grep -E "(/usr/sbin/lighttpd -f /srv/www/yast/config/lighttpd.conf|/usr/sbin/nginx -c /etc/yastwc/nginx.conf)" | grep -v grep | wc -l`
	
	if [ $WS -eq 1 ] && [ $WC -eq 1 ]; then
		RETVAL=0
	else
		RETVAL=3
	fi
    ;;
esac

exit $RETVAL


