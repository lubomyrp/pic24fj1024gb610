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

#include "mikrobus_a.h"
#include "mcc_generated_files/mcc.h"

inline void MIKROBUS_A_PWM_SetHigh(void)
{
    LATDbits.LATD0 = 1;
}

inline void MIKROBUS_A_PWM_SetLow(void)
{
    LATDbits.LATD0 = 0;
}

inline void MIKROBUS_A_CS_SetHigh(void)
{
    LATGbits.LATG9 = 1;
}

inline void MIKROBUS_A_CS_SetLow(void)
{
    LATGbits.LATG9 = 0;
}