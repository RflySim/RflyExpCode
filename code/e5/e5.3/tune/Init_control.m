%%% AttitudeControl_tune
clear
path('./icon/',path);
%Run the model initialization file icon/init.m
Init;

%% Initial condition
ModelInit_PosE = [0, 0, -100];
ModelInit_VelB = [0, 0, 0];
ModelInit_AngEuler = [0, 0, 0];
ModelInit_RateB = [0, 0, 0];
ModelInit_Rads = 557.142;
%% run simulink model
AttitudeControl_tune