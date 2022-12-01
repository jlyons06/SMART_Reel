/** @file Clapp.cpp
 *  This file contains code relating to HW4, tasks to debounce a button
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "IMU_R.h"
#include "encoder.h"
#include "HX711.h"
#include "Motor.h"
#include "WiFi.h"
#include "WebServer.h"



/** @brief   Task preforms debouncing of a button
 *  @details This task ensures that when a button is pressed that there is no 
 *           issue where the button bounces from high to low before settling to the correct value
 *  @param   p_params A pointer to parameters passed to this task. This 
 *           pointer is ignored; it should be set to @c NULL in the 
 *           call to @c xTaskCreate() which starts this task
 */
//#define Button 13               //  USES GIOPXX NOT REGULAR PIN NUMBER
#define FAST_PIN 12               //  USES GIOPXX NOT REGULAR PIN NUMBER

void task_IMU (void* p_params)
{
    Serial << "Creating IMU"<< endl;
    while (true)
    {
    //IMU_get_data();            // runs the IMU_Get_Data function to retrieve accel and gryo data from IMU
    vTaskDelay(200000);
    }
}


/** @brief   Task which creates a motor control task.
 *  @details This task creates a square wave at 500Hz and 50% duty on GPIO 12
 *  @param   p_params An unused pointer to (no) parameters passed to this task
 */
void task_Motor (void* p_params)
{
    Serial << "Creating Motor"<< endl;
    Motor Motor1;
    while (true)
    {
    // //Minnow
    // Motor1.SetSpeed(85);
    // vTaskDelay(10000);
    // Motor1.SetSpeed(0);
    // vTaskDelay(10000);

    // //Crawdad
    // Motor1.SetSpeed(190);  
    // vTaskDelay(500);
    // Motor1.SetSpeed(0); 
    // vTaskDelay(3000);
    // Motor1.SetSpeed(125);  
    // vTaskDelay(700);
    // Motor1.SetSpeed(0); 
    // vTaskDelay(1000);

    // SwimBait
    // Motor1.SetSpeed(255);
    // vTaskDelay(10);
    // Motor1.SetSpeed(220);
    // vTaskDelay(150);
    // Motor1.SetSpeed(100);
    // vTaskDelay(1500);
    // Motor1.SetSpeed(180);
    // vTaskDelay(250);

    }
}
void task_Encoder (void* p_params)
{
    Serial << "Creating Encoder"<< endl;
    encoder enc1(34,35);
    //enc1.reset();
    while (true)
    {
        //enc1.measure();
        vTaskDelay(100000);
    }
}
void task_Strain (void* p_params)
{
    Serial << "Creating Strain"<< endl;
    uint16_t LOADCELL_DOUT_PIN = 21 ;
    uint16_t LOADCELL_SCK_PIN  = 22 ;
    

    HX711 Strain;
    Strain.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN,1);
    Strain.set_scale(1.f); // this value is obtained by calibrating the scale with known weights; see the README for details
    Strain.tare();            // reset the scale to 0
    uint16_t Reading1 =0;
    uint16_t Reading2 =0;
    uint16_t Reading3 =0;
    while(true)
    {
    
   
    Serial.print("one reading:\t");
    Serial.println(Strain.get_units(), 1);


    // Strain.power_down(); // put the ADC in sleep mode  
    // vTaskDelay(10);
    // Strain.power_up();
    vTaskDelay(10);
    }
}


/** @brief   The Arduino setup function.
 *  @details This function is used to set up the microcontroller by starting
 *           the serial port, saying hello, and creating the tasks.
 */
void setup (void) 
{
    // The serial port must begin before it may be used
    Serial.begin (115200);
    while (!Serial) 
    {
    }
    Serial << "Serial Connected" << endl;
    
    // Create the task which prints dashes. The stack size should be large
    // enough to prevent the program from crashing no matter what the inputs
    xTaskCreate (task_IMU, "IMU", 4096, NULL, 3, NULL);
    xTaskCreate (task_Motor, "Fast", 2048, NULL, 5, NULL);
    xTaskCreate (task_Encoder, "Fast", 2048, NULL, 2, NULL);
    xTaskCreate (task_Strain, "Fast", 2048, NULL, 6, NULL);
    IMU_setup();
}


/** @brief   The Arduino loop function.
 *  @details This function is called periodically by the Arduino system. It
 *           runs as a low priority task. On some microcontrollers it will
 *           crash when FreeRTOS is running, so we usually don't use this
 *           function for anything, instead just having it delay itself. 
 */
void loop (void)
{
    // Delay for a whole minute, which is an eternity to a microcontroller
    vTaskDelay (60000);
}

