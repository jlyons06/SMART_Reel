/** @file shares.h
 *  This file contains extern declarations of shares and queues which are used
 *  in more than one file of a demonstration project.
 *
 *  @author JR Ridgely
 *  @author JR Lyons
 *  @date   2021-Oct-23 Original file
 *  @date   2022-Nov-30 Modifications for SMART Reel by Lyons
 *  @copyright (c) 2022 by the authors
 */

#ifndef _SHARES_H_
#define _SHARES_H_

#include <Arduino.h>
#include <taskshare.h>

// A share which holds the flag to begin the pattern of the minnow bait
/** @brief Boolean variable for the minnow bait pattern
 */
extern Share<bool> minnow_flag;

// A share which holds the flag to begin the pattern of the crawdad bait
/** @brief Boolean variable for the crawdad bait pattern
 */
extern Share<bool> crawdad_flag;

// A share which holds the flag to begin the pattern of the topwater bait
/** @brief Boolean variable for the topwater bait pattern
 */
extern Share<bool> topwater_flag;

#endif // _SHARES_H_
