### SMART_Reel
ME507 SMART_Reel Project Fall 2022
This files contained in this repository are the software used in the implementation and control of 
the SMART Fishing Reel designed and prototyped in ME507, at Cal Poly - SLO, in Fall 2022.
  
The team members of this project are Nolan Clapp, Chloe Chou, Sowmya Ramakrishnan, and Joseph Lyons.
Additional assitiance on this project provided by Prof. J. Ridgely, Cal Poly - SLO Mechanical Engineering.


### Description 
This SMART Reel was designed to be used while bass fishing. Bass fishing uses a variety of differnet bait depending on many factors
including: depth of water, time of day, geographical location, weather, season, and more. Every type of bait (Crankbait, Topwater, Spinnerbaits, Swimbaits, ect.) 
has a unique retrival pattern associated with it. The goal of our project is to automate the bait retreval process. This was accomplished by 
interfacing our ESP32 Microcontroller with a webpage where a user can choose which type of bait they are using, and then the reel will begin retreving bait in that pattern. 
For example, when using a minnow as bait, the typical retrival pattern is a constant, moderate speed of retrival; however a bait such as a crawdad, requires the fisherman
to reel quickly for a short duration, then wait, then reel quickly, then wait, and continue this pattern until a fish takes the bait or the bait has been fully reeled in. 
With our SMART Reel, we can streamline the process of switching between different baits quickly, and give users who are not accustom to fishing certain types of bait, the confidence
to fish with it becuase they do not have to worry about learning the bait retrival pattern. It was importnat to our group that although the SMART Reel would reel in the bait, 
it should not be able to reel in a fish. The SMART Reel will alert the user when it detects that a fish has taken the bait, this is done through measuring the strain in the fishing rod,
as well as the current draw from the motor. These are effective means of determining the presence of a fish, becasue when a fish takes the bait, the rod will bend (creating strain in the rod), and the current draw from the motor will increase because it will require more torque (and subsequently current). 

The SMART fishing reel designed in this project will be able to automatically reel in differnet bait patterns

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