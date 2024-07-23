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

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules. 
// Call this function in your application if you wish to do all module 
// initialization.
// If you wish to not use some of the initializations, instead of the 
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
	EALLOW;

	PinMux_init();
	SYNC_init();
	ECAP_init();
	EPWM_init();
	GPIO_init();
	SCI_init();
	INTERRUPT_init();

	EDIS;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
	//
	// PinMux for modules assigned to CPU1
	//
	
	//
	// EPWM1 -> myEPWM0 Pinmux
	//
	GPIO_setPinConfig(myEPWM0_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM0_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM0_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(myEPWM0_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM0_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM0_EPWMB_GPIO, GPIO_QUAL_SYNC);

	//
	// EPWM2 -> myEPWM1 Pinmux
	//
	GPIO_setPinConfig(myEPWM1_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM1_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM1_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(myEPWM1_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM1_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM1_EPWMB_GPIO, GPIO_QUAL_SYNC);

	// GPIO62 -> OUT_IR Pinmux
	GPIO_setPinConfig(GPIO_62_GPIO62);
	// GPIO40 -> OUT_TRIG Pinmux
	GPIO_setPinConfig(GPIO_40_GPIO40);
	// GPIO31 -> LED1 Pinmux
	GPIO_setPinConfig(GPIO_31_GPIO31);
	// GPIO34 -> LED2 Pinmux
	GPIO_setPinConfig(GPIO_34_GPIO34);
	//
	// SCIA -> mySCIA Pinmux
	//
	GPIO_setPinConfig(mySCIA_SCIRX_PIN_CONFIG);
	// AGPIO -> GPIO mode selected
	GPIO_setAnalogMode(28, GPIO_ANALOG_DISABLED);
	GPIO_setPadConfig(mySCIA_SCIRX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(mySCIA_SCIRX_GPIO, GPIO_QUAL_ASYNC);

	GPIO_setPinConfig(mySCIA_SCITX_PIN_CONFIG);
	GPIO_setPadConfig(mySCIA_SCITX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(mySCIA_SCITX_GPIO, GPIO_QUAL_ASYNC);


}

//*****************************************************************************
//
// ECAP Configurations
//
//*****************************************************************************
void ECAP_init(){
	ECAP_ECHO_init();
}

void ECAP_ECHO_init(){
	//
	// Disable ,clear all capture flags and interrupts
	//
	ECAP_disableInterrupt(ECAP_ECHO_BASE,
		(ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
		ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
		ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
		ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
		ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
		ECAP_ISR_SOURCE_COUNTER_PERIOD   |
		ECAP_ISR_SOURCE_COUNTER_COMPARE));
	ECAP_clearInterrupt(ECAP_ECHO_BASE,
		(ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
		ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
		ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
		ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
		ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
		ECAP_ISR_SOURCE_COUNTER_PERIOD   |
		ECAP_ISR_SOURCE_COUNTER_COMPARE));
	//
	// Disables time stamp capture.
	//
	ECAP_disableTimeStampCapture(ECAP_ECHO_BASE);
	//
	// Stops Time stamp counter.
	//
	ECAP_stopCounter(ECAP_ECHO_BASE);
	//
	// Sets eCAP in Capture mode.
	//
	ECAP_enableCaptureMode(ECAP_ECHO_BASE);
	//
	// Sets the capture mode.
	//
	ECAP_setCaptureMode(ECAP_ECHO_BASE,ECAP_CONTINUOUS_CAPTURE_MODE,ECAP_EVENT_2);
	//
	// Sets the Capture event prescaler.
	//
	ECAP_setEventPrescaler(ECAP_ECHO_BASE, 0U);
	//
	// Sets the Capture event polarity.
	//
	ECAP_setEventPolarity(ECAP_ECHO_BASE,ECAP_EVENT_1,ECAP_EVNT_RISING_EDGE);
	ECAP_setEventPolarity(ECAP_ECHO_BASE,ECAP_EVENT_2,ECAP_EVNT_FALLING_EDGE);
	ECAP_setEventPolarity(ECAP_ECHO_BASE,ECAP_EVENT_3,ECAP_EVNT_RISING_EDGE);
	ECAP_setEventPolarity(ECAP_ECHO_BASE,ECAP_EVENT_4,ECAP_EVNT_RISING_EDGE);
	//
	// Configure counter reset on events
	//
	ECAP_enableCounterResetOnEvent(ECAP_ECHO_BASE,ECAP_EVENT_1);	
	ECAP_disableCounterResetOnEvent(ECAP_ECHO_BASE,ECAP_EVENT_2);
	ECAP_disableCounterResetOnEvent(ECAP_ECHO_BASE,ECAP_EVENT_3);
	ECAP_disableCounterResetOnEvent(ECAP_ECHO_BASE,ECAP_EVENT_4);
	//
	// Select eCAP input.
	//
	ECAP_selectECAPInput(ECAP_ECHO_BASE,ECAP_INPUT_GPIO22);
	//
	// Sets a phase shift value count.
	//
	ECAP_setPhaseShiftCount(ECAP_ECHO_BASE,0U);
	//
	// Disable counter loading with phase shift value.
	//
	ECAP_disableLoadCounter(ECAP_ECHO_BASE);
	//
	// Configures Sync out signal mode.
	//
	ECAP_setSyncOutMode(ECAP_ECHO_BASE,ECAP_SYNC_OUT_SYNCI);
	//
	// Configures emulation mode.
	//
	ECAP_setEmulationMode(ECAP_ECHO_BASE,ECAP_EMULATION_STOP);
	//
	// Set up the source for sync-in pulse..
	//
	ECAP_setSyncInPulseSource(ECAP_ECHO_BASE,ECAP_SYNC_IN_PULSE_SRC_DISABLE);
	//
	// Starts Time stamp counter for ECAP_ECHO.
	//
	ECAP_startCounter(ECAP_ECHO_BASE);
	//
	// Enables time stamp capture for ECAP_ECHO.
	//
	ECAP_enableTimeStampCapture(ECAP_ECHO_BASE);
	//
	// Re-arms the eCAP module for ECAP_ECHO.
	//
	ECAP_reArm(ECAP_ECHO_BASE);
	//
	// Enables interrupt source for ECAP_ECHO.
	//
	ECAP_enableInterrupt(ECAP_ECHO_BASE,(ECAP_ISR_SOURCE_CAPTURE_EVENT_2));

    //-----------------Signal Monitoring--------------------//
}

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
void EPWM_init(){
    EPWM_setClockPrescaler(myEPWM0_BASE, EPWM_CLOCK_DIVIDER_32, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(myEPWM0_BASE, 46874);	
    EPWM_setTimeBaseCounter(myEPWM0_BASE, 0);	
    EPWM_setTimeBaseCounterMode(myEPWM0_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);	
    EPWM_disablePhaseShiftLoad(myEPWM0_BASE);	
    EPWM_setPhaseShift(myEPWM0_BASE, 0);	
    EPWM_setCounterCompareValue(myEPWM0_BASE, EPWM_COUNTER_COMPARE_A, 11718);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM0_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(myEPWM0_BASE, EPWM_COUNTER_COMPARE_B, 23437);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM0_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(myEPWM0_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(myEPWM0_BASE);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(myEPWM0_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(myEPWM0_BASE);	
    EPWM_setClockPrescaler(myEPWM1_BASE, EPWM_CLOCK_DIVIDER_32, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(myEPWM1_BASE, 46874);	
    EPWM_setTimeBaseCounter(myEPWM1_BASE, 0);	
    EPWM_setTimeBaseCounterMode(myEPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);	
    EPWM_disablePhaseShiftLoad(myEPWM1_BASE);	
    EPWM_setPhaseShift(myEPWM1_BASE, 0);	
    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, 23437);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, 35155);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(myEPWM1_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(myEPWM1_BASE);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(myEPWM1_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(myEPWM1_BASE);	
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
	OUT_IR_init();
	OUT_TRIG_init();
	LED1_init();
	LED2_init();
}

void OUT_IR_init(){
	GPIO_setPadConfig(OUT_IR, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(OUT_IR, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(OUT_IR, GPIO_DIR_MODE_IN);
	GPIO_setControllerCore(OUT_IR, GPIO_CORE_CPU1);
}
void OUT_TRIG_init(){
	GPIO_setPadConfig(OUT_TRIG, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(OUT_TRIG, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(OUT_TRIG, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(OUT_TRIG, GPIO_CORE_CPU1);
}
void LED1_init(){
	GPIO_setPadConfig(LED1, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(LED1, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(LED1, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(LED1, GPIO_CORE_CPU1);
}
void LED2_init(){
	GPIO_setPadConfig(LED2, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(LED2, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(LED2, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(LED2, GPIO_CORE_CPU1);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){
	
	// Interrupt Settings for INT_ECAP_ECHO
	Interrupt_register(INT_ECAP_ECHO, &INT_ECAP_ECHO_ISR);
	Interrupt_enable(INT_ECAP_ECHO);
}
//*****************************************************************************
//
// SCI Configurations
//
//*****************************************************************************
void SCI_init(){
	mySCIA_init();
}

void mySCIA_init(){
	SCI_clearInterruptStatus(mySCIA_BASE, SCI_INT_RXFF | SCI_INT_TXFF | SCI_INT_FE | SCI_INT_OE | SCI_INT_PE | SCI_INT_RXERR | SCI_INT_RXRDY_BRKDT | SCI_INT_TXRDY);
	SCI_clearOverflowStatus(mySCIA_BASE);
	SCI_resetTxFIFO(mySCIA_BASE);
	SCI_resetRxFIFO(mySCIA_BASE);
	SCI_resetChannels(mySCIA_BASE);
	SCI_setConfig(mySCIA_BASE, DEVICE_LSPCLK_FREQ, mySCIA_BAUDRATE, (SCI_CONFIG_WLEN_8|SCI_CONFIG_STOP_ONE|SCI_CONFIG_PAR_NONE));
	SCI_disableLoopback(mySCIA_BASE);
	SCI_performSoftwareReset(mySCIA_BASE);
	SCI_setFIFOInterruptLevel(mySCIA_BASE, SCI_FIFO_TX0, SCI_FIFO_RX0);
	SCI_enableFIFO(mySCIA_BASE);
	SCI_enableModule(mySCIA_BASE);
}

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************
void SYNC_init(){
	SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_EPWM1SYNCOUT);
	//
	// SOCA
	//
	SysCtl_enableExtADCSOCSource(0);
	//
	// SOCB
	//
	SysCtl_enableExtADCSOCSource(0);
}
