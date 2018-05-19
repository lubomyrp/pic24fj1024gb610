================================================================
microSD Click Demo for the Explorer 16/32
================================================================

Overview
----------------------------------------------------------------
This demo shows how to use the microSD click board on the 
Explorer 16/32.  MPLAB(R) Code Configurator(MCC) is used to 
configure the processor, pins, and peripherals.

NOTE: a micro-SD card and card reader are not provided with the
microSD click board.  These will need to be purchased 
separately.


Hardware Configuration
----------------------------------------------------------------
1) Plug the microSD Click into mikroBUS(tm) A.
2) Plug the target processor module into the Explorer 16/32.
3) Refer to the hardware.txt file attached to the project for 
   more information about any processor specific limitations or
   configuration required.

This demo uses the following mikroBUS pins:
* AN
* CS
* SCK
* MOSI
* MISO

For more information about the bus mapping for this specific
processor, please refer to the hardware.txt file packaged with 
this example.


Running the Demo
----------------------------------------------------------------
Once programmed, the demo will prompt on the LCD for a SD card:

+----------------+
|Insert card in  |
|mikroBus A      |
+----------------+

Check the hardware.txt file for information about the LCD if 
nothing shows up on the display.  Some processor modules may not
support the LCD and may output the text elsewhere.

Once the card is inserted, the code will write a file named 
"HELLO.TXT" with the text "Hello World!!" in it.  While it is 
writing the LCD will have the following message:

+----------------+
|Card found.     |
|Writing file.   |
+----------------+

While this message is on the screen, do not remove the drive.
Doing so may corrupt the file system on the card resulting in
a loss of data.

The write may only take a fraction of a second so the message
above may only flash on the screen for a brief moment.  If you
don't see this message before the write complete message, the
write operation just completed very quickly.

Once the write is complete, the following message will appear
and it is now safe to remove the drive:

+----------------+
|Write complete. |
|Remove card.    |
+----------------+

At this point of time you can remove the SD card from the 
microSD click board and plug it into a card reader attached to
a computer to verify that the new "HELLO.TXT" file now exists
with the correct data.


References/Links
----------------------------------------------------------------
[1] http://www.mikroe.com/click/microsd/
[2] http://www.microchip.com/mplab/mplab-code-configurator

Legal
----------------------------------------------------------------
mikroBUS(tm) a trademark of MikroElectronika.
MPLAB(R) is a registered trademark of Microchip Technology Inc.