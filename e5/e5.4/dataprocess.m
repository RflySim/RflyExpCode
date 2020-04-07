clear
close all
%@ filename = 'log001';
if ~exist(filename,'file')
    ulog2csv([filename,'.ulg'],filename);
end
csvname = ['./',filename,'/',filename,'_costom_attctrl_e5_0.csv'];
M = xlsread(csvname);
interval = 305:434;
timestamp = M(:,1)*1e-6;%s
pitch = M(:,3);

figure
plot(timestamp(interval)-timestamp(interval(1)),pitch(interval))