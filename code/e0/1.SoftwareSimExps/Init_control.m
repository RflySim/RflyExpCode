path(path, './icon/');

%模型参数 运行模型初始化文件icon/init.m
Init;


%PID参数
Kp_RP_ANGLE =6.5;
Kp_RP_AgngleRate = 0.55;
Ki_RP_AgngleRate = 0.01;
Kd_RP_AgngleRate = 0.005;

Kp_YAW_AngleRate = 3.2;
Ki_YAW_AngleRate = 0.8;
Kd_YAW_AngleRate = 0.05;
%最大控制角度，单位度
MAX_CONTROL_ANGLE_RP = 45;
MAX_CONTROL_ANGLE_Y = 180;
%最大控制角速度，单位度
MAX_CONTROL_ANGLE_RATE_RP = 180;
MAX_CONTROL_ANGLE_RATE_Y = 90;
