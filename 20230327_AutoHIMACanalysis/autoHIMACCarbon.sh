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
 
# Run 3067 with different conditions

./autoBDC.sh 3067 2 -1 10 false true 1.5 false
./autoBDC.sh 3067 2 -1 10 false true 1.5 true

# Run 3067 with savepng true

./autoBDC.sh 3067 2 -1 10 true true 1.5 false
./autoBDC.sh 3067 2 -1 10 true true 1.5 true

