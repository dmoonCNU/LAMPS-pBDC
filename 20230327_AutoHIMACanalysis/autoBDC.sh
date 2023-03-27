#!/bin/bash
#void bdcOrgTimeDist_Data_v16_ori(int locano=2, int minip=-1, int maxip=10, int runopt=0, int RunNumber=3067){
#TString loca;
#if (locano==2) loca="~/Research_2023/202302HIMACBeamTest/AllData/2_Carbon200MeV/Data";

#            if (runopt==0 || runopt==1 || runopt==2) {if (!(nX11==1 && nX12==1 && nX21==1 && nX22==1)) continue;}
#            if (runopt==1) {
#                int datadiff1 = Ch1X2[0]-Ch1X1[0];
#                int datadiff2 = Ch2X2[0]-Ch2X1[0];
#                if (!(datadiff1==-1 || datadiff1==0)) continue;
#                if (!(datadiff2==0 || datadiff2==1)) continue;
#                }
#            else if (runopt==2) {
#                if (!(13<=Ch1X1[0] && Ch1X1[0]<=17)) continue;
#            }

#void bdcOrgTimeDist_Data_v16(int locano=2, int minip=-1, int maxip=10, int runopt=0, int RunNumber=3067){

#void bdcTimeDist_Data_v16(int locano=2, int minip=-1, int maxip=10, int runopt=0, int RunNumber=3067)

#void bdcTrackTreeMaker_Data_v16(int locano=2, int minip=-1, int maxip=10, int runopt=0, int RunNumber=3067){

#bdcTrackFinderData_CNU_Cosmic_getResolution_v16(const bool savepng=false, bool corr_=true, double nsigma=1.5, bool angleCut_=false)

#RunNumber=$1
#localno=2
#minip=-1
#maxip=10
#savepng=false
#corr_=true
#nsigma=1.5
#angleCut_=false

RunNumber=$1
localno=$2
minip=$3
maxip=$4
savepng=$5
corr_=$6
nsigma=$7
angleCut_=$8
rmk=$9

if [ $9 -z ]
then
	rmk=""
else
	rmk=_$9
fi

if [ [ $3 -eq "-1" ] && [ $4 -eq "10" ] ]
then
	iprmk=all
else
	iprmk=$3to$4
fi

echo ${iprmk}

wdir=/Users/hyunchoryhome/Research_2023/202302HIMACBeamTest/LAMPS-pBDC-main_HIMAC/20230327_AutoHIMACanalysis

protondir=${wdir}/Proton100MeV/
carbondir=${wdir}/Carbon200MeV/

mkdir ${protondir}
mkdir ${carbondir}

dir=Carbon200MeV_Run${RunNumber}_ip${iprmk}_png${savepng}_corr${corr_}_nsigma${nsigma}_angle${angleCut_}${rmk}

if [ "$2" -eq "1" ]
then
	dir=Proton100MeV_Run${RunNumber}_ip${iprmk}_png${savepng}_corr${corr_}_nsigma${nsigma}_angle${angleCut_}${rmk}
	loc=${protondir}
elif [ "$2" -eq "2" ]
then
	dir=Carbon200MeV_Run${RunNumber}_ip${iprmk}_png${savepng}_corr${corr_}_nsigma${nsigma}_angle${angleCut_}${rmk}
	loc=${carbondir}
fi

echo ${loc}

cd ${loc}

mkdir ${dir}
cd ${dir}
cp ../../*.C ./
cp ../../*.sh ./


ploc=${loc}${dir}

root -l -b -q ${ploc}/bdcDrawAll_HIMAC.C"(${localno},${RunNumber})" >& ${ploc}/log_step0
echo step0 is done
root -l -b -q ${ploc}/bdcOrgTimeDist_Data_v16_ori.C"(${localno},${minip},${maxip},0,${RunNumber})" >& ${ploc}/log_step1
#root -l -b -q bdcOrgTimeDist_Data_v16_ori.C"(${localno},${minip},${maxip},0,${RunNumber})"
echo step1 is done!

root -l -b -q ${ploc}/bdcOrgTimeDist_Data_v16.C"(${localno},${minip},${maxip},0,${RunNumber})" >& ${ploc}/log_step2
#root -l -b -q bdcOrgTimeDist_Data_v16.C"(${localno},${minip},${maxip},0,${RunNumber})"
echo step2 is done!!

root -l -b -q ${ploc}/anaTimeZero.C"(1)" >& ${ploc}/log_step3
#root -l -b -q anaTimeZero.C"(1)"
echo step3 is done!!!!

root -l -b -q ${ploc}/bdcTimeDist_Data_v16.C"(${localno},${minip},${maxip},0,${RunNumber})" >& ${ploc}/log_step4
#root -l -b -q bdcTimeDist_Data_v16.C"(${localno},${minip},${maxip},0,${RunNumber})"
echo step4 is done!!!!!!!!

root -l -b -q ${ploc}/bdcTrackTreeMaker_Data_v16.C"(${localno},${minip},${maxip},0,${RunNumber})" >& ${ploc}/log_step5
#root -l -b -q bdcTrackTreeMaker_Data_v16.C"(${localno},${minip},${maxip},0,${RunNumber})"
echo step5 is done!!!!!!!! !!!!!!!!

root -l -b -q ${ploc}/anaCorr.C"(1)" >& ${ploc}/log_step6
#root -l -b -q anaCorr.C"(1)"
echo step6 is done!!!!!!!! !!!!!!!! !!!!!!!!

root -l -b -q ${ploc}/bdcTrackFinderData_CNU_Cosmic_getResolution_v16.C"(${savepng},${corr_},${nsigma},${angleCut_})" >& ${ploc}/log_step7
#root -l -b -q bdcTrackFinderData_CNU_Cosmic_getResolution_v16.C"(${savepng},${corr_},${nsigma},${angleCut_})"
echo step7 is done!!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!!

root -l -b -q ${ploc}/draw_Resolution.C >& ${ploc}/log_step8
#root -l -b -q draw_Resolution.C
echo step8 is done!!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!!

grep=grep
${grep} "Resolution" ${ploc}/log_step8

root -l -b -q ${ploc}/anaAngle.C >& ${ploc}/log_step9
#root -l -b -q anaAngle.C
echo step8 is done!!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!!

${grep} "Mean :" ${ploc}/log_step8
${grep} "Sigma :" ${ploc}/log_step8

echo DONE!!!!! ^_^

echo back to ${wdir}
cd ${wdir}

