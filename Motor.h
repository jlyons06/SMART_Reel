/** @file IMU_R.h
 *  This helps print an array
 *  @author Nolan Clapp
 *  @author JR Ridgely, added more documentation and functionality
 *  @date 2022-Oct-26 Original file by Clapp
 */

#ifndef Motor_h
#define Motor_h

#include <Arduino.h> 
#include "PrintStream.h"

/** @brief   Class which contains stat tracking data
 */
class Motor
{
protected:

public:
    uint16_t PIN_1;           ///< Motor Pin1
    uint16_t PIN_2;           ///< Motor Pin2
    Motor (void);
    void SetSpeed(uint16_t PWM);
    float getcurrent(void);
    

};
/** This class operates several print array funcitons with different inputs
 */





#endif