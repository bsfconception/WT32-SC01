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

#define GENERAL_CONFIG_FILE "/GEN_CFG.INI"

typedef struct {
    int CurrentIndex;
    String Data;
} INI_FILE_STRUCTURE;

INI_FILE_STRUCTURE g_IniFileData;


int INI_getValue( char *Section, char *Key, char *Data, int Len )
{
int index_section, index_key, index_end, data_len;  
    __DEBUG_FCT__();

    
  // find the Section
  index_section = g_IniFileData.Data.indexOf(Section);
  if( index_section < 0)
    return(0);
    
  // find the key
  index_key = g_IniFileData.Data.indexOf(Key, index_section);
  if( index_key < 0)
    return(0);
    
// find the '='
  index_key = g_IniFileData.Data.indexOf('=', index_key);
  if( index_key < 0)
    return(0);
    
  index_key++;
  // get the value
  // find the CR/LF (0D0A)
  index_end = g_IniFileData.Data.indexOf((char)(0x0d), index_key);
  if( index_end < 0)
    return(0);
    
  data_len = index_end - index_key;
  if(data_len >= Len)
    data_len = Len-1;
    
  strncpy( Data, g_IniFileData.Data.c_str() + index_key, data_len );
  Data[data_len] = 0;

  return(1);
       
}



int INI_SPIFF_Load( char *Name )
{
    __DEBUG_FCT__();
 
  // init
  g_IniFileData.Data = "";
  File file = SPIFFS.open(Name,FILE_READ); 
  if( file )
  {
    g_IniFileData.Data.reserve( file.size() );
    while(file.available())
    {
        g_IniFileData.Data += (char)file.read();
    }
    file.close(); //Close the file  
    return(1);
  }
  return(0);
}






/**************************************************************************/
/**************************************************************************/
// GENERAL ConfigURATION

void InitConfigData( void )
{
    __DEBUG_FCT__();

 // HT_Home
  strcpy( g_general_Config.ModuleName, "WT32");

  // HT_conf
  g_general_Config.Description[0] = 0;

    // HT Wifi 
  g_general_Config.WIFIID[0] = 0;
  g_general_Config.WIFIPWD[0] = 0;
  strcpy( g_general_Config.WIFIIP, "0.0.0.0") ;
  strcpy( g_general_Config.WIFIGW, "0.0.0.0") ;

}

void ForceNetworkReset( void )
{
  g_general_Config.WIFIID[0] = 0;
  g_general_Config.WIFIPWD[0] = 0;
  strcpy( g_general_Config.WIFIIP, "0.0.0.0") ;
  strcpy( g_general_Config.WIFIGW, "0.0.0.0") ;
}



short LoadConfigData( void )
{
String label;
char Message[16];  
    __DEBUG_FCT__();
  InitConfigData();
   
  if (!INI_SPIFF_Load(GENERAL_CONFIG_FILE)) 
  {
    g_SerialDebug.print("Ini file ");
    g_SerialDebug.print(GENERAL_CONFIG_FILE);
    g_SerialDebug.println(" does not exist");
    return(0);
  }

// HT_Home
  INI_getValue("[HOME]", "ModuleName", g_general_Config.ModuleName, NAME_SIZE-1);

  // HT_conf
  INI_getValue("[CONFIG]", "Description", g_general_Config.Description, MESSAGE_SIZE-1);


  INI_getValue("[WIFI]", "ID", g_general_Config.WIFIID, MESSAGE_SIZE-1);
  INI_getValue("[WIFI]", "PWD", g_general_Config.WIFIPWD, MESSAGE_SIZE-1);
  INI_getValue("[WIFI]", "IP", g_general_Config.WIFIIP, MESSAGE_SIZE-1);
  INI_getValue("[WIFI]", "GW", g_general_Config.WIFIGW, MESSAGE_SIZE-1);

   

  return(1);
}


short SaveConfigData( void )
{
String label;  
    __DEBUG_FCT__();

 // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  SPIFFS.remove(GENERAL_CONFIG_FILE);
  
  File dataFile = SPIFFS.open(GENERAL_CONFIG_FILE, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) 
  {
  // HT_Home
    dataFile.println("[HOME]");
    dataFile.print("ModuleName=");
    dataFile.println(g_general_Config.ModuleName);


     
    // HT_conf
    dataFile.println("[CONFIG]");
    dataFile.print("Description=");
    dataFile.println(g_general_Config.Description);
    
    dataFile.println("[WIFI]");
    dataFile.print("ID=");
    dataFile.println(g_general_Config.WIFIID);
    dataFile.print("PWD=");
    dataFile.println(g_general_Config.WIFIPWD);
    dataFile.print("IP=");
    dataFile.println(g_general_Config.WIFIIP);
    dataFile.print("GW=");
    dataFile.println(g_general_Config.WIFIGW);

 
    
    dataFile.close();

    g_SerialDebug.print("Saving Ini file ");
    g_SerialDebug.print(GENERAL_CONFIG_FILE);
    g_SerialDebug.println(" DONE");
   
    return(1);
  }

  g_SerialDebug.print("Saving Ini file ");
  g_SerialDebug.print(GENERAL_CONFIG_FILE);
  g_SerialDebug.println(" ERROR");

  return(0);
}
