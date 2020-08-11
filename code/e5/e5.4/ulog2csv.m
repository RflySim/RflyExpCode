function ulog2csv(ulogfile, outputFileName)
%ulogfile : .ulg data file
%outputFileName
%usage£ºulog2csv('log001.ulg','log001')
if exist(ulogfile,'file')
    dirNmae=[userpath,'\ulogTmp'];
    if exist(dirNmae,'dir')
        rmdir(dirNmae,'s');    
    end    
    mkdir(dirNmae);  
    mkdir([dirNmae,'\',outputFileName]); 
    
    copyfile(ulogfile,dirNmae,'f');
    
    pathstr = dirNmae;
    pathstr=strrep(pathstr,':','');
    pathstr=strrep(pathstr,'\','/');
    pathstr(1)=lower(pathstr(1));
    pathstr1=['/mnt/',pathstr];
    pathstr1=strrep(pathstr1,' ','\ ');
    
    PSPFold='PX4PSP';
    if exist([userpath,'\Add-Ons\Toolboxes\PX4 PSP'],'dir')
        PSPFold='PX4 PSP';
    end
    
if exist([userpath,'\Add-Ons\Toolboxes\',PSPFold,'\code\+codertarget\+Pixhawk\+CMAKE_Utils\FirmwareVersion.mat'],'file')
    load([userpath,'\Add-Ons\Toolboxes\',PSPFold,'\code\+codertarget\+Pixhawk\+CMAKE_Utils\FirmwareVersion.mat']);
    if exist('buildToolchain','var')
        toolchainType=buildToolchain;
        
        if toolchainType == '1'
            command = ['wsl ','cd ~; ulog2csv ','-o ',pathstr1,'/',outputFileName,'/ ',pathstr1,'/',ulogfile,''];
        else
            defaultPX4Path = 'C:\PX4PSP';
            if exist([userpath,'\Add-Ons\Toolboxes\',PSPFold,'\code\+codertarget\+Pixhawk\+CMAKE_Utils\CmakeInfo.mat'],'file')
                load([userpath,'\Add-Ons\Toolboxes\',PSPFold,'\code\+codertarget\+Pixhawk\+CMAKE_Utils\CmakeInfo.mat']);
                if~isempty(Px4PSP_CmakeInfo.Px4_Base_Dir)
                    defaultPX4Path=Px4PSP_CmakeInfo.Px4_Base_Dir;
                end
            end             
            Px4_Base_Dir_win = defaultPX4Path;
            if toolchainType == '3'
                command = [Px4_Base_Dir_win(1:2),' && cd ',Px4_Base_Dir_win,'\CygwinToolchain && CALL setPX4Env.bat && bash -l -i -c ''ulog2csv ','-o ',pathstr1,'/',outputFileName,'/ ',pathstr1,'/',ulogfile,''''];
            else
                command = [Px4_Base_Dir_win(1:2),' && cd ',Px4_Base_Dir_win,'\PX4Msys2Toolchain && CALL setPX4Env.bat && bash -l -i -c '' ulog2csv ','-o ',pathstr1,'/',outputFileName,'/ ',pathstr1,'/',ulogfile,''''];
            end
        end
        
    else
        error('The PSP Toolbox is not corectlly installed.');
    end
end    
  status = system(command);
  if status
    fprintf(2,'Error: Make sure this code executes in the same workspace as the data file!\n');
  else
      copyfile([dirNmae,'\',outputFileName],[pwd,'\',outputFileName],'f');
    disp('*******The conversion is complete!*******');
  end
    if exist(dirNmae,'dir')
        rmdir(dirNmae,'s');    
    end   
else
    error('file does not exist!');
end
