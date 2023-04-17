#!/bin/bash

grep=grep

#root -l -b -q bdcDrawAll_HIMAC.C >& log_step0
#root -l -b -q bdcOrgTimeDist_Data_ori.C >& log_step1
#root -l -b -q bdcOrgTimeDist_Data.C >& log_step2
root -l -b -q anaTimeZero.C >& log_step3
#root -l -b -q bdcTimeDist_Data.C >& log_step4
#root -l -b -q bdcTrackTreeMaker_Data.C >& log_step5
#root -l -b -q anaCorr.C >& log_step6
#root -l -b -q bdcTrackFinderData_CNU_Cosmic_getResolution.C >& log_step7
#root -l -b -q draw_Resolution.C >& log_step8
grep=grep
${grep} "Resolution" log_step8
root -l -b -q anaAngle.C >& log_step9
${grep} "Mean :" log_step9
${grep} "Sigma :" log_step9
echo DONE!!!!! ^_^
