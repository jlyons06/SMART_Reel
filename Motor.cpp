/** @file IMU_R
 *  Prints an array of data
 *  @author Nolan Clapp
 *  @date 2022-Oct-26 Original file by Clapp
 *  
 */

#include <Arduino.h>
#include <PrintStream.h>
#include "IMU_R.h"
#include "Motor.h"
// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#include "Wire.h" // This library allows you to communicate with I2C devices.
Motor::Motor(void)
{
  Motor::PIN_1=12;
  Motor::PIN_2=14;
  pinMode(Motor::PIN_1, INPUT);
  pinMode(Motor::PIN_2, INPUT);
  
}

void Motor::SetSpeed(uint16_t PWM)
{
  analogWrite(Motor::PIN_1, PWM);
  digitalWrite(Motor::PIN_2, HIGH);
}
