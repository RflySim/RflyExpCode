clear
path('./icon/',path);
Init;

%Constant value
RAD2DEG = 57.2957795;
DEG2RAD = 0.0174533;
%throttle when UAV is hovering
THR_HOVER = 0.609;
%% Initial condition
ModelInit_PosE = [0, 0, -100];
ModelInit_VelB = [0, 0, 0];
ModelInit_AngEuler = [0, 0, 0];
ModelInit_RateB = [0, 0, 0];
ModelInit_Rads = 557.142;

%max control angle,default 35deg
MAX_CONTROL_ANGLE_ROLL = 35;
MAX_CONTROL_ANGLE_PITCH  = 35;
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
PosControl_tune

