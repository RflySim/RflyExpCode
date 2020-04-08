%The influence of the parameter tao on the filtering effect
clear;
load logdata
n = length(ax);  %Number of data collected
Ts = zeros(1,n);  %time interval
Ts(1) = 0.004;

for k =1:n-1
    Ts(k+1) = (timestamp(k + 1) - timestamp(k))*0.000001;
end

theta_cf = zeros(3, n);  %roll calculated from complementary filtering, unit: rad
phi_cf = zeros(3, n);  %pitch calculated from complementary filtering, unit: rad
tao = 0.001;
%@


t = timestamp*0.000001;
rad2deg = 180/pi;
figure(1)
plot(t, theta_cf(1, :)*rad2deg, 'g', t, theta_cf(2, :)*rad2deg, 'b', t, theta_cf(3, :)*rad2deg, 'r')
legend('0.01', '0.1', '1');
xlabel('t(s)')
ylabel('theta(deg)')
title('Parameter tao effect')

