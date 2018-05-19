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

#ifndef CLICK_GPS_H
#define CLICK_GPS_H

#include <stdbool.h>
#include <stdint.h>

typedef void (*CLICK_GSP_LocationListener_t)(double latitude, double longitude);
typedef void (*CLICK_GSP_TimeListener_t)(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t milliseconds);

bool CLICK_GPS_AddLocationListener(CLICK_GSP_LocationListener_t listener);
bool CLICK_GPS_AddTimeListener(CLICK_GSP_TimeListener_t listener);

void CLICK_GPS_Initialize(void);

void CLICK_GPS_RemoveLocationListener(CLICK_GSP_LocationListener_t listener);
void CLICK_GPS_RemoveTimeListener(CLICK_GSP_TimeListener_t listener);

void CLICK_GPS_Tasks(void);

#endif
