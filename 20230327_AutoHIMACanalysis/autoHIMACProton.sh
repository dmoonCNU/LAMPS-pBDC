#!/bin/bash

#RunNumber=$1
#localno=$2
#minip=$3
#maxip=$4
#savepng=$5
#corr_=$6
#nsigma=$7
#angleCut_=$8

#./autoBDC.sh ${RunNumber} ${localno} ${minip} ${maxip} ${savepng} ${corr_} ${nsigma} ${angleCut_}

# Run 2043 with different conditions

#./autoBDC.sh 2043 1 -1 10 false true 2 false
./autoBDC.sh 2043 1 -1 10 false true 1.5 false
#./autoBDC.sh 2043 1 -1 10 false true 1 false
#./autoBDC.sh 2043 1 -1 10 false false 1 false
#./autoBDC.sh 2043 1 -1 10 true false 1 false
#./autoBDC.sh 2043 1 -1 10 false true 2 true
./autoBDC.sh 2043 1 -1 10 false true 1.5 true
#./autoBDC.sh 2043 1 -1 10 false true 1 true
#./autoBDC.sh 2043 1 -1 10 false false 1 true

# Run 2043 with savepng

./autoBDC.sh 2043 1 -1 10 true true 1.5 false
./autoBDC.sh 2043 1 -1 10 true true 1.5 true

