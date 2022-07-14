# Demonstration Softwares

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
- WT32_BSF_LVGL_Demo : code based on the previous but adding the LVGL graphical interface. A setting enables or disables the LVGL features
- old/WT32_BSF_Demo : using only TFT_eSPI graphical library

The both examples have been compiled using Arduino IDE 1.8.15
All the libraries are up to date for building

the following file list all installed libraries on my system when compiling:
[Libraries_Version_20220714.txt](https://github.com/bsfconception/WT32-SC01/files/9112208/Libraries_Version_20220714.txt)



Ensure that you enable the SPIFF features when compiling and uploading the code on the ESP32



## Notes
Somes guides have been helpfull to make it run
- https://blog.csdn.net/weixin_44007534/article/details/115224595
- https://daumemo.com/how-to-use-lvgl-library-on-arduino-with-an-esp-32-and-spi-lcd/

