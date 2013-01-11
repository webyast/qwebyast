#!/bin/bash

case "$1" in
    start)
	/usr/sbin/rccollectd start
	/usr/sbin/rcwebyast start
	RETVAL=$?
   ;;
    stop)
	/usr/sbin/rccollectd stop
	/usr/sbin/rcwebyast stop
	RETVAL=$?
    ;;
    status)
        WY=`pgrep -c -f "/usr/sbin/nginx -c /etc/webyast/nginx.conf"`
	
	if [ $WY -eq 0 ]; then
		RETVAL=3
	else
		RETVAL=0
	fi
    ;;
esac

exit $RETVAL


