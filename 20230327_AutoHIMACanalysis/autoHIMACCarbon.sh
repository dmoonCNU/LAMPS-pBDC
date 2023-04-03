#!/bin/bash

#RunNumber=$1
#locano=$2
#QDCopt=$3
#minip=$4
#maxip=$5
#savepng=$6
#corr_=$7
#nsigma=$8
#angleCut_=$9
#runopt=${10}
#t0opt=${11}
#minang=${12}
#maxang=${13}
#rmk=${14}


#./autoBDC.sh ${RunNumber} [${QDCopt} ${t0opt} ${tdopt} ${hitopt} ${chopt} ${centopt} ${pedopt}] ${savepng} ${corr_} ${nsigma} ${angleCut_} ${minang} ${maxang} ${rmk}

#./autoBDC.sh 3067 2 1111121 1 7 false true 1.5 true -2 2
#./autoBDC.sh 3067 2 1121121 1 7 false true 1.5 true -2 2

./autoBDC.sh 3067 2 1111121 1 7 true true 1.5 true -2 2
./autoBDC.sh 3067 2 1121121 1 7 true true 1.5 true -2 2

#./autoBDC.sh 3067 2 1111121 -1 10 false true 1.5 true -2 2
#./autoBDC.sh 3067 2 1121121 -1 10 false true 1.5 true -2 2

./autoBDC.sh 3067 2 1111121 -1 10 true true 1.5 true -2 2
./autoBDC.sh 3067 2 1121121 -1 10 true true 1.5 true -2 2



# Run 3067 with different conditions

#./autoBDC.sh 3067 2 -1 10 false true 1.5 false
#./autoBDC.sh 3067 2 -1 10 false true 1.5 true

# Run 3067 with savepng true

#./autoBDC.sh 3067 2 -1 10 true true 1.5 false
#./autoBDC.sh 3067 2 -1 10 true true 1.5 true

