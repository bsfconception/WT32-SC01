#ifdef __MANAGE_LCD__

#define NB_BTN  5

#define BTN_RAY  4


Button HomePage[NB_BTN] = {
   { "Time", 5,10,150,70 },
   { "Battery", 165,10,150,70 },
   { "Picture", 5,90,150,70 },
   { "Sound", 165,90,150,70 },
   { "Sleep", 85,180,150,70 },
   };


void Menu1_DrawGUI( void )
{
int x, y, w, h;
int i, j;

  g_tft.fillScreen(TFT_BLACK);

  g_tft.setTextColor(TFT_WHITE,TFT_BLACK);  
  g_tft.setTextSize(2);

  
  
//  g_tft.setBackColor(0,0,0 );
  
  for(i=0;i<NB_BTN;i++)
  {

    x = HomePage[i].x;
    y = HomePage[i].y;
    w = HomePage[i].w;
    h = HomePage[i].h;

    g_tft.fillRoundRect( x, y, w, h, BTN_RAY, TFT_BLUE );
    g_tft.drawRoundRect( x, y, w, h, BTN_RAY, TFT_DARKGREY );
      
    x = x + (w/2) - g_tft.textWidth(HomePage[i].Name) / 2;
    y = y + (h/2) - g_tft.fontHeight()/2;

    g_tft.setTextColor(TFT_YELLOW,TFT_BLUE);
    g_tft.drawString(HomePage[i].Name, x, y );
  }

}

void Menu1_PushGUI( int index, int mode )
{
int x, y, w, h;

  x = HomePage[index].x;
  y = HomePage[index].y;
  w = HomePage[index].w;
  h = HomePage[index].h;
  
  if(mode)
  {
    g_tft.drawRoundRect( x, y, w, h, BTN_RAY, TFT_RED );
  }
  else
  {
    g_tft.drawRoundRect( x, y, w, h , BTN_RAY, TFT_BLUE );
  }
  
  
}


int Menu1_GetButton( int x, int y )
{
int i;

  for(i=0;i<NB_BTN;i++)
  {
    if( (HomePage[i].x < x) &&
        ((HomePage[i].x + HomePage[i].w) > x) &&
        (HomePage[i].y < y) &&
        ((HomePage[i].y + HomePage[i].h) > y) )
        return(i);
    
  }
  return(-1);
}

#endif
