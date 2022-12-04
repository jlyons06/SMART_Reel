## SMART_Reel
ME507 SMART_Reel Project Fall 2022
This files contained in this repository are the software used in the implementation and control of 
the SMART Fishing Reel designed and prototyped in ME507, at Cal Poly - SLO, in Fall 2022.
  
The team members of this project are Nolan Clapp, Chloe Chou, Sowmya Ramakrishnan, and Joseph Lyons.
Additional assitiance on this project provided by Prof. J. Ridgely, Cal Poly - SLO Mechanical Engineering.


### Description 
This SMART Reel was designed to be used while bass fishing. Bass fishing uses a variety of different bait depending on many factors including depth of water, time of day, geographical location, weather, season, and more. Every type of bait (Crankbait, Topwater, Spinnerbaits, Swimbaits, etc..) has a unique retrieval pattern associated with it. The goal of our project is to automate the bait retrieval process. This was accomplished by interfacing our ESP32 Microcontroller with a webpage where a user can choose which type of bait they are using, and then the reel will begin retrieving bait in that pattern. For example, when using a minnow as bait, the typical retrieval pattern is a constant, moderate speed of retrieval; however, a bait such as a crawdad, requires the fisherman to reel quickly for a short duration, then wait, then reel quickly, then wait, and continue this pattern until a fish takes the bait or the bait has been fully reeled in. 
With our SMART Reel, we can streamline the process of switching between different baits quickly, and give users who are not accustomed to fishing certain types of bait, the confidence to fish with it because they do not have to worry about learning the bait retrieval pattern. It was important to our group that although the SMART Reel would reel in the bait, it should not be able to reel in a fish. The SMART Reel will alert the user when it detects that a fish has taken the bait, this is done through measuring the strain in the fishing rod, as well as the current draw from the motor. These are effective means of determining the presence of a fish, because when a fish takes the bait, the rod will bend (creating strain in the rod), and the current draw from the motor will increase because it will require more torque (and subsequently current).
The SMART fishing reel designed in this project will be able to automatically reel in different bait patterns


### Bill of Materials and Estimated Cost

| Qty. | Part                      | Source                | Est. Cost |
|:----:|:--------------------------|:----------------------|:---------:|
|  1   | Zebco Fishing Rod +Reel   | Amazon                |   $11.95  |
|  1   | ESP32 Feather Board       | EZSBC                 |   $11.95  |
|  1   | Custom PCB                | JLC PCB               |     -     |
|  1   | 400mAh Battery            | EZSBC                 |     -     |
|  1   | 12V DC Motor+Encoder      | Amazon                |   $19.49  |
|  2   | Strain Gauges             | Amazon                |   $2.80   |
|  1   | 12V Lipo Battery          | TinkerSphere          |   $21.90  |
|  1   | Assorted Electronic Parts | Digikey/Mouser        |  ~$15.00  |
|  1   | Assorted M3 Fastners      | Personal Supply       |     -     |

Additional Components Used
| Qty. | Part                      | Source                | Est. Cost |
|:----:|:--------------------------|:----------------------|:---------:|
|  1   | MPU650 IMU Sensor         | Dr. Ridgley           |     -     |
|  1   | HX711 Breakout Board      | Amazon                |   $10.59  |
|  1   | DRV8876 Breakout Board    | Pololu                |   $6.95   |


### Sketch of Mechanical Design 

![Sketch of Mechanical System](https://github.com/jlyons06/SMART_Reel/blob/437eeac43a9c9140996a29065c9eb7d16c187148/Initial%20Drawing.png)
Initial Sketch of Mechanical System 

The idea behind this mechanical system was to allow for the user to manually reel in if they desire, while still having the capability 
to reel in using the DC motor. We utilized a gear train of 3 gears in order to keep the gear ratio between the motor and reel as close to 1:1 as possible.
This is becuase when we initially speced the motor, we planned to have it interface directly with the handle and chose to move to a geared system later. All custom 
parts such as gears and mounting fixtures will be 3D printed in PLA.

### Final Mechanical Design and CAD Model
The CAD model for this project had one main hurdle; the fishing reel CAD model was not readily available online and was very difficult to reproduce due to some organic shapes 
and contours that were not easily measurable. The way we overcame this was taking key measurements to characterize the design using the center of the handle as the orgin for our model. Once we got these measurements, We created a 2D sketch from the center of the handle with refrence to the edge of the fishing rod. This allowed us to easily use the Solidworks gear toolbox to
select the correct gears to fit in our design. Below is an image of this characteristic sketch we used. 

![Gear Fit Sketch](https://github.com/jlyons06/SMART_Reel/blob/c20623955b924674a5ff0d627aa1d01427db8c82/2DGearFit.png)
Solidworks Sketch of our gear fit


Below is the full CAD model of our design. The leftmost gear is the gear that will be attached to the reel, the middle gear will be idle, and the right gear is the driven gear. 

![Final Design](https://github.com/jlyons06/SMART_Reel/blob/c20623955b924674a5ff0d627aa1d01427db8c82/FullCAD.png)
 Solidworks Model of our design 

Below is fully physical system. All custom parts were 3D printed. 
![Full System](https://github.com/jlyons06/SMART_Reel/blob/81e06ca9aa2a09d9bc581f14b7b454a0ffec9981/mech.png)
Image of physical system 

### Electronics

#### Wiring Diagram
![Wiring Diagram](https://github.com/jlyons06/SMART_Reel/blob/ec3297f52a36d3cf54e479043f5b22853faf3d7b/ReportPics/WiringDG.png)
Image of the wiring diagram of our system

#### PCB Design
A large portion of this project was to design a custom PCB. The goal of this was to integrate all of the chips we plan on using [HX711 (Strain), DRV8876 (Motor Driver), LSM303 (Accelerometer), L3G4200D(Gyro)] into a single board. Below is an image of our PCB Design. 

![PCB Top](https://github.com/jlyons06/SMART_Reel/blob/98818e8a439611ab85505778bd46f60cab7026f7/SmartReelV1_top.png)
Picture of the top of our PCB 

![PCB Bottom](https://github.com/jlyons06/SMART_Reel/blob/98818e8a439611ab85505778bd46f60cab7026f7/SmartReelV1_bottom.png)
Picture of the bottom of our PCB 

This primary iteration of our PCB had several issues. A few traces were routed to flash pins on the ESP32, which prevented code from uploading. This was fixed by cutting the traces to those pins and jumping them to the correct pins by soldering on wires. One more significant issue we had was the fact that something in our design fried our ESP32. We could not diagnose the problem and to prevent letting out the magic smoke on anymore of our ESP's, we resorted to using breakout boards. Fornately, after switching to breakout boards, we were able to get all of our electronics up and running. 

 
### Software Design Overview

![Task Diagram](https://github.com/jlyons06/SMART_Reel/blob/ec3297f52a36d3cf54e479043f5b22853faf3d7b/ReportPics/ActualTD.png)
Image of our acutal Task Diagram  <br>

-Talk about all the tasks <br>
    ![Task Motor FSM](https://github.com/jlyons06/SMART_Reel/blob/ec3297f52a36d3cf54e479043f5b22853faf3d7b/ReportPics/MotorFSM.png)
Image of our task motor finite state machine (FSM)  <br>
-Webpage integration <br>


Full Source Code:   [LINK]  <br>
Documentation:      [LINK] <br>


### System Performance
We were able to sucessfully get our system working. To operate the SMART Reel, the user will connect to the ESP32's wifi on their smart phone, verify connection by selecting the "Fish On" button and ensuring the blue LED on the ESP32 turns on. Next, the user would cast their line. Then, the user will select the type of bait they are using by clicking the correct button on the user interface webpage. The SMART reel will then begin reeling in that bait pattern. The user should keep view of the ESP32 because if the blue LED turns on while the reeling is happening, the SMART Reel has determined that a fish could have taken the bait. This determination is made by checking to see if the strain in the rod has increased above a certain threshold (a bend/increase in strain is typically associated with increased tension on the line when a fish takes the bait)

<img src= "https://github.com/jlyons06/SMART_Reel/blob/81e06ca9aa2a09d9bc581f14b7b454a0ffec9981/RunningSystem.gif" alt=System Running>


### Future System Modifications 
Being on the quarter system, we were not able to accomplish everything we wanted to in 10 weeks. With more time, there is several modifications we could make to increase system performance and potentially make this a product that is desireable to people who want to fish but find the process of reeling/learning different bait patterns tedious. The first of these modifications would be to correct the mistakes on our PCB so that the electronics could be contained to a much cleaner package. 
In addition, we were able to collect IMU data, but we did not end up using the data for anything. We think it would be very interesting to take the IMU data and import it into a program like Matlab in order to create a visualization of how the rod angle is changing as the person reels. 
Something else we would have like to add was the ability to use the encoder on the motor to record new bait patterns. This would be very interesting because with this functionality, the user would be able to create custom bait patterns if they desired. We would implement this by calculating the angular velocity input by the user, and saving how the angular velocity changes with time into an array so that we could feed these velocity values to our motor task to imitate the exact pattern the user inputed. Below is an image of the new task diagram that would need to be implementd to accomodate these changes. 

![Ideal Task Diagram](https://github.com/jlyons06/SMART_Reel/blob/ec3297f52a36d3cf54e479043f5b22853faf3d7b/ReportPics/IdealTD.png)
Image of our proposed updated Task Diagram  <br>

Overall, we were very happy with the performace of our system and feel that we achieved the majority of what we set out to do in the begining of the quarter. 