# DSP F28335 Examples
Document explaining process of programming TI F28335 using Simulink models and Code Composer Studio v10.3

## Requirements

### Hardware Requirements
* [TMDSCNCD28335](https://www.ti.com/tool/TMDSCNCD28335)
* [TMDSDOCK28335](https://www.ti.com/tool/TMDSDOCK28335)

### Software Requirements
* MATLAB2020b
* [CCSTUDIO](https://www.ti.com/tool/CCSTUDIO)

## Installation

### Arduino IDE
A ready to use Marquee-Sign.zip is available on the [release page](https://github.com/Furkanprlk/Marquee-Sign/) and is based on HTML.

#### Requirements
* Install the library "MD_Parola" (available from the library manager).
* Install the library "MD_MAX72xx" (available from the library manager).

#### Schematic
![Schematic](https://github.com/Furkanprlk/Marquee-Sign/blob/main/photos/schematic.png)

#### Setup

1. Download the RadioTelescope Zip package from the releases page
2. Extract the Zip
3. Connect the ESP8266 to your computer.
4. Open the "MarqueeSign.ino" sketch.
5. Upload the sketch.
6. Connect WiFi: SSID: MarqueeSign Password: MarqueeSign
7. Get your local IP Address "192.168.4.1"
8. Have FUN!

Now you can type http://192.168.4.1 in your browser and Marquee Sign shows up.
