/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// EPWM1 -> myEPWM0 Pinmux
//
//
// EPWM1_A - GPIO Settings
//
#define GPIO_PIN_EPWM1_A 0
#define myEPWM0_EPWMA_GPIO 0
#define myEPWM0_EPWMA_PIN_CONFIG GPIO_0_EPWM1_A
//
// EPWM1_B - GPIO Settings
//
#define GPIO_PIN_EPWM1_B 1
#define myEPWM0_EPWMB_GPIO 1
#define myEPWM0_EPWMB_PIN_CONFIG GPIO_1_EPWM1_B

//
// EPWM2 -> myEPWM1 Pinmux
//
//
// EPWM2_A - GPIO Settings
//
#define GPIO_PIN_EPWM2_A 2
#define myEPWM1_EPWMA_GPIO 2
#define myEPWM1_EPWMA_PIN_CONFIG GPIO_2_EPWM2_A
//
// EPWM2_B - GPIO Settings
//
#define GPIO_PIN_EPWM2_B 3
#define myEPWM1_EPWMB_GPIO 3
#define myEPWM1_EPWMB_PIN_CONFIG GPIO_3_EPWM2_B
//
// GPIO62 - GPIO Settings
//
#define OUT_IR_GPIO_PIN_CONFIG GPIO_62_GPIO62
//
// GPIO40 - GPIO Settings
//
#define OUT_TRIG_GPIO_PIN_CONFIG GPIO_40_GPIO40
//
// GPIO31 - GPIO Settings
//
#define LED1_GPIO_PIN_CONFIG GPIO_31_GPIO31
//
// GPIO34 - GPIO Settings
//
#define LED2_GPIO_PIN_CONFIG GPIO_34_GPIO34

//
// SCIA -> mySCIA Pinmux
//
//
// SCIA_RX - GPIO Settings
//
#define GPIO_PIN_SCIA_RX 28
#define mySCIA_SCIRX_GPIO 28
#define mySCIA_SCIRX_PIN_CONFIG GPIO_28_SCIA_RX
//
// SCIA_TX - GPIO Settings
//
#define GPIO_PIN_SCIA_TX 29
#define mySCIA_SCITX_GPIO 29
#define mySCIA_SCITX_PIN_CONFIG GPIO_29_SCIA_TX

//*****************************************************************************
//
// ECAP Configurations
//
//*****************************************************************************
#define ECAP_ECHO_BASE ECAP1_BASE
#define ECAP_ECHO_SIGNAL_MUNIT_BASE ECAP1SIGNALMONITORING_BASE
void ECAP_ECHO_init();

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
#define myEPWM0_BASE EPWM1_BASE
#define myEPWM0_TBPRD 46874
#define myEPWM0_COUNTER_MODE EPWM_COUNTER_MODE_STOP_FREEZE
#define myEPWM0_TBPHS 0
#define myEPWM0_CMPA 11718
#define myEPWM0_CMPB 23437
#define myEPWM0_CMPC 0
#define myEPWM0_CMPD 0
#define myEPWM0_DBRED 0
#define myEPWM0_DBFED 0
#define myEPWM0_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM0_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM0_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define myEPWM1_BASE EPWM2_BASE
#define myEPWM1_TBPRD 46874
#define myEPWM1_COUNTER_MODE EPWM_COUNTER_MODE_STOP_FREEZE
#define myEPWM1_TBPHS 0
#define myEPWM1_CMPA 23437
#define myEPWM1_CMPB 35155
#define myEPWM1_CMPC 0
#define myEPWM1_CMPD 0
#define myEPWM1_DBRED 0
#define myEPWM1_DBFED 0
#define myEPWM1_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM1_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM1_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define OUT_IR 62
void OUT_IR_init();
#define OUT_TRIG 40
void OUT_TRIG_init();
#define LED1 31
void LED1_init();
#define LED2 34
void LED2_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_ECAP_ECHO
#define INT_ECAP_ECHO INT_ECAP1
#define INT_ECAP_ECHO_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP4
extern __interrupt void INT_ECAP_ECHO_ISR(void);

//*****************************************************************************
//
// SCI Configurations
//
//*****************************************************************************
#define mySCIA_BASE SCIA_BASE
#define mySCIA_BAUDRATE 9600
#define mySCIA_CONFIG_WLEN SCI_CONFIG_WLEN_8
#define mySCIA_CONFIG_STOP SCI_CONFIG_STOP_ONE
#define mySCIA_CONFIG_PAR SCI_CONFIG_PAR_NONE
#define mySCIA_FIFO_TX_LVL SCI_FIFO_TX0
#define mySCIA_FIFO_RX_LVL SCI_FIFO_RX0
void mySCIA_init();

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	ECAP_init();
void	EPWM_init();
void	GPIO_init();
void	INTERRUPT_init();
void	SCI_init();
void	SYNC_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
