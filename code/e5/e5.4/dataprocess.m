clear
close all
%@ filename = 'log001';
if ~exist(filename,'file')
    ulog2csv([filename,'.ulg'],filename);
end

% csvname = ['./',filename,'/',filename,'_costom_attctrl_e5_0.csv'];
% M = xlsread(csvname);
% 
% timestamp = M(:,1)*1e-6;  % s
% pitch = M(:,3);
% 
% figure
% plot(timestamp,pitch)