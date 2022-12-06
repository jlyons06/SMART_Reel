#include <Arduino.h>

/*     Arduino Rotary Encoder Tutorial
 *      WORKS FINE
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
 
 #define outputA 34
 #define outputB 35

 int32_t counter = 0; 
 int32_t aState;
 int32_t aLastState;  

 void setup() 
 { 
   pinMode (outputA,INPUT_PULLUP);
   pinMode (outputB,INPUT_PULLUP);
   
   Serial.begin (115200);
   Serial.print ("init");
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);   
 } 

 void loop() 
 { 
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState)
   {     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) 
     { 
       counter ++;
     } 
     
     else {
       counter --;
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state

 }

