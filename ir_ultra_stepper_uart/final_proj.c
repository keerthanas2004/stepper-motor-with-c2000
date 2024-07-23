//#############################################################################
//
// FILE:   empty_driverlib_main.c
//
//! \addtogroup driver_example_list
//! <h1>Empty Project Example</h1> 
//!
//! This example is an empty project setup for Driverlib development.
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
#include "string.h"


/*__interrupt void INT_myCPUTIMER0_ISR(void);

__interrupt void INT_myCPUTIMER0_ISR(void)
{
    cpuTimer0IntCount++;
    if (cpuTimer0IntCount >= delayCount){
        cpuTimer0IntCount = 0;
        GPIO_togglePin(myBoardLED0_GPIO);
    }
    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    Interrupt_clearACKGroup(INT_myCPUTIMER0_INTERRUPT_ACK_GROUP);
}*/

//
// Main
//
uint32_t obj;
uint32_t clk_no;
uint32_t dist;
char cmd;
uint32_t choice;
uint32_t prev;

void display_menu()
{
    char* msg = "\n\n\r MENU: \n\r1. Start the Motor\n\r2. Stop the motor\n\r3.Display the speed\n\r4. Read IR Sensor\n\r5.Read Ultrasonic Sensor\n\rEnter your choice: \0";
    SCI_writeCharArray(mySCIA_BASE, (uint16_t*)msg, strlen(msg));
}

uint32_t get_command()
{

    return choice;

}
void print_integer(int msg)

{

    char arr[64], arr2[64];

    int length = 0, i;



    while(msg != 0)

    {

        arr[length] = msg%10 + '0';

        msg/=10;

        length++;

    }



    for(i=0; i<length; i++)

    {

        arr2[i] = arr[length-i-1];

    }

    arr2[length] = '\r';

    arr2[length+1] = '\n';

    arr2[length+2] = '\0';



    SCI_writeCharArray(mySCIA_BASE, (uint16_t*)arr2, length+2);

}

void process_command(int choice)
{
    char* msg;
    if(choice==1)
    {
        EPWM_setTimeBaseCounterMode(myEPWM0_BASE, EPWM_COUNTER_MODE_UP);
        EPWM_setTimeBaseCounterMode(myEPWM1_BASE, EPWM_COUNTER_MODE_UP);
    }
    else if(choice==2)
    {
        EPWM_setTimeBaseCounterMode(myEPWM0_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
        EPWM_setTimeBaseCounterMode(myEPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
    }
    else if(choice==3)
    {
        msg="\nSpeed: \0";
        SCI_writeCharArray(mySCIA_BASE, (uint16_t*)msg, strlen(msg));


    }
    else if(choice==4)
    {
        msg="\nReading of IR Sensor: \0";
        SCI_writeCharArray(mySCIA_BASE, (uint16_t*)msg, strlen(msg));
        print_integer(obj);

    }
    else if(choice==5)
    {
        msg="\nReading of UltraViolet Sensor: \0";
        SCI_writeCharArray(mySCIA_BASE, (uint16_t*)msg, strlen(msg));
        print_integer(dist/10000);
    }
    else
    {
        msg="\nWrong Input\0";
        SCI_writeCharArray(mySCIA_BASE, (uint16_t*)msg, strlen(msg));
    }
}
void main(void)
{

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;
    //
    // Start CPU Timer 0
    //
    //CPUTimer_startTimer(myCPUTIMER0_BASE);
    //

    while(1)
    {
        obj = GPIO_readPin(OUT_IR);
        GPIO_writePin(LED1, 0);
        GPIO_writePin(OUT_TRIG, 0);
        DEVICE_DELAY_US(200000);

        GPIO_writePin(LED1, 1);
        GPIO_writePin(OUT_TRIG, 1);
        DEVICE_DELAY_US(200000);
        if(choice!=2 ){
            if(obj==0)
            {
                EPWM_setTimeBaseCounterMode(myEPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
                EPWM_setTimeBaseCounterMode(myEPWM0_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
            }
            if(obj == 1){
                EPWM_setTimeBaseCounterMode(myEPWM1_BASE, EPWM_COUNTER_MODE_UP);
                EPWM_setTimeBaseCounterMode(myEPWM0_BASE, EPWM_COUNTER_MODE_UP);
            }
        }

        /* Display the options */
        display_menu();
        /* Read the command */
        //cmd = get_command();
        cmd=SCI_readCharBlockingFIFO(mySCIA_BASE);
        choice = cmd - '0';
        uint16_t rxStatus = 0U;
        rxStatus = SCI_getRxStatus(mySCIA_BASE);
        if((rxStatus & SCI_RXSTATUS_ERROR) != 0)
        {
            //
            //If Execution stops here there is some error
            //Analyze SCI_getRxStatus() API return value
            //
            ESTOP0;
        }
        /* Process the command */
        process_command(choice);
    }
}

interrupt void INT_ECAP_ECHO_ISR(void){
    GPIO_writePin(LED2, 0);
    clk_no = ECAP_getEventTimeStamp(ECAP_ECHO_BASE, ECAP_EVENT_2);
    dist = 343 * clk_no / (2 * 160);   //cm
    DEVICE_DELAY_US(200000);
    GPIO_writePin(LED2, 1);
    if(choice!=2){
        if(dist> 250000){
                EPWM_setClockPrescaler(myEPWM1_BASE, EPWM_CLOCK_DIVIDER_32, EPWM_HSCLOCK_DIVIDER_1);
                EPWM_setClockPrescaler(myEPWM0_BASE, EPWM_CLOCK_DIVIDER_32, EPWM_HSCLOCK_DIVIDER_1);
            }
            else if(dist>=200000 && dist<=250000)
            {
                EPWM_setClockPrescaler(myEPWM1_BASE, EPWM_CLOCK_DIVIDER_32, EPWM_HSCLOCK_DIVIDER_2);
                EPWM_setClockPrescaler(myEPWM0_BASE, EPWM_CLOCK_DIVIDER_32, EPWM_HSCLOCK_DIVIDER_2);
            }
            else if(dist>=150000 && dist<200000)
            {
                EPWM_setClockPrescaler(myEPWM1_BASE, EPWM_CLOCK_DIVIDER_32, EPWM_HSCLOCK_DIVIDER_4);
                EPWM_setClockPrescaler(myEPWM0_BASE, EPWM_CLOCK_DIVIDER_32, EPWM_HSCLOCK_DIVIDER_4);
            }
            else if(dist>=100000 && dist<150000)
            {
                EPWM_setClockPrescaler(myEPWM1_BASE, EPWM_CLOCK_DIVIDER_32, EPWM_HSCLOCK_DIVIDER_8);
                EPWM_setClockPrescaler(myEPWM0_BASE, EPWM_CLOCK_DIVIDER_32, EPWM_HSCLOCK_DIVIDER_8);
            }
            else if(dist<100000)
            {
                EPWM_setClockPrescaler(myEPWM1_BASE, EPWM_CLOCK_DIVIDER_32, EPWM_HSCLOCK_DIVIDER_14);
                EPWM_setClockPrescaler(myEPWM0_BASE, EPWM_CLOCK_DIVIDER_32, EPWM_HSCLOCK_DIVIDER_14);
            }

    }


    ECAP_clearInterrupt(ECAP_ECHO_BASE,ECAP_ISR_SOURCE_CAPTURE_EVENT_2);
    ECAP_clearGlobalInterrupt(ECAP_ECHO_BASE);
    ECAP_reArm(ECAP_ECHO_BASE);
    Interrupt_clearACKGroup(INT_ECAP_ECHO_INTERRUPT_ACK_GROUP);
}

//
// End of File
// EPWM_setClockPrescaler(myEPWM1_BASE, EPWM_CLOCK_DIVIDER_32, EPWM_HSCLOCK_DIVIDER_1);
