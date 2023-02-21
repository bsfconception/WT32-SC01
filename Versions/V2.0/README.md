# WT32-SC01 Extension Board V2.0

## Extension board for the WT32-SC01 Dev Kit

this board is ready to be plugged one of the WT32-SC01 from Wireless-Tag (c)
http://www.wireless-tag.com/portfolio/wt32-sc01/

It includes the following features:
- New LiPo - LiIon battery charger with overcharge and overdischarge protection
- 4 power status LEDs (0 to 100%)
- 2 push buttons with sleep and deep sleep capabilities
- DS3121M - DS3231 - PCF8563T RTC clock + backup battery - SuperCapa
- Micro SD connector
- MCP4725 DAC + LM386 Speaker amplifier 
- I2C, IO, Control and Power extension connectors
- MicroUSB connector for Li-Ion charging 
- Buzzer

The last current version is V2.0



The manufactiring files are avialable here : https://github.com/bsfconception/WT32-SC01/tree/main/Versions/V2.0
![3D_CAPA](https://user-images.githubusercontent.com/84618082/219873292-c3183de7-3d9a-4b2f-8b31-b162a7ea319d.png)

![PinOut](https://user-images.githubusercontent.com/84618082/219873302-4922c9a2-f291-437b-9ede-fc6165873301.png)

![WT32-SC01-Layout](https://user-images.githubusercontent.com/84618082/219873501-3464c8a2-5f6e-4ff2-83c0-0f44a59918f5.svg)

## Note about he IP5306 Integrated Power Bank SOC
The datasheet contains an error about the usage of the POWER key : 
- Short Pulse : POWER ON
- 2 Short Pulses : POWER OFF
- Long Pulse (>2sec) : Toggle Torch Light


## Demo Source Code

The demo source code tests all the expansion board feature. The testing code is provided "as is" and includes : 
- DAC setup and test
- IO4 PMW output if NO DEC is present
- Basic GUI with buttons and actions control
- I2C scanner
- JPEG decoder and display
- SD Card files acces control
- SPIFF files acces control
- DS3231 / DS3232 / PCF8563 RTC chip management
- Web Server with WiFi settings and control
- ...

Note : check the code to mofidy and adjust for your testing. The "Display Picture" feature loads by defaut "logo.jpg" from the SD Card
The source code is provided "as is" as an example. Some adjustments may be required in your configuration to compile


These measurements are performed using the provided test code.


## Li-Ion battery Charging Note
The battery cna be charged from several power sources
- Micro USB Connector
- Wireless IQ module
- external power plug

The WT32-SC01 USBC-C connector CANNOT be used to charge the Li-Ion battery.

### Important Notice : Power OFF the on board power supply during the programming


# Change History
- V1.0 : 
  - correction of the Beta V0.9 (bad connector positon)
- V1.1 : 
  - Micro USB connector for battery charging
  - SEL button option selection (Pull-Up or Down)
- V1.2 : 
  - Power led on the PCB
  - RF Emitter footprint
  - DS1307 footprint (less accurate, but less expensive)
  - Jumper between ESP32 pin and Audio Amp
- V2.0 : 
  - New Li-Ion charger + Bulk Power 
  - Support DS3231 - PCF8563T
  - Super Capacitor (RTC backup)
  - On Board Buzzer
  - Merge of the 2 "audio" connectors


## You want a PCB ?
You can either bluid your own with the provided manufactiring files, or purchase here :
#NOTE : the previous version are not more available. The new vervion (V2.0) is in production.

PCB Only : https://www.tindie.com/products/28469/

Assembled board : https://www.tindie.com/products/26898/

<a href="https://www.tindie.com/stores/blacksfactory/?ref=offsite_badges&utm_source=sellers_BlackSFactory&utm_medium=badges&utm_campaign=badge_small"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-smalls.png" alt="I sell on Tindie" width="200" height="55"></a>

