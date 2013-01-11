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
        WY=`pgrep -c -f /usr/bin/nginx`
	
	if [ $WY -eq 0 ]; then
		RETVAL=3
	else
		RETVAL=0
	fi
    ;;
esac

exit $RETVAL


