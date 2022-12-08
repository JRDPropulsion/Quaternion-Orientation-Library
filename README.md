# Quaternion-Orientation-Library
This is a library that takes in raw gyroscope measurements in radians / second and outputs the correct angle of the gyroscope.

* Note that this library is under developement and will take time to be fully functional. As of 12/5/22, 
this library functions to convert raw gyro rates in radians / seconds to quaternions and then to Euler Angles.
The roll, pitch, and yaw angles do not yet restrict singularities, so upon reacing each singularity, all angles will be incorrect. *

Future developments include:
- The addition of a user guide that explains how the code works and how to use it effectively
- Easier to use functions and function names
- An example sketch
