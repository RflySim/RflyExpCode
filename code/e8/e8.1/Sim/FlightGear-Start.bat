C:
cd C:\Program Files\FlightGear 2016.1.2

SET FG_ROOT=C:\Program Files\FlightGear 2016.1.2\data
.\\bin\fgfs --aircraft=F450 --fdm=null --native-fdm=socket,in,30,127.0.0.1,5502,udp --native-ctrls=socket,out,30,127.0.0.1,5505,udp --fog-fastest --disable-clouds --start-date-lat=2017:06:01:21:00:00 --disable-sound --in-air --disable-freeze --airport=KSF0 --runway=10L --altitude=0 --heading=0 --offset-distance=0 --offset-azimuth=0 --timeofday=noon
