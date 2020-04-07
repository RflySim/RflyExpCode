px4demo_ParameterUpdate_CSC_example.slx
This model is used to update the parameters with QGC. Note, that you may need to delete the parameters.xml 
file to properly update the list of parameters. This file is located :
C:\px4_firmware_test\Firmware\build_<fimware_variant>\parameters.xml
Where <firmware_variant> could be px4fmu-v3_default or px4fmu-v2_default, etc


Use the 'px4_simulink_app_params.c' file to define the new parameters that will show up in QGC
