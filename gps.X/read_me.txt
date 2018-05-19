================================================================
GPS Click Demo for the Explorer 16/32
================================================================

Overview
----------------------------------------------------------------
This demo shows how to use the GPS click board on the Explorer
16/32.  MPLAB(R) Code Configurator(MCC) is used to configure 
the processor, pins, and peripherals.

NOTE: A GPS antenna may be required for this demo and is not
included in the GPS click board box.  At the bottom of the GPS
click board page there is a link to purchage a GPS antenna right
below the link to purchase the click board.

Hardware Configuration
----------------------------------------------------------------
1) Plug the GPS Click into mikroBUS(tm) slot.  For most processors
   this will be in slot A.  If there is a mikrobus_a.c file in the
   project, plug the board into slot A.  If there is a
   mikrobus_b.c file, plug it into slot B.
2) Plug the target processor module into the Explorer 16/32.
3) Refer to the hardware.txt file attached to the project for 
   more information about any processor specific limitations or
   configuration required.

NOTE: You may need to connect an antenna to the GPS click
board for it to effectively get a signal or to speed up the
rate at which it locks.  If the demo appears to be taking a 
long time to connect, make sure you have an antenna connected
and it is placed in a location where it can receive a signal.

This demo uses the following mikroBUS pins:
* RX
* RST

For more information about the bus mapping for this specific
processor, please refer to the hardware.txt file packaged with 
this example.


Running the Demo
----------------------------------------------------------------
This demo will wait for the GPS module to receive valid data
from the satellite system.  While it is waiting for that
connection, the LCD will have the following message:

+----------------+
|Waiting for GPS |
|data...         |
+----------------+

It may take a few minutes for the GSP to lock on the location.
Once the GPS module gets a valid location/time, it will callback
into the main code via the registered LocationListener function.

The location data will look like the following:

+----------------+
|Lat:   -83.61004|
|Long:   34.62890|
+----------------+

By holding a button on the Explorer 16, the display will be
switched to the time information received from the GPS.  The
screen will only updated on the next reception of new data.  The
time display will be in UTC and will look like the following:

+----------------+
|Time (UTC):     |
|17:50:23        |
+----------------+

Please refer to the button_mapping.h file to find which button
to hold for this feature.  For most processor modules this will
be the S3 button.  Due to pin conflicts on some processor modules
it is not possible to use S3 and another switch may be in use.
If BUTTON_NONE is selected, then this feature is not available
and only the GPS data is possible.

References/Links
----------------------------------------------------------------
[1] http://www.mikroe.com/click/gps/
[2] http://www.microchip.com/mplab/mplab-code-configurator

Legal
----------------------------------------------------------------
mikroBUS(tm) a trademark of MikroElectronika.
MPLAB(R) is a registered trademark of Microchip Technology Inc.