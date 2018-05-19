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
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "click_gps.h"
#include "mikrobus_a.h"

#ifndef CLICK_GPS_LOCATION_LISTENER_COUNT
#define CLICK_GPS_LOCATION_LISTENER_COUNT 1
#endif

#if (CLICK_GPS_LOCATION_LISTENER_COUNT>UINT8_MAX)
#error "This code is written with the assumption there will be fewer than UINT8_MAX listeners at any point of time."
#endif

#ifndef CLICK_GPS_TIME_LISTENER_COUNT
#define CLICK_GPS_TIME_LISTENER_COUNT 1
#endif

#if (CLICK_GPS_TIME_LISTENER_COUNT>UINT8_MAX)
#error "This code is written with the assumption there will be fewer than UINT8_MAX listeners at any point of time."
#endif

static CLICK_GSP_TimeListener_t time_listeners[CLICK_GPS_TIME_LISTENER_COUNT] = {0};
static CLICK_GSP_LocationListener_t location_listeners[CLICK_GPS_LOCATION_LISTENER_COUNT] = {0};

static void sendLocationNotifications(double longitude, double latitude);
static void sendTimeNotifications(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t milliseconds);

static char uartBuffer[300];

void CLICK_GPS_Initialize(void)
{
  
}

void CLICK_GPS_Tasks(void)
{   
    double longitude;
    double latitude;
    uint8_t hours, minutes, seconds;
    uint16_t milliseconds;
    
    uint16_t i = 0;
    char* data;
    char* terminator;
    char conversionString[8];
    
    for(i=0; i<sizeof(uartBuffer)-1; i++)
    {
        while(MIKROBUS_A_UART_ReceiveBufferIsEmpty() == true) {}
        uartBuffer[i] = (char)MIKROBUS_A_UART_Read();
    }
    
    /* make sure that there is a null terminator at the end of the UART string.
     */
    uartBuffer[sizeof(uartBuffer)-1] = '\0';

    data = strstr(uartBuffer, "$GPGLL");   
    if(data == NULL)
    {
        return;
    }
    
    terminator = strstr(data,",");
    if(terminator == NULL)
    {
        return;
    }
    
    /* If the first byte of the latitude field is ',', there is no latitude
     * info because the GPS doesn't have a lock yet. */
    if(data[7] == ',')
    {
        return;
    }
    
    data = terminator+1;
    terminator = strstr(data,",");
    if(terminator == NULL)
    {
        return;
    }
    memset(conversionString,0,sizeof(conversionString));
    memcpy(conversionString, data, 2);
    latitude = atof(conversionString);
    
    data += 2;
    *terminator = '\0';
    latitude += (atof(data)/60);
    
    data = terminator+1;
    terminator = strstr(data,",");
    if(terminator == NULL)
    {
        return;
    }
    if(*data == 'S')
    {
        latitude *= -1;
    }

    data = terminator+1;
    terminator = strstr(data,",");
    if(terminator == NULL)
    {
        return;
    }
    memset(conversionString,0,sizeof(conversionString));
    memcpy(conversionString, data, 3);
    longitude = atof(conversionString);
    
    data += 3;
    *terminator = '\0';
    longitude += (atof(data)/60);
    
    data = terminator+1;
    terminator = strstr(data,",");
    if(terminator == NULL)
    {
        return;
    }
    if(*data == 'W')
    {
        longitude *= -1;
    }
    
    sendLocationNotifications(latitude, longitude);
    
    data = terminator+1;
    terminator = strstr(data,",");
    if(terminator == NULL)
    {
        return;
    }
    memset(conversionString,0,sizeof(conversionString));
    memcpy(conversionString, data, 2);
    hours = atoi(conversionString);
    data += 2;

    memset(conversionString,0,sizeof(conversionString));
    memcpy(conversionString, data, 2);
    minutes = atoi(conversionString);
    data += 2;

    memset(conversionString,0,sizeof(conversionString));
    memcpy(conversionString, data, 2);
    seconds = atoi(conversionString);
    data += 2;
    data += 1;  /* For the '.' */
    
    *terminator = '\0';
    milliseconds = atoi(data)/60;
    
    sendTimeNotifications(hours, minutes, seconds, milliseconds);
}

static void sendLocationNotifications(double latitude, double longitude)
{
    uint8_t i;
    
    for(i=0; i<CLICK_GPS_LOCATION_LISTENER_COUNT; i++)
    {
        if(location_listeners[i] != NULL)
        {
            location_listeners[i](latitude, longitude);
        }
    }    
}

bool CLICK_GPS_AddLocationListener(CLICK_GSP_LocationListener_t listener)
{
    uint8_t i;

    for(i=0; i<CLICK_GPS_LOCATION_LISTENER_COUNT; i++)
    {
        if(location_listeners[i] == listener)
        {
            return true;
        }
    } 

    for(i=0; i<CLICK_GPS_LOCATION_LISTENER_COUNT; i++)
    {
        if(location_listeners[i] == NULL)
        {
            location_listeners[i] = listener;
            return true;
        }
    }
    
    return false;
}

void CLICK_GPS_RemoveLocationListener(CLICK_GSP_LocationListener_t listener)
{
    uint8_t i;
    for(i=0; i<CLICK_GPS_LOCATION_LISTENER_COUNT; i++)
    {
        if(location_listeners[i] == listener)
        {
            location_listeners[i] = NULL;
        }
    } 
}

static void sendTimeNotifications(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t milliseconds)
{
    uint8_t i;
    
    for(i=0; i<CLICK_GPS_TIME_LISTENER_COUNT; i++)
    {
        if(time_listeners[i] != NULL)
        {
            time_listeners[i](hours, minutes, seconds, milliseconds);
        }
    }    
}

bool CLICK_GPS_AddTimeListener(CLICK_GSP_TimeListener_t listener)
{
    uint8_t i;

    for(i=0; i<CLICK_GPS_TIME_LISTENER_COUNT; i++)
    {
        if(time_listeners[i] == listener)
        {
            return true;
        }
    } 

    for(i=0; i<CLICK_GPS_TIME_LISTENER_COUNT; i++)
    {
        if(time_listeners[i] == NULL)
        {
            time_listeners[i] = listener;
            return true;
        }
    }
    
    return false;
}

void CLICK_GPS_RemoveTimeListener(CLICK_GSP_TimeListener_t listener)
{
    uint8_t i;
    for(i=0; i<CLICK_GPS_TIME_LISTENER_COUNT; i++)
    {
        if(time_listeners[i] == listener)
        {
            time_listeners[i] = NULL;
        }
    } 
}