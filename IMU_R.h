/** @file IMU_R.h
 *  This helps print an array
 *  @author Nolan Clapp
 *  @date 2022-Oct-26 Original file by Clapp
 */

#ifndef IMU_R_h
#define IMU_R_h

#include <Arduino.h> 
#include "PrintStream.h"



/** @brief Function to set up IMU
 */
void IMU_setup();
/** @brief Function to get IMU data
 */
void IMU_get_data();


#endif
