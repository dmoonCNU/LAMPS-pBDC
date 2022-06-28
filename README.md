# LAMPS-pBDC
Code to run analyzing BDC data

Running order
1. root -l bdcDraw.C : decide pedestal level of each ASD (e.g. QDCCUT1 = 300; for ASD16)
2. root -l -q -b bdcTimeDist_Data_v15.C : analyzing time distribution and get time - distance relation for each ASD
3. root -l -q -b bdcTrackTreeMaker_Data_v15.C : convert time to distance and create TTree for reconstructing pBDC tracks 
4. root -l -q -b bdcTrackFinderData_getResolution_v15.C : reconstruct pBDC track by using drift length in each layer

Analysis code
1. root -l anaTime.C : draw time distribution
2. root -l anaCorr.C : correlation study of channels and times
3. root -l anaAngle.C : angle distributions
4. root -l draw_Resolution.C : get resolution study
