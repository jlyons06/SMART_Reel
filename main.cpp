/** @file main.h
 *  Main code to operate and collect data from the SMART Reel.
 *  @author Joe Lyons
 *  @date 2022-Nov-17
 *  @copyright 2022 by the authors
 */

#include <HX711.h>
#include <IMU_R.h>

/** @brief   Code to collect data from strain gauges via HX711.
 *  @details The following code is used to collect and display data from
 *           the two strain gauges of the SMART Reel via the HX711 load
 *           cell amplifier.
 */

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 21;
const int LOADCELL_SCK_PIN = 22;

HX711 scale;
int filt_out = 0;
float A = .5;
float B = 1-A;
float raw_read = 0.0;


void setup()
{
  Serial.begin(115200);
  Serial.println("HX711 Demo");

  Serial.println("Initializing the scale");

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read()); // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20)); // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5)); // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1); // print the average of 5 readings from the ADC minus tare weight (not set) divided
                                         // by the SCALE parameter (not set yet)

  //scale.set_scale(2280.f); // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();            // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read()); // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20)); // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5)); // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1); // print the average of 5 readings from the ADC minus tare weight, divided
                                         // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}


/** @brief   The Arduino loop function used to repeat collection of data.
 *  @details This loop function is used to cycle printing of strain gauge
 *           measurements through the HX711. 
 */
void loop()
{
  raw_read = scale.get_units();
  filt_out = A*filt_out + B*raw_read;

  Serial.print("one reading:\t");
  Serial.print(filt_out, 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 1);

  scale.power_down(); // put the ADC in sleep mode
  vTaskDelay(10);
  scale.power_up();
}