    As for basic experiment, if you don't have hardware, you can use the 'e4\e4.1\logdata.mat' data directly, 
and the corresponding filter code is 'e4\e4.1\Attitude_estimator0_fly.m'; if you have hardware, you will get
a file similar to 'e4\e4.1\e4_A.bin', and the corresponding filter code is 'e4\e4.1\Attitude_estimator0.m'.

    The data in 'e4\e4.1\e4_A.bin' and 'e4\e4.1\logdata.mat' are obtained by the 'e4\e4.1\log_data.slx' and
they both include three-axis gyroscope data, three-axis acceleration data and the attitude estimated by self-contained
filter in PX4 software.The file 'e4\e4.1\e4_A.bin' stores the data directly from Pixhawk autopilot rotating by hands and
the other file 'e4\e4.1\logdata.mat' stores the data from a practical flight of a quadcopter.
 