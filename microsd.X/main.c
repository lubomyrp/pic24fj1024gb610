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
#include <string.h>
#include <stdio.h>

#include "fileio.h"
#include "system.h"
#include "sd_spi.h"
#include "lcd.h"

// GetTimestamp will be called by the FILEIO library when it needs a timestamp for a file
void GetTimestamp (FILEIO_TIMESTAMP * timeStamp);


extern FILEIO_SD_DRIVE_CONFIG mikroBusA;
extern FILEIO_SD_DRIVE_CONFIG mikroBusB;

// The gSDDrive structure allows the user to specify which set of driver functions should be used by the
// FILEIO library to interface to the drive.
// This structure must be maintained as long as the user wishes to access the specified drive.
const FILEIO_DRIVE_CONFIG gSdDrive =
{
    (FILEIO_DRIVER_IOInitialize)FILEIO_SD_IOInitialize,                      // Function to initialize the I/O pins used by the driver.
    (FILEIO_DRIVER_MediaDetect)FILEIO_SD_MediaDetect,                       // Function to detect that the media is inserted.
    (FILEIO_DRIVER_MediaInitialize)FILEIO_SD_MediaInitialize,               // Function to initialize the media.
    (FILEIO_DRIVER_MediaDeinitialize)FILEIO_SD_MediaDeinitialize,           // Function to de-initialize the media.
    (FILEIO_DRIVER_SectorRead)FILEIO_SD_SectorRead,                         // Function to read a sector from the media.
    (FILEIO_DRIVER_SectorWrite)FILEIO_SD_SectorWrite,                       // Function to write a sector to the media.
    (FILEIO_DRIVER_WriteProtectStateGet)FILEIO_SD_WriteProtectStateGet,     // Function to determine if the media is write-protected.
};

// Declare a state machine for our device
typedef enum
{
    DEMO_STATE_NO_MEDIA = 0,
    DEMO_STATE_MEDIA_DETECTED,
    DEMO_STATE_DRIVE_MOUNTED,
    DEMO_STATE_DONE,
    DEMO_STATE_FAILED
} DEMO_STATE;

// Some sample data to write to the file
uint8_t sampleData[] = "Hello World!!\r\n";
char readBuffer[36];
size_t dataRead;

#define MESSAGE_INSERT_CARD         "\fInsert card in\r\nmikroBus A"
#define MESSAGE_CARD_FOUND          "\fCard found.\r\nWriting file.\r\n"
#define MESSAGE_WRITE_COMPLETE      "\fWrite complete.\r\nRemove card.\r\n"

// Main loop.
// This demo program implements a simple data logger.
int main (void)
{
    DEMO_STATE demoState = DEMO_STATE_NO_MEDIA;
    FILEIO_OBJECT file;

    SYSTEM_Initialize();
    LCD_Initialize();

    // Initialize the library
    if (!FILEIO_Initialize())
    {
        while(1);
    }

    // Register the GetTimestamp function as the timestamp source for the library.
    FILEIO_RegisterTimestampGet (GetTimestamp);

    printf(MESSAGE_INSERT_CARD);
    
    while(1)
    {
        switch (demoState)
        {
            case DEMO_STATE_NO_MEDIA:
                // Loop on this function until the SD Card is detected.
                if (FILEIO_MediaDetect(&gSdDrive, &mikroBusA) == true)
                {                   
                    demoState = DEMO_STATE_MEDIA_DETECTED;
                    break;
                }
                
                break;
                
            case DEMO_STATE_MEDIA_DETECTED:
                // Try to mount the drive we've defined in the gSdDrive structure.
                // If mounted successfully, this drive will use the drive Id 'A'
                // Since this is the first drive we're mounting in this application, this
                // drives root directory will also become the current working directory
                // for our library.               
                if (FILEIO_DriveMount('A', &gSdDrive, &mikroBusA) == FILEIO_ERROR_NONE)
                {
                    demoState = DEMO_STATE_DRIVE_MOUNTED;
                }
                else
                {
                    demoState = DEMO_STATE_NO_MEDIA;
                }
                break;
                
            case DEMO_STATE_DRIVE_MOUNTED:
                printf(MESSAGE_CARD_FOUND);
                
                // Specifying CREATE will create the file is it doesn't exist.
                // Specifying APPEND will set the current read/write location to the end of the file.
                // Specifying WRITE will allow you to write to the code.
                if (FILEIO_Open (&file, "HELLO.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_APPEND | FILEIO_OPEN_CREATE) == FILEIO_RESULT_FAILURE)
                {
                    demoState = DEMO_STATE_FAILED;
                    break;
                }

                // Write some sample data to the card
                if (FILEIO_Write (sampleData, 1, sizeof(sampleData)-1, &file) != (sizeof(sampleData)-1))
                {
                    demoState = DEMO_STATE_FAILED;
                    break;
                }

                // Close the file to save the data
                if (FILEIO_Close (&file) != FILEIO_RESULT_SUCCESS)
                {
                    demoState = DEMO_STATE_FAILED;
                    break;
                }

                printf(MESSAGE_WRITE_COMPLETE);
                
                // We're done with this drive.
                // Unmount it.
                FILEIO_DriveUnmount ('A');
                demoState = DEMO_STATE_DONE;
                break;
                
            case DEMO_STATE_DONE:
                // Now that we've written all of the data we need to write in the application, wait for the user
                // to remove the card
                if (FILEIO_MediaDetect(&gSdDrive, &mikroBusA) == false)
                {
                    printf(MESSAGE_INSERT_CARD);
                    demoState = DEMO_STATE_NO_MEDIA;
                }
                break;
                
            case DEMO_STATE_FAILED:
                printf(MESSAGE_INSERT_CARD);
                
                // An operation has failed.  Try to unmount the drive.  This will also try to
                // close all open files that use this drive (it will at least deallocate them).
                FILEIO_DriveUnmount ('A');
                // Return to the media-detect state
                demoState = DEMO_STATE_NO_MEDIA;
                break;
        }
    }
}

void GetTimestamp (FILEIO_TIMESTAMP * timeStamp)
{
    timeStamp->timeMs = 0;
    timeStamp->time.bitfield.hours = 1;
    timeStamp->time.bitfield.minutes = 1;
    timeStamp->time.bitfield.secondsDiv2 = 0 / 2;

    timeStamp->date.bitfield.day = 1;
    timeStamp->date.bitfield.month = 1;
    
    timeStamp->date.bitfield.year = 36;
}

