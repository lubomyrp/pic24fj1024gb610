/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

#include <xc.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "mcc_generated_files/mcc.h"
#include "click_gps.h"

#include "lcd.h"
#include "buttons.h"
#include "button_mapping.h"

static void LocationDataReady(double latitude, double longitude);
static void TimeDataReady(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t milliseconds);

int main(void)
{        
    SYSTEM_Initialize();

    /* Please refer to button_mapping.h to determine how the buttons
     * are mapped in this demo.  Due to hardware conflicts and pin mapping on the
     * various processor modules, this may be different on different processor
     * modules. 
     */
    BUTTON_Enable(BUTTON_PRINT_TIME);
    
    CLICK_GPS_Initialize();
    
    CLICK_GPS_AddLocationListener(&LocationDataReady);
    CLICK_GPS_AddTimeListener(&TimeDataReady);
    
    LCD_Initialize();
       
    printf("\fWaiting for GPS\r\ndata...\r\n");
    
    while(1)
    {
        CLICK_GPS_Tasks();      
    }
    
    return 0;
}

static void LocationDataReady(double latitude, double longitude)
{
    if(BUTTON_IsPressed(BUTTON_PRINT_TIME) == false)
    {
        printf("\fLat:%12.5f\r\nLong:%11.5f\r\n", latitude, longitude);
    }
}

static void TimeDataReady(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t milliseconds)
{
    if(BUTTON_IsPressed(BUTTON_PRINT_TIME) == true)
    {
        printf("\fTime (UTC):\r\n%02i:%02i:%02i\r\n", hours, minutes, seconds);
    }
}

