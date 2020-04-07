clear;
%Initial condition
ModelInit_Rads = 557.1420;  %Initial motor speed(rad/s)

%Motor parameters
ModelParam_motorCr = 1148; %Motor throttle-speed curve slope(rad/s)
ModelParam_motorWb = -141.4;  %Motor throttle-speed curve constant term(rad/s)
ModelParam_motorT = 0.02;  %Motor inertia time constant(s)
ModelParam_motorJm = 0.0001287;    %Moment of inertia of motor rotor + propeller(kg.m^2)

%Propeller parameters
%Rotor torque coefficient£¨N.m/(rad/s)^2£©
%Definition: Torque M (N.m), propeller speed w (rad/s), M = Cm*w^2
ModelParam_rotorCm = 1.779e-07;
%Rotor thrust coefficient£¨N/(rad/s)^2£©
%Definition: Tensile force T (N), T = Ct**w^2
ModelParam_rotorCt = 1.105e-05;

ModelParam_uavCd = 0.055;   %Damping coefficient(N/(m/s)^2)
ModelParam_uavCCm = [0.0035 0.0039 0.0034]; %Damping moment coefficient vector(N/(m/s)^2)
ModelParam_uavMass = 1.4; %Mass of UAV(kg)
ModelParam_uavR = 0.225;  %Body radius(m)
ModelParam_uavJxx = 0.0211;
ModelParam_uavJyy = 0.0219; 
ModelParam_uavJzz = 0.0366;
%Moment of inertia matrix
ModelParam_uavJ= [ModelParam_uavJxx, 0, 0;...
    0, ModelParam_uavJyy, 0;...
    0, 0, ModelParam_uavJzz];

ModelParam_envGravityAcc = 9.8;  %Gravity acceleration(m/s^2)
