%  Please complete the section using the "%@" logo before run the code.
close all
clear
load accdata.mat  % raw accelerometer data collected
%% load calibration parameters
%@ load calP1.mat
%@ load ../e3.1/calP9_8.mat

acc_1 = Ka1*(acc - ba1);  % calibrated accelerometer data
acc_9_8 = Ka9_8*(acc - ba9_8);  

n = length(acc);
roll_1 = zeros(1, 100);
pitch_1 = zeros(1, 100);
roll_9_8 = zeros(1, 100);
pitch_9_8 = zeros(1, 100);
for k = 1:100
    g = normest(acc_1(:, k));
    roll_1(k) = asin(acc_1(1, k)./g);
    pitch_1(k) = -asin(acc_1(2,k)./(g.*cos(roll_1(k))));
    g = normest(acc_9_8(:, k));
    roll_9_8(k) = asin(acc_9_8(1, k)./g);
    pitch_9_8(k) = -asin(acc_9_8(2, k)./(g.*cos(roll_9_8(k))));
end
t = 1:100;
figure(1)
plot(t, pitch_9_8, '*-', t, pitch_1, '^-');
title('pitch')
legend('g=9.8', 'g=1.0')
xlabel('Sampling sequence');ylabel('angle/rad/s');
