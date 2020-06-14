    You can do basic experiment using the models in 'e5\e5.1'.
    'e5\e5.1\Sim' is used for Simulink simulation of a quadcopter and analyze the function of control allocation.
    'e5\e5.1\tune' is used for analyzing the performance of the control system.
    'e5\e5.1\HIL' is used for performing the HIL simulation.

    The Simulink model in 'e5\e5.2' is similar to that in 'e5\e5.1\tune', which is uesd for adjusting and analyzing
the performance of the control system.

    'e5\e5.3' contains the attitude control model we design in analysis experiment.

    'e5\e5.4' contains the file for flight test and flight data analysis.Before you open the file 
'e4\e4.4\AttitudeControl_FLY.slx', you'd better add custom logger data as follows:
    (1) Create customized message."costom_attctrl_e5.msg" is the customized message, which should be put in "Firmware/msg/";
    (2) Modify "Firmware/msg/CmakeLists.txt". Add the follow words in the 'set()'':
        costom_attctrl_e5.msg.msg
    (3) Modify "Firmware/src/modules/logger/logger.cpp". Add the follow words in add_common_topics():
        add_topic( "costom_attctrl_e5", 4);
        Where "costom_attctrl_e5" is the name of message, "4" is logging period. That is, the system records the
        data with a sampling period of 4ms.
    All the modified files are put in 'e5\e5.4\PSPfile' as an example.
    
 