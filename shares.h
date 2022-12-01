/** @file shares.h
 *  This file contains extern declarations of shares and queues which are used
 *  in more than one file of a demonstration project.
 * 
 *  @author JR Ridgely
 *  @date   2021-Oct-23 Original file
 *  @copyright (c) 2021 by JR Ridgely, released under the LGPL 3.0. 
 */

#ifndef _SHARES_H_
#define _SHARES_H_

<<<<<<< Updated upstream
#include <Arduino.h>
=======
#include "Arduino.h"
>>>>>>> Stashed changes
#include "taskshare.h"

// A share which holds the flag to begin the pattern of the minnow bait
extern Share<bool> minnow_flag;

// A share which holds the flag to begin the pattern of the crawdad bait
extern Share<bool> crawdad_flag;

// A share which holds the flag to begin the pattern of the worm bait
extern Share<bool> topwater_flag;

#endif // _SHARES_H_
