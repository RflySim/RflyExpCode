function [ x_aposteriori, P_aposteriori, phi, theta] = Attitude_ekf( dt, z, q, r, x_aposteriori_k, P_aposteriori_k)
%Function description:
%  Extended Kalman Filter for State Estimation
%Input:
%  dt: sampling time
%  z: measurement data (6,1)
%  q: system noise, r: measurement noise
%  x_aposteriori_k: estimated state at the last moment (6,1)
%  P_aposteriori_k: error covariance at the last moment (6,6)
%Output:
%  x_aposteriori£ºestimated state at current time (6,1)
%  P_aposteriori£ºerror covariance at the current moment (6,6)
%  roll¡¢pitch£ºEuler angle, unit: rad

w_m = z(1:3);  % angular velocity measurement
a_m = z(4:6);  % acceleration measurement
g = norm(a_m,2);   % gravitational acceleration
%   w_x_=[ 0,-(wz-bzg, wy-byg;
%         wz-bzg, 0 ,-(wx-bxg);
%         -(wy-byg), wx-bxg, 0];
w_x_ = [0, -(w_m(3) - x_aposteriori_k(3)), w_m(2) - x_aposteriori_k(2);
      w_m(3) - x_aposteriori_k(3), 0, -(w_m(1) - x_aposteriori_k(1));
      -(w_m(2) - x_aposteriori_k(2)), w_m(1) - x_aposteriori_k(1), 0];
     
bCn = eye(3, 3) - w_x_*dt;

%% predict
% update a priori state matrix
  x_apriori = zeros(1, 6);
  x_apriori(1: 3) = x_aposteriori_k(1 : 3);  % angular velocity drift
  x_apriori(4 : 6) = bCn*x_aposteriori_k(4 : 6);   % normalized acceleration
  
%[x]x
  x_aposteriori_k_x = [0, -x_aposteriori_k(6), x_aposteriori_k(5);
                        x_aposteriori_k(6), 0, -x_aposteriori_k(4);
                        -x_aposteriori_k(5), x_aposteriori_k(4), 0];
% update state transition matrix
PHI = [eye(3, 3), zeros(3, 3);
         -x_aposteriori_k_x*dt, bCn];
GAMMA = [eye(3, 3)*dt, zeros(3, 3);
       zeros(3, 3), -x_aposteriori_k_x*dt];

Q = [eye(3, 3)*q(1), zeros(3, 3);
   zeros(3, 3), eye(3, 3)*q(2)];
 % prediction error covariance matrix
 P_apriori = PHI*P_aposteriori_k*PHI' + GAMMA*Q*GAMMA';
%% update
 R = eye(3, 3)*r(1);
 H_k = [zeros(3, 3), -g*eye(3, 3)];
 % Kalman gain
 K_k = (P_apriori*H_k')/(H_k*P_apriori*H_k' + R);
  % state estimate update
 x_aposteriori = x_apriori' + K_k*(a_m - H_k*x_apriori');
 % error covariance update
 P_aposteriori = (eye(6, 6) - K_k*H_k)*P_apriori;
  %% calculate roll, pitch
  k = x_aposteriori(4 : 6) /norm(x_aposteriori(4 : 6), 2);
  
  phi = atan2(k(2), k(3));
  theta = -asin(k(1));
end

