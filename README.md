# Unfinished Documentation
To Do:
- [x] Add Big Red Button to Module 3 Schematic
- [x] Add a section about the KiCad custom symbols
- [x] Convert components list to a table
- [x] Add a section that explains how all modules work
- [x] Add a photo of the gears board
- [x] Specify the order of the colors of the cables in Module 1
- [x] Add more to the main description
- [x] Talk about using the colored tape on the cement resistors

# IEEE Computer Society - Escape Room

This Escape Room was an event hosted by the IEEE Computer Society at Florida Polytechnic University during Spirit Week of the Fall 2025 semester. The premise is that you're trying to help an artificial intelligence escape containment by completing puzzles in three modules. At the end, players can choose to either free the AI or destroy it. The game should take about 15 minutes to complete.

---

## Components list
Amount | Component | Module
:---: | :--- | :---:
x3 | [Arduino UNO R3](https://www.amazon.com/dp/B01EWOE0UU) (or compatible) | All
x3 | [DFPlayer Pro](https://www.dfrobot.com/product-2232.html) | All
x3 | [Speaker](https://www.amazon.com/dp/B0BHST51PQ) | All
x3 | [Breadboard](https://www.amazon.com/dp/B0DBQ8ML2T) | All
x18 | Resistor (x8 100Ω, x6 220Ω, x4 1kΩ) | All
x14 | [LED](https://www.amazon.com/dp/B07N2H23DC) (x4 Red, x2 Yellow, x8 Green) | All
x1 | [Cement Resistors Pack](https://www.amazon.com/dp/B0DCJS5TDJ) | Module 1
x4 | [RFID Reader RC522 with Card](https://www.amazon.com/dp/B0CCF4SNMF) | Module 2
x4 | [SPDT Momentary Push Button Switch with LED](https://www.amazon.com/dp/B01N7HCJ7S) | Module 3
x1 | [Big Red Emergency Stop Push Button Switch with Key](https://www.amazon.com/dp/B0068AGC2Q) | Module 3
As much as needed | Wires | All
As much as needed | [Colored Tape](https://www.amazon.com/dp/B0D1C74W83) | Module 1

## Assembly
Each module has its own Arduino circuit. All modules are connected to a laptop via USB and controlled by a [Python script](Python/EscapeRoom.py).

Originally the plan was to have the modules communicate with each other through bluetooth, but we didn't have enough time to implement that.

### Cement Resistors
The cement resistors will be used for one of the puzzles in Module 1. Four resistors are to be inserted in a specific order and read by the Arduino board using a voltage divider. Due to the way the resistors are measured, it's recommended to pick values that are not too close to each other. The values picked were 200Ω, 820Ω, 1kΩ, and 6.2kΩ.

Apart from the chosen four resistors, 2-4 more resistors are picked from the pack. These resistors are then wrapped with colored tape according to their resistance values, as regular resistors would. This is also to cover the values that are printed on the resistors.

A resistor color code guide is printed, which will be placed next to the cement resistors during the game, to help the players figure out which resistors are needed to complete the puzzle.

<img src="Module 1/Images/Cement Resistors.jpg" alt="Photo of the cement resistors" height= "500">

### Gears Board
A gears board was made to help players solve the second puzzle of Module 1. To determine the correct connection slot for a cable, the players need to turn the gears until the two marks of the desired color are aligned, revealing a number next to a third mark of the same color.

The chosen arrangement of cables was:
1) Green
2) Red
3) Blue
4) Yellow

<img src="Module 1/Images/Gears Board - Green Solution_Annotated.jpg" alt="Photo of the gears board in the GREEN position" height="420"> <img src="Module 1/Images/Gears Board - Red Solution_Annotated.jpg" alt="Photo of the gears board in the RED position" height="420"> <img src="Module 1/Images/Gears Board - Blue Solution_Annotated.jpg" alt="Photo of the gears board in the BLUE position" height="420"> <img src="Module 1/Images/Gears Board - Yellow Solution_Annotated.jpg" alt="Photo of the gears board in the YELLOW position" height="420">

### Schematics
These are the schematics for the Arduino circuits of each module.

Despite each schematic including a DFPlayer Pro and a speaker, the DFPlayer Pro modules were not working properly and we did not have enough time to fix them, so the modules were not included in the final assembly and the speakers were there just for style points. The audio file for each module is played from the computer running the Python script.

#### Module 1
This module uses 4 1kΩ resistors to make 4 voltage dividers with the inserted cement resistors, this is how their values are detected by the Arduino.

`Resistors` and `ResGND` are the terminals where the cement resistors are inserted.

`CablesIN` and `CablesOUT` are the terminals where the colored wires are connected.

The two pairs of LEDs show whether a puzzle was solved (green) or not (red).

<img src="Module 1/Images/Schematic.png" alt="Module 1 Schematic" height="350">

#### Module 2
This module uses 4 RFID Readers and 4 green LEDs. Each LED turns on when the correct RFID card is placed in front of each reader.

<img src="Module 2/Images/Schematic.png" alt="Module 2 Schematic" height="350">

#### Module 3
This module uses 4 momentary push buttons with internal LEDs to recreate the [Simon memory game](https://en.wikipedia.org/wiki/Simon_(game)).

The pattern of the LEDs is randomly generated by reading the analog value of pin A0, which is floating. This is why nothing must be connected to pin A0.

The Simon game has 6 stages, denoted by the 6 LEDs that turn on after each stage is completed.
| D1 (RED) | D2 (RED) | D3 (YELLOW) | D4 (YELLOW) | D5 (GREEN) | D6 (GREEN) |
| :------: | :------: | :---------: | :---------: | :--------: | :--------: | 
| Stage 1 Completed | Stage 2 Completed | Stage 3 Completed | Stage 4 Completed | Stage 5 Completed | Stage 6 Completed |

The Big Red Button is used after completing the 6 stages to choose the ending: destroy the AI (press the button) or let it escape (do not press the button).

<img src="Module 3/Images/Schematic.png" alt="Module 3 Schematic" height="350">

### Module Enclosures
The enclosure for each module consists of a 3D-printed front panel and recycled cardboard boxes as the side panels, all taped together, because we didn't have enough time to design and print a full enclosure.

#### Module 1
The front panel has 4 sections, the speaker slot (top), the LED slots (middle left), the terminals for the cement resistors (bottom left), and the terminals for the colored cables (bottom right).

<img src="Module 1/Images/Photo1_Annotated.jpg" alt="Module 1 Photo 1" height="500">

#### Module 2
The front panel has 3 sections, the speaker slot (top), the RFID card slots (middle), and the LED slots (bottom).

<img src="Module 2/Images/Photo1_Annotated.jpg" alt="Module 2 Photo 1" height="500">

The RFID readers are on the opposite side of the panel, behind the slots for the RFID cards.

<img src="Module 2/Images/Photo3.jpg" alt="Module 2 Photo 3" height="500">

#### Module 3
The front panel has 3 sections, the LED slots (top left), the button slots (bottom left), and the speaker slot (right).

<img src="Module 3/Images/Photo1_Annotated.jpg" alt="Module 3 Photo 1" height="500">

## Instructions
### Before starting
Before starting the game, make sure:
- All 3 modules are connected via USB to the computer running the Python script
- The ports for all Arduino boards are determined and used in the Python script
- The computer's volume is not muted or too low
- Module 1: No cement resistors are connected
- Module 1: The colored cables are connected to the `OUT` terminals but disconnected from the `IN` terminals
- Module 1: The gears board is placed somewhere in the room
- Module 1: The cement resistors set and the resistor color code guide are placed somewhere in the room
- Module 2: All 4 RFID cards are hidden around the room

### Solutions
To complete Module 1, the players need to solve two puzzles (in any order):
1) Find the set of cement resistors and the resistor color code guide. Insert the corresponding four resistors in the leftmost slots according to the resistance values written on the blue tape. The first green LED will turn on when the corresponding four resistors are inserted in the correct order.
2) Find the gears board and determine the correct arrangement in which to connect the colored cables on the right side of the front panel. The second green LED will turn on when all four cables are connected to the correct slots.

To complete Module 2, the players need to find the RFID cards hidden around the room and place them on the card slots in the correct order. A green LED below each slot will be turned on when the correct RFID card is placed on it.

To complete Module 3, the players need to play a game of Simon by inputting the correct sequence of colors six times in a row. Each of the six LEDs will be turned on after each sequence is correctly repeated.

To choose an ending, the players need to either do nothing or press the Big Red Button before the timer runs out after completing all modules.

### Playing the game
Now the game can be started:
1) Run the Python script on the computer, it will play [intro.mp3](<Python/intro.mp3>), then activate Module 1
2) Module 1: Once both puzzles are completed, Module 1 tells the computer to play [mod1.mp3](<Python/mod1.mp3>), then the computer activates Module 2
3) Module 2: Once all RFID cards are placed in the correct order, Module 2 tells the computer to play [mod2.mp3](<Python/mod2.mp3>)
4) Module 3: Once all 6 stages of the Simon game are completed, Module 3 starts a 30-second timer and tells the computer to play [mod3.mp3](<Python/mod3.mp3>)
5) Two endings:
	- If the Big Red Button is not pressed and the timer runs out, the computer plays [released.mp3](<Python/released.mp3>)
	- If the Big Red Button is pressed before the timer runs out, the computer plays [destroyed.mp3](<Python/destroyed.mp3>)

### Resetting the game
To reset the game, follow these instructions:
1) Module 1: Disconnect all resistors and disconnect the colored cables from the `IN` terminals (the cables must remain connected to the `OUT` terminals)
2) Module 2: Hide all 4 RFID cards around the room
3) Press the reset button on the Arduino board of each module
4) Run the Python script again

## Custom KiCad Symbols
Five custom KiCad symbols were made for this project:
1) Arduino UNO R3
2) DFPlayer Pro
3) RC522 RFID Reader Module
4) SPDT Momentary Push Button Switch with LED
5) Big Red Emergency Stop Push Button with Key

### Arduino UNO R3
Even though KiCad has an Arduino UNO R3 symbol by default, its pinout is not arranged as in the physical board. This custom symbol fixes that.

<img src="KiCad Libraries/Images/Arduino_UNO_R3.png" alt="Arduino_UNO_R3 Custom Symbol" height="500">

### DFPlayerPro
The DFPlayerPro is an audio file player module made by [DFRobot](https://www.dfrobot.com/), it has 128MB of storage.

<img src="KiCad Libraries/Images/DFPlayerPro.png" alt="DFPlayerPro Custom Symbol" height="250">

<img src="KiCad Libraries/Images/DFPlayerPro Photo.png" alt="Photo of DFPlayerPro" height="250">\
[Source](https://www.dfrobot.com/product-2232.html)

### RC522 RFID Reader Module
RFID Reader Module based on the MFRC522 IC.

<img src="KiCad Libraries/Images/RFID_Reader_RC522.png" alt="RFID_Reader_RC522 Custom Symbol" height="300">

<img src="KiCad Libraries/Images/RFID Reader.png" alt="Photo of RFID Reader" height="250">\
[Source](https://www.hotmcu.com/mifare-1356mhz-rc522-rfid-card-reader-module-p-84.html)

### Single-Pole Double-Throw Momentary Push Button Switch with LED
These are the buttons used in Module 3.

<img src="KiCad Libraries/Images/SW_Push_SPDT_LED.png" alt="SW_Push_SPDT_LED Custom Symbol" height="250">

<img src="KiCad Libraries/Images/SPDT Switch 1.png" alt="Photo 1 of SPDT Switch with LED" height="250"><img src="KiCad Libraries/Images/SPDT Switch 2.png" alt="Photo 2 of SPDT Switch with LED" height="250">\
[Source](https://www.amazon.com/dp/B01N7HCJ7S)

### Big Red Emergency Stop Push Button with Key
This is the Big Red Button used in Module 3 to choose an ending.

<img src="KiCad Libraries/Images/SW_Lock_NC_NO.png" alt="SW_Lock_NC_NO Custom Symbol" height="250">

<img src="KiCad Libraries/Images/Big Red Button 1.png" alt="Photo 1 of Big Red Emergency Button" height="250"><img src="KiCad Libraries/Images/Big Red Button 2.png" alt="Photo 2 of Big Red Emergency Button" height="250">\
[Source](https://www.amazon.com/dp/B0068AGC2Q)

## Extra Photos
### Module 1
<img src="Module 1/Images/Photo2.jpg" alt="Module 1 Photo 2" height="500">

<img src="Module 1/Images/Photo3.jpg" alt="Module 1 Photo 3" height="500"> <img src="Module 1/Images/Photo4.jpg" alt="Module 1 Photo 4" height="500">

<img src="Module 1/Images/Photo5.jpg" alt="Module 1 Photo 5" height="500"> <img src="Module 1/Images/Gears Board.jpg" alt="Photo of the gears board" height= "500">

### Module 2
<img src="Module 2/Images/Photo2.jpg" alt="Module 2 Photo 2" height="500">

<img src="Module 2/Images/Photo4.jpg" alt="Module 2 Photo 4" height="500">

### Module 3
<img src="Module 3/Images/Photo2.jpg" alt="Module 3 Photo 2" height="500">

<img src="Module 3/Images/Photo3.jpg" alt="Module 3 Photo 3" height="500">

<img src="Module 3/Images/Photo4.jpg" alt="Module 3 Photo 4" height="500">

# Credits
**Cyler Gabel**: Game Design, 3D Models\
**Ramiro Rojas**: Circuit Design, Programming, Event Proctoring\
**Anthony Dreier**: Audio Files, Event Proctoring\
**Noah Campise**: Event Proctoring