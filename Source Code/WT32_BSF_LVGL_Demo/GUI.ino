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

#ifdef __USE_LVGL__
  /* Counter button event handler */
  static void counter_event_handler(lv_event_t * e)
  {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED)
    {
      static uint8_t cnt = 0;
      cnt++;
  
      /*Get the first child of the button which is the label and change its text*/
      lv_obj_t *label = lv_obj_get_child(btn, 0);
      lv_label_set_text_fmt(label, "Button: %d", cnt);
      LV_LOG_USER("Clicked");
      Serial.println("Clicked");
    }
  }
  
  /* Toggle button event handler */
  static void toggle_event_handler(lv_event_t * e)
  {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
      LV_LOG_USER("Toggled");
      Serial.println("Toggled");
    }
  }
  
  void lv_button_demo(void)
  {
    lv_obj_t *label;
  
    // Button with counter
    lv_obj_t *btn1 = lv_btn_create(g_screenMain);
    lv_obj_add_event_cb(btn1, counter_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(btn1, 100, 100);   /*Set its position*/
    lv_obj_set_size(btn1, 120, 50);   /*Set its size*/
    label = lv_label_create(btn1);
    lv_label_set_text(label, "Button");
    lv_obj_center(label);
  
  
    // Toggle button
    lv_obj_t *btn2 = lv_btn_create(g_screenMain);
    lv_obj_add_event_cb(btn2, toggle_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_pos(btn2, 250, 100);   /*Set its position*/
    lv_obj_set_size(btn2, 120, 50);   /*Set its size*/
    label = lv_label_create(btn2);
    lv_label_set_text(label, "Toggle Button");
    lv_obj_center(label);
  }

#else

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
