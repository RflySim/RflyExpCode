%%%  AttitudeControl_ADRC_Sim
clear
path('./icon/',path);
%Run the model initialization file icon/init.m
Init;

%add disturb to the system
DisturbOn = 0;
DisturbStartTime = 2.0;

%Constant value
RAD2DEG = 57.2957795;
DEG2RAD = 0.0174533;
%throttle when UAV is hovering
THR_HOVER = 0.609;

%% Initial condition
ModelInit_PosE = [0, 0, 0];
ModelInit_VelB = [0, 0, 0];
ModelInit_AngEuler = [0, 0, 0];
ModelInit_RateB = [0, 0, 0];
ModelInit_Rads = 0;
%% control parameter
%Attitude PID parameters
Kp_YAW_AngleRate = 0.5;
Ki_YAW_AngleRate = 0.01;
Kd_YAW_AngleRate = 0.00;
%integral saturation
Saturation_I_RP_Max = 0.3;
Saturation_I_RP_Min = -0.3;
Saturation_I_Y_Max = 0.2;
Saturation_I_Y_Min = -0.2;
%max control angle,default 35deg
MAX_CONTROL_ANGLE_ROLL = 35;
MAX_CONTROL_ANGLE_PITCH  = 35;
%max control angle rate,rad/s 
MAX_CONTROL_ANGLE_RATE_PITCH = 220;
MAX_CONTROL_ANGLE_RATE_ROLL = 220;
MAX_CONTROL_ANGLE_RATE_Y = 200;
%parameters in adrc
TD_R = single(20.0);
TD_H = single(1.0);
NLSEF_R = single(200.0);
NLSEF_H = single(25.0);
NLSEF_C = single(5.0);
ESO_B01 = single(250.0);
ESO_B02 = single(2000.0);
ESO_B03 = single(3000.0);
ESO_B0 = single(47.4);
ESO_H = single(1.0);
ESO_D = single(0.01);
tau2sigma = single(0.108);
%CSC
RC1_MIN = single(1050);
RC1_MAX = single(1950);
RC2_MIN = single(1050);
RC2_MAX = single(1950);
RC3_MIN = single(1050);
RC3_MAX = single(1950);
RC4_MIN = single(1050);
RC4_MAX = single(1950);
%% run simulink model
%AttitudeControl_ADRC_Sim