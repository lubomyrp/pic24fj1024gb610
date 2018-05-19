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

#include <stdio.h>
#include <stdint.h>

#include "mcc_generated_files/mcc.h"
#include "click_adc.h"
#include "lcd.h"

int main(void)
{   
    uint16_t channel_0, channel_1, channel_2, channel_3;
      
    SYSTEM_Initialize();
    
    LCD_Initialize();
       
    while(1)
    {
        CLICK_ADC_ChannelSelect(CLICK_ADC_CHANNEL_0);
        channel_0 = CLICK_ADC_ConversionResultGet();
        
        CLICK_ADC_ChannelSelect(CLICK_ADC_CHANNEL_1);
        channel_1 = CLICK_ADC_ConversionResultGet();
        
        CLICK_ADC_ChannelSelect(CLICK_ADC_CHANNEL_2);
        channel_2 = CLICK_ADC_ConversionResultGet();
        
        CLICK_ADC_ChannelSelect(CLICK_ADC_CHANNEL_3);
        channel_3 = CLICK_ADC_ConversionResultGet();
        
        printf("0: %4u  1: %4u\r\n2: %4u  3: %4u\r\n", channel_0, channel_1, channel_2, channel_3);
    }
    
    return 0;
}