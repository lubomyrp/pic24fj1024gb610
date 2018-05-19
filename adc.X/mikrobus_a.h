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

#ifndef MIKROBUS_A_H
#define MIKROBUS_A_H

#include <stdbool.h>
#include <stdint.h>

void MIKROBUS_A_CS_SetHigh(void);
void MIKROBUS_A_CS_SetLow(void);

uint8_t MIKROBUS_A_SPI_Exchange8bit(uint8_t data);

#endif
