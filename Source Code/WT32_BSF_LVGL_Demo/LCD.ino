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

/*** Display callback to flush the buffer to screen ***/
#ifdef __USE_LVGL__

  void _LCD_Setup( void )
  {
    __DEBUG_FCT__();
        
    g_tft.init();
 
    lv_tick_inc(10);
    lv_init();  // Initialize lvgl
    // Setup tick hook for lv_tick_task
//    esp_err_t err = esp_register_freertos_tick_hook((esp_freertos_tick_cb_t)lv_tick_task); 
  
    // Setting display to landscape
     g_tft.setRotation(__ORIENTATION__);
  
    /* LVGL : Setting up buffer to use for display */
    lv_disp_draw_buf_init(&g_draw_buf, g_buf, NULL, g_screenWidth * 10);
  
    /*** LVGL : Setup & Initialize the display device driver ***/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
//    disp_drv.hor_res = g_screenHeight;
//    disp_drv.ver_res = g_screenWidth;
    if( __ORIENTATION__ )
    {
      disp_drv.hor_res = g_screenHeight;
      disp_drv.ver_res = g_screenWidth;
    }
    else
    {
      disp_drv.hor_res = g_screenWidth;
      disp_drv.ver_res = g_screenHeight;
    }

    
    disp_drv.flush_cb = display_flush;
    disp_drv.draw_buf = &g_draw_buf;
    lv_disp_drv_register(&disp_drv);
  
    /*** LVGL : Setup & Initialize the input device driver ***/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    lv_indev_t *pt = lv_indev_drv_register(&indev_drv);
    if(pt == NULL)
    {
      Serial.println("Couldn't start touchscreen registration");
    }
 
    // Screen Object
    g_screenMain = lv_obj_create(NULL);
        // Screen load
    lv_scr_load(g_screenMain);

  }



  void display_flush(lv_disp_drv_t * disp, const lv_area_t *area, lv_color_t *color_p)
  {
    __DEBUG_FCT__();
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
  
    g_tft.startWrite();
    g_tft.setAddrWindow(area->x1, area->y1, w, h);
    g_tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    g_tft.endWrite();
  
    lv_disp_flush_ready(disp);
  }

  
#else

  void _LCD_Setup( void )
  {
    __DEBUG_FCT__();
    g_tft.init();
    g_tft.setRotation(0);
    g_tft.fillScreen(TFT_BLACK); 
    digitalWrite(TFT_BL, 128);
  }


  
#endif
