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

### Important Notice : Power OFF the on board power supply during the programming
