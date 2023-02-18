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

void displayTime( void )
{
int y, mo, d, h, m, s, res, v;

#ifdef __MANAGE_RTC__

    g_tft.fillRect( 0, 270, g_screenWidth, g_screenHeight - 270, TFT_BLACK);

    // Get RTC info
    _RTC_GetCurrent(&y, &mo, &d, &h, &m, &s );
    g_MessageBuffer = (char)(h / 10 + '0');
    g_MessageBuffer = g_MessageBuffer + (char)(h % 10 + '0');
    g_MessageBuffer = g_MessageBuffer + ":";
    g_MessageBuffer = g_MessageBuffer + (char)(m / 10 + '0');
    g_MessageBuffer = g_MessageBuffer + (char)(m % 10 + '0');
    g_MessageBuffer = g_MessageBuffer + ":";
    g_MessageBuffer = g_MessageBuffer + (char)(s / 10 + '0');
    g_MessageBuffer = g_MessageBuffer + (char)(s % 10 + '0');
    
    g_SerialDebug.print("Time : ");
    g_SerialDebug.println( g_MessageBuffer.c_str() );
  
    g_tft.setTextColor(TFT_YELLOW,TFT_BLACK);
    g_tft.drawString("Time", 100, 300 );
    g_tft.drawString(g_MessageBuffer.c_str(), 100, 350 );
#endif  
}

void displaybattery( void )
{
    g_tft.fillRect( 0, 270, g_screenWidth, g_screenHeight - 270, TFT_BLACK);
    BPVal = analogRead(PIN_BATTERY);
    g_SerialDebug.print("Battery : ");
    g_SerialDebug.println( BPVal );
        
    g_MessageBuffer = (int)(BPVal);
    g_tft.setTextColor(TFT_YELLOW,TFT_BLACK);
    g_tft.drawString("Battery Value:", 100, 300 );
    g_tft.drawString(g_MessageBuffer.c_str(), 100, 350 );
  
}

void displayPicture( void )
{
    g_tft.fillRect( 0, 270, g_screenWidth, g_screenHeight - 270, TFT_BLACK);
  drawSdJpeg("/logo.jpg", 0, 270);     
  
}

void playSound( void )
{
#ifdef __MANAGE_DAC__
  
    g_tft.fillRect( 0, 270, g_screenWidth, g_screenHeight - 270, TFT_BLACK);
    g_tft.setTextColor(TFT_YELLOW,TFT_BLACK);
    g_tft.drawString("Play Sound", 100, 300 );
    _MCP_Play( 220, 0 , 200000 ); 

#endif  
}

void enterSleep( void )
{
    g_tft.fillRect( 0, 270, g_screenWidth, g_screenHeight - 270, TFT_BLACK);

    g_tft.setTextColor(TFT_YELLOW,TFT_BLACK);
    g_tft.drawString("Light Sleep", 100, 300 );

    g_SerialDebug.println("Configure Light Sleep Mode");
    gpio_wakeup_enable(GPIO_WAKE, GPIO_INTR_HIGH_LEVEL);  
    
    digitalWrite(TFT_BL, 0);
    esp_sleep_enable_gpio_wakeup();

    g_SerialDebug.println("Enter Light Sleep Mode");
    esp_light_sleep_start();

    g_SerialDebug.println("Leaving Light Sleep Mode");
    gpio_wakeup_disable(GPIO_WAKE);
    digitalWrite(TFT_BL, 128);
}
