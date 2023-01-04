/*
  Orientation.h - Library for retrieving orientation.
  Created by Aryan Kapoor, 12/4/22.
  Released into the public domain.
*/


#include "Arduino.h"
#include "Orientation.h"

double q[4] = {1, 0, 0, 0};
double w[4] = {0, 0, 0, 0};
double a[4] = {0, 0, 0, 0};


double Orientation::quaternion_update(double gyro_x, double gyro_y, double gyro_z, double dt, double *px, double *py, double *pz)
{   
    // Quaternion magnitude
    double quat_mag = max(sqrt(abs((gyro_x * gyro_x) + (gyro_y * gyro_y) + (gyro_z * gyro_z))), 1e-12);
    double theta = quat_mag * dt;

    //Definition of Quaternion W. Quaternion W combines gyro measurements to get it in reference to the IMU.
    w[0] = cos(theta / 2.0);
    w[1] = (gyro_x / quat_mag) * sin(theta / 2.0);
    w[2] = (gyro_y / quat_mag) * sin(theta / 2.0);
    w[3] = (gyro_z / quat_mag) * sin(theta / 2.0);
    
    //Definition of Quaternion A. Quaternion A is the same as Quaternion Q but in the previous time frame.
    a[0] = q[0];
    a[1] = q[1];
    a[2] = q[2];
    a[3] = q[3];

    //Gets the Hamiltion product of quaternion A and quaternion W.
    q[0] = (a[0] * w[0]) - (a[1] * w[1]) - (a[2] * w[2]) - (a[3] * w[3]);
    q[1] = (a[0] * w[1]) + (a[1] * w[0]) + (a[2] * w[3]) - (a[3] * w[2]);
    q[2] = (a[0] * w[2]) - (a[1] * w[3]) + (a[2] * w[0]) + (a[3] * w[1]);
    q[3] = (a[0] * w[3]) + (a[1] * w[2]) - (a[2] * w[1]) + (a[3] * w[0]);

    // Calculates the normalized quaternion and ensures that the equation never divides by zero by defining a magnitude.
    double quat_norm = max(sqrt(abs(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3])), 1e-12); // Guaranteed to be a positive number

    double qw = q[0] / quat_norm;
    double qx = q[1] / quat_norm;
    double qy = q[2] / quat_norm;
    double qz = q[3] / quat_norm;

    // Quaternion to Euler conversion
    *px = RAD_TO_DEG * atan2(2.0 * (qw * qx + qy * qz), (qw * qw + qz * qz - qx * qx - qy * qy));
    *py = RAD_TO_DEG * asin(2.0 * (qw * qy - qx * qz));
    *pz = RAD_TO_DEG * atan2(2.0 * (qw * qz + qx * qy), qw * qw + qx * qx - qy * qy - qz * qz);

    return 0;
}

