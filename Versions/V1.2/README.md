# WT32-SC01 Extension Board V1.2

## Extension board for the WT32-SC01 Dev Kit

this board is ready to be plugged one of the WT32-SC01 from Wireless-Tag (c)
http://www.wireless-tag.com/portfolio/wt32-sc01/

It includes the following features:
- LiPo - LiIon battery charger with overcharge and overdischarge protection
- Charging status LEDs
- 2 push buttons with sleep and deep sleep capabilities
- DS3121M RTC clock + backup battery (OR)
- DS1307 + Crystal + backup battery
- Micro SD connector
- MCP4725 DAC + LM386 Speaker amplifier 
- I2C, IO, Control and Power extension connectors
- Battery Voltage feedback to the ESP
- MicroUSB connector for Li-Ion charging 
- Power LED
- RF Transmitter 3 pins connector

The last current version is V1.2
![View](https://user-images.githubusercontent.com/84618082/182651188-6b95a6a9-0cad-4527-8996-4ed6f2a0c1c8.jpg)


Previus versions are V1.1
![PCB_3](https://user-images.githubusercontent.com/84618082/182650659-49ee3693-f450-4f07-b696-53cd78732bde.jpg)


and V1.0
![PCB3D](https://user-images.githubusercontent.com/84618082/182650530-611f4af8-e021-40be-80cf-20123aca5450.jpg)



## Demo Source Code

The demo source code tests all the expansion board feature. The testing code is provided "as is" and includes : 
- DAC setup and test
- Basic GUI with buttons and actions control
- I2C scanner
- JPEG decoder and display
- SD Card files acces control
- SPIFF files acces control
- RTC management
- Web Server with WiFi settings and control
- ...

Note : check the code to mofidy and adjust for your testing. The "Display Picture" feature loads by defaut "logo.jpg" from the SD Card
The source code is provided "as is" as an example. Some adjustments may be required in your configuration to compile

## Power Consumption
The Powwer consumption of the entire system (WT32 + Expansion board) have been performed using the Li-Ion battery: 
- Wifi Connection and registration : 700mA
- Normal running : 460 mA
- Light Sleep Mode : 80 mA

These measurements are performed using the provided test code.
![Pinout](https://user-images.githubusercontent.com/84618082/178008853-b726c6a8-c3a5-43ba-b987-e3e57cf9d6bb.png)

## Li-Ion battery Charging Note
The battery cna be charged from several power sources
- Micro USB Connector
- Wireless IQ module
- external power plug

The TP4056 charge controler chip ist configured to charge at 550 mA. 
Thus the charging time depends on your battery capacity : Duration(h) = Capacity(mA)/550 (approx)

The WT32-SC01 USBC-C connector CANNOT be used to charge the Li-Ion battery.

### Important Notice : Power OFF the on board power supply during the programming

## Enclosing examples

the STL files are available in this repo

### USB Charging enclosure box 

![Image3](https://user-images.githubusercontent.com/84618082/178920625-3a422964-880a-4192-9f70-5f7fc48ed0a0.jpg)
![Image1](https://user-images.githubusercontent.com/84618082/178920636-b5857ee1-936c-4fcb-a46a-ebc54b5cbf00.jpg)
![Image4](https://user-images.githubusercontent.com/84618082/178920643-7eff9802-b3e8-4e47-907a-ba5c66905cd6.jpg)


### Wireless Charging with stand

The current repo includes also additional file to enclose the WT32 with the board and manage the battery charging :
![IMG_20220603_190443](https://user-images.githubusercontent.com/84618082/171991305-c7984d57-45f8-4f77-8732-01891abf1b96.jpg)
![IMG_20220603_190458](https://user-images.githubusercontent.com/84618082/171991308-a0f0558f-5b66-437b-a4ff-4b37b8273da0.jpg)
![WT32_SC01_V0](https://user-images.githubusercontent.com/84618082/171991329-1f8d4e8e-22a2-4803-aea3-f63e086c694c.png)


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


## You want a PCB ?
You can either bluid your own with the provided manufactiring files, or purchase it here :

https://www.tindie.com/products/26898/

<a href="https://www.tindie.com/stores/blacksfactory/?ref=offsite_badges&utm_source=sellers_BlackSFactory&utm_medium=badges&utm_campaign=badge_small"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-smalls.png" alt="I sell on Tindie" width="200" height="55"></a>

