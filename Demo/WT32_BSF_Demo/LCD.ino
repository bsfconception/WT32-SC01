#ifdef __MANAGE_LCD__

void _LCD_Setup( void )
{
  g_tft.init();
  g_tft.setRotation(0);
  g_tft.fillScreen(TFT_BLACK); 
  g_screenWidth = g_tft.width();
  g_screenHeight = g_tft.height();


  digitalWrite(TFT_BL, 128);
  
}

void _LCD_DisplayStartMessage( void )
{
  // Set "cursor" at top left corner of display (0,0) and select font 4
  g_tft.setCursor(0, 0, 4);
  // Set the font colour to be white with a black background
  g_tft.setTextColor(TFT_WHITE, TFT_BLACK);
  // We can now plot text on screen using the "print" class
  g_tft.println("Initialised\n");
}
#endif
