# Demonstration Software

The demo code is provided "as is". Is is based on personal developement and from examples retrived from sereval sources.

The intend of this software is to check the operation of the board, NOT TO PROVIDE A FINAL SOLUTION. 

## Arduino Configuration
- Version 1.8.19
- Boards Manager in "preferences":
    - https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
    - http://arduino.esp8266.com/stable/package_esp8266com_index.json


Some libraries are required to compile the code: 
- TFT_eSPI : https://github.com/Bodmer/TFT_eSPI
- Adafruit_FT6206 : https://github.com/adafruit/Adafruit_FT6206_Library
- RTClib : https://github.com/adafruit/RTClib
- MCP4725 : https://github.com/RobTillaart/MCP4725

# Important Note
It seems that the legacy Adafruit library for the TF6206 does contain the expected propotypes
Here is a modified library : [Adafruit_FT6206_Library-master.zip](https://github.com/bsfconception/WT32-SC01/files/9152723/Adafruit_FT6206_Library-master.zip)


# Libraries customisation
Sereval modification are requied in the downloaded libraries:
## TFT_eSPI library 
has to be correctly setup for the destination board during compiling : 
A configuration file has to be created and stored in the LIB folder
C:\Users\xxxuserxxx\Documents\Arduino\libraries\TFT_eSPI
- User_Setup_Select.h
- WT32-SC01-User_Setup.h

## LVGL
the 
    C:\Users\XXXX\Documents\Arduino\libraries\lvgl\lv_conf_template.h file 
    must be copied to 
    C:\Users\XXXX\Documents\Arduino\libraries\lvgl\src\lv_conf.h
    


# Test code 
Two examples are provided : 
- WT32_BSF_LVGL_Demo : code based on the previous but adding the LVGL graphical interface. A setting enables or disables the LVGL features


the following file list all installed libraries on my system when compiling:
[Libraries_Version_20220714.txt](https://github.com/bsfconception/WT32-SC01/files/9112208/Libraries_Version_20220714.txt)



Ensure that you enable the SPIFF features when compiling and uploading the code on the ESP32



## Notes
Somes guides have been helpfull to make it run
- https://blog.csdn.net/weixin_44007534/article/details/115224595
- https://daumemo.com/how-to-use-lvgl-library-on-arduino-with-an-esp-32-and-spi-lcd/
- https://github.com/sukesh-ak/LVGL8-WT32-SC01-Arduino

