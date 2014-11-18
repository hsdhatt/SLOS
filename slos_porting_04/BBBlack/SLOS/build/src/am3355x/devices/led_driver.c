/*
 *  ____________________________________________________________________
 * 
 *  Copyright (c) 2002, Andrew N. Sloss, Chris Wright and Dominic Symes
 *  All rights reserved.
 *  ____________________________________________________________________
 * 
 *  NON-COMMERCIAL USE License
 *  
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met: 
 *  
 *  1. For NON-COMMERCIAL USE only.
 * 
 *  2. Redistributions of source code must retain the above copyright 
 *     notice, this list of conditions and the following disclaimer. 
 * 
 *  3. Redistributions in binary form must reproduce the above 
 *     copyright notice, this list of conditions and the following 
 *     disclaimer in the documentation and/or other materials provided 
 *     with the distribution. 
 * 
 *  4. All advertising materials mentioning features or use of this 
 *     software must display the following acknowledgement:
 * 
 *     This product includes software developed by Andrew N. Sloss,
 *     Chris Wright and Dominic Symes. 
 * 
 *   THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY 
 *   EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 *   PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE 
 *   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
 *   OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 *   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
 *   OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
 *   TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *   OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 *   OF SUCH DAMAGE. 
 * 
 *  If you have questions about this license or would like a different
 *  license please email :
 * 
 * 	andrew@sloss.net
 * 
 * 
 */
 
/*****************************************************************************
 * Simple Little Operating System - SLOS
 *****************************************************************************/

/*****************************************************************************
 *
 * Module      : led_driver.c
 * Description : device driver for led on the e7t
 * OS          : SLOS 0.09
 * Platform    : e7t
 * History     :
 *
 * 19th November 2001 Andrew N. Sloss
 * - started working on an example device driver
 *
 * December 2nd 2001 Andrew N. Sloss
 * - added uid generator to the LED driver
 *
 *****************************************************************************/

/*****************************************************************************
 * IMPORT
 *****************************************************************************/

#include "../../devices/ddf_frame.h"
#include "led_driver.h"
#include "../headers/reg.h"

/*****************************************************************************
 * MACROS
 *****************************************************************************/

#define ACCESS_VALUE     0x5AA8
#define LEDPORT    	 0x08000008
#define LEDBANK    	 __REG8(LEDPORT)		

/* -- set */

/*****************************************************************************
 * DATATYPES
 *****************************************************************************/

typedef struct 
{
unsigned char led; 
unsigned char uid;
} internal_ledstr;

/*****************************************************************************
 * STATICS
 *****************************************************************************/

typedef unsigned int uint32_t;



internal_ledstr		diodes[2];

/* -- led_init ----------------------------------------------------------------
 *
 * Description : initalize the LED device driver internal 
 *               data structures and hardware. Set all the
 *               LED's to be zero.
 * 
 * Parameters  : none...
 * Return      : none...
 * Notes       : none...
 *
 */

static inline void setbits_le32(const void* addr, uint32_t pattern)
{
        uint32_t register_value = *(volatile uint32_t *) addr;
        register_value = register_value | pattern;
        *(volatile uint32_t *)addr = register_value;
}

static inline void clrbits_le32(const void* addr, uint32_t pattern)
{
        uint32_t register_value = *(volatile uint32_t *) addr;
        register_value = register_value & ~pattern;
        *(volatile uint32_t *)addr = register_value;
}

void led_init(void) 
{
	/* Set clock for GPIO1 */

#if 0
	__REG(CM_PER_GPIO1_CLKCTRL)	= ((0x2 << 0) | (1 << 18));

	/* Clear the IRQ status for GPIO1 */

	setbits_le32((uint32_t *)(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_CLR), 0xf << LED0);
	setbits_le32((uint32_t *)(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_CLR), 0xf << LED1);

	/* Enable the output pin */

	clrbits_le32((uint32_t *)(SOC_GPIO_1_REGS + GPIO_OE), 0xf << LED0);
	clrbits_le32((uint32_t *)(SOC_GPIO_1_REGS + GPIO_OE), 0xf << LED1);
#endif
	/* switch of led 1*/
                        clrbits_le32((uint32_t *)(SOC_GPIO_1_REGS + GPIO_DATAOUT), 0x1 << LED1);
                clrbits_le32((uint32_t *)(0x4804c000 + 0x13c), 0x1 << 23);

//	setbits_le32((uint32_t *)(SOC_GPIO_1_REGS + GPIO_DATAOUT), LED_PATTERN << LED1);
/* initialize internal data structure ............. */

diodes[0].led = OFF;
diodes[1].led = OFF;
diodes[0].uid = NONE;
diodes[1].uid = NONE;

}

/* -- led_open ----------------------------------------------------------------
 *
 * Description : example open on the LED 
 * 
 * Parameters  : unsigned major = 55075 
 *             : unsigned minor = (0=LED0,1=LED1,2=LED2,3=LED3,...,7=LED7)
 * Return      : UID -
 * Notes       : 
 *
 */

UID led_open(unsigned int major,unsigned int minor) 
{

//  if (major==DEVICE_LED_BBBLACK)
//			setbits_le32((uint32_t *)(SOC_GPIO_1_REGS + GPIO_DATAOUT), LED_PATTERN << 24);
	//else
	//		setbits_le32((uint32_t *)(SOC_GPIO_1_REGS + GPIO_DATAOUT), LED_PATTERN << 21);
	
  if (major==DEVICE_LED_BBBLACK)
  {
    if (minor < 2) 
    {
      if (diodes[0].uid==NONE)
      {
      diodes[0].uid = uid_generate();
      diodes[1].uid = diodes[0].uid ;
      return diodes[0].uid;      /* unique ID */
      }
      else
      {
      return diodes[1].uid;
      }
    } 
    else
    {
    return DEVICE_UNKNOWN;	
    }
 }

return DEVICE_NEXT;
}

/* -- led_close ---------------------------------------------------------------
 *
 * Description : example open on the LED 
 * 
 * Parameters  : UID id 
 * Return      : 
 *
 *   DEVICE_SUCCESS - successfully close the device
 *   DEVICE_UNKNOWN - couldn't identify the UID
 *
 * Notes       : 
 *
 */

int led_close(UID id) 
{
    if (diodes[0].uid==id) 
    {
    diodes[0].uid = NONE;
    return DEVICE_SUCCESS;
    }
return DEVICE_UNKNOWN;
}

/* -- led_write_bit -----------------------------------------------------------
 *
 * Description : write a particular bit to an LED 
 * 
 * Parameters  : UID id = 55075 + unit (0..7)
 *	     	: BYTE led_set - least significant bit is used
 * Return	     : none...
 *
 * Notes       : an example of a led write bit
 *
 */

void led_write_byte(UID id,BYTE led_set) 
{
	unsigned int _led_set; 
	if (led_set == 'a')
		_led_set = 0;
	if (led_set == 'b')
		_led_set = 1;
if ((diodes[_led_set].uid==id)&&(diodes[_led_set].uid!=NONE)) {

	if (_led_set == 0 ){
		 /* Change the Led by clearing the corresponding bit in GPIO_DATAOUT */

//			clrbits_le32((uint32_t *)(SOC_GPIO_1_REGS + GPIO_DATAOUT), LED_PATTERN << LED0);
#if 1
		if (diodes[0].led == ON){ 
			clrbits_le32((uint32_t *)(SOC_GPIO_1_REGS + GPIO_DATAOUT), LED_PATTERN << LED0);
			diodes[0].led = OFF;
		}
		else {
			setbits_le32((uint32_t *)(SOC_GPIO_1_REGS + GPIO_DATAOUT), LED_PATTERN << LED0);
			diodes[0].led = ON;
		}
#endif

	} else if (_led_set  == 1 ){
    //                    setbits_le32((uint32_t *)(SOC_GPIO_1_REGS + GPIO_DATAOUT), LED_PATTERN << LED0);


		   /* Change the Led by clearing the corresponding bit in GPIO_DATAOUT */
#if 1   
             if (diodes[1].led == ON){
                        clrbits_le32((uint32_t *)(SOC_GPIO_1_REGS + GPIO_DATAOUT), LED_PATTERN << LED1);
                        diodes[1].led = OFF;
                }
                else {
                        setbits_le32((uint32_t *)(SOC_GPIO_1_REGS + GPIO_DATAOUT), LED_PATTERN << LED1);
                        diodes[1].led = ON;
                }
#endif
	}
	
}

}

/* -- led_read_bit ------------------------------------------------------------
 *
 * Description : read a particular bit value 
 * 
 * Parameters  : UID id = 55075 + unit (0..3)
 * Return      : value return error if 255
 *
 * Notes       : an example of a led read bit
 */

BYTE led_read_byte(UID id) 
{
    if ((diodes[0].uid==id)&&(diodes[0].uid!=NONE)) 
      return diodes[0].led;
/* 
 * error correction goes here...
 */

return 255;
}

