# Quaternion-Orientation-Library
This is a library that takes in raw gyroscope measurements in radians / seconds and outputs the correct angle of the gyroscope.

* Note that this library is under developement and will take time to be fully functional. As of 12/5/22, 
this library functions to convert raw gyro rates in radians / seconds to quaternions and then to Euler Angles.
The roll axis is not yet restricted to +-90 degrees so if the gyros are rotated past +-90 degrees,
the pitch and yaw angles get messed up. *

Future developments include:
- The addition of a user guide that explains how the code works and how to use it
- More efficient code taking less space
- More easy to use functions
- An example sketch
