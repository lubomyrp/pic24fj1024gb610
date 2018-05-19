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

#include "click_digipot.h"
#include "mikrobus_a.h"

#define MCP4161_COMMAND_READ        (0b11)
#define MCP4161_COMMAND_WRITE       (0b00)
#define MCP4161_COMMAND_INCREMENT   (0b01)
#define MCP4161_COMMAND_DECREMENT   (0b10)

#define MCP4161_ADDRESS_WIPER0      (0b0000)

void CLICK_DIGIPOT_WiperSet(uint16_t value)
{   
    uint8_t command;
    
    if(value <= CLICK_DIGIPOT_WIPER_MAX)
    {
        MIKROBUS_A_CS_SetLow();
        
        command = (uint8_t)((MCP4161_ADDRESS_WIPER0<<4) | (MCP4161_COMMAND_WRITE<<2) | (value>>8));
        MIKROBUS_A_SPI_Exchange8bit(command);
        
        command = (uint8_t)(value & 0x00FF);
        MIKROBUS_A_SPI_Exchange8bit(command);
        
        MIKROBUS_A_CS_SetHigh();
    }
}

void CLICK_DIGIPOT_WiperIncrement(uint16_t steps)
{
    uint8_t command;
    
    if(steps > CLICK_DIGIPOT_WIPER_MAX)
    {
        steps = CLICK_DIGIPOT_WIPER_MAX;
    }
    
    MIKROBUS_A_CS_SetLow();
    
    while(steps--)
    {
        command = (uint8_t)((MCP4161_ADDRESS_WIPER0<<4)|(MCP4161_COMMAND_INCREMENT<<2));
        MIKROBUS_A_SPI_Exchange8bit(command);
    }
    
    MIKROBUS_A_CS_SetHigh();
}

void CLICK_DIGIPOT_WiperDecrement(uint16_t steps)
{
    uint8_t command;
    
    if(steps > CLICK_DIGIPOT_WIPER_MAX)
    {
        steps = CLICK_DIGIPOT_WIPER_MAX;
    }
    
    MIKROBUS_A_CS_SetLow();
    
    while(steps--)
    {
        command = (uint8_t)((MCP4161_ADDRESS_WIPER0<<4)|(MCP4161_COMMAND_DECREMENT<<2));
        MIKROBUS_A_SPI_Exchange8bit(command);
    }
    
    MIKROBUS_A_CS_SetHigh();
}