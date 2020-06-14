%The influence of the parameter tao on the complementary filter
clear;
load logdata
n = length(ax);  % the number of data collected
Ts = zeros(1,n);  % sampling time
Ts(1) = 0.004;

for k =1:n-1
    Ts(k+1) = (timestamp(k + 1) - timestamp(k))*0.000001;
end

theta_cf = zeros(3, n);  %roll calculated from complementary filtering, unit: rad
phi_cf = zeros(3, n);  %pitch calculated from complementary filtering, unit: rad
tao = 0.001;
%@
for i = 1 : 3
    tao = tao*10;
    for k = 2 : n
        
        g = sqrt(ax(k)*ax(k) + ay(k)*ay(k) + az(k)*az(k));
        theta_am = asin(ax(k)/g);
        phi_am = -asin(ay(k)/(g*cos(theta_am)));
    
        theta_cf(i, k) = tao/(tao + Ts(k))*(theta_cf(i, k - 1) + gy(k)*Ts(k)) + Ts(k)/(tao + Ts(k))*theta_am;
        phi_cf(i,k) = tao/(tao + Ts(k))*(phi_cf(i, k -  1) + gx(k)*Ts(k)) + Ts(k)/(tao + Ts(k))*phi_am;
    end
end

t = timestamp*0.000001;
rad2deg = 180/pi;
figure(1)
plot(t, theta_cf(1, :)*rad2deg, 'g', t, theta_cf(2, :)*rad2deg, 'b', t, theta_cf(3, :)*rad2deg, 'r')
legend('0.01', '0.1', '1');
xlabel('t(s)')
ylabel('theta(deg)')
title('Parameter tao effect')

