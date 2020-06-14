[datapoints, numpoints] = px4_read_binary_file('e4_ekf_A.bin');
roll_ekf = datapoints(1, :);
pitch_ekf = datapoints(2, :);
roll_cf = datapoints(3, :);
pitch_cf = datapoints(4, :);
roll_px4 = datapoints(5, :);
pitch_px4 = datapoints(6, :);
t = datapoints(7, :);
rad2deg = 180/pi;
figure(1)
plot(t, roll_ekf*rad2deg, 'g', t, roll_cf*rad2deg, 'b', t, roll_px4*rad2deg, 'r')
legend('ekf', 'cf', 'px4');
xlabel('time/s');
ylabel('roll/deg')
title('roll-Filter effect comparison')
