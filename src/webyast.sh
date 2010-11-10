#!/bin/bash

case "$1" in
    start)
	/usr/sbin/rcyastws start && /usr/sbin/rcyastwc start
	RETVAL=$?
   ;;
    stop)
	/usr/sbin/rcyastws stop && /usr/sbin/rcyastwc stop
	RETVAL=$?
    ;;
    status)

	WS=`ps -ef | grep "/usr/sbin/lighttpd -f /etc/yastws/" | grep -v grep | wc -l`
	WC=`ps -ef | grep "/usr/sbin/lighttpd -f /srv/www/yast/config/lighttpd.conf" | grep -v grep | wc -l`
	
	if [ $WS -eq 1 ] && [ $WC -eq 1 ]; then
		RETVAL=0
	else
		RETVAL=3
	fi
    ;;
esac

exit $RETVAL


