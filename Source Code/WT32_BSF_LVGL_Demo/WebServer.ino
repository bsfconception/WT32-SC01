/* 
 * This file is part of the BSFConception distribution (https://github.com/bsfconception/WT32-SC01).
 * Copyright (c) 2022 BSF Conception - France
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef __MANAGE_WEB__

IPAddress subnet(255, 255, 255, 0); 
IPAddress addr1, addr2;

String g_CurrentFolder;

void disableWifi() 
{
   WiFi.mode(WIFI_OFF);
}


void setupWifi() 
{
int trycnt = 0;
    __DEBUG_FCT__();

  g_WifiMode = WIFIMODE_NONE;
  // try in station mode
  if( strlen( g_general_Config.WIFIID) > 0 ) // an access point is defined
  {
    g_SerialDebug.print("Trying to connect to:");
    g_SerialDebug.print(g_general_Config.WIFIID);
    g_SerialDebug.print("-");
    g_SerialDebug.println(g_general_Config.WIFIPWD);


    
//    esp_wifi_set_max_tx_power(8);
    WiFi.mode(WIFI_STA); //Connect it to a wifi Network

    // if some IP address are defined
    if( (strcmp( g_general_Config.WIFIIP, "0.0.0.0") !=0) && (strcmp( g_general_Config.WIFIGW, "0.0.0.0") !=0) )
    {
      g_SerialDebug.print("Setting Static address : ");
      g_SerialDebug.println(g_general_Config.WIFIIP);
      g_SerialDebug.println(g_general_Config.WIFIGW);
      addr1.fromString(g_general_Config.WIFIIP);
      g_SerialDebug.println(addr1);
      addr2.fromString(g_general_Config.WIFIGW);
      g_SerialDebug.println(addr2);
      WiFi.config( addr1, addr2, subnet);
    }
    
    WiFi.begin(g_general_Config.WIFIID, g_general_Config.WIFIPWD); 

    while( (WiFi.status() != WL_CONNECTED) && (trycnt<90 ) )
    {// Wait for connection
      delay(500);
      g_SerialDebug.print(".");
      trycnt++;


    }
    if( WiFi.status() == WL_CONNECTED )
    {
      g_WifiMode = WIFIMODE_STA;
      
      g_SerialDebug.println("");
      g_SerialDebug.print("Connected to ");
      g_SerialDebug.println(g_general_Config.WIFIID);
      g_SerialDebug.print("IP address: ");
      g_SerialDebug.println(WiFi.localIP()); //prints the local ip given to the esp by the router
      g_SerialDebug.print("MAC address: ");
      g_SerialDebug.println(WiFi.macAddress()); //prints the local ip given to the esp by the router
      
    }
  }

  if( g_WifiMode == WIFIMODE_NONE )
  {
   g_SerialDebug.print("Setting soft-AP ... ");
    boolean result = WiFi.softAP(host, "");
    if(result == true)
    {
      g_SerialDebug.println("Ready");
      g_WifiMode = WIFIMODE_AP;
    }
    else
    {
      g_SerialDebug.println("Failed!");
    }
  
    g_SerialDebug.print("Connected! IP address: ");
    g_SerialDebug.println(WiFi.softAPIP());



  }  

  if( g_WifiMode == WIFIMODE_NONE )
  {
    return;
  }

  ////////////////Server
  server.onNotFound(handleRoot); //Calls the function handleRoot regardless of the server uri ex.(192.168.100.110/edit server uri is "/edit")
  server.on("/srv_cfg.ini", HTTP_GET, INI_File);


//  server.on("/", HTTP_GET, HT_Home);
  server.on("/HT_Home.htm", HTTP_GET, HT_Home);
  server.on("/HT_Conf.htm", HTTP_GET, HT_Config);
  server.on("/HT_Conf.htm", HTTP_POST, HT_ConfigPost);
  server.on("/HT_Reset.htm", HTTP_GET, HT_Reset);
  server.on("/trigger", HTTP_GET, HT_Trigger);

  g_CurrentFolder="/data";

 
  
  server.begin();//starts the server
  g_SerialDebug.println("HTTP server started");

  
}


void handleRoot() 
{
    __DEBUG_FCT__();
  String path = server.uri(); //saves the to a string server uri ex.(192.168.100.110/edit server uri is "/edit")
  g_SerialDebug.print("handleRoot-path ");  g_SerialDebug.println(path);

 //To send the index.html when the serves uri is "/"
  if (path.endsWith("/")) {
    path += "HT_Home.htm";
  }
  //gets the extension name and its corresponding content type
  String contentType = getContentType(path);
  File file = SDF.open(path,FILE_READ); //Open the File with file name = to path with intention to read it. For other modes see <a href="https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html" style="font-size: 13.5px;"> https://arduino-esp8266.readthedocs.io/en/latest/...</a>

  if( file )
  {
    size_t sent = server.streamFile(file, contentType); //sends the file to the server references from <a href="https://github.com/espressif/arduino-esp32/blob/master/libraries/WebServer/src/WebServer.h" style="font-size: 13.5px;"> https://arduino-esp8266.readthedocs.io/en/latest/...</a>
    file.close(); //Close the file
  }  
}

void INI_File() 
{
    __DEBUG_FCT__();

  String path = server.uri(); //saves the to a string server uri ex.(192.168.100.110/edit server uri is "/edit")
  g_SerialDebug.print("INI File-path ");  g_SerialDebug.println(path);

  //To send the index.html when the serves uri is "/"
/*  
  if (path.endsWith("/")) {
    path += "index.html";
  }
*/
  //gets the extension name and its corresponding content type
  String contentType = getContentType(path);
  File file = SDF.open(path,FILE_READ); //Open the File with file name = to path with intention to read it. For other modes see <a href="https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html" style="font-size: 13.5px;"> https://arduino-esp8266.readthedocs.io/en/latest/...</a>
  if(file)
  {
    size_t sent = server.streamFile(file, contentType); //sends the file to the server references from <a href="https://github.com/espressif/arduino-esp32/blob/master/libraries/WebServer/src/WebServer.h" style="font-size: 13.5px;"> https://arduino-esp8266.readthedocs.io/en/latest/...</a>
    file.close(); //Close the file
  }
}





//This functions returns a String of content type
String getContentType(String filename) {
    __DEBUG_FCT__();
  
  if (server.hasArg("download")) { // check if the parameter "download" exists
    return "application/octet-stream";
  } else if (filename.endsWith(".htm")) { //check if the string filename ends with ".htm"
    return "text/html";
  } else if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".gpx")) {
    return "application/octet-stream";
  } else if (filename.endsWith(".csv")) {
    return "application/octet-stream";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } else if (filename.endsWith(".png")) {
    return "image/png";
  } else if (filename.endsWith(".gif")) {
    return "image/gif";
  } else if (filename.endsWith(".jpg")) {
    return "image/jpeg";
  } else if (filename.endsWith(".ico")) {
    return "image/x-icon";
  } else if (filename.endsWith(".xml")) {
    return "text/xml";
  } else if (filename.endsWith(".pdf")) {
    return "application/x-pdf";
  } else if (filename.endsWith(".zip")) {
    return "application/x-zip";
  } else if (filename.endsWith(".gz")) {
    return "application/x-gzip";
  }
  return "text/plain";
}

/***********************************************************/



void HT_Home() 
{
String label;  
  int y, mo, d, h, m, s;
  String LocalPage, Message;
    __DEBUG_FCT__();
  
  
  String path = server.uri(); //saves the to a string server uri ex.(192.168.100.110/edit server uri is "/edit")
 //To send the index.html when the serves uri is "/"
  if (path.endsWith("/")) {
    path += "HT_Home.htm";
  }
  
  g_SerialDebug.print("HT Home-path ");  g_SerialDebug.println(path);
 
  String contentType = getContentType(path);
  File file = SDF.open(path,FILE_READ); //Open the File with file name = to path with intention to read it. For other modes see <a href="https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html" style="font-size: 13.5px;"> https://arduino-esp8266.readthedocs.io/en/latest/...</a>
//  g_SerialDebug.println( file.size() );
  if( file )
  {
    LocalPage.reserve( file.size() +1024 );
    while(file.available())
    {
        LocalPage += (char)file.read();
    }
    file.close(); //Close the file
  }


  
    server.send(200, contentType, LocalPage);
}



void HT_Config() 
{
  int y, mo, d, h, m, s;
  String LocalPage, Message;
      __DEBUG_FCT__();

  String path = server.uri(); //saves the to a string server uri ex.(192.168.100.110/edit server uri is "/edit")
  g_SerialDebug.print("HT Config-path ");  g_SerialDebug.println(path);
 
  String contentType = getContentType(path);
  File file = SDF.open(path,FILE_READ); //Open the File with file name = to path with intention to read it. For other modes see <a href="https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html" style="font-size: 13.5px;"> https://arduino-esp8266.readthedocs.io/en/latest/...</a>
//  g_SerialDebug.println( file.size() );
  if( file )
  {
  
    LocalPage.reserve( file.size() );
    while(file.available())
    {
        LocalPage += (char)file.read();
    }
    file.close(); //Close the file
  }


#ifdef __MANAGE_RTC__
  g_curDateTime = g_rtc.now();
  h = g_curDateTime.hour();
  m = g_curDateTime.minute();
  s = g_curDateTime.second();
  y = g_curDateTime.year();
  mo = g_curDateTime.month();
  d = g_curDateTime.day();
#endif
  
  Message = y;
  if( mo < 10 )
    Message = Message + "-0" + mo;
  else
    Message = Message + "-" + mo;
  if( d < 10 )
    Message = Message + "-0" + d;
  else
    Message = Message + "-" + d;
  
  LocalPage.replace("#DATE#", Message );

  Message = h;
  Message = Message + ":" + m;
//  Message = Message + d;
  
  LocalPage.replace("#TIME#", Message );

  
  LocalPage.replace("#MODULENAME#", g_general_Config.ModuleName );
  LocalPage.replace("#DESCRIPTION#", g_general_Config.Description );
  LocalPage.replace("#MAC#", WiFi.macAddress() );
  LocalPage.replace("#WIFIID#", g_general_Config.WIFIID );
  LocalPage.replace("#WIFIPWD#", g_general_Config.WIFIPWD );
  LocalPage.replace("#WIFIIP#", g_general_Config.WIFIIP );
  LocalPage.replace("#WIFIGW#", g_general_Config.WIFIGW );  
  server.send(200, contentType, LocalPage);
}





/**************************************************************************************************************/
/**************************************************************************************************************/



void HT_ConfigPost() 
{
  int y, mo, d, h, m, s;
      __DEBUG_FCT__();

  String path = server.uri(); //saves the to a string server uri ex.(192.168.100.110/edit server uri is "/edit")
  String message;
  g_SerialDebug.print("pathPOST ");  g_SerialDebug.println(path);

  if (server.hasArg("ACTION")!= false)
  { 
      String Action = server.arg("ACTION");
      
      if( !strcmp( Action.c_str() , "UPDATE_DATE" ) )
      {
        if (server.hasArg("DATE")!= false)
        { 
          String message = server.arg("DATE"); // 2020-12-15
          // parse date
          y = atoi(message.c_str());
          mo = atoi(message.c_str()+5);
          d = atoi(message.c_str()+8);
#ifdef __MANAGE_RTC__
          g_curDateTime = g_rtc.now();
          h = g_curDateTime.hour();
          m = g_curDateTime.minute();
          s = g_curDateTime.second();
          g_rtc.adjust(DateTime(y, mo, d, h, m, s));
#endif            
//          strncpy(g_general_Config.EMessage, message.c_str(), MESSAGE_SIZE-1);
//          SaveConfigData();
        }
      }
      if( !strcmp( Action.c_str() , "UPDATE_TIME" ) )
      {
        if (server.hasArg("TIME")!= false)
        { 
          String message = server.arg("TIME"); // 2020-12-15
          // parse date
          h = atoi(message.c_str());
          m = atoi(message.c_str()+3);
#ifdef __MANAGE_RTC__
          g_curDateTime = g_rtc.now();
          y = g_curDateTime.year();
          mo = g_curDateTime.month();
          d = g_curDateTime.day();
          s = g_curDateTime.second();
          g_rtc.adjust(DateTime(y, mo, d, h, m, s));
#endif            
        } 
      }  
      if( !strcmp( Action.c_str() , "UPDATE" ) )
      {
        if (server.hasArg("MODULENAME")!= false) { 
          message = server.arg("MODULENAME");
        }
        else {
          message = "";
        }
        message.replace( " ", "" );
        strncpy(g_general_Config.ModuleName, message.c_str(), NAME_SIZE-1);
        
/***************/
        if (server.hasArg("DESCRIPTION")!= false) { 
          message = server.arg("DESCRIPTION");
        }
        else {
          message = "";
        }
        strncpy(g_general_Config.Description, message.c_str(), MESSAGE_SIZE-1);
/***************/
        if (server.hasArg("WIFIID")!= false) { 
          message = server.arg("WIFIID");
        }
        else {
          message = "";
        }
        strncpy(g_general_Config.WIFIID, message.c_str(), MESSAGE_SIZE-1);
/***************/
        if (server.hasArg("WIFIPWD")!= false) { 
          message = server.arg("WIFIPWD");
        }
        else {
          message = "";
        }
        strncpy(g_general_Config.WIFIPWD, message.c_str(), MESSAGE_SIZE-1);
/***************/
/***************/
        if (server.hasArg("WIFIIP")!= false) { 
          message = server.arg("WIFIIP");
        }
        else {
          message = "";
        }
        strncpy(g_general_Config.WIFIIP, message.c_str(), MESSAGE_SIZE-1);
/***************/
/***************/
        if (server.hasArg("WIFIGW")!= false) { 
          message = server.arg("WIFIGW");
        }
        else {
          message = "";
        }
        strncpy(g_general_Config.WIFIGW, message.c_str(), MESSAGE_SIZE-1);
/***************/

        SaveConfigData();
         
      }
    
  } 

  HT_Config();
}



void HT_Reset() 
{

unsigned char Length;
unsigned char Type;
unsigned short Delay;
unsigned char Repetition;
    __DEBUG_FCT__();
            
  String path = server.uri(); //saves the to a string server uri ex.(192.168.100.110/edit server uri is "/edit")
  String message;

 
  server.sendHeader("Location","/HT_Home.htm");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);   

  delay(500);

  ESP.restart(); 

}


void HT_Trigger() 
{
unsigned char Length;
unsigned char Type;
unsigned short Delay;
unsigned char Repetition;
    __DEBUG_FCT__();
            

  String path = server.uri(); //saves the to a string server uri ex.(192.168.100.110/edit server uri is "/edit")
  String message;

  if (server.hasArg("type")!= false)
  { 
      String Action = server.arg("type");
      
      int ID = atoi( Action.c_str() );
      if( (ID>0) && (ID<9) )
      {
        switch(ID)
        {
            case 1:
              displayTime(  );
              break;
              
            case 2:
              displaybattery(  );
              break;
              
            case 3:
              displayPicture(  );
              break;
              
            case 4:
              playSound(  );
              break;
         
        }
      }
  } 

  server.sendHeader("Location","/HT_Home.htm");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);   
}


#endif
