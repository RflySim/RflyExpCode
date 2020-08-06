    'e5\e5.4' contains the file for flight test and flight data analysis.Before you open the file 
'e4\e4.4\AttitudeControl_FLY.slx', you'd better add custom logger data as follows:
    (1) Create customized message."costom_attctrl_e5.msg" is the customized message, which should be put in "Firmware/msg/"; Note for PX4 firmware 1.9 and Above, the "uint64 timestamp" should be added on the top of msg file. Please refer to the demo file "PSPfile/PX4_1.9andAbove/costom_attctrl_e5.msg"
    (2) Modify "Firmware/msg/CmakeLists.txt". Add the follow words below the "set(msg_files":
        costom_attctrl_e5.msg
    (3) Modify "Firmware/src/modules/logger/logger.cpp" (If you are using PX4 1.11 and above, please modify "Firmware/src/modules/logger/logged_topics.cpp"). Add the follow words in add_default_topics():
        add_topic( "costom_attctrl_e5", 4);
where "costom_attctrl_e5" is the name of message, "4" is logging period. That is, the system records the data with a sampling period of 4ms, i.e., 250Hz.
    
 