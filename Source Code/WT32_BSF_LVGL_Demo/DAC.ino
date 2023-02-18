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
//
//    FILE: MCP4725_wave_generator.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo function generators
//    DATE: 2021-01-07
//     URL: https://github.com/RobTillaart/FunctionGenerator
//
//  depending on the platform, the range of "smooth" sinus is limited.
//  other signals are less difficult so have a slightly larger range.
//
//  PLATFORM     SINUS    SQUARE  SAWTOOTH  TRIANGLE
//  UNO          -100 Hz
//  ESP32        -200 Hz  -1000   -250      -100
//


#ifdef __MANAGE_DAC__



// LOOKUP TABLE SINE
uint16_t sine[360];


int _MCP_setup(void)
{

  // fill table
  for (int i = 0; i < 361; i++)
  {
    sine[i] = 2047 + round(2047 * sin(i * PI / 180));
  }

  // ESP32
  // Wire.setClock(3400000);
  //Wire.setClock(800000);

  if (g_MCP.begin() == false)
  {
    return(0);
  }
  
  g_MCP.setValue(0);
  if (!g_MCP.isConnected())
  {
    return(0);
  }

  return(1);
}



void _MCP_Play( int freq, int mode, long duration )
{
uint32_t   period = 0;
uint32_t   halvePeriod = 0;
uint32_t lastTime = 0;
uint32_t EndTime = 0;

  period = 1e6 / freq;
  halvePeriod = period / 2;

  EndTime = micros() + duration;

  Serial.println("Start DAC");

  while (1)
  {
    yield();
    uint32_t now = micros();


    if(now > EndTime)
    {
      g_MCP.setValue(0);
      Serial.println("End DAC");
      return;
    }

    uint32_t t = now % period;

    switch (mode)
    {
      case 0:
        if (t < halvePeriod ) g_MCP.setValue(4095);
        else g_MCP.setValue(0);
        break;
      case 1:
        g_MCP.setValue(t * 4095 / period );
        break;
     
      case 2:
        int idx = (360 * t) / period;
        g_MCP.setValue(sine[idx]);  // lookuptable
        break;
    }
  }
}

#endif
