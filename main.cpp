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
#include "taskshare.h"
#include "shares.h"
#include "task_webserver.h"



/// A share which holds a counter of how many times a simulated event occurred
/** @brief Boolean variable for the minnow bait pattern 
*/
Share<bool> minnow_flag ("Minnow");
/** @brief Boolean variable for the crawdad bait pattern 
*/
Share<bool> crawdad_flag ("Crawdad");
/** @brief Boolean variable for the topwater bait pattern 
*/
Share<bool> topwater_flag ("Topwater");

/** @brief   Task gets data from IMU 
 *  @details This task calls the IMU_get_data() function to print the 
 *           current IMU readings
 *  @param   p_params A pointer to parameters passed to this task. This 
 *           pointer is ignored; it should be set to @c NULL in the 
 *           call to @c xTaskCreate() which starts this task
 */
void task_IMU (void* p_params)
{
    Serial << "Creating IMU"<< endl;
    while (true)
    {
    IMU_get_data();            // runs the IMU_Get_Data function to retrieve accel and gryo data from IMU
    vTaskDelay(150);
    }
}


/** @brief   Task which creates a motor control task.
*  @details This task creates an object, "Motor1" of the motor class
*           and then uses a FSM to determine which bait pattern to perform
*  @param   p_params An unused pointer to (no) parameters passed to this task
*/
void task_Motor (void* p_params)
{
    Serial << "Creating Motor"<< endl;
    Motor Motor1;
    while (true)
    {
    //Minnow
    if (minnow_flag.get()==true)
    {
    Motor1.SetSpeed(85);
    vTaskDelay(10010);
    Motor1.SetSpeed(0);
    vTaskDelay(10010);
    minnow_flag.put(false);
    }
    //Crawdad
    else if (crawdad_flag.get()==true)
    {
    Motor1.SetSpeed(190);  
    vTaskDelay(2000);
    Motor1.SetSpeed(0); 
    vTaskDelay(3000);
    Motor1.SetSpeed(125);  
    vTaskDelay(7000);
    Motor1.SetSpeed(0); 
    vTaskDelay(10000);
    crawdad_flag.put(false);
    }
    // TopWater
    else if (topwater_flag.get()==true)
    {
    Motor1.SetSpeed(255);
    vTaskDelay(100);
    Motor1.SetSpeed(220);
    vTaskDelay(1500);
    Motor1.SetSpeed(100);
    vTaskDelay(5000);
    Motor1.SetSpeed(180);
    vTaskDelay(500);
    topwater_flag.put(false);
    }
    }
}
/** @brief   Task which creates an encoder object
*  @details This task creates an object, "enc1" of the encoder class
*           it created the object by calling the correct pins on the ESP32
*           and then calls the measure() function. 
*           the majority of the code has been commented out due to some issues
*  @param   p_params An unused pointer to (no) parameters passed to this task
*/
void task_Encoder (void* p_params)
{
//     Serial << "Creating Encoder"<< endl;
//     encoder enc1(34,35);
//     //enc1.reset();
     while (true)
     {
//         //enc1.measure();
     vTaskDelay(100);
      }
}

/** @brief   Task which creates an strain object
*  @details This task creates an object, "Strain" of the Hx711 class.
*           This object is used to measure strain data from the fishing rod.
*           the majority of the code has been commented out due to some issues
*  @param   p_params An unused pointer to (no) parameters passed to this task
*/
void task_Strain (void* p_params)
{
    Serial << "Creating Strain"<< endl;
    /** @brief Variable for the first strain pin (MISO)
    */
    uint16_t LOADCELL_DOUT_PIN = 19 ;
    /** @brief Variable for the second strain pin (SCK)
    */
    uint16_t LOADCELL_SCK_PIN  = 18 ;
    
    HX711 Strain; // creates an object of the HX711 class
    Strain.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN,128);
    //Strain.set_scale(20.f); // this value is obtained by calibrating the scale with known weights; see the README for details
    //Strain.tare();            // reset the scale to 0   
    while(true)
    {
    
    // long reading = Strain.read();
    // Serial.print("HX711 reading: ");
    // Serial.println(reading);
    if (Strain.is_ready()) 
    {
    long reading = Strain.read();
    if (reading>=9250 || reading<=8900)
    
    {bool FishFlag=true;}
    Serial.print("HX711 reading: ");
    Serial.println(reading);
    } 
    else 
    {
    Serial.println("HX711 not found.");
    }
    vTaskDelay(1000);

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
    uint16_t ledPin=2;
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    setup_wifi();

    // Create the task which prints dashes. The stack size should be large
    // enough to prevent the program from crashing no matter what the inputs
    xTaskCreate (task_IMU, "IMU", 4096, NULL, 3, NULL);
    xTaskCreate (task_Motor, "Motor", 2048, NULL, 5, NULL);
    //xTaskCreate (task_Encoder, "Fast", 2048, NULL, 2, NULL);
    xTaskCreate (task_Strain, "Strain", 8192, NULL, 6, NULL);
    xTaskCreate(task_webserver, "Web Server", 8192, NULL, 2, NULL);
    minnow_flag.put(false);
    crawdad_flag.put(false);
    topwater_flag.put(false);
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

