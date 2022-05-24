#define __MANAGE_SDCARD__
#define __MANAGE_RTC__
#define __MANAGE_WEB__
#define __MANAGE_DAC__
#define __MANAGE_LCD__

#define __DEBUG__


#include "Global_Settings.h"
#include <TFT_eSPI.h> 

#include <SPI.h>
#include <FS.h>
#include <SD.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

//#include "WT32-SC01-User_Setup.h"
#include <Adafruit_FT6206.h>


SPIClass SPI_SD(VSPI);


GENERAL_Config g_general_Config;
int g_WifiMode = WIFIMODE_NONE;
int g_screenWidth = 0;
int g_screenHeight = 0;
String MessageBuffer;


/***********************************************************************************************************************************/
#define g_SerialDebug Serial


#ifdef __MANAGE_RTC__
  #include "RTClib.h"
  DateTime g_curDateTime;  
  RTC_DS3231 g_rtc;
#endif

#ifdef __MANAGE_WEB__
  WebServer server(80);
#endif

#ifdef __MANAGE_DAC__
  #include "MCP4725.h"
  MCP4725 g_MCP(0x60);  // 0x62 or 0x63 or ....  Use "_I2C_Scan();" line to verify the connected I2C devices 
#endif


#ifdef __MANAGE_LCD__
  TFT_eSPI g_tft = TFT_eSPI();
  Adafruit_FT6206 g_ts = Adafruit_FT6206();
#endif


/***********************************************************************************************************************************/

int GetKey( void )
{
int res = 0;  

  res = digitalRead( PIN_SEL );
  if(res == 0)
    return( BUTTON_SEL );


  res = digitalRead( PIN_WAKE );
  if(res)
    return( BUTTON_WAKE );

  return( BUTTON_NONE );
}


void setup() {
  Serial.begin(115200);
  Serial.println("Starting WT32+Addon");

  pinMode( PIN_SEL, INPUT_PULLUP );
    pinMode( PIN_WAKE, INPUT );
  pinMode( PIN_BATTERY, INPUT);  
  
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, LOW);
  
// Begind DISABLE THIS LINE TO SCAN THE I2C DEvIcES
//  _I2C_Scan();
// end : DISABLE ...


// Start filing subsystem
  if (SPIFFS.begin()) 
  {
    Serial.println("SPIFFS Active");
  } 
  else 
  {
    Serial.println("Unable to activate SPIFFS");
  }
  

  Serial.println("Loading Configuration Data");
  LoadConfigData();

  #ifdef __MANAGE_SDCARD__
    _SD_MountSDCard();
  #endif

  #ifdef __MANAGE_LCD__
    // Pins 18/19 are SDA/SCL for touch sensor on this device
    // 40 is a touch threshold
    if (!g_ts.begin(PIN_SDA, PIN_SCL, 40)) 
    {
      Serial.println("Couldn't start touchscreen controller");
    }
  #else
        // init i2C communication 
    Wire.begin(PIN_SDA, PIN_SCL);
  #endif

  #ifdef __MANAGE_RTC__
    _RTC_Init();
  #endif

  #ifdef __MANAGE_DAC__
    if (_MCP_setup == false)
    {
      Serial.println("Could not find DAC");
    }
    else 
    {
      Serial.println("DAC Connected");
    }
  #endif

#ifdef __MANAGE_LCD__
  _LCD_Setup();
#endif


#ifdef __MANAGE_WEB__
    setupWifi();
#endif



/*
  cube();
  fact = 180 / 3.14159259; // conversion from degrees to radians.
  Xoff = 240; // Position the center of the 3d conversion space into the center of the TFT screen.
  Yoff = 160;
  Zoff = 550; // Z offset in 3D space (smaller = closer and bigger rendering)
*/
//  listDir(SD, "/", 0);

//  drawSdJpeg("/logo.jpg", 0, 0);     // This draws a jpeg pulled off the SD Card
#ifdef __MANAGE_LCD__
  Menu1_DrawGUI();
#endif  

}

/***********************************************************************************************************************************/

int curkey = BUTTON_NONE, BPVal;


long LastTimerTop = 0;
int g_SecCounter = 0;
int g_MinCounter = 0;
int g_100msCounter = 0;
int g_500msCounter = 0;
int g_1hCounter = 0;
int g_5SecCounter = 0;
int g_5MinCounter = 0;
int l_KeyboardTick = 1;
int g_Touched = -1;

void loop() {
int y, mo, d, h, m, s, res, v;


  #ifdef __MANAGE_WEB__
      server.handleClient();
  #endif     

/***********************************************************/
  // manage the timer 
 if( ( millis() - LastTimerTop ) > 10 )   // each 10 ms - 100Hz
  {
    LastTimerTop = millis();
      
    g_SecCounter ++;
    g_100msCounter ++;
    g_500msCounter ++;
    g_5SecCounter++;
  }

  if (g_100msCounter >= 10)  // earch 100 ms
  {
    g_100msCounter = 0;
    l_KeyboardTick = 1;
   
  }

  if (g_500msCounter >= 50)  // earch 500 ms
  {
    g_500msCounter = 0;
  }


  if (g_SecCounter >= 100)  // earch 1 s
  {
    g_SecCounter = 0;
    g_MinCounter ++;
    g_5MinCounter ++;
    
  }

  if (g_5SecCounter >= 500)  // earch 5 s
  {
    g_5SecCounter = 0;
  }

  if (g_MinCounter >= 60)  // each 1 min
  {
    g_MinCounter = 0;
    g_1hCounter++;
  }
  
  if (g_5MinCounter >= 180)  // each 3 min
  {
    g_5MinCounter = 0;

  }


  if( l_KeyboardTick )
  {
    l_KeyboardTick = 0;
#ifdef __MANAGE_LCD__

    if( (g_ts.touched()) && (g_Touched < 0 ) )  
    {
      TS_Point p = g_ts.getPoint();

      res = Menu1_GetButton(p.x, p.y);
      g_Touched = res;
      if( g_Touched >= 0)
      {
        Menu1_PushGUI( g_Touched, 1 );
      }
      
      Serial.printf("%d %d : %d\n", p.x, p.y, res);
    }
    if( g_Touched >= 0 )
    {
      if( !g_ts.touched() ) 
      {
        Menu1_PushGUI( g_Touched, 0 );
        switch(g_Touched)
        {
            case 0:
              displayTime(  );
              break;
              
            case 1:
              displaybattery(  );
              break;
              
            case 2:
              displayPicture(  );
              break;
              
            case 3:
              playSound(  );
              break;
              
            case 4:
              enterSleep(  );
              break;
        }
 
         
        g_Touched = -1;
      }
    }
#endif
  
    if( curkey != GetKey() )
    {
      curkey = GetKey();
      if( curkey == BUTTON_SEL )
        g_SerialDebug.println( "Key Pressed : SEL" );
      if( curkey == BUTTON_WAKE )
        g_SerialDebug.println( "Key Pressed : WAKE" );
    }
    
  }


  
/*
  // Rotate around x and y axes in 1 degree increments
  Xan++;
  Yan++;

  Yan = Yan % 360;
  Xan = Xan % 360; // prevents overflow.

  SetVars(); //sets up the global vars to do the 3D conversion.

  for (int i = 0; i < LinestoRender ; i++)
  {
    ORender[i] = Render[i]; // stores the old line segment so we can delete it later.
    ProcessLine(&Render[i], Lines[i]); // converts the 3d line segments to 2d.
  }
  RenderImage(); // go draw it!


*/

  
}
