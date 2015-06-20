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
 * Modules      : ddf_types.h
 * Description  : Device Driver Types
 * OS           : SLOS 0.09
 * Platform     : e7t
 * History      :
 *
 * 15 July 2002 Andrew N. Sloss
 * - added the header information
 *
 *****************************************************************************/

#ifndef _DEVICE_DDF_BBBLACK_TYPES

#define _DEVICE_DDF_BBBLACK_TYPES 1

#define DEVICE_LED_BBBLACK		55075   /* range 55075 - 55082 ....... */ 
#define DEVICE_SERIAL_BBBLACK	55090   /* range 55090 - 55091 ....... */
#define DEVICE_CACHE_BBBLACK	55092   /* range 55090 - 55091 ....... */


/* cache device definitions */

#define READ_CACHE_TYPE		0x1
#define READ_CACHE_LEVEL_ID	0x2
#define READ_CACHE_SIZE_ID	0x3
#define ID_MASK			0x3
#define SELECT_L2_CACHE		0x2
#define SELECT_L1_ICACHE	0x1
#define SELECT_L1_DCACHE	0x0
#define CACHE_SIZE_SELECT_MASK	0x3
#define CACHE_SIZE_SELECT_SHIFT	0x2

#endif
