/*
  JRD Propulsion Quaternion Orientation Example
  By: Aryan Kapoor
  Last updated on: 1/4/23
*/


// Importing libraries
#include <Arduino.h>
// Include IMU library of choice
#include <Orientation.h>


// Initialization and definitions
Orientation orientation; 

double orientation_x, orientation_y, orientation_z;
double gyro_x, gyro_y, gyro_z, gyro_bais_x, gyro_bais_y, gyro_bais_z;
double gyro_x_cal, gyro_y_cal, gyro_z_cal, orientation_x_offset, orientation_y_offset, orientation_z_offset;
double current_time, previous_time;
int state = 0;


// Finds the gyro bias by taking the average of a set of gyro measurements
void gyro_bias()
{
  // Initialize local gyro sums as 0
  double gyro_x_sum = 0;
  double gyro_y_sum = 0;
  double gyro_z_sum = 0;

  int count = 0;
  int sample_count = 200; // Total number of samples collected

  while (count < sample_count)
  {
    led_blink();
    BNO055.get_gyro(&gyro_x, &gyro_y, &gyro_z);
    gyro_x_sum += gyro_x;
    gyro_y_sum += gyro_y;
    gyro_z_sum += gyro_z;

    Serial.print("X: ");
    Serial.print(gyro_x_sum, 8);
    Serial.print("  Y: ");
    Serial.print(gyro_y_sum, 8);
    Serial.print("  Z: ");
    Serial.println(gyro_z_sum, 8);

    delay(10);
    count += 1;
  }

  // All functions that happen right after the gyro biases are calculated
  if (count == sample_count)
  {
    gyro_bais_x = gyro_x_sum / sample_count;
    gyro_bais_y = gyro_y_sum / sample_count;
    gyro_bais_z = gyro_z_sum / sample_count;

    orientation_x_offset = -(gyro_x_cal);
    orientation_y_offset = -(gyro_y_cal);
    orientation_z_offset = -(gyro_z_cal);

    Serial.print("gyro_bias_x: ");
    Serial.print(gyro_bais_x, 8);
    Serial.print("  gyro_bias_y: ");
    Serial.print(gyro_bais_y, 8);
    Serial.print("  gyro_bias_z: ");
    Serial.println(gyro_bais_z, 8);
    
    state = 1;
  }
}


// the setup routine runs once at startup
void setup() 
{
  Serial.begin(115200);
  // Initialize IMU here
}


// Main loop function
void loop()
{
  previous_time = current_time;
  current_time = millis();            
  double dt = (current_time - previous_time) / 1000; 

  gyro_x_cal = (gyro_x - gyro_bais_x) + orientation_x_offset; // Calibrated x-axis gyro measurement
  gyro_y_cal = (gyro_y - gyro_bais_y) + orientation_y_offset; // Calibrated y-axis gyro measurement
  gyro_z_cal = (gyro_z - gyro_bais_z) + orientation_z_offset; // Calibrated z-axis gyro measurement

  // Get raw gyro readings of IMU here
  orientation.quaternion_update(gyro_x_cal, gyro_y_cal, gyro_z_cal, dt, &orientation_x, &orientation_y, &orientation_z);

  // Refer to the start of the code to find out the role of each state.
  if (state == 0)
  {
    gyro_bias(); // manually calibrate the gyros by finding the bias and zero them out after
  }

  if (state == 1)
  {
    Serial.print("X: ");
    Serial.print(orientation_x);
    Serial.print("  Y: ");
    Serial.print(orientation_y);
    Serial.print("  Z: ");
    Serial.println(orientation_z);
    delay(10); // Change this to alter the sample rate.
  }
}
