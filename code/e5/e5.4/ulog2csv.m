function ulog2csv(ulogfile, outputFileName)
%ulogfile : .ulg data file
%outputFileName
%usage£ºulog2csv('log001.ulg','log001')
if exist(ulogfile,'file')
  mkdir(outputFileName);
  pathstr = pwd;
  pathstr=strrep(pathstr,':','');
  pathstr=strrep(pathstr,'\','/');
  pathstr(1)=lower(pathstr(1));
  pathstr1=['/mnt/',pathstr];

  command = ['C:\Windows\system32\bash.exe -c ','cd ~; ulog2csv ','-o ',pathstr1,'/',outputFileName,'/ ',pathstr1,'/',ulogfile,''];

  status = system(command);
  if status
    error('Make sure this code executes in the same workspace as the data file!');
  else
    disp('*******The conversion is complete!*******');
  end
else
    error('file does not exist!');
end
