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

#ifdef __MANAGE_RTC__

int _RTC_Init( void )
{
  #ifdef __DEBUG__
    g_SerialDebug.println("RTC : init");
  #endif
  g_rtc.begin(); // initialize RTC
  if (! g_rtc.begin()) 
  {
  #ifdef __DEBUG__
      g_SerialDebug.println("RTC Issue");
    #endif
    return(0);  
  }  
  
  #ifdef __DEBUG__
    g_SerialDebug.println("RTC OK");
  #endif
  
  g_rtc.adjust(DateTime(__DATE__, __TIME__));
  
  return(1);  
}

void _RTC_Adjust( int y, int mo, int d, int h, int m, int s )
{
int cy, cmo, cd, ch, cm, cs;

  _RTC_GetCurrent( &cy, &cmo, &cd, &ch, &cm, &cs );

  if( y >= 0 )
    cy = y;
    
  if( mo >= 0 )
    cmo = mo;
    
  if( d >= 0 )
    cd = d;
    
  if( h >= 0 )
    ch = h;
    
  if( m >= 0 )
    cm = m;
    
  if( s >= 0 )
    cs = s;

  g_rtc.adjust(DateTime(cy, cmo, cd, ch, cm, cs));
}

void _RTC_GetCurrent( int *y, int *mo, int *d, int *h, int *m, int *s )
{
  
  g_curDateTime = g_rtc.now();
  if( h != NULL)
    *h = g_curDateTime.hour();
    
  if( m != NULL)
    *m = g_curDateTime.minute();
    
  if( s != NULL)
    *s = g_curDateTime.second();
    
  if( y != NULL)
    *y = g_curDateTime.year();
    
  if( mo != NULL)
    *mo = g_curDateTime.month();
    
  if( d != NULL)
    *d = g_curDateTime.day();
}

#endif
