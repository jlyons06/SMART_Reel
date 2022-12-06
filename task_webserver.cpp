/** @file task_webserver.cpp
 *  This program runs the webserver for the SMART Reel, displaying several
 *  bait patterns to be selected by the user.
 *
 *  Based on an examples by A. Sinha at
 *  @c https://github.com/hippyaki/WebServers-on-ESP32-Codes
 *
 *  @author A. Sinha
 *  @author JR Ridgely
 *  @author JR Lyons
 *  @date   2022-Mar-28 Original stuff by Sinha
 *  @date   2022-Nov-04 Modified for ME507 use by Ridgely
 *  @date   2022-Nov-30 Modified by Lyons for specific considerations of the
 *          SMART Reel
 *  @copyright 2022 by the authors, released under the MIT License.
 */

#include <Arduino.h>
#include <PrintStream.h>
#include <WiFi.h>
#include <WebServer.h>
#include <shares.h>

// #define USE_LAN to have the ESP32 join an existing Local Area Network or
// #undef USE_LAN to have the ESP32 act as an access point, forming its own LAN
#undef USE_LAN

// If joining an existing LAN, get certifications from a header file which you
// should NOT push to a public repository of any kind
#ifdef USE_LAN
#include "mycerts.h" // For access to your WiFi network; see setup_wifi()

// If the ESP32 creates its own access point, put the credentials and network
// parameters here; do not use any personally identifying or sensitive data
#else
const char *ssid = "SMART Reel";   // SSID, network name seen on LAN lists
const char *password = "password"; // ESP32 WiFi password (min. 8 characters)

/* Put IP Address details */
IPAddress local_ip(192, 168, 5, 1); // Address of ESP32 on its own network
IPAddress gateway(192, 168, 5, 1);  // The ESP32 acts as its own gateway
IPAddress subnet(255, 255, 255, 0); // Network mask; just leave this as is
#endif

/// The pin connected to an LED controlled through the Web interface
const uint8_t ledPin = 2;

/** @brief   The web server object for this project.
 *  @details This server is responsible for responding to HTTP requests from
 *           other computers, replying with useful information.
 */
WebServer server(80);

/** @brief   Get the WiFi running so we can serve some web pages.
 */
void setup_wifi(void)
{
#ifdef USE_LAN // If connecting to an existing LAN
    Serial << "Connecting to " << ssid;

    // The SSID and password should be kept secret in @c mycerts.h.
    // This file should contain the two lines,
    //   const char* ssid = "YourWiFiNetworkName";
    //   const char* password = "YourWiFiPassword";
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(1000);
        Serial.print(".");
    }

    Serial << "connected at IP address " << WiFi.localIP() << endl;

#else // If the ESP32 makes its own LAN
    Serial << "Setting up WiFi access point...";
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(ssid, password);
    Serial << "done." << endl;
#endif
}

/** @brief   Put a web page header into an HTML string.
 *  @details This header may be modified if the developer wants some actual
 *           @a style for her or his web page. It is intended to be a common
 *           header (and style) for each of the pages served by this server.
 *  @param   a_string A reference to a string to which the header is added; the
 *           string must have been created in each function that calls this one
 *  @param   page_title The title of the page
 */
void HTML_header(String &a_string, const char *page_title)
{
    a_string += "<!DOCTYPE html> <html>\n";
    a_string += "<head><meta name=\"viewport\" content=\"width=device-width,";
    a_string += " initial-scale=1.0, user-scalable=no\">\n<title> ";
    a_string += page_title;
    a_string += "</title>\n";
    a_string += "<style>html { font-family: Helvetica; display: inline-block;";
    a_string += " margin: 0px auto; text-align: center;}\n";
    a_string += "body{margin-top: 50px;} h1 {color: #4444AA;margin: 50px auto 30px;}\n";
    a_string += "p {font-size: 24px;color: #222222;margin-bottom: 10px;}\n";
    a_string += "</style>\n</head>\n";
}

/** @brief   Callback function that responds to HTTP requests without a subpage
 *           name.
 *  @details When another computer contacts this ESP32 through TCP/IP port 80
 *           (the insecure Web port) with a request for the main web page, this
 *           callback function is run. It sends the main web page's text to the
 *           requesting machine.
 */
void handle_DocumentRoot()
{
    Serial << "HTTP request from client #" << server.client() << endl;

    String a_str;
    HTML_header(a_str, "ESP32 Web Server Test");
    a_str += "<body>\n<div id=\"webpage\">\n";
    a_str += "<h1>ME507 SMART Reel </h1>\n";
    a_str += "Chou, Clapp, Lyons, Ramakrishnan\n";
    a_str += "<p><p> <a href=\"/fish_on\">Fish On</a>\n";
    a_str += "<p><p> <a href=\"/minnow_bait\">Minnow Bait</a>\n";
    a_str += "<p><p> <a href=\"/crawdad_bait\">Crawdad Bait</a>\n";
    a_str += "<p><p> <a href=\"/top_water_bait\">Top Water Bait</a>\n";
    a_str += "</div>\n</body>\n</html>\n";

    server.send(200, "text/html", a_str);
}

/** @brief   Respond to a request for an HTTP page that doesn't exist.
 *  @details This function produces the Error 404, Page Not Found error.
 */
void handle_NotFound(void)
{
    server.send(404, "text/plain", "Not found");
}

/** @brief   Toggle blue LED when called by the web server.
 *  @details This function exists as a testing task to verify connectivity
 *           by turning a blue LED on and off.
 *           @c http://server.address/fish_on as the web address request from a
 *           browser.
 */
void handle_Fish_On(void)
{
    // This variable must be declared static so that its value isn't forgotten
    // each time this function runs. BUG: It takes two requests to the toggle
    // page before the LED turns on, after which it toggles as expected.
    static bool state = false;

    digitalWrite(ledPin, state);
    state = !state;

    String fish_on_page = "<!DOCTYPE html> <html> <head>\n";
    fish_on_page += "<meta http-equiv=\"refresh\" content=\"1; url='/'\" />\n";
    fish_on_page += "</head> <body> <p> <a href='/'>Back to main page</a></p>";
    fish_on_page += "</body> </html>";

    server.send(200, "text/html", fish_on_page);
}

/** @brief   Spin motor in pattern 1 (continuous) when called by the web server.
 *  @details Pattern 1 of the motor is to imitate a minnow bait, where the bait
 *           "swims" in a continuous, slow motion.
 *           @c http://server.address/minnow_bait as the web address request from a
 *           browser.
 */
void handle_Minnow_Bait(void)
{
    // This variable must be declared static so that its value isn't forgotten
    // each time this function runs.
    minnow_flag.put(true);

    String minnow_page = "<!DOCTYPE html> <html> <head>\n";
    minnow_page += "<meta http-equiv=\"refresh\" content=\"1; url='/'\" />\n";
    minnow_page += "</head> <body> <p> <a href='/'>Back to main page</a></p>";
    minnow_page += "</body> </html>";

    server.send(200, "text/html", minnow_page);
}

/** @brief   Spin motor in pattern 2 when called by the web server.
 *  @details Pattern 2 of the motor is to imitate a crawdad bait, where the bait
 *           cycles between quick jerks, slow walks, and pauses in motion.
 *           @c http://server.address/crawdad_bait as the web address request from a
 *           browser.
 */
void handle_Crawdad_Bait(void)
{
    // This variable must be declared static so that its value isn't forgotten
    // each time this function runs.
    crawdad_flag.put(true);

    String crawdad_page = "<!DOCTYPE html> <html> <head>\n";
    crawdad_page += "<meta http-equiv=\"refresh\" content=\"1; url='/'\" />\n";
    crawdad_page += "</head> <body> <p> <a href='/'>Back to main page</a></p>";
    crawdad_page += "</body> </html>";

    server.send(200, "text/html", crawdad_page);
}

/** @brief   Spin motor in pattern 3 when called by the web server.
 *  @details Pattern 3 of the motor is to imitate a topwater bait, where the bait
 *           cycles between quick and slow continuous motion, to imitate a frog or
 *           duck moving on the top surface of the water.
 *           @c http://server.address/top_water_bait as the web address request from a
 *           browser.
 */
void handle_Top_Water_Bait(void)
{
    // This variable must be declared static so that its value isn't forgotten
    // each time this function runs.
    topwater_flag.put(true);

    String topwater_page = "<!DOCTYPE html> <html> <head>\n";
    topwater_page += "<meta http-equiv=\"refresh\" content=\"1; url='/'\" />\n";
    topwater_page += "</head> <body> <p> <a href='/'>Back to main page</a></p>";
    topwater_page += "</body> </html>";

    server.send(200, "text/html", topwater_page);
}

/** @brief   Task which sets up and runs a web server.
 *  @details After setup, function @c handleClient() must be run periodically
 *           to check for page requests from web clients. One could run this
 *           task as the lowest priority task with a short or no delay, as there
 *           generally isn't much rush in replying to web queries.
 *  @param   p_params Pointer to unused parameters
 */
void task_webserver(void *p_params)
{
    // The server has been created statically when the program was started and
    // is accessed as a global object because not only this function but also
    // the page handling functions referenced below need access to the server
    server.on("/", handle_DocumentRoot);
    server.on("/fish_on", handle_Fish_On);
    server.on("/minnow_bait", handle_Minnow_Bait);
    server.on("/crawdad_bait", handle_Crawdad_Bait);
    server.on("/top_water_bait", handle_Top_Water_Bait);
    server.onNotFound(handle_NotFound);

    // Get the web server running
    server.begin();
    Serial.println("HTTP server started");

    for (;;)
    {
        // The web server must be periodically run to watch for page requests
        server.handleClient();
        vTaskDelay(500);
    }
}