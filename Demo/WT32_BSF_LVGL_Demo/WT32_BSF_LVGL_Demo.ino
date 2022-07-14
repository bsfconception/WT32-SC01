#define __SEL_INVERT_PIN__

#define __ORIENTATION__  1

#define __MANAGE_SDCARD__
//#define __MANAGE_RTC__
#define __MANAGE_WEB__
//#define __MANAGE_DAC__
//#define __USE_LVGL__




#define __DEBUG__

//#define __DEBUG_FCT__(a)  g_SerialDebug.println(__FUNCTION__)
//#define __DEBUG_FCT__(a)  g_DisplayStack()
#define __DEBUG_FCT__(a)


// Variables for touch x,y
#ifdef DRAW_ON_SCREEN
static int32_t x, y;
#endif


#include "Global_Settings.h"
#include <TFT_eSPI.h> 

#include <SPI.h>
#include <FS.h>
#include <SD.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#include <Adafruit_FT6206.h>

static const uint16_t g_screenWidth = TFT_WIDTH;
static const uint16_t g_screenHeight = TFT_HEIGHT;

#ifdef __USE_LVGL__
  #include <lvgl.h>
  #include "esp_freertos_hooks.h"
  #include "lv_conf_local.h"

  static lv_disp_draw_buf_t g_draw_buf;
  static lv_color_t g_buf[g_screenWidth * 10];
  lv_obj_t *g_screenMain;

#endif

SPIClass SPI_SD(VSPI);

/*** global variables ***/
GENERAL_Config g_general_Config;
int g_WifiMode = WIFIMODE_NONE;
String g_MessageBuffer;


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


TFT_eSPI g_tft = TFT_eSPI();
Adafruit_FT6206 g_ts = Adafruit_FT6206();

void g_DisplayStack( void )
{
    long Stack = uxTaskGetStackHighWaterMark( NULL );
    Serial.print("Stack:");
    Serial.println(Stack);
  
}

/***********************************************************************************************************************************/
#ifdef __USE_LVGL__
  int GetKey( void )
  {
    __DEBUG_FCT__();

    Serial.println("Feature not implemented");
    delay(10);
    return( BUTTON_NONE );
  }
#else
  int GetKey( void )
  {
  int res = 0;  
    __DEBUG_FCT__();
  
    res = digitalRead( PIN_SEL );
    #ifdef __SEL_INVERT_PIN__
      if(res)
        return( BUTTON_SEL );
    #else
      if(res == 0)
        return( BUTTON_SEL );
    #endif
  
  
    res = digitalRead( PIN_WAKE );
    if(res)
      return( BUTTON_WAKE );
  
    return( BUTTON_NONE );
  }
  
#endif


/*** Function declaration ***/
/*
void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
//void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
void lv_button_demo(void);
*/


/*** Touchpad callback to read the touchpad ***/
#ifdef __USE_LVGL__
  void touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
  {
    if( ! g_ts.touched() )   
    {
  
      data->state = LV_INDEV_STATE_RELEASED;
    }
    else
    {
      data->state = LV_INDEV_STATE_PRESSED;
      TS_Point p = g_ts.getPoint();
  
      /*Set the coordinates*/
      if( __ORIENTATION__ )
      {
        data->point.x = p.y;
        data->point.y = TFT_WIDTH-p.x;
      }
      else
      {
        data->point.x = p.x;
        data->point.y = p.y;
      }
      #ifdef __DEBUG__
        Serial.printf("Touch (x,y): (%03d,%03d)\n", data->point.x,  data->point.y );
      #endif
    }
  }

  static void lv_tick_task(void)
  {
   lv_tick_inc(portTICK_RATE_MS);
  }

#endif

void setup(void)
{
  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.println("Starting WT32+Addon");

  #ifdef __SEL_INVERT_PIN__
    pinMode( PIN_SEL, INPUT );
  #else
    pinMode( PIN_SEL, INPUT_PULLUP );
  #endif
  pinMode( PIN_WAKE, INPUT );
  pinMode( PIN_BATTERY, INPUT);  
  
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, LOW);
  digitalWrite(TFT_BL, 128);

  // init i2C communication 
  Wire.begin(PIN_SDA, PIN_SCL);

  
// Begind DISABLE THIS LINE TO SCAN THE I2C DEvIcES
//  _I2C_Scan();
// end : DISABLE ...

  if (!g_ts.begin(PIN_SDA, PIN_SCL, 40)) 
  {
    Serial.println("Couldn't start touchscreen controller");
  }
  else
  {
    Serial.println("Start touchscreen controller");
  }


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


  #ifdef __MANAGE_RTC__
    _RTC_Init();
  #endif

  #ifdef __MANAGE_DAC__
    if (_MCP_setup() == 0)
    {
      Serial.println("Could not find DAC");
    }
    else 
    {
      Serial.println("DAC Connected");
    }
  #endif

  _LCD_Setup();


#ifdef __MANAGE_WEB__
    setupWifi();
#endif

  #ifdef __USE_LVGL__
    /*** Create simple label and show LVGL version ***/
    String LVGL_Arduino = "WT32-SC01 with LVGL ";
    LVGL_Arduino += String('v') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
    lv_obj_t *label = lv_label_create(g_screenMain); // full screen as the parent
    lv_label_set_text(label, LVGL_Arduino.c_str());  // set label text
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);      // Center but 20 from the top
    lv_button_demo();
    // Screen load
    lv_scr_load(g_screenMain);
  #else
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

void loop()
{
int y, mo, d, h, m, s, res, v;




#ifdef __MANAGE_WEB__
  server.handleClient();
#endif     

/***********************************************************/
  // manage the timer 
 if( ( millis() - LastTimerTop ) > 10 )   // each 10 ms - 100Hz
 {
    LastTimerTop = millis();

    #ifdef __USE_LVGL__
      lv_tick_inc(10);
      lv_timer_handler(); /* let the GUI do its work */
    #endif     

      
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

/***************************************/
  if( l_KeyboardTick )
  {
    l_KeyboardTick = 0;
    
#ifndef __USE_LVGL__

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
    if( curkey != GetKey() )
    {
      curkey = GetKey();
      if( curkey == BUTTON_SEL )
        g_SerialDebug.println( "Key Pressed : SEL" );
      if( curkey == BUTTON_WAKE )
        g_SerialDebug.println( "Key Pressed : WAKE" );
    }
#endif    
  }




#ifdef DRAW_ON_SCREEN
  /*** Draw on screen with touch ***/
//  if (g_ts.getTouch(&x, &y))
  if( g_ts.touched() )   
  {
    TS_Point p = g_ts.getPoint();
    
    g_tft.fillRect(p.x - 2, p.y - 2, 5, 5, TFT_RED);
    g_tft.setCursor(380, 0);
    g_tft.printf("Touch:(%03d,%03d)", p.x, p.y);
    // 
  }
#endif

}
