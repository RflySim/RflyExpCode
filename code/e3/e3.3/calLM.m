%File Description:
%  Unknown parameters in magnetometer error model are calculated using the
%  lm optimization algorithm.
close all
clc
clear
load MagRaw.mat
%magnetometer calibration parameters in the Pixhawk autopilot which can
 %be obtained from QGC
CAL_MAG_SCALE = [1, 1, 1]'; 
CAL_MAG_OFF = [0.064, 0.014, -0.053]';
MagRaw = (mag + CAL_MAG_OFF)./CAL_MAG_SCALE;  % raw data

m = length(MagRaw);
MagSum = 0;
for k = 1 : m
    MagSum = MagSum + norm(MagRaw(:, k));
end
MagAver = MagSum/m;  % estimated magnetic field strength 
Vdata = MagRaw/MagAver;  % normalization


y_dat = ones(m, 1);
p0 = [1 1 1 0 0 0]';
p_init = [1 1 1 0.01 0.01 0.01]';  % initial value of unknown parameters
 
y_raw = calFunc(Vdata, p0);  %magnetic field strength measured by magnetometer
y_raw = y_raw(:);
r_raw = y_dat - y_raw;
p_fit = lm('calFunc', p_init, Vdata, y_dat, 0.001);
y_lm = calFunc(Vdata, p_fit);  % magnetic field strength measured by calibrated magnetometer
y_lm = y_lm(:);
r_lm = y_dat - y_lm;
y_px4 = calFunc(mag/MagAver, p0);  % magnetic field strength measured by calibrated magnetometer of PX4
y_px4 = y_px4(:);
r_px4 = y_dat - y_px4;

kx = p_fit(1);
ky = p_fit(2);
kz = p_fit(3);
bx = p_fit(4);
by = p_fit(5);
bz = p_fit(6);

Km = [kx 0 0;0 ky 0;0 0 kz]
bm = [bx by bz]'

figure
bar([r_raw'*r_raw, r_lm'*r_lm, r_px4'*r_px4])
grid on;
set(gca, 'XTickLabel', {'raw','lm','px4'});
ylabel('Index');

t=1:m;
figure
title('Magnetometer Calibration')
plot(t, r_raw, '-.', t, r_lm, '-')
legend('Uncalibrated','Calibrated-LM')
xlabel('Measurement sampling number')
ylabel('Residual')
