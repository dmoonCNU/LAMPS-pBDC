#!/bin/bash

# usage : ./autoBDC.sh ${RunNumber} [${runopt}] ${savepng} ${corr_} ${nsigma} ${angleCut_} ${minang} ${maxang} ${ltopt} ${ltch} ${rmk}

#${runopt} is consist of 7 digits with the meaning of the condition

#QDCopt :
#	1(default) : hisQDC1->Fill(ip,tmpQDC);hisQDCDist1->Fill(tmpQDC);
#	2 : only fill if ( Data[ip*128+64+ich] > 0) {hisQDC1->Fill(ip,tmpQDC);hisQDCDist1->Fill(tmpQDC)}; 
#t0opt (v20230412):
#   1(default, from v20230412) : t0 from fitting(after automation code running, please check!), t1 is from the distribution
#   2 : from fitting
#   3 : from distribution (default before v20230412)
#tdopt
#	1(default) : Time at earlier time is in left side(proposed by Prof.Ahn at Korea Univ.), time = 4000 - ftt + TDC time
#	2 : time = ftt - TDC time
#hitopt
#	1(default) : only consider the case nX11=1 && nX12=1 && nX21=1 && nX22=1
#	2 : no apply the option
#chopt
#	1(default) : Ch1X2-Ch1X1 = 0 or 1, Ch2X2-Ch2X1 = -1 or 0
#	2 : no apply the option
#centopt
#	1(default) : not apply this option
#	2 : only consider CH 13-17 
#pedopt
#	1(default) : collect QDC values when TDC value is existed(not zero)
#	2 : Collect QDC values after extracting decided pedestal values (i.e. only collect the QDC values - pedestal)

#angleCut_
#	angleCut_==0, angleCut_ = false
#	angleCut<0, ${minang}, ${maxang} is same as in the script
#	angleCut>0, ang0mean, ang0RMS are from anaAngleResultang0.root (angleCut_==0 case)
#		minang=ang0mean-angleCut_*ang0RMS;
#		maxang=ang0mean+angleCut_*ang0RMS;

#ltopt in bdcTimeDist_Data_v17_iter.C
#    if (ltopt==1) {ltch=13~17, ltch, ltch+1, ltch, ltch
#    else if (ltopt==2) {ltch=13~17, ltch, ltch, ltch, ltch-1
#    else {//ltopt=0, select ltch and ltopt with minimum chisquare

#ltch

#./autoBDC.sh ${RunNumber} [${QDCopt} ${t0opt} ${tdopt} ${hitopt} ${chopt} ${centopt} ${pedopt}] ${savepng} ${corr_} ${nsigma} ${angleCut_} ${minang} ${maxang} ${ltopt} ${ltch} ${rmk}

###############################################################################
### Default option (with 1.5 sigma correlation and 1 sigma angle cut)

./autoBDC.sh 7999 3 1111111 1 6 true true 1.5 1 -5 5 0 15 "r5" # 1 sigma
###############################################################################

