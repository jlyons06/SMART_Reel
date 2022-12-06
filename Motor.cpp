/** @file Motor.cpp
 *  Creates a motor class to interface with a brushless DC motor
 *  it works by seting motor pins as inputs and passing a PWM signal to 
 *  one of the pins and sets teh other as high per the motor driver data sheet. 
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
/** @brief   Constructor which creates a motor object.
 */
Motor::Motor(void)
{
  Motor::PIN_1=12;
  Motor::PIN_2=14;
  pinMode(Motor::PIN_1, INPUT);
  pinMode(Motor::PIN_2, INPUT);
  
}
/** @brief   Method sets the motor speed (0-255)
 *  @details This method sets the motor speed by passing in a PWM
 *           signal and setting one motor pin to high
 *  @params PWM The motor speed (0=Off; 255=100%)
 */
void Motor::SetSpeed(uint16_t PWM)
{
  analogWrite(Motor::PIN_1, PWM);
  digitalWrite(Motor::PIN_2, HIGH);
}
