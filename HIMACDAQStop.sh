#!/usr/bin/env bash
#PIDLIST=`pidof BDCDAQ_TIME`
#PIDLIST=`pidof bdcDaq_20221105`
PID=`ps aux | grep -i bdcDaq_20221105 | grep -vw grep | awk '{ print $2} '` 
#echo $PID

for i in $(echo $PID )
do
    echo "KILL $i"
    kill -s SIGINT $i
#    sleep 1
done

echo "All process was terminated"
