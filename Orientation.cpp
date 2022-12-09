/*
  Orientation.h - Library for retrieving orientation.
  Created by Aryan Kapoor, 12/4/22.
  Released into the public domain.
*/


#include "Arduino.h"
#include "Orientation.h"
#include "BNO055.h"
#include <tuple>

double q[4] = {1, 0, 0, 0};
double w[4] = {0, 0, 0, 0};
double a[4] = {0, 0, 0, 0};


double Orientation::quaternion_update(double gyro_x, double gyro_y, double gyro_z, double dt, double *px, double *py, double *pz)
{   
    double axis_x = gyro_x * dt;
    double axis_y = gyro_y * dt;
    double axis_z = gyro_z * dt;
    
    //Calulates the normalized quaternion and ensures that the equation never divides by zero by defining a magnitude.
    double axis_mag = max(1e-12, sqrt((axis_x * axis_x) + (axis_y * axis_y) + (axis_z * axis_z)));

    //Definition of Quaternion W. Quaternion W combines gyro measurements to get it in reference to the IMU.
    w[0] = cos(axis_mag / 2);
    w[1] = axis_x / axis_mag * sin(axis_mag / 2);
    w[2] = axis_y / axis_mag * sin(axis_mag / 2);
    w[3] = axis_z / axis_mag * sin(axis_mag / 2);
    
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
 
    double qw = q[0];
    double qx = q[1];
    double qy = q[2];
    double qz = q[3];

    double sinx_cosp = 2 * ((qw * qx) + (qy * qz));
    double cosx_cosp = 1 - (2 * ((qx * qx) + (qy * qy)));
    double sinz_cosp = 2 * ((qw * qz) + (qx * qy));
    double cosz_cosp = 1 - (2 * ((qz * qz) + (qy * qy)));

    double orientation_x = (180 / PI) * (atan2(sinz_cosp, cosz_cosp));
    double orientation_y = (180 / PI) * (atan2(sinx_cosp, cosx_cosp));
    double orientation_z = (180 / PI) * (asin(2 * ((qw * qy) - (qz * qx))));

    *px = orientation_x;
    *py = orientation_y;
    *pz = orientation_z;

    return 0;
}

