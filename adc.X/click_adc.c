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
#include <stdint.h>
#include <stdbool.h>

#include "click_adc.h"
#include "mikrobus_a.h"

#define MCP3204_START_BIT       (1<<2)
#define MCP3204_SINGLE_ENDED    (1<<1)
#define MCP3204_DIFFERENTIAL    (0<<1)
#define MCP3204_D2              (0<<0)

static CLICK_ADC_CHANNEL currentChannel;

void CLICK_ADC_ChannelSelect(CLICK_ADC_CHANNEL channel)
{   
#ifdef CLICK_ADC_SAFE
    switch(currentChannel)
    {
        case CLICK_ADC_CHANNEL_0:
        case CLICK_ADC_CHANNEL_1:
        case CLICK_ADC_CHANNEL_3:
        case CLICK_ADC_CHANNEL_4:
            break;
        default:
            return;
    }
#endif
    
    currentChannel = channel;
}

uint16_t CLICK_ADC_ConversionResultGet(void)
{ 
    uint16_t result = 0;
    
#ifdef CLICK_ADC_SAFE
    switch(currentChannel)
    {
        case CLICK_ADC_CHANNEL_0:
        case CLICK_ADC_CHANNEL_1:
        case CLICK_ADC_CHANNEL_3:
        case CLICK_ADC_CHANNEL_4:
            break;
        default:
            return UINT16_MAX;
    }
#endif
    
    MIKROBUS_A_CS_SetLow();
    
    MIKROBUS_A_SPI_Exchange8bit(MCP3204_START_BIT | MCP3204_SINGLE_ENDED | MCP3204_D2);                  
    result = MIKROBUS_A_SPI_Exchange8bit(currentChannel) & 0x0F;   
    result = result << 8;                           
    result = result | MIKROBUS_A_SPI_Exchange8bit(0);                                              
    
    MIKROBUS_A_CS_SetHigh();
    
    return result;
  

}