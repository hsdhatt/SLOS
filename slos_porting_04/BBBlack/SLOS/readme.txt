
<base>SLOS

  <base> SLOS is a version of the SLOS operating system that does not use 
  hadrware assisted memory management.

Processor Supported

 This version of SLOS supports the TI AM3355x SoC
 Tested on BeagleBone Black Rev A5C

Board Supported

  BeagleBone Black Rev A5C

Host Platform

  Ubuntu - 12.04

Build Process

  To build SLOS you need the arm-none-eabi- toolchain.
   
  1. cd obj/

  2. make CROSS_COMPILE=arm-none-eabi-

  If there are no errors the binary image is placed into build/image 
  directory and is given the name app. app can then be copied to the sdcard
  along with MLO and executed on a beaglebone black rev a5c. The MLO file is
  a bootloader file which will copy the binary called "app" and place it at
  RAM address 0x80000000.







 
