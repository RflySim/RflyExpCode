    ADRC law is greatly affected by the execution frequency of the controller. HIL simulation cannot reflect the actual flight performance due to its unstable execution frequency. The parameters in 'FLY' are tested on a real aircraft, but when you apply them to your own aircraft, you need to re-turn. 

    The following steps can help you tune custom parameters in QGC
1. Use the 'px4_simulink_app_params.c' file to define the new parameters that will show up in QGC
2. simulink configuration
Configuration Parameters->Code Generation->Custom Code
Insert custom C code in generated:Header file
#include <px4_config.h>
#include <px4_tasks.h>
#include <px4_posix.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
Additional build information:Source files
px4_simulink_app_params.c
3. delete the parameters.xml 
This file is located :
C:\PX4PSP\Firmware\build_<fimware_variant>\parameters.xml
Where <firmware_variant> could be px4fmu-v3_default or px4fmu-v2_default, etc

