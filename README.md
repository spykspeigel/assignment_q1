# assignment_q1

## To build the project use the following commands.

`mkdir -p build`

`cd build`

`cmake ../ -DCMAKE_BUILD_TYPE=RelWithDebInfo`

`make`

`sudo make install`


## To run the controller:

`roscore`

`rosrun mc_rtc_ticker mc_rtc_ticker`

`roslaunch mc_rtc_ticker display.launch`
