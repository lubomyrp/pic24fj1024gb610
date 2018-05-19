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

#include "system_config.h"
#include "system.h"
#include <xc.h>
#include <stdbool.h>
#include "sd_spi.h"

/** CONFIGURATION Bits **********************************************/
// FSEC
#pragma config BWRP = OFF    // Boot Segment Write-Protect bit->Boot Segment may be written
#pragma config BSS = DISABLED    // Boot Segment Code-Protect Level bits->No Protection (other than BWRP)
#pragma config BSEN = OFF    // Boot Segment Control bit->No Boot Segment
#pragma config GWRP = OFF    // General Segment Write-Protect bit->General Segment may be written
#pragma config GSS = DISABLED    // General Segment Code-Protect Level bits->No Protection (other than GWRP)
#pragma config CWRP = OFF    // Configuration Segment Write-Protect bit->Configuration Segment may be written
#pragma config CSS = DISABLED    // Configuration Segment Code-Protect Level bits->No Protection (other than CWRP)
#pragma config AIVTDIS = OFF    // Alternate Interrupt Vector Table bit->Disabled AIVT

// FOSCSEL
#pragma config FNOSC = PRIPLL    // Oscillator Source Selection->Primary Oscillator with PLL module (XT + PLL, HS + PLL, EC + PLL)
#pragma config PLLMODE = PLL96DIV2    // PLL Mode Selection->96 MHz PLL. (8 MHz input)
#pragma config IESO = ON    // Two-speed Oscillator Start-up Enable bit->Start up device with FRC, then switch to user-selected oscillator source

// FOSC
#pragma config POSCMD = XT    // Primary Oscillator Mode Select bits->XT Crystal Oscillator Mode
#pragma config OSCIOFCN = OFF    // OSC2 Pin Function bit->OSC2 is clock output
#pragma config SOSCSEL = ON    // SOSC Power Selection Configuration bits->SOSC is used in crystal (SOSCI/SOSCO) mode
#pragma config PLLSS = PLL_PRI    // PLL Secondary Selection Configuration bit->PLL is fed by the Primary oscillator
#pragma config IOL1WAY = ON    // Peripheral pin select configuration bit->Allow only one reconfiguration
#pragma config FCKSM = CSDCMD    // Clock Switching Mode bits->Both Clock switching and Fail-safe Clock Monitor are disabled

// FWDT
#pragma config WDTPS = PS32768    // Watchdog Timer Postscaler bits->1:32768
#pragma config FWPSA = PR128    // Watchdog Timer Prescaler bit->1:128
#pragma config FWDTEN = OFF    // Watchdog Timer Enable bits->WDT and SWDTEN disabled
#pragma config WINDIS = OFF    // Watchdog Timer Window Enable bit->Watchdog Timer in Non-Window mode
#pragma config WDTWIN = WIN25    // Watchdog Timer Window Select bits->WDT Window is 25% of WDT period
#pragma config WDTCMX = WDTCLK    // WDT MUX Source Select bits->WDT clock source is determined by the WDTCLK Configuration bits
#pragma config WDTCLK = LPRC    // WDT Clock Source Select bits->WDT uses LPRC

// FPOR
#pragma config BOREN = ON    // Brown Out Enable bit->Brown Out Enable Bit
#pragma config LPCFG = OFF    // Low power regulator control->No Retention Sleep
#pragma config DNVPEN = ENABLE    // Downside Voltage Protection Enable bit->Downside protection enabled using ZPBOR when BOR is inactive

// FICD
#pragma config ICS = PGD2    // ICD Communication Channel Select bits->Communicate on PGEC2 and PGED2
#pragma config JTAGEN = OFF    // JTAG Enable bit->JTAG is disabled
#pragma config BTSWP = OFF    // BOOTSWP Disable->BOOTSWP instruction disabled

// FDEVOPT1
#pragma config ALTCMPI = DISABLE    // Alternate Comparator Input Enable bit->C1INC, C2INC, and C3INC are on their standard pin locations
#pragma config TMPRPIN = OFF    // Tamper Pin Enable bit->TMPRN pin function is disabled
#pragma config SOSCHP = ON    // SOSC High Power Enable bit (valid only when SOSCSEL = 1->Enable SOSC high power mode (default)
#pragma config ALTVREF = ALTREFEN    // Alternate Voltage Reference Location Enable bit->VREF+ and CVREF+ on RA10, VREF- and CVREF- on RA9

// FBOOT
#pragma config BTMODE = SINGLE    // Boot Mode Configuration bits->Device is in Single Boot (legacy) mode

void SYSTEM_Initialize (void)
{
}


void MIKROBUS_A_SdSpiConfigurePins (void)
{
    RPOR9bits.RP19R = 0x0007;   //RG8->SPI1:SDO1;
    RPOR10bits.RP21R = 0x0008;   //RG6->SPI1:SCK1OUT;
    RPINR20bits.SDI1R = 0x001A;   //RG7->SPI1:SDI1;
    
    //Settings for microSD click board using mikroBUS Interface A
    //CS = P14_CSA = RG9 
    //CD = P25_ANA_USBOC = RB10
    LATGbits.LATG9 = 0;
    TRISGbits.TRISG9 = 0;
    TRISBbits.TRISB10 = 1;
    
    ANSBbits.ANSB10 = 0;
    ANSG = 0;
}

inline void MIKROBUS_A_SdSpiSetCs(uint8_t a)
{
    LATGbits.LATG9 = a;     //mikroBUS click on interface B
}

inline bool MIKROBUS_A_SdSpiGetCd(void)
{
    return (!PORTBbits.RB10) ? true : false;

}

inline bool MIKROBUS_A_SdSpiGetWp(void)
{
    return false;
}

// The sdCardMediaParameters structure defines user-implemented functions needed by the SD-SPI fileio driver.
// The driver will call these when necessary.  For the SD-SPI driver, the user must provide
// parameters/functions to define which SPI module to use, Set/Clear the chip select pin,
// get the status of the card detect and write protect pins, and configure the CS, CD, and WP
// pins as inputs/outputs (as appropriate).
// For this demo, these functions are implemented in system.c, since the functionality will change
// depending on which demo board/microcontroller you're using.
// This structure must be maintained as long as the user wishes to access the specified drive.
FILEIO_SD_DRIVE_CONFIG mikroBusA =
{
    1,                                  // Use SPI module 1
    MIKROBUS_A_SdSpiSetCs,                    // User-specified function to set/clear the Chip Select pin.
    MIKROBUS_A_SdSpiGetCd,                    // User-specified function to get the status of the Card Detect pin.
    MIKROBUS_A_SdSpiGetWp,                    // User-specified function to get the status of the Write Protect pin.
    MIKROBUS_A_SdSpiConfigurePins             // User-specified function to configure the pins' TRIS bits.
};




void MIKROBUS_B_SdSpiConfigurePins (void)
{
    RPINR22bits.SDI2R = 0x0017;   //RD2->SPI2:SDI2;
    RPOR7bits.RP15R = 0x000A;   //RF8->SPI2:SDO2;
    RPOR0bits.RP0R = 0x000B;   //RB0->SPI2:SCK2OUT;
    
    //Settings for microSD click board using mikroBUS Interface A
    //CS = P23_CSB = RB2 
    //CD = P24_ANB = RB1
    LATBbits.LATB2 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB1 = 1;
    
    ANSBbits.ANSB2 = 0;
    ANSBbits.ANSB1 = 0;
    ANSG = 0;
}

inline void MIKROBUS_B_SdSpiSetCs(uint8_t a)
{
    LATBbits.LATB2 = a;     //mikroBUS click on interface B
}

inline bool MIKROBUS_B_SdSpiGetCd(void)
{
    return (!PORTBbits.RB1) ? true : false;

}

inline bool MIKROBUS_B_SdSpiGetWp(void)
{
    return false;
}

// The sdCardMediaParameters structure defines user-implemented functions needed by the SD-SPI fileio driver.
// The driver will call these when necessary.  For the SD-SPI driver, the user must provide
// parameters/functions to define which SPI module to use, Set/Clear the chip select pin,
// get the status of the card detect and write protect pins, and configure the CS, CD, and WP
// pins as inputs/outputs (as appropriate).
// For this demo, these functions are implemented in system.c, since the functionality will change
// depending on which demo board/microcontroller you're using.
// This structure must be maintained as long as the user wishes to access the specified drive.
FILEIO_SD_DRIVE_CONFIG mikroBusB =
{
    2,                                  // Use SPI module 1
    MIKROBUS_B_SdSpiSetCs,                    // User-specified function to set/clear the Chip Select pin.
    MIKROBUS_B_SdSpiGetCd,                    // User-specified function to get the status of the Card Detect pin.
    MIKROBUS_B_SdSpiGetWp,                    // User-specified function to get the status of the Write Protect pin.
    MIKROBUS_B_SdSpiConfigurePins             // User-specified function to configure the pins' TRIS bits.
};