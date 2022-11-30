/** @file main.h
 *  Main code to operate and collect data from the SMART Reel.
 *  @author Joe Lyons
 *  @date 2022-Nov-17
 *  @copyright 2022 by the authors
 */



/** @brief   Code to collect data from strain gauges via HX711.
 *  @details The following code is used to collect and display data from
 *           the two strain gauges of the SMART Reel via the HX711 load
 *           cell amplifier.
 */

// HX711 circuit wiring
#define PIN_1 12
#define PIN_2 14
#define CurrentPin 36
#define PWM 0

void setup()
{
  Serial.begin(115200);
  while (!Serial){}
  pinMode(PIN_1, INPUT);
  pinMode(PIN_2, INPUT);
}
void loop()
{
  analogWrite(PIN_1, PWM);
  digitalWrite(PIN_2, HIGH);
  Serial.println(analogRead(CurrentPin));
  vTaskDelay(200);
} 