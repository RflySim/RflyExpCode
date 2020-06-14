function [ phi_cf, theta_cf ] = Attitude_cf(dt, z, phi_cf_k, theta_cf_k, tao)
%Function description:
%  complementary filter  for attitude estimation.
%Input:
%  dt: sampling time, unit: s
%  z: three-axis gyroscope and three-axis accelerometer data, [gx, gy, gz, ax, ay, az]', unit: rad/s, m/s2
%  phi_cf_k, theta_cf_k: angle value of the previous sampling, unit: rad
%  tao: filter coefficient
%Output:
%  phi_cf, theta_cf: attitude angle, unit: rad

    gx = z(1); gy = z(2);
    ax = z(4); ay = z(5); az = z(6);
    
    % calculate Euler angles using accelerometer data
    g = sqrt(ax*ax + ay*ay + az*az);
    theta_am = asin(ax/g);
    phi_am = -asin(ay/(g*cos(theta_am)));
    
    % complementary filtering
    theta_cf = tao/(tao + dt)*(theta_cf_k + gy*dt) + dt/(tao + dt)*theta_am;
    phi_cf = tao/(tao + dt)*(phi_cf_k + gx*dt) + dt/(tao + dt)*phi_am;
end
