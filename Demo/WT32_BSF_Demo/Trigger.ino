void displayTime( void )
{
int y, mo, d, h, m, s, res, v;

    g_tft.fillRect( 0, 270, g_screenWidth, g_screenHeight - 270, TFT_BLACK);

    // Get RTC info
    _RTC_GetCurrent(&y, &mo, &d, &h, &m, &s );
    MessageBuffer = (char)(h / 10 + '0');
    MessageBuffer = MessageBuffer + (char)(h % 10 + '0');
    MessageBuffer = MessageBuffer + ":";
    MessageBuffer = MessageBuffer + (char)(m / 10 + '0');
    MessageBuffer = MessageBuffer + (char)(m % 10 + '0');
    MessageBuffer = MessageBuffer + ":";
    MessageBuffer = MessageBuffer + (char)(s / 10 + '0');
    MessageBuffer = MessageBuffer + (char)(s % 10 + '0');
    
    g_SerialDebug.print("Time : ");
    g_SerialDebug.println( MessageBuffer.c_str() );
  
    g_tft.setTextColor(TFT_YELLOW,TFT_BLACK);
    g_tft.drawString("Time", 100, 300 );
    g_tft.drawString(MessageBuffer.c_str(), 100, 350 );
  
}

void displaybattery( void )
{
    g_tft.fillRect( 0, 270, g_screenWidth, g_screenHeight - 270, TFT_BLACK);
    BPVal = analogRead(PIN_BATTERY);
    g_SerialDebug.print("Battery : ");
    g_SerialDebug.println( BPVal );
        
    MessageBuffer = (int)(BPVal);
    g_tft.setTextColor(TFT_YELLOW,TFT_BLACK);
    g_tft.drawString("Battery Value:", 100, 300 );
    g_tft.drawString(MessageBuffer.c_str(), 100, 350 );
  
}

void displayPicture( void )
{
    g_tft.fillRect( 0, 270, g_screenWidth, g_screenHeight - 270, TFT_BLACK);
  drawSdJpeg("/logo.jpg", 0, 270);     
  
}

void playSound( void )
{
    g_tft.fillRect( 0, 270, g_screenWidth, g_screenHeight - 270, TFT_BLACK);
    g_tft.setTextColor(TFT_YELLOW,TFT_BLACK);
    g_tft.drawString("Play Sound", 100, 300 );
    _MCP_Play( 220, 0 , 200000 ); 

  
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
