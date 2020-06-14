[datapoints, numpoints] = px4_read_binary_file('./rawdataFile/e3_m_A.bin');

mag = datapoints;
save MagRaw mag
figure(1)
plot3(mag(1,:),mag(2,:),mag(3,:),'*')
title('Magnetometer calibration sampling')
xlabel('x(Gs_)'); ylabel('y(Gs)'); zlabel('z(Gs)');
axis equal