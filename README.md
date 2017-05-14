TM4C-MSC-bootloader
===================

A mass storage bootloader for the Stellaris/Tiva Launchpad and other Texas Instruments LM4F/TM4C chips.

It is inspired by, and similar in use to, the bootloader found on some NXP LPC chips.

It appears as a regular external drive (formatted with FAT12) when plugged into a PC, no drivers or custom software needed!

It takes up 16kB of flash memory.

Bootloader is entered when SW1 and SW2 button is pressed during reset.

REMEMBER TO EDIT YOUR PROGRAM'S LINKER SCRIPT TO START THE CODE AT ADDRESS 0x6000

This software is still experimental, please report any issues!

INSTALLATION:

* Put the source in a directory inside stellarisware/boards/ek-lm4f120xl/ or tivaware/examples/boards/ek-tm4c123gxl/
* Run make
* Flash gcc/boot_usb_msc.bin onto your Launchpad or other Stellaris/Tiva board

HOW TO USE:

* Edit the linker script of the firmware you want to flash using the bootloader, so that the code starts at address 0x6000.

  Usually it means you have to find this in projectname.ld:
    ```
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x00040000
    ```
  and change it to:
    ```
    FLASH (rx) : ORIGIN = 0x00006000, LENGTH = 0x0003A000
    ```
  then rebuild your project

* Plug in your board while holding down SW1 and SW2, or press the reset button while holding SW1 and SW2, the system should recognize it as a 512kB mass storage device. The Blue LED will blink when the bootloader is running.

* You can download the firmware.bin found on the drive to download the contents of flash memory.

* You can upload your firmware to the board by copying your firmware to the device (the first file you put on the device will be considered new firmware).

* Safely eject the drive and should jump to your code immediately.

KNOWN ISSUES:

* On Linux, ejecting the drive will show an error, but that doesn't break anything
