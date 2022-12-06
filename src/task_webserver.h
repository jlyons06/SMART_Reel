/** @file task_webserver.h
 *  This program is the header for the SMART Reel webpage.
 *
 *  @author A. Sinha
 *  @author JR Ridgely
 *  @author JR Lyons
 *  @date   2022-Mar-28 Original stuff by Sinha
 *  @date   2022-Nov-04 Modified for ME507 use by Ridgely
 *  @date   2022-Nov-30 Modified for SMART Reel specific use
 *          by Lyons.
 *  @copyright 2022 by the authors, released under the MIT License.
 */

#ifndef task_webserver_h
#define task_webserver_h
#include <Arduino.h>
#include <PrintStream.h>
#include <WiFi.h>
#include <WebServer.h>
#include <shares.h>

void setup_wifi(void);

void HTML_header(String &a_string, const char *page_title);

void handle_DocumentRoot();

void handle_NotFound(void);

void handle_Fish_On(void);

void handle_Minnow_Bait(void);

void handle_Crawdad_Bait(void);

void handle_Top_Water_Bait(void);

void task_webserver(void *p_params);

#endif