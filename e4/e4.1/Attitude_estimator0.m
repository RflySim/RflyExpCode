clear;

%@ [datapoints, numpoints] = px4_read_binary_file('e4_A.bin');
ax = datapoints(1, :);  %m/s2
ay = datapoints(2, :);
az = datapoints(3, :);
gx = datapoints(4, :);  %rad/s
gy = datapoints(5, :);
gz = datapoints(6, :);
phi_px4 = datapoints(7, :);  %Roll calculated in PX4, unit: rad
theta_px4 = datapoints(8, :);  %Pitch calculated in PX4, unit: rad
timestamp=datapoints(9, :);  %us

n = length(ax);  %Number of data collected
Ts = zeros(1,n);  %time interval
Ts(1) = 0.004;

for k = 1 : n-1
    Ts(k+1) = (timestamp(k + 1) - timestamp(k))*0.000001;
end

theta_am = zeros(1, n);  %roll calculated from acceleration, unit: rad
phi_am = zeros(1, n);  %pitch calculated from acceleration, unit: rad
theta_gm = zeros(1, n);  %roll from the gyroscope, unit: rad
phi_gm = zeros(1, n);  %pitch from the gyroscope, unit: rad
theta_cf = zeros(1, n);  %roll obtained from complementary filtering, unit: rad
phi_cf = zeros(1, n);  %pitch obtained from complementary filtering, unit: rad
tao = 0.1;
for k = 2 : n
    %Calculate Euler angles using accelerometer data
    %@
    
    %Calculate Euler angles using gyroscope data
    %@
    
    %Complementary filtering
    %@
    
end

t = timestamp*0.000001;
rad2deg = 180/pi;
figure(1)
subplot(2, 1, 1)
plot(t, theta_gm*rad2deg, 'g', t, theta_am*rad2deg, 'b', t, theta_cf*rad2deg, 'r')
legend('gyro', 'acc', 'cf');
ylabel('theta(deg)')
title('pitch')
subplot(2, 1, 2)
plot(t, theta_cf*rad2deg, 'r', t, theta_px4*rad2deg, 'k')
legend('cf', 'px4');
xlabel('t(s)')
ylabel('theta(deg)')


figure(2)
subplot(2, 1, 1)
plot(t, phi_gm*rad2deg, 'g', t, phi_am*rad2deg, 'b', t, phi_cf*rad2deg, 'r')
legend('gyro', 'acc', 'cf');
ylabel('theta(deg)')
title('roll')
subplot(2, 1, 2)
plot(t, phi_cf*rad2deg, 'r', t, phi_px4*rad2deg, 'k')
legend('cf', 'px4');
xlabel('t(s)')
ylabel('theta(deg)')
