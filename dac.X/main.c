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

#include "mcc_generated_files/mcc.h"
#include "click_dac.h"

int main(void)
{   
    uint16_t output = 0;
      
    SYSTEM_Initialize();
    
    while(1)
    {
        CLICK_DAC_OutputSet(output++);
        
        if(CLICK_DAC_MAX_OUTPUT < output)
        {
            output = 0;
        }
    }
    
    return 0;
}