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

#include "click_dac.h"
#include "mikrobus_a.h"

#define MCP4921_SHUTDOWN_MASK               (1<<12)
#define MCP4921_SHUTDOWN_ACTIVE_MODE        (1<<12)
#define MCP4921_SHUTDOWN_INACTIVE_MODE      (0<<12)

#define MCP4921_GAIN_MASK                   (1<<13)
#define MCP4921_GAIN_1X                     (1<<13)
#define MCP4921_GAIN_2X                     (0<<13)

#define MCP4921_BUFFER_CONTROL_MASK         (1<<14)
#define MCP4921_BUFFER_CONTROL_BUFFERED     (1<<14)
#define MCP4921_BUFFER_CONTROL_UNBUFFERED   (0<<14)

#define MCP4921_DAC_INPUT_MASK              (0x0FFF)

void CLICK_DAC_OutputSet(uint16_t value)
{   
    if(value <= CLICK_DAC_MAX_OUTPUT)
    {
        uint8_t toWrite;
        
        MIKROBUS_A_CS_SetLow();

        value |= (MCP4921_GAIN_1X | MCP4921_SHUTDOWN_ACTIVE_MODE | MCP4921_BUFFER_CONTROL_UNBUFFERED);
        
        toWrite = (uint8_t)(value >> 8);
        MIKROBUS_A_SPI_Exchange8bit(toWrite);

        toWrite = (uint8_t) (value & 0x00FF);
        MIKROBUS_A_SPI_Exchange8bit(toWrite);

        MIKROBUS_A_CS_SetHigh();
    }
}

void CLICK_DAC_Shutdown()
{
    uint8_t toWrite;
    
    MIKROBUS_A_CS_SetLow();

    toWrite = (MCP4921_SHUTDOWN_INACTIVE_MODE >> 8);
    MIKROBUS_A_SPI_Exchange8bit(toWrite);

    toWrite = 0;
    MIKROBUS_A_SPI_Exchange8bit(toWrite);

    MIKROBUS_A_CS_SetHigh();    
}