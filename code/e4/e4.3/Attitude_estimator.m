clear;
load logdata
n = length(ax);  % number of collected data 
Ts = zeros(1,n);  % samping time
Ts(1)  =0.004;

for k = 1 : n-1
    Ts(k+1) = (timestamp(k + 1) - timestamp(k))*0.000001;
end

theta_am = zeros(1, n);  % roll calculated from accelerometer data, unit: rad
phi_am = zeros(1, n);  % pitch calculated from accelerometer data, unit: rad
theta_gm = zeros(1, n);  %roll calculated from gyroscope data, unit: rad
phi_gm = zeros(1, n);  %pitch calculated from gyroscope data, unit: rad
theta_cf = zeros(1, n);  %roll calculated from complementary filter
phi_cf = zeros(1, n);  %pitch calculated from complementary filter
phi_ekf = zeros(1, n);  %roll calculated from EKF
theta_ekf = zeros(1, n);  %pitch caculated from EKF

tao = 0.3;
w = [0.08, 0.01];  % system noise
v = 50;  % measurement noise
  
P_aposteriori = zeros(6, 6, n);
P_aposteriori(:, :, 1)=eye(6, 6)*100;  %P0
x_aposteriori = zeros(6, n);
x_aposteriori(:, 1) = [0, 0, 0, 0, 0, -1];  %X0

for k = 2 : n
     % calculate Euler angles using accelerometer data
    g = sqrt(ax(k)*ax(k) + ay(k)*ay(k) + az(k)*az(k));
    theta_am(k) = asin(ax(k)/g);
    phi_am(k) = -asin(ay(k)/(g*cos(theta_am(k))));
    % calculate Euler angles using gyroscope data
    theta_gm(k) = theta_gm(k - 1) + gy(k)*Ts(k);
    phi_gm(k) = phi_gm(k - 1) + gx(k)*Ts(k);
    % complementary filter and EKF
    z = [gx(k), gy(k), gz(k), ax(k), ay(k), az(k)];
    [ phi_cf(k), theta_cf(k) ] = Attitude_cf(Ts(k), z', phi_cf(k - 1), theta_cf(k - 1), tao);
    [x_aposteriori(1 : 6, k), P_aposteriori(1 : 6, 1 : 6, k), phi_ekf(k), theta_ekf(k)] = Attitude_ekf(Ts(k), z', w, v, x_aposteriori(1 : 6, k - 1), P_aposteriori(1 : 6, 1 : 6, k - 1));
end

t = timestamp*0.000001;
rad2deg = 180/pi;

figure(1)
plot(t, theta_cf*rad2deg, 'g', t, theta_ekf*rad2deg, 'r', t, theta_px4*rad2deg, 'c')
legend('cf', 'ekf', 'px4');
xlabel('t(s)')
ylabel('theta(deg)')
title('pitch-fly')
figure(2)
plot(t, theta_am*rad2deg, 'g', t, theta_gm*rad2deg, 'c', t, theta_ekf*rad2deg, 'r')
legend('am', 'gm', 'ekf');
xlabel('t(s)')
ylabel('theta(deg)')
title('pitch-fly')

figure(3)
plot(t, phi_cf*rad2deg, 'g', t, phi_ekf*rad2deg, 'r', t, phi_px4*rad2deg, 'c')
legend('cf', 'ekf', 'px4');
xlabel('t(s)')
ylabel('theta(deg)')
title('roll-fly')
figure(4)
plot(t, phi_am*rad2deg, 'g', t, phi_gm*rad2deg, 'c', t, phi_ekf*rad2deg, 'r')
legend('am', 'gm', 'ekf');
xlabel('t(s)')
ylabel('phi(deg)')
title('roll-fly')
