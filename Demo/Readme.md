# Demonstration Software

The demo code is provided "as is". Is is based on personal developement and from examples retrived from sereval sources.

The intend of this software is to check the operation of the board, NOT TO PROVIDE A FINAL SOLUTION. 

## Arduino Configuration
- Version 1.8.19
- Boards Manager in "preferences":
    - https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
    - http://arduino.esp8266.com/stable/package_esp8266com_index.json


## Some libraries are required to compile the code:

- name=Adafruit BusIO       url=https://github.com/adafruit/Adafruit_BusIO	        version=1.12.0
- name=Adafruit FT6206 Library      url=https://github.com/adafruit/Adafruit_FT6206_Library	        version=1.0.6
- name=Adafruit GFX Library     	url=https://github.com/adafruit/Adafruit-GFX-Library	        version=1.11.3
- name=Adafruit ILI9341	        url=https://github.com/adafruit/Adafruit_ILI9341	        version=1.5.11
- name=JPEGDecoder	        url=https://github.com/Bodmer/JPEGDecoder	        version=1.8.1
- name=lvgl	        url=https://lvgl.io	        version=8.2.0
- name=MCP4725	        url=https://github.com/RobTillaart/MCP4725	    version=0.3.3
- name=RTClib	        url=https://github.com/adafruit/RTClib	        version=2.0.3
- name=TFT_eSPI	        url=https://github.com/Bodmer/TFT_eSPI	        version=2.4.72


# Libraries customisation

Sereval modification are requied in the downloaded libraries:

## TFT_eSPI library 
has to be correctly setup for the destination board during compiling : 
A configuration file has to be created and stored in the LIB folder
C:\Users\xxxuserxxx\Documents\Arduino\libraries\TFT_eSPI
- User_Setup_Select.h
- WT32-SC01-User_Setup.h

## LVGL
the following file 
    C:\Users\XXXX\Documents\Arduino\libraries\lvgl\lv_conf_template.h
    must be renamed and copied to 
    C:\Users\XXXX\Documents\Arduino\libraries\lvgl\src\lv_conf.h
    


# Test code 
Two examples are provided : 
- WT32_BSF_LVGL_Demo : code based on the previous but adding the LVGL graphical interface. A setting enables or disables the LVGL features





Ensure that you enable the SPIFF features when compiling and uploading the code on the ESP32



## Notes
Somes guides have been helpfull to make it run
- https://blog.csdn.net/weixin_44007534/article/details/115224595
- https://daumemo.com/how-to-use-lvgl-library-on-arduino-with-an-esp-32-and-spi-lcd/
- https://github.com/sukesh-ak/LVGL8-WT32-SC01-Arduino

