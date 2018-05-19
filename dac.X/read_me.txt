================================================================
DAC Click Demo for the Explorer 16/32
================================================================

Overview
----------------------------------------------------------------
This demo shows how to use the DAC click board on the Explorer
16/32.  MPLAB(R) Code Configurator(MCC) is used to configure 
the processor, pins, and peripherals.


Hardware Configuration
----------------------------------------------------------------
1) Plug the DAC Click into mikroBUS(tm) A.
2) Plug the target processor module into the Explorer 16/32.
3) Refer to the hardware.txt file attached to the project for 
   more information about any processor specific limitations or
   configuration required.

This demo uses the following mikroBUS pins:
* CS
* SCK
* MOSI

For more information about the bus mapping for this specific
processor, please refer to the hardware.txt file packaged with 
this example.


Running the Demo
----------------------------------------------------------------
This demo simply increments the DAC output a few steps at a time
until it reaches the maximum output value and then resets back
down to 0.  This will create a saw wave on the DAC output.  Take
an oscilloscope and connect it to the GND and VOUT pins of the
DAC click board to view the output waveform.


References/Links
----------------------------------------------------------------
[1] http://www.mikroe.com/click/dac/
[2] http://www.microchip.com/mplab/mplab-code-configurator

Legal
----------------------------------------------------------------
mikroBUS(tm) a trademark of MikroElectronika.
MPLAB(R) is a registered trademark of Microchip Technology Inc.