#!/bin/bash

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
ltopt=${12}
ltch=${13}
rmk=${14}

#QDCopt=$3
#runopt=${10}
#t0opt=${11}

echo '${RunNumber} ${locano} [ ${runopt} ] ${minip} ${maxip} ${savepng} ${corr_} ${nsigma} ${angleCut_} ${minang} ${maxang} ${ltopt} ${ltch} ${rmk}'
echo $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} ${11} ${12} ${13} ${14}

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

echo '${RunNumber} ${locano} [ ${QDCopt} ${t0opt} ${tdopt} ${hitopt} ${chopt} ${centopt} ${pedopt} ] ${minip} ${maxip} ${savepng} ${corr_} ${nsigma} ${angleCut_} ${minang} ${maxang} ${ltopt} ${ltch} ${rmk}'
echo ${RunNumber} ${locano} [ ${QDCopt} ${t0opt} ${tdopt} ${hitopt} ${chopt} ${centopt} ${pedopt} ] ${minip} ${maxip} ${savepng} ${corr_} ${nsigma} ${angleCut_} ${minang} ${maxang} ${ltopt} ${ltch} ${rmk}

if [ -z ${rmk} ]
then
	rmk=""
else
	rmk=_${14}
fi

echo rmk=${rmk}

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
#wdir=/Users/hyunchoryhome/20230330/LAMPS-pBDC/20230327_AutoHIMACanalysis
wdir=/Users/hyunchoryhome/Research_2023/pBDC/20230327_AutoHIMACanalysis

protondir=${wdir}/Proton100MeV/
carbondir=${wdir}/Carbon200MeV/
cosmicdir=${wdir}/CosmicCNU/


mkdir ${protondir}
mkdir ${carbondir}
mkdir ${cosmicdir}

dir=test
dire=test

if [ "$2" -eq "1" ]
then
	dir=Proton100MeV_Run${RunNumber}_opt${runopt}_ip${iprmk}_png${savepng}_cor${corr_}_nsig${nsigma}_ang${angleCut_}_w${minang}_${maxang}_lt${ltopt}CH${ltch}${rmk}
	dire=Proton100MeV_Run${RunNumber}_opt${runopt}_ip${iprmk}_png${savepng}_cor${corr_}_nsig${nsigma}_ang0_w-5_5_lt0CH${ltch}${rmk}
	loc=${protondir}
	loca="/Users/hyunchoryhome/Research_2023/202302HIMACBeamTest/AllData/1_Proton100MeV/Data"
elif [ "$2" -eq "2" ]
then
	dir=Carbon200MeV_Run${RunNumber}_opt${runopt}_ip${iprmk}_png${savepng}_cor${corr_}_nsig${nsigma}_ang${angleCut_}_w${minang}_${maxang}_lt${ltopt}CH${ltch}${rmk}
	dire=Carbon200MeV_Run${RunNumber}_opt${runopt}_ip${iprmk}_png${savepng}_cor${corr_}_nsig${nsigma}_ang0_w-5_5_lt0CH${ltch}${rmk}
	loc=${carbondir}
	loca="/Users/hyunchoryhome/Research_2023/202302HIMACBeamTest/AllData/2_Carbon200MeV/Data"
elif [ "$2" -eq "3" ]
then
	dir=CosmicCNU_Run${RunNumber}_opt${runopt}_ip${iprmk}_png${savepng}_cor${corr_}_nsig${nsigma}_ang${angleCut_}_w${minang}_${maxang}_lt${ltopt}CH${ltch}${rmk}
	dire=CosmicCNU_Run${RunNumber}_opt${runopt}_ip${iprmk}_png${savepng}_cor${corr_}_nsig${nsigma}_ang0_w-5_5_lt0CH${ltch}${rmk}
	loc=${cosmicdir}
	loca="/Users/hyunchoryhome/Research_2023/202304CosmicCNU/Data"
fi

echo ${loc}

cd ${loc}

mkdir ${dir}
cd ${dir}

anaf=/anaAngleResult.root
ana0=/anaAngleResultang0.root
#if [ "${dir}" -eq "${dir2}" ]
#then
cp ${loc}${dire}${anaf} ${loc}${dir}${ana0}
#cp ${loc}${dire}/anaAngleResult.root ${loc}${dir}/
#mv anaAngleResult.root anaAngleResult_ang0.root
#fi

cp ../../*.C ./
cp ../../*.sh ./
#cp ../${dire}/anaAngleResult.root ./anaAngleResultang0.root

ploc=${loc}${dir}

sed -i '.bak' "s,___LOCA___,$loca,g" *.C

root -l -b -q ${ploc}/bdcDrawAll_HIMAC.C"(${locano},${RunNumber},${QDCopt})" >& ${ploc}/log_step0
echo step0 is done
root -l -b -q ${ploc}/bdcOrgTimeDist_Data_ori.C"(${locano},${minip},${maxip},${tdopt},${hitopt},${chopt},${centopt},${RunNumber})" >& ${ploc}/log_step1
echo step1 is done!

root -l -b -q ${ploc}/bdcOrgTimeDist_Data.C"(${locano},${minip},${maxip},${tdopt},${hitopt},${chopt},${centopt},${RunNumber})" >& ${ploc}/log_step2
echo step2 is done!!

root -l -b -q ${ploc}/anaTimeZero.C"(${t0opt})" >& ${ploc}/log_step3
echo step3 is done!!!!

root -l -b -q ${ploc}/bdcTimeDist_Data.C"(${locano},${minip},${maxip},${tdopt},${hitopt},${chopt},${centopt},${RunNumber},${ltopt},${ltch})" >& ${ploc}/log_step4
echo step4 is done!!!!!!!!

root -l -b -q ${ploc}/bdcTrackTreeMaker_Data.C"(${locano},${minip},${maxip},${tdopt},${hitopt},${chopt},${centopt},${pedopt},${RunNumber})" >& ${ploc}/log_step5
echo step5 is done!!!!!!!! !!!!!!!!

root -l -b -q ${ploc}/anaCorr.C"(${nsigma})" >& ${ploc}/log_step6
echo step6 is done!!!!!!!! !!!!!!!! !!!!!!!!

root -l -b -q ${ploc}/bdcTrackFinderData_CNU_Cosmic_getResolution.C"(${savepng},${corr_},${nsigma},${angleCut_},${minang},${maxang})" >& ${ploc}/log_step7
echo step7 is done!!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!!

root -l -b -q ${ploc}/draw_Resolution.C >& ${ploc}/log_step8
echo step8 is done!!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!!

grep=grep
${grep} "Resolution" ${ploc}/log_step8

root -l -b -q ${ploc}/anaAngle.C >& ${ploc}/log_step9
echo step8 is done!!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!! !!!!!!!!

${grep} "Mean :" ${ploc}/log_step9
${grep} "Sigma :" ${ploc}/log_step9

echo DONE!!!!! ^_^

echo back to ${wdir}
cd ${wdir}

