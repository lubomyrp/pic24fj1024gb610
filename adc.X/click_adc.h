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

#ifndef CLICK_ADC_H
#define CLICK_ADC_H

#include <stdint.h>

typedef enum
{
    CLICK_ADC_CHANNEL_0 = (0<<6),
    CLICK_ADC_CHANNEL_1 = (1<<6),
    CLICK_ADC_CHANNEL_2 = (2<<6),
    CLICK_ADC_CHANNEL_3 = (3<<6),
} CLICK_ADC_CHANNEL;

void CLICK_ADC_ChannelSelect(CLICK_ADC_CHANNEL channel);
uint16_t CLICK_ADC_ConversionResultGet(void);

#endif

