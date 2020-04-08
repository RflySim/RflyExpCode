%%%  e8.2_Sim
clear
path('./icon/',path);
%Run the model initialization file icon/init.m
Init;

%Constant value
RAD2DEG = 57.2957795;
DEG2RAD = 0.0174533;
%throttle when UAV hover
THR_HOVER = 0.609;

%% control parameter
%Attitude PID parameters
Kp_PITCH_ANGLE =6.5;
Kp_PITCH_AngleRate = 0.1;
Ki_PITCH_AngleRate = 0.02;
Kd_PITCH_AngleRate = 0.001;
Kp_ROLL_ANGLE =6.5;
Kp_ROLL_AngleRate = 0.1;
Ki_ROLL_AngleRate = 0.02;
Kd_ROLL_AngleRate = 0.001;

Kp_YAW_ANGLE = 3;
Kp_YAW_AngleRate = 0.5;
Ki_YAW_AngleRate = 0.01;
Kd_YAW_AngleRate = 0.00;

%Position PID parameters
Kpxp = 1.0;
Kpyp = 1.0;
Kpzp = 4.0;
Kvxp = 3.0; Kvxi = 0.1; Kvxd = 0.01;
Kvyp = 3.0; Kvyi = 0.1; Kvyd = 0.01;
Kvzp = 0.45; Kvzi = 0.01; Kvzd = 0.005;

Saturation_I_RP_Max = 0.3;
Saturation_I_RP_Min = -0.3;
Saturation_I_Y_Max = 0.2;
Saturation_I_Y_Min = -0.2;
Saturation_I_ah = 3.43;
Saturation_I_az = 5;

%max control angle,default 35deg
MAX_CONTROL_ANGLE_ROLL = 35;
MAX_CONTROL_ANGLE_PITCH  = 35;
%Maximum navigation angle, used in position control to avoid large attitude angles
MAX_CONTROL_ANGLE_NAV_ROLL = 15; 
MAX_CONTROL_ANGLE_NAV_PITCH  = 15;
%max control angle rate,rad/s
MAX_CONTROL_ANGLE_RATE_PITCH = 220;
MAX_CONTROL_ANGLE_RATE_ROLL = 220;
MAX_CONTROL_ANGLE_RATE_Y = 200;
%Maximum control speed, m/s
MAX_CONTROL_VELOCITY_XY = 5;
MAX_CONTROL_VELOCITY_Z = 3;
%Throttle amplitude
MAX_MAN_THR = 0.9;
MIN_MAN_THR = 0.05;
%% run simulink model
e8_2_sim