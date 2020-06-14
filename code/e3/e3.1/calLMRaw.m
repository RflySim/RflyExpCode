%File Description:
%  Unknown parameters in accelerometer error model are calculated using the
%  lm optimization algorithm.
%  Please complete the section using the "%@" logo before run the code.
close all
clc
clear

%% Decode the binary data
%datapoints are 6-dimensional array, the first three are the values of the
%accelerometer; the last three are feature points.
%@ [datapoints, numpoints] = px4_read_binary_file(' ');

%% Get uncalibrated data
 %Accelerometer calibration parameters in the Pixhawk autopilot which can
 %be obtained from QGC
 %@ CAL_ACC_SCALE= ;  % 3*1 
 %@ CAL_ACC_OFF= ;  % 3*1

acc_acq = find(datapoints(4, :));  % find the position of feature points 
g = 9.8;
AccPX4 = datapoints(4:6, acc_acq);
datapoints(1:3, :) = (datapoints(1:3, :) + CAL_ACC_OFF) ./CAL_ACC_SCALE;
datapoints(4:6, acc_acq) = (datapoints(4:6, acc_acq) + CAL_ACC_OFF) ./CAL_ACC_SCALE;
plot_data(datapoints, acc_acq);

AccRaw = datapoints(4:6, acc_acq);  % raw data
m=length(AccRaw);

%% calibration procedure
y_dat = g*ones(m, 1); % expected gravitational acceleration
p0 = [1 1 1 0 0 0]';
p_init = [1.0 1.0 1.0 0.1 0.1 0.1]';  % initial value of unknown parameters

y_raw = calFunc(AccRaw, p0);  % gravitational acceleration measured by accelerometer
y_raw = y_raw(:);

r_raw = y_dat - y_raw;
p_fit = lm('calFunc', p_init, AccRaw, y_dat); 
y_lm = calFunc(AccRaw, p_fit);  % gravitational acceleration measured by calibrated accelerometer
y_lm = y_lm(:);
r_lm = y_dat - y_lm;

kx = p_fit(1);
ky = p_fit(2);
kz = p_fit(3);
bx = p_fit(4);
by = p_fit(5);
bz = p_fit(6);

%% print and save the parameters
Ka9_8=[kx 0 0;0 ky 0;0 0 kz]
ba9_8=[bx by bz]'
save('calP9_8', 'Ka9_8', 'ba9_8')

figure
bar([r_raw'*r_raw,r_lm'*r_lm])
grid on;
set(gca,'XTickLabel', {'raw','lm'});
ylabel('fa');

t = 1:m;
figure
title('Accelerometer Calibration')
plot(t, r_raw, t, r_lm)
legend('Uncalibrated','Calibrated-LM')
xlabel('Sampling sequence')
ylabel('Residual')

function plot_data(datapoints, acc_acq)
    fprintf('***Accelerometer data collected***¡£\n')
    fprintf('***The collected data are averaged from the previous 100 data points***\n')

    figure
    plot(1:length(datapoints), datapoints(1,:))
    hold on
    plot(acc_acq, datapoints(4,acc_acq), '*')
    legend('Accelerometer data(ax)','Feature point')
    title('x-axis accelerometer sampling data')
    hold off
    figure
    plot(1:length(datapoints), datapoints(2,:))
    hold on
    plot(acc_acq, datapoints(5, acc_acq), '*')
    legend('Accelerometer data(ay)', 'Feature point')
    title('y-axis accelerometer sampling data')
    hold off
    figure
    plot(1:length(datapoints), datapoints(3,:))
    hold on
    plot(acc_acq, datapoints(6,acc_acq), '*')
    legend('Accelerometer data(az)', 'Feature point')
    title('z-axis accelerometer sampling data')
    hold off
end
