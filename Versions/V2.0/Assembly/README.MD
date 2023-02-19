# BOM #
List of components
|Item|Qty|Reference(s)|Value|
|----|----|----|----|
|1|1|BT1|CR1220 Holder|
|2|1|BZ1|SMD Buzzer|
|3|5|C1, C3, C14, C19, C20|100nF|
|4|2|C2, C17|10uF|
|5|6|C4, C5, C6, C7, C8, C11|22uF|
|6|2|C9, C18|470uF|
|7|1|C10|47uF|
|8|3|C12, C13, C15|100uF|
|9|1|C16|47nF|
|10|1|C21|1F|
|11|1|D1|25% LED|
|12|1|D2|1N4004|
|13|1|D3|50% LED|
|14|1|D4|100% LED|
|15|1|D5|75% LED|
|16|1|D6|LED|
|17|2|D7, D8|1N4001|
|18|1|J1|TF_SDCard|
|19|2|J2, J4|JST_PH_S4B-PH-K_1x04_P2.00mm_Horizontal|
|20|1|J3|JST_PH_S4B-PH-K_1x04_P2.00mm_Horizontal|
|23|1|J8|JST_PH_S3B-PH-K_1x03_P2.00mm_Horizontal|
|24|1|J10|JST_PH_S8B-PH-K_1x08_P2.00mm_Horizontal|
|25|1|J12|JST_SH_SM04B-SRSS-TB_1x04-1MP_P1.00mm_Horizontal|
|26|1|J13|JST_PH_S2B-PH-K_1x02_P2.00mm_Horizontal|
|27|1|J14|USB_B_Micro|
|32|1|L1|1uH|
|33|1|Q1|MMBT3904|
|34|1|R1|0R5|
|35|1|R2|20|
|36|2|R3, R19|47K|
|37|1|R4|10K|
|38|2|R5, R16|1K|
|39|1|R6|4K7|
|40|1|R15|20K|
|41|1|R17|10|
|42|1|R18|1K2|
|43|1|SW1|PUSH_TS_1224W|
|44|1|SW2|Push_1P1T_Mini4x4x1.5|
|45|1|SW3|PUSH_TS_1224W|
|46|1|SW4|PUSH_TS_1224W|
|47|1|SW5|SW_Tactile_SPST_Angled|
|48|1|SW6|SW_Tactile_SPST_Angled|
|49|1|SW7|SW_Tactile_SPST_Angled|
|50|1|U1|DS3231M|
|52|1|U3|IP5306|
|53|1|U4|PCF8563T|
|54|1|U5|DS3232M|
|55|1|U7|MCP4725-DAC7571|
|56|1|U8|LM386|
|58|1|Y1|32KHz|


# Mandatoru components based on options
|Reference(s)|Value|Mandatory|DS323x-CR1220|DS323x-0.5F Capa|PCF8563 CR1220|PCF8563 0.5F Capa|Buzzer|Audio Amplifier|MCP4725DAC|
|----|----|----|----|----|----|----|----|----|----|
|BT1|CR1220||Y||Y|||||
|BZ1|Buzzer||||||Y|||
|C1|100nF||Y|Y||||||
|C2|10uF|Y||||||||
|C3|100nF|Y||||||||
|C4|22uF|Y||||||||
|C5|22uF|Y||||||||
|C6|22uF|Y||||||||
|C7|22uF|Y||||||||
|C8|22uF|Y||||||||
|C9|470uF|Y||||||||
|C10|47uF|Y||||||||
|C11|22uF|Y||||||||
|C12|100uF|||||||Y||
|C13|100uF|||||||Y||
|C14|100nF||||||||Y|
|C15|100uF||||||||Y|
|C16|47nF|||||||Y||
|C17|10uF|||||||Y||
|C20|100nF||||Y|Y||||
|C21|0F5|||Y||Y||||
|D1|0.25|Y||||||||
|D2|1N4004|Y||||||||
|D3|0.5|Y||||||||
|D4|1|Y||||||||
|D5|0.75|Y||||||||
|D6|LED|Opt||||||||
|D7|1N4001|||Y|Y|Y||||
|D8|1N4001||||Y|||||
|J1|SD_Card|Y||||||||
|J2|CTRL|Y||||||||
|J3|I2C|Y||||||||
|J4|CTRL|Y||||||||
|J8|POWER|Y||||||||
|J10|GPIO|Y||||||||
|J12|I2C|Opt||||||||
|J13|BAT|Y||||||||
|J14|USB_B_Micro|Y||||||||
|JP1|IO4_OUT|||||||Closed|Open|
|JP2|RTC_BAT||Open|Closed|Open|Open|Don't Care|Don't Care|Don't Care|
|JP3|DAC A0|DAC I2C address||||||||
|JP4|SEL|Linked to R19 option||||||||
|L1|1uH|Y||||||||
|Q1|MMBT3904||||||Y|||
|R1|0R5|Y||||||||
|R3|47K|Y||||||||
|R4|10K|Y||||||||
|R5|1K|||Y||Y||||
|R6|4K7||||||Y|||
|R15|20K|||||||Y||
|R16|1K|||||||Y||
|R17|10|||||||Y||
|R18|1K2|||||||Y||
|R19|47K|Linked to JP4 option||||||||
|SW1 / SW6|WAKE|Y||||||||
|SW2|RESET|Y||||||||
|SW3 / SW7|SEL|Y||||||||
|SW4 / SW5|PWR|Y||||||||
|U1|DS3231M||Y|Y||||||
|U3|IP5306|Y||||||||
|U4|PCF8563T||||Y|Y||||
|U5|DS3232M||Y|Y||||||
|U7|MCP4725-DAC7571||||||||Y|
|U8|LM386|||||||Y||
|Y1|32KHz||||Y|Y||||

# Jumper settings
| Jumper | Picture | Description | 
| ---- | ---- | ---- | 
| JP1 | ![JP1](https://user-images.githubusercontent.com/84618082/219957034-e954d172-2c32-4da3-90e9-747deb850008.jpg) | Link IO4 to Audio Amplifier | 
| JP2 | ![JP2](https://user-images.githubusercontent.com/84618082/219957057-29de11a6-ca3f-49e8-b91a-95704823dae4.jpg) | Solder only with DS323x + 0.5FCapa | 
| JP3 | ![JP3_L](https://user-images.githubusercontent.com/84618082/219957524-68242c41-43bf-4867-a656-01750658b648.jpg) | DAC I2C Address=0x63 | 
|  | ![JP3_r](https://user-images.githubusercontent.com/84618082/219957528-86750cc2-f627-4cf7-b462-981b1e056b1f.jpg) | DAC I2C Address=0x63 | 
| JP4 | ![JP4_L](https://user-images.githubusercontent.com/84618082/219957555-0f2b647f-db7c-478f-b3c7-9370388bec7d.jpg) | Default value for SEL is '1' Remove R19 | 
|  | ![JP4_r](https://user-images.githubusercontent.com/84618082/219957559-eb3f1c6d-e0d2-4e53-b751-87656cb2cd59.jpg) | Default value for SEL is '0' Solder R19 | 


# Examples of assembled PCB #
## Base Version
![Base](https://user-images.githubusercontent.com/84618082/219873674-359837d6-7c5d-49a2-88f0-c229368e3fdf.png)

## Base Version + Audio Amp
![opt4](https://user-images.githubusercontent.com/84618082/219873691-34a80357-db52-4684-95ce-8fa7a2eea096.png)

## Base Version + Audio Amp + Buzzer
![opt3](https://user-images.githubusercontent.com/84618082/219873715-bb43910a-4eca-4673-b687-e6cd12b8cba9.png)

## Base Version + Audio Amp + Buzzer + DAC
![opt2](https://user-images.githubusercontent.com/84618082/219873738-7ec366cf-68ae-4a44-8095-6e63e4763134.png)

## Base Version + Audio Amp + Buzzer + DAC + DS3232
![DS3232](https://user-images.githubusercontent.com/84618082/219873760-c614199b-b6fb-43c9-a8ec-c2cd76a44178.png)

## Full Mounted PCB  + PCF8563 + Capacitor
![Full_CAPA](https://user-images.githubusercontent.com/84618082/219873795-992b8f21-4fec-46de-8510-d7ee792509d8.png)

## Full Mounted PCB  + PCF8563 + Battery Support
![Full_CR](https://user-images.githubusercontent.com/84618082/219873621-798adab5-4a83-448e-85c2-c95bc60a61b0.png)

## Full Mounted PCB  + DS3231 + Battery Support
![DS3231](https://user-images.githubusercontent.com/84618082/219873642-e8f2b819-b7f2-4c7e-82d2-90595061a8c2.png)

