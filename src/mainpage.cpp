/** @file mainpage.cpp
 *  @brief Brief Project description
 *  @date 2022-12-06 
 *  
 * @mainpage 
 * 
 * @section sec_intro SMART Reel ME 507
 *          by Nolan Clapp, Chloe Chou, Sowmya Ramakrishnan, Joseph Lyons /b
 *          This page acts as documentation for the software side of our project.
 *          Links to other parts of the project are contained in the section below.  
 * @section Links to External Documents
 *          Full Reporrt: [Link] /b
 *          Source Code:[https://github.com/jlyons06/SMART_Reel/tree/main/src] /b
 *          Main GitHub Page: [https://github.com/jlyons06/SMART_Reel.git]     /b 
 *          
 * @section sec_lb1 Project Description
 *          This SMART Reel was designed to be used while bass fishing. Bass fishing 
 * uses a variety of different bait depending on many factors including depth of water,
 *  time of day, geographical location, weather, season, and more. Every type of bait 
 * (Crankbait, Topwater, Spinnerbaits, Swimbaits, etc..) has a unique retrieval pattern 
 * associated with it. The goal of our project is to automate the bait retrieval process.
 *  This was accomplished by interfacing our ESP32 Microcontroller with a webpage where 
 * a user can choose which type of bait they are using, and then the reel will begin 
 * retrieving bait in that pattern. For example, when using a minnow as bait, the typical
 *  retrieval pattern is a constant, moderate speed of retrieval; however, a bait such 
 * as a crawdad, requires the fisherman to reel quickly for a short duration, then wait, 
 * then reel quickly, then wait, and continue this pattern until a fish takes the bait
 *  or the bait has been fully reeled in. With our SMART Reel, we can streamline the 
 * process of switching between different baits quickly, and give users who are not 
 * accustomed to fishing certain types of bait, the confidence to fish with it because 
 * they do not have to worry about learning the bait retrieval pattern. It was important
 *  to our group that although the SMART Reel would reel in the bait, it should not 
 * be able to reel in a fish. The SMART Reel will alert the user when it detects that a 
 * fish has taken the bait, this is done through measuring the strain in the fishing rod,
 *  as well as the current draw from the motor. These are effective means of determining
 *  the presence of a fish, because when a fish takes the bait, the rod will bend 
 * (creating strain in the rod), and the current draw from the motor will increase
 *  because it will require more torque (and subsequently current). The SMART fishing 
 * reel designed in this project will be able to automatically reel in different bait 
 * patterns
 * 
 * 
 */
