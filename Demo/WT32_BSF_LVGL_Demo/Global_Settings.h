const char* host = "WT32-SC01";



#define FILE_WRITE "w"
#define FILE_READ "r"
#define FILE_APPEND "a"

#define WIFIMODE_NONE  0
#define WIFIMODE_STA   1
#define WIFIMODE_AP    2

#define PIN_SEL    2
#define PIN_WAKE   5
#define GPIO_WAKE   GPIO_NUM_5

#define PIN_BATTERY  32
// measurement gives value = 560 for VBat = 4.000V

#define BUTTON_NONE   0
#define BUTTON_SEL    1
#define BUTTON_WAKE   2

#define SDF SPIFFS

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  60        /* Time ESP32 will go to sleep (in seconds) */

#define NAME_SIZE     32
#define MESSAGE_SIZE        64

#define NB_BATTERY_LEVEL 11

typedef struct Button
{
  char Name[32];
  int x;
  int y;
  int w;
  int h;
} Button;


typedef struct {
  // HT_Home
  char ModuleName[NAME_SIZE];
  // HT_conf
  char Description[MESSAGE_SIZE];  
  // HT Wifi 
  char WIFIID[MESSAGE_SIZE];
  char WIFIPWD[MESSAGE_SIZE];
  char WIFIIP[MESSAGE_SIZE];
  char WIFIGW[MESSAGE_SIZE];
  
} GENERAL_Config;



int  Batterylevels[NB_BATTERY_LEVEL][2] =  { 
{100,4010},
{90,3920},
{80,3830},
{70,3740},
{60,3650},
{50,3560},
{40,3470},
{30,3380},
{20,3290},
{10,3200},
{0,2000}
};
