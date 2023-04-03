#!/bin/bash

# usage : ./autoBDC.sh ${RunNumber} [${runopt}] ${savepng} ${corr_} ${nsigma} ${angleCut_} ${minang} ${maxang} ${rmk}

#${runopt} is consist of 7 digits with the meaning of the condition

#QDCopt :
#   1(default) : hisQDC1->Fill(ip,tmpQDC);hisQDCDist1->Fill(tmpQDC);
#   2 : only fill if ( Data[ip*128+64+ich] > 0) {hisQDC1->Fill(ip,tmpQDC);hisQDCDist1->Fill(tmpQDC)}; 
#t0opt :
#   1(default) : t0 is calculated from the time distribution by the code
#   2 : t0 is calculated from the fitting of the time distribution
#tdopt
#   1(default) : Time at earlier time is in left side(proposed by Prof.Ahn at Korea Univ.), time = 4000 - ftt + TDC time
#   2 : time = ftt - TDC time
#hitopt
#   1(default) : only consider the case nX11=1 && nX12=1 && nX21=1 && nX22=1
#   2 : no apply the option
#chopt
#   1(default) : Ch1X2-Ch1X1 = 0 or 1, Ch2X2-Ch2X1 = -1 or 0
#   2 : no apply the option
#centopt
#   1(default) : not apply this option
#   2 : only consider CH 13-17 
#pedopt
#   1(default) : collect QDC values when TDC value is existed(not zero)
#   2 : Collect QDC values after extracting decided pedestal values (i.e. only collect the QDC values - pedestal)

#./autoBDC.sh ${RunNumber} [${QDCopt} ${t0opt} ${tdopt} ${hitopt} ${chopt} ${centopt} ${pedopt}] ${savepng} ${corr_} ${nsigma} ${angleCut_} ${minang} ${maxang} ${rmk}

### Reference ###
#./autoBDC.sh 3067 2 1111111 1 7 false true 1.5 true -0.9612 0.022

# All Carbon runs with default conditions

./autoBDC.sh 3057 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3059 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3066 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3067 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3068 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3069 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3070 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3071 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3072 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3073 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3074 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3075 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3076 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3077 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3078 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3079 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3080 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 3081 2 1111111 1 7 false true 1.5 true -0.9612 0.022

### Last Carbon run with Target

./autoBDC.sh 3082 2 1111111 1 7 false true 1.5 true -0.9612 0.022

### Not matched HIMAC central run, but only BDC received beam data

./autoBDC.sh 4010 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 4011 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 4012 2 1111111 1 7 false true 1.5 true -0.9612 0.022
./autoBDC.sh 4013 2 1111111 1 7 false true 1.5 true -0.9612 0.022

