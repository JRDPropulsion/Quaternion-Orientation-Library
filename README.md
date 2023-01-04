# Quaternion-Orientation-Library
This is a library that takes in raw gyroscope measurements in radians / second and outputs the correct attitude measurement.

Note that this library is under developement and will take time to be fully functional. As of 1/5/23, 
this library functions to convert raw gyro rates in radians / second to quaternions and then to Euler Angles.
The roll, pitch, and yaw angles do not yet restrict singularities, so upon reacing each singularity, all angles will be incorrect.

How to implement:

Step 1:
You need to make sure that you have a library for your IMU of choice and include that in the libraries folder of your IDE.

Step 2:
Put all of the necessary functions of your IMU that are stated in comments in the example file. 
Make sure that the input to the quaternion library are in RAD / SEC otherwise it will not work. This is a common mistake.

Step 3:
Run the example file and the orientation will print to your serial monitor. Depending on yout IMU configuration,
your roll, pitch, or yaw may have euler singularities at +-90 degrees. This means that if the IMU is rotated and the orientation reaches
+-90, the orientation readings will be incorrect. This will be soon fixed in a future update.
