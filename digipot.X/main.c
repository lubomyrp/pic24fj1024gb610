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

#include <stdbool.h>

#include "mcc_generated_files/mcc.h"
#include "click_digipot.h"
#include "buttons.h"
#include "button_mapping.h"

#define STEPS_PER_PRESS     3

int main(void)
{            
    bool button_increment_pressed = false;
    bool button_decrement_pressed = false;
    bool button_wiper_reset_pressed = false;
    
    SYSTEM_Initialize();
    
    /* Please refer to button_mapping.h to determine how the buttons
     * are mapped in this demo.  Due to hardware conflicts and pin mapping on the
     * various processor modules, this may be different on different processor
     * modules. 
     */
    BUTTON_Enable(BUTTON_WIPER_RESET);
    BUTTON_Enable(BUTTON_INCREMENT);
    BUTTON_Enable(BUTTON_DECREMENT);
    
    while(1)
    {
        /* Check for any button presses.   Only take action once until button is
         * released. Only take one action in the below priority. */
        if( (BUTTON_IsPressed(BUTTON_WIPER_RESET) == true) && (button_wiper_reset_pressed == false) )
        {
            button_wiper_reset_pressed = true;
            CLICK_DIGIPOT_WiperSet(CLICK_DIGIPOT_WIPER_MAX/2);
        }
        else if( (BUTTON_IsPressed(BUTTON_INCREMENT) == true) && (button_increment_pressed == false) )
        {
            button_increment_pressed = true;
            CLICK_DIGIPOT_WiperIncrement(STEPS_PER_PRESS);
        }
        else if( (BUTTON_IsPressed(BUTTON_DECREMENT) == true) && (button_decrement_pressed == false) )
        {
            button_decrement_pressed = true;
            CLICK_DIGIPOT_WiperDecrement(STEPS_PER_PRESS);
        }
            
        
        /* check for release of button to re-enable the associated action. */
        if(BUTTON_IsPressed(BUTTON_WIPER_RESET) == false)
        {
            button_wiper_reset_pressed = false;
        }
        
        if(BUTTON_IsPressed(BUTTON_INCREMENT) == false)
        {
            button_increment_pressed = false;
        }
        
        if(BUTTON_IsPressed(BUTTON_DECREMENT) == false)
        {
            button_decrement_pressed = false;
        }
        
    }
    
    return 0;
}
