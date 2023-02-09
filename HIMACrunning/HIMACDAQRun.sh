#!/usr/bin/env bash

#RunNumber=`ssh lamps@192.168.10.2 "cat ~/.daq/CurRunNumber" ` 
RunNumber=$1
NoEvts=1000000
echo $RunNumber

#EXE=/home/cnuhep313/Documents/BDCWorks/BDCDAQ_20201117/BDC/DAQ/bin/BDCDAQ_TIME
#EXE=/Users/pbdc/DAQ/DAQ/bin/bdcDAQ_BinaryTest_dual_v20221214
EXE=/Users/pbdc/DAQ/DAQ/bin/bdcDaq_20221105

for i in $(seq 0 3 )
do
    index=$((3-$i))
    #index=$i
    #EXE2=${EXE}"_"$i
    echo $index bdcDaq_20221105_${index}_${RunNumber} 
    #$EXE2 $i bdcDaq_20221105_${i}_${RunNumber} &    
    $EXE ${RunNumber} ${NoEvts} ${index} &
done
