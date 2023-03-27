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

./autoBDC.sh 3067 2 -1 10 false true 2 false
./autoBDC.sh 3067 2 -1 10 false true 1.5 false
./autoBDC.sh 3067 2 -1 10 false true 1 false
./autoBDC.sh 3067 2 -1 10 false false 1 false
./autoBDC.sh 3067 2 -1 10 true false 1 false
./autoBDC.sh 3067 2 -1 10 false true 2 true
./autoBDC.sh 3067 2 -1 10 false true 1.5 true
./autoBDC.sh 3067 2 -1 10 false true 1 true
./autoBDC.sh 3067 2 -1 10 false false 1 true

# Run 3067 with savepng true

./autoBDC.sh 3067 2 -1 10 true true 1.5 false
./autoBDC.sh 3067 2 -1 10 true true 1.5 true

# All Carbon runs with correlation cuts, with or without anglecuts

./autoBDC.sh 3057 2 -1 10 false true 1.5 true
./autoBDC.sh 3057 2 -1 10 false true 1.5 false

./autoBDC.sh 3059 2 -1 10 false true 1.5 true
./autoBDC.sh 3059 2 -1 10 false true 1.5 false

./autoBDC.sh 3066 2 -1 10 false true 1.5 true
./autoBDC.sh 3066 2 -1 10 false true 1.5 false

./autoBDC.sh 3068 2 -1 10 false true 1.5 true
./autoBDC.sh 3068 2 -1 10 false true 1.5 false

./autoBDC.sh 3069 2 -1 10 false true 1.5 true
./autoBDC.sh 3069 2 -1 10 false true 1.5 false

./autoBDC.sh 3070 2 -1 10 false true 1.5 true
./autoBDC.sh 3070 2 -1 10 false true 1.5 false

./autoBDC.sh 3071 2 -1 10 false true 1.5 true
./autoBDC.sh 3071 2 -1 10 false true 1.5 false

./autoBDC.sh 3072 2 -1 10 false true 1.5 true
./autoBDC.sh 3072 2 -1 10 false true 1.5 false

./autoBDC.sh 3073 2 -1 10 false true 1.5 true
./autoBDC.sh 3073 2 -1 10 false true 1.5 false

./autoBDC.sh 3074 2 -1 10 false true 1.5 true
./autoBDC.sh 3074 2 -1 10 false true 1.5 false

./autoBDC.sh 3075 2 -1 10 false true 1.5 true
./autoBDC.sh 3075 2 -1 10 false true 1.5 false

./autoBDC.sh 3076 2 -1 10 false true 1.5 true
./autoBDC.sh 3076 2 -1 10 false true 1.5 false

./autoBDC.sh 3077 2 -1 10 false true 1.5 true
./autoBDC.sh 3077 2 -1 10 false true 1.5 false

./autoBDC.sh 3078 2 -1 10 false true 1.5 true
./autoBDC.sh 3078 2 -1 10 false true 1.5 false

./autoBDC.sh 3079 2 -1 10 false true 1.5 true
./autoBDC.sh 3079 2 -1 10 false true 1.5 false

./autoBDC.sh 3080 2 -1 10 false true 1.5 true
./autoBDC.sh 3080 2 -1 10 false true 1.5 false

./autoBDC.sh 3081 2 -1 10 false true 1.5 true
./autoBDC.sh 3081 2 -1 10 false true 1.5 false

### Last Carbon run with Target

./autoBDC.sh 3082 2 -1 10 false true 1.5 true
./autoBDC.sh 3082 2 -1 10 false true 1.5 false

### Not matched HIMAC central run, but only BDC received beam data

#./autoBDC.sh 4010 2 -1 10 false true 1.5 true
#./autoBDC.sh 4010 2 -1 10 false true 1.5 false

#./autoBDC.sh 4011 2 -1 10 false true 1.5 true
#./autoBDC.sh 4011 2 -1 10 false true 1.5 false

#./autoBDC.sh 4012 2 -1 10 false true 1.5 true
#./autoBDC.sh 4012 2 -1 10 false true 1.5 false

#./autoBDC.sh 4013 2 -1 10 false true 1.5 true
#./autoBDC.sh 4013 2 -1 10 false true 1.5 false

