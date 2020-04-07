    The instruction package for the basic experiment is e2/e2.1. We copy some system parameters in
'e2/e2.1/icon/Init.m' to 'e2/e2.1/Init_control.m' for your easy modification.

    'e2/e2.3/dynamics.slx' is a quadcopter dynamic model we have established. You can design your own
multicopter dynamic model according to our design style.
    The quadcopter parameters in 'e2/e2.3/Init.m' are obtained by using the system identification method 
for real aircraft, which are also used in the subsequent models.
    'e2/e2.3/myownUAV' is a simple quadcopter model we provide, which includes a 3D model and two xml
configuration files. The model path and parameters in the xml file shoule be consistent with the path 
and parameters of quadcopter model.