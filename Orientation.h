/*
  Orientation.h - Library for retrieving orientation.
  Created by Aryan Kapoor, 12/4/22.
  Released into the public domain.
*/


#ifndef Orientation_h
#include "Arduino.h"


// Defines Orientation class
class Orientation
{
    public:
        double quaternion_update(double gyro_x, double gyro_y, double gyro_z, double dt, double *px, double *py, double *pz);
        double x();
        double y();
        double z();

    private:
};

#endif
