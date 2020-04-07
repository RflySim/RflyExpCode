    This instruction package is used for failsafe logic design experiment.There are many types of failure for 
multicopters, including communication breakdown, sensor failure, and propulsion system anomalies.Here we only 
consider the loss of Radio Control which is the one of communication breakdown.
    First, we realize the basic mode switch between the mannual mode and Return-to-Launch(RTL) as well as switch
between the mannual flight mode and the auto-landing mode in 'e8\e8.1'.
    Next, an design example that a multicopter can switch between the RTL mode and auto-landing mode mannually is presented
in 'e8\e8.2'.
    Finally, we design a logic to realize a multicoper that can return and land automatically under conditions where the
connection to the Radio Control transmitter is abnormal and the sim & HIL model is put in 'e8\e8.3', flight test model is 
put in 'e8\e8.4'.
    
 