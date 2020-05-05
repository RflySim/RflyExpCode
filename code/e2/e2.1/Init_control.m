clear
path('./icon/',path);
Init;

% constant parameters
RAD2DEG = 57.2957795;
DEG2RAD = 0.0174533;
% initial condition
ModelInit_PosE = [0, 0, -100];  %Initial position
ModelInit_VelB = [0, 0, 0];  %Initial velocity
ModelInit_AngEuler = [0, 0, 0];  %Initial Euler angle
ModelInit_RateB = [0, 0, 0];  %Initial angular velocity
ModelInit_Rads = 557.1420; %Initial motor speed(rad/s)

% UAV model parameter
ModelParam_uavMass = 1.4; %Mass of UAV(kg)
ModelParam_uavJxx = 0.0211;
ModelParam_uavJyy = 0.0219; 
ModelParam_uavJzz = 0.0366;
% Moment of inertia matrix
ModelParam_uavJ= [ModelParam_uavJxx, 0, 0;...
    0, ModelParam_uavJyy, 0;...
    0, 0, ModelParam_uavJzz];
ModelParam_uavR = 0.225;   %Body radius(m)

ModelParam_motorCr = 1148; %Motor throttle-speed curve slope(rad/s)
ModelParam_motorWb = -141.4;  %Motor speed-throttle curve constant term(rad/s)
ModelParam_motorT = 0.02;  %Motor inertia time constant(s)
ModelParam_motorJm = 0.0001287;    %Moment of inertia of motor rotor + propeller(kg.m^2)
% M=Cm*w^2
ModelParam_rotorCm = 1.779e-07;    %Rotor torque coefficient(kg.m^2)
% T=Ct**w^2
ModelParam_rotorCt = 1.105e-05;    %Rotor thrust coefficient(kg.m^2)

% calculation formula for hovering throttle
% THR = (sqrt(ModelParam_uavMass*9.8/4/ModelParam_rotorCt) - ModelParam_motorWb)/ModelParam_motorCr;
