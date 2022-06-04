# WT32-SC01 Expansion Board

## Expansion board for the WT32-SC01 Dev Kit

this board is ready to be connected to one of the 2 expansions connector of the WT32-SC01 from Wireless-Tag (c)
http://www.wireless-tag.com/portfolio/wt32-sc01/

It includes the following features:
- LiPo - LiIon battery charger with overcharge and overdischarge protection
- 2 push buttons
- DS3131M + backup battery RTC clock
- Micro SD connector
- MCP4725 DAC + Speaker amplifier
- I2C, IO, Control, Power connectors
- Battery Voltage Senror

The PCB dimension fits to the WT32-SC01's.
![PCB_cnt](https://user-images.githubusercontent.com/84618082/171991256-95f700ce-6a8f-4fe4-9719-ac3704c6d6b5.jpg)
![PCB3D](https://user-images.githubusercontent.com/84618082/171991262-c997b919-290f-492b-8c03-d610d510bfbd.jpg)



## Demo Source Code

The demo source code tests all the expansion board feature. The testing code is provided "as is" and includes : 
- DAC setup and test
- Basic GUI with buttons and actions control
- I2C scanner
- JPEG decoder and display
- SD Card files acces control
- SPIFF files acces control
- RTC maangement
- Web Server with WiFi settings and control
- ...

Note : check the code to mofidy and adjust for your testing. The "Display Picture" feature loads by defaut "logo.jpg" from the SD Card

## Power Consumption
The Powwer consumption of the entire system (WT32 + Expansion board) have been performed using the Li-Ion battery: 
- Wifi Connection and registration : 700mA
- Normal running : 460 mA
- Light Sleep Mode : 80 mA

These measurements are performed using the provided test code.
![WT32_PinOut](https://user-images.githubusercontent.com/84618082/171991270-e8a274b4-90a0-4d45-b052-a17b18b785e3.png)


### Important Notice : Power OFF the on board power supply during the programming

## You want a PCB ?
the PCB can be purchased here : 

https://www.etsy.com/fr/listing/1239499505/wt32-sc01-expansion-board-pcb-only

https://www.tindie.com/products/blacksfactory/wt32-sc01-expansion-board-pcb-only/

The current repo includes also additional file to enclose the WT32 with the board and maange the battery charging :
![IMG_20220603_165824](https://user-images.githubusercontent.com/84618082/171991297-3b7ad8bd-ed56-42aa-a7ef-7966c8f96caa.jpg)
![IMG_20220603_190443](https://user-images.githubusercontent.com/84618082/171991305-c7984d57-45f8-4f77-8732-01891abf1b96.jpg)
![IMG_20220603_190458](https://user-images.githubusercontent.com/84618082/171991308-a0f0558f-5b66-437b-a4ff-4b37b8273da0.jpg)
![WT32_SC01_V0](https://user-images.githubusercontent.com/84618082/171991329-1f8d4e8e-22a2-4803-aea3-f63e086c694c.png)





