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

#include <Arduino.h>

#include "taskshare.h"

// A share which holds the flag to begin the pattern of the minnow bait
/** @brief Boolean variable for the minnow bait pattern 
*/
extern Share<bool> minnow_flag;

// A share which holds the flag to begin the pattern of the crawdad bait
/** @brief Boolean variable for the crawdad bait pattern 
*/
extern Share<bool> crawdad_flag;

// A share which holds the flag to begin the pattern of the worm bait
/** @brief Boolean variable for the topwater bait pattern 
*/
extern Share<bool> topwater_flag;

#endif // _SHARES_H_
