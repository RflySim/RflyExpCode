    You can do basic experiment using the models in 'e5\e5.1'.
    'e5\e5.1\Sim' is used for Simulink simulation of a quadcopter and analyze the function of control allocation.
    'e5\e5.1\tune' is used for analyzing the performance of the control system.
    'e5\e5.1\HIL' is used for performing the HIL simulation.

    The Simulink model in 'e5\e5.2' is similar to that in 'e5\e5.1\tune', which is uesd for adjusting and analyzing
the performance of the control system.

    'e5\e5.3' contains the attitude control model we design in analysis experiment.

    'e5\e5.4' contains the file for flight test and flight data analysis.Before you open the file 
'e4\e4.4\AttitudeControl_FLY.slx', you'd better add custom logger data as follows:
    (1) Create customized message."costom_attctrl_e5.msg" is the customized message, which should be put in "Firmware/msg/"; Note that, for PX4 firmware 1.9 and Above, the "uint64 timestamp" should be added on the top of the msg file. Please refer to the demo file "PSPfile/PX4_1.9andAbove/costom_attctrl_e5.msg";
    (2) Modify "Firmware/msg/CmakeLists.txt". Add the follow words below the "set(msg_files":
        costom_attctrl_e5.msg
    (3) Modify "Firmware/src/modules/logger/logger.cpp" (If you are using PX4 1.10 and above, please modify "Firmware/src/modules/logger/logged_topics.cpp"). Add the follow words in add_default_topics():
        add_topic( "costom_attctrl_e5", 4);
        Where "costom_attctrl_e5" is the name of message, "4" is logging period. That is, the system records the data with a sampling period of 4ms.
    
 