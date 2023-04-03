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

./autoBDC.sh 3067 2 1111111 1 7 false false 1.5 false -5 5


# no corr cut + no angle cut
###./autoBDC.sh 3067 2 1111111 1 7 true false 1.5 false -1.4 0.6
###./autoBDC.sh 3067 2 1111111 1 7 false false 1.5 false -1.4 0.6

#./autoBDC.sh 3067 2 1111111 1 7 false true 1.5 false -1.4 0.6
# -0.4696 +- 0.4916

#./autoBDC.sh 3067 2 1111111 1 7 true true 1.5 false -1.4 0.6

#./autoBDC.sh 3067 2 1111111 1 7 true true 1.5 true -0.9612 0.022	# 1 sigma
#./autoBDC.sh 3067 2 1111111 1 7 true true 1.5 true -1.4528 0.5136	# 2 sigma
#./autoBDC.sh 3067 2 1111111 1 7 true true 1.5 true -1.9444 1.0052	# 3 sigma
#./autoBDC.sh 3067 2 1111111 1 7 true true 1.5 true -0.7154 -0.2238	# 0.5 sigma

# corr cut + angle cut effect

# corr cut + no angle cut

###./autoBDC.sh 3067 2 1111111 1 7 false true 1.5 true -0.9612 0.022	# 1 sigma
###./autoBDC.sh 3067 2 1111111 1 7 false true 1.5 true -1.4528 0.5136	# 2 sigma
###./autoBDC.sh 3067 2 1111111 1 7 false true 1.5 true -1.9444 1.0052	# 3 sigma
###./autoBDC.sh 3067 2 1111111 1 7 false true 1.5 true -0.7154 -0.2238	# 0.5 sigma

#./autoBDC.sh 3067 2 2121112 1 7 true true 1.5 true -0.9612 0.022

#./autoBDC.sh 3067 2 1121112 1 7 true true 1.5 true -0.9612 0.022
#./autoBDC.sh 3067 2 1111112 1 7 true true 1.5 true -0.9612 0.022
#./autoBDC.sh 3067 2 1121111 1 7 true true 1.5 true -0.9612 0.022

#./autoBDC.sh 3067 2 2111112 1 7 true true 1.5 true -0.9612 0.022
#./autoBDC.sh 3067 2 2111111 1 7 true true 1.5 true -0.9612 0.022
#./autoBDC.sh 3067 2 2121111 1 7 true true 1.5 true -0.9612 0.022

#./autoBDC.sh 3067 2 1121111 1 7 true true 1.5 false -0.9612 0.022

#./autoBDC.sh 3067 2 1121111 1 7 true true 1.5 true -2 2

###./autoBDC.sh 3067 2 1111112 1 7 false true 1.5 false -1.4 0.6
#
#./autoBDC.sh 3082 2 1111111 1 7 false true 1.5 false -1.4 0.6
#./autoBDC.sh 3082 2 1111111 1 7 true true 1.5 false -1.4 0.6
