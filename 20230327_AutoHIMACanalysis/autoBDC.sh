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
#locano=2
#minip=-1
#maxip=10
#savepng=false
#corr_=true
#nsigma=1.5
#angleCut_=false

RunNumber=$1
locano=$2

runopt=$3

minip=$4
maxip=$5
savepng=$6
corr_=$7
nsigma=$8
angleCut_=$9
minang=${10}
maxang=${11}
rmk=${12}

#QDCopt=$3
#runopt=${10}
#t0opt=${11}

echo '${RunNumber} ${locano} [ ${runopt} ] ${minip} ${maxip} ${savepng} ${corr_} ${nsigma} ${angleCut_} ${minang} ${maxang} ${rmk}'
echo $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} ${11} ${12}

f0=1000000
f1=100000
f2=10000
f3=1000
f4=100
f5=10

runopt2=${runopt}
QDCopt=$(($runopt2 / $f0))

runopt2=$(( $runopt2 - ($QDCopt * $f0) ))
t0opt=$(($runopt2 / $f1))

runopt2=$(( $runopt2 - ($t0opt * $f1) ))
tdopt=$(($runopt2 / $f2))

runopt2=$(( $runopt2 - ($tdopt * $f2) ))
hitopt=$(($runopt2 / $f3))

runopt2=$(( $runopt2 - ($hitopt * $f3) ))
chopt=$(($runopt2 / $f4))

runopt2=$(( $runopt2 - ($chopt * $f4) ))
centopt=$(($runopt2 / $f5))

runopt2=$(( $runopt2 - ($centopt * $f5) ))
pedopt=$runopt2

echo '${RunNumber} ${locano} [ ${QDCopt} ${t0opt} ${tdopt} ${hitopt} ${chopt} ${centopt} ${pedopt} ] ${minip} ${maxip} ${savepng} ${corr_} ${nsigma} ${angleCut_} ${minang} ${maxang} ${rmk}'
echo ${RunNumber} ${locano} [ ${QDCopt} ${t0opt} ${tdopt} ${hitopt} ${chopt} ${centopt} ${pedopt} ] ${minip} ${maxip} ${savepng} ${corr_} ${nsigma} ${angleCut_} ${minang} ${maxang} ${rmk}

if [ ${12} -z ]
then
	rmk=""
else
	rmk=_${12}
fi

if [ $4 -eq "-1" ]
then
	if [ $5 -eq "10" ]
	then
		iprmk=all
	else
		iprmk=$4to$5
	fi
else
	iprmk=$4to$5
fi

echo ${iprmk}

#wdir=/Users/hyunchoryhome/Research_2023/202302HIMACBeamTest/LAMPS-pBDC-main_HIMAC/20230327_AutoHIMACanalysis
wdir=/Users/hyunchoryhome/20230330/LAMPS-pBDC/20230327_AutoHIMACanalysis

protondir=${wdir}/Proton100MeV/
carbondir=${wdir}/Carbon200MeV/

mkdir ${protondir}
mkdir ${carbondir}

dir=test

if [ "$2" -eq "1" ]
then
	dir=Proton100MeV_Run${RunNumber}_opt${runopt}_ip${iprmk}_png${savepng}_cor${corr_}_nsig${nsigma}_ang${angleCut_}_w${minang}to${maxang}${rmk}
	loc=${protondir}
	loca="/Users/hyunchoryhome/Research_2023/202302HIMACBeamTest/AllData/1_Proton100MeV/Data"
elif [ "$2" -eq "2" ]
then
	dir=Carbon200MeV_Run${RunNumber}_opt${runopt}_ip${iprmk}_png${savepng}_cor${corr_}_nsig${nsigma}_ang${angleCut_}_w${minang}to${maxang}${rmk}
	loc=${carbondir}
	loca="/Users/hyunchoryhome/Research_2023/202302HIMACBeamTest/AllData/2_Carbon200MeV/Data"
fi

echo ${loc}

cd ${loc}

mkdir ${dir}
cd ${dir}
cp ../../*.C ./
cp ../../*.sh ./


ploc=${loc}${dir}

root -l -b -q ${ploc}/bdcDrawAll_HIMAC.C"(${locano},${RunNumber},${QDCopt})" >& ${ploc}/log_step0
echo step0 is done
root -l -b -q ${ploc}/bdcOrgTimeDist_Data_v16_ori.C"(${locano},${minip},${maxip},${tdopt},${hitopt},${chopt},${centopt},${RunNumber})" >& ${ploc}/log_step1
echo step1 is done!

root -l -b -q ${ploc}/bdcOrgTimeDist_Data_v16.C"(${locano},${minip},${maxip},${tdopt},${hitopt},${chopt},${centopt},${RunNumber})" >& ${ploc}/log_step2
echo step2 is done!!

root -l -b -q ${ploc}/anaTimeZero.C"(${t0opt})" >& ${ploc}/log_step3
echo step3 is done!!!!

root -l -b -q ${ploc}/bdcTimeDist_Data_v16.C"(${locano},${minip},${maxip},${tdopt},${hitopt},${chopt},${centopt},${RunNumber})" >& ${ploc}/log_step4
echo step4 is done!!!!!!!!

root -l -b -q ${ploc}/bdcTrackTreeMaker_Data_v16.C"(${locano},${minip},${maxip},${tdopt},${hitopt},${chopt},${centopt},${pedopt},${RunNumber})" >& ${ploc}/log_step5
echo step5 is done!!!!!!!! !!!!!!!!

root -l -b -q ${ploc}/anaCorr.C"(${nsigma})" >& ${ploc}/log_step6
echo step6 is done!!!!!!!! !!!!!!!! !!!!!!!!

root -l -b -q ${ploc}/bdcTrackFinderData_CNU_Cosmic_getResolution_v16.C"(${savepng},${corr_},${nsigma},${angleCut_},${minang},${maxang})" >& ${ploc}/log_step7
echo step7 is done!!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!!

root -l -b -q ${ploc}/draw_Resolution.C >& ${ploc}/log_step8
echo step8 is done!!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!!

grep=grep
${grep} "Resolution" ${ploc}/log_step8

root -l -b -q ${ploc}/anaAngle.C >& ${ploc}/log_step9
echo step8 is done!!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!!

${grep} "Mean :" ${ploc}/log_step8
${grep} "Sigma :" ${ploc}/log_step8

echo DONE!!!!! ^_^

echo back to ${wdir}
cd ${wdir}

