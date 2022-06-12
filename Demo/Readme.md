# Demonstration Software

The demo code is provided "as is". Is is based on personal developement and examples from sereval sources.

The intend of this software is to check the operation of the board. 

Some libraries are required to compile the code: 
- TFT_eSPI : https://github.com/Bodmer/TFT_eSPI
- Adafruit_FT6206 : https://github.com/adafruit/Adafruit_FT6206_Library
- RTClib : https://github.com/adafruit/RTClib
- MCP4725 : https://github.com/RobTillaart/MCP4725

About the TFT_eSPI library, a configuration file has to be created and stored in the LIB folder : 
C:\Users\xxxuserxxx\Documents\Arduino\libraries\TFT_eSPI
- User_Setup_Select.h
- WT32-SC01-User_Setup.h

Two examples are provided : 
- WT32_BSF_Demo : using only TFT_eSPI graphical library
- WT32_BSF_LVGL_Demo : based on hte previous one but adding the LVGL graphical interface. A setting enable or disable the LVGL features

The both examples have been compiled using Arduino IDE 1.8.15
All the libraries are up to date


Ensure that you enable the SPIFF features when compiling and uploading the code on the ESP32
