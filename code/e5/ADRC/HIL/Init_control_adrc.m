%%% AttitudeControl_ADRC_HIL 
clear
path('./icon/',path);

%Constant value
RAD2DEG = 57.2957795;
DEG2RAD = 0.0174533;
%throttle when UAV is hovering
THR_HOVER = 0.609;

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
%Throttle amplitude
MAX_MAN_THR=0.9;
MIN_MAN_THR=0.05;

%parameters in adrc
TD_R = Pixhawk_CSC.Parameter({single(100), 'SL_TD_R'});
TD_H = Pixhawk_CSC.Parameter({single(1), 'SL_TD_H'});
NLSEF_R = Pixhawk_CSC.Parameter({single(220), 'SL_NLSEF_R'});
NLSEF_H = Pixhawk_CSC.Parameter({single(25), 'SL_NLSEF_H'});
NLSEF_C = Pixhawk_CSC.Parameter({single(6), 'SL_NLSEF_C'});
ESO_B01 = Pixhawk_CSC.Parameter({single(250), 'SL_ESO_B01'});
ESO_B02 = Pixhawk_CSC.Parameter({single(6000), 'SL_ESO_B02'});
ESO_B03 = Pixhawk_CSC.Parameter({single(1000), 'SL_ESO_B03'});
ESO_B0 = Pixhawk_CSC.Parameter({single(47.4), 'SL_ESO_B0'});
ESO_H = Pixhawk_CSC.Parameter({single(1), 'SL_ESO_H'});
ESO_D = Pixhawk_CSC.Parameter({single(0.01), 'SL_ESO_D'});
tau2sigma = single(0.108);
%CSC
RC1_MIN = Pixhawk_CSC.Parameter({single(1050), 'RC1_MIN'});
RC1_MAX = Pixhawk_CSC.Parameter({single(1950), 'RC1_MAX'});
RC2_MIN = Pixhawk_CSC.Parameter({single(1050), 'RC2_MIN'});
RC2_MAX = Pixhawk_CSC.Parameter({single(1950), 'RC2_MAX'});
RC3_MIN = Pixhawk_CSC.Parameter({single(1050), 'RC3_MIN'});
RC3_MAX = Pixhawk_CSC.Parameter({single(1950), 'RC3_MAX'});
RC4_MIN = Pixhawk_CSC.Parameter({single(1050), 'RC4_MIN'});
RC4_MAX = Pixhawk_CSC.Parameter({single(1950), 'RC4_MAX'});
%% run simulink model
AttitudeControl_ADRC_HIL 