    As for basic experiment, if you don't have hardware, you can use the 'e3\e3.1\AccRaw.mat' data directly, 
and the corresponding calibration function is 'e3\e3.1\calLM.m'; if you have hardware, you will get a file similar 
to 'e3\e3.1\rawdataFile\e_acc1_A.bin', and the corresponding calibration function is 'e3\e3.1\calLMRaw.m'.

    The data in 'e3\e3.1\rawdataFile\e_acc1_A.bin' are obtained by the 'e3\e3.1\acquire_dataag.slx' acceleration
data acquisition model and they have been calibrated by PX4 before logged.So before using them for calibration, you 
should withdraw the uncalibrated data using 'Sensor Calibration' parameters which can be found in QGC as we do in 
fourteenth and fifteenth lines of 'e3\e3.1\calLMRaw.m'.
    The data in 'e3\e3.1\AccRaw.mat' are the uncalibrated data which can be directly used for calibration.

    The data in 'e3\e3.2\accdata.mat' are used for computing pitch.You can get the similar data by
'e3\e3.1\acquire_dataag.slx',and you should slowly rotate the Pixhawk. 