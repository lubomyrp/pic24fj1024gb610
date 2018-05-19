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

#include "mcc_generated_files/mcc.h"
#include "buttons.h"
#include "click_relay.h"

#include "button_mapping.h"

int main(void)
{        
    SYSTEM_Initialize();
    
    /* Please refer to button_mapping.h to determine how the buttons
     * are mapped in this demo.  Due to hardware conflicts and pin mapping on the
     * various processor modules, this may be different on different processor
     * modules. 
     */
    BUTTON_Enable(BUTTON_RELAY_1);
    BUTTON_Enable(BUTTON_RELAY_2);
    
    while(1)
    {
        if(BUTTON_IsPressed(BUTTON_RELAY_1) == true)
        {
            CLICK_RELAY_Relay1Close();
        }
        else
        {
            CLICK_RELAY_Relay1Open();
        }
        
        if(BUTTON_IsPressed(BUTTON_RELAY_2) == true)
        {
            CLICK_RELAY_Relay2Close();
        }
        else
        {
            CLICK_RELAY_Relay2Open();
        }    
    }
    
    return 0;
}