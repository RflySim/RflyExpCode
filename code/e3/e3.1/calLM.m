%File Description:
%  According to the accelerometer error model, the accelerometer error model parameters are calculated using the lm optimization algorithm.
close all
clc
clear

load AccRaw  %Load uncalibrated accelerometer value
g = 9.8;
m = length(AccRaw);

y_dat = g*ones(m, 1);  %Expected gravitational acceleration value  
p0 = [1 1 1 0 0 0]';
p_init = [1.0 1.0 1.0 0.1 0.1 0.1]';  %Accelerometer error model parameter initial value

y_raw = calFunc(AccRaw, p0);  %2-norm of uncalibrated accelerometer value
y_raw = y_raw(:);
%The difference between the uncalibrated gravitational acceleration measured by the accelerometer 
%and the standard gravitational acceleration
r_raw = y_dat - y_raw;  
p_fit = lm('calFunc', p_init, AccRaw, y_dat);
y_lm = calFunc(AccRaw, p_fit);  %2-norm of calibrated accelerometer value
y_lm = y_lm(:);
r_lm = y_dat - y_lm;

kx = p_fit(1);
ky = p_fit(2);
kz = p_fit(3);
bx = p_fit(4);
by = p_fit(5);
bz = p_fit(6);

Ka9_8 = [kx 0 0; 0 ky 0; 0 0 kz]
ba9_8 = [bx by bz]'
save('calP9_8', 'Ka9_8', 'ba9_8')

figure
bar([r_raw'*r_raw, r_lm'*r_lm])
grid on;
set(gca, 'XTickLabel', {'raw', 'lm'});
ylabel('fa');

t=1:m;
figure
title('Accelerometer Calibration')
plot(t, r_raw, t, r_lm)
legend('Uncalibrated', 'Calibrated-LM')
xlabel('Measurement sampling number')
ylabel('Residual')
