#include <msp430.h>
#include "lenet.h"
//#include "model.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

short int i,percent,j,predict;
uint8 left;
image *test_data={0};
uint8 *test_label={0};
int cnt = 0;

void testFirstImage()
{

    left = 7;
    predict = Predict(test_data[0], 10);

    if(left == predict)
    {
        printf("Shauo! prediction milse. Ha ha!");
    }

}

void configGPIO(void)
{
    // Configure ports for low power
    PADIR = 0xFFFF;  PAOUT = 0;
    PBDIR = 0xFFFF;  PBOUT = 0;
    PCDIR = 0xFFFF;  PCOUT = 0;
    PDDIR = 0xFFFF;  PDOUT = 0;
    PJDIR = 0xFFFF;  PJOUT = 0;
    P1DIR = 0xFF;  P1OUT = 0;
    P2DIR = 0xFF;  P2OUT = 0;
    P3DIR = 0xFF;  P3OUT = 0;
    P4DIR = 0xFF;  P4OUT = 0;
    P5DIR = 0xFF;  P5OUT = 0;
    P6DIR = 0xFF;  P6OUT = 0;
    P7DIR = 0xFF;  P7OUT = 0;
    P8DIR = 0xFF;  P8OUT = 0;
}

void configTimer(void)
{
    // CPU frequency doesn't specifically setup, it can cause timer to stop working. Detailed reason requires more testing.
    // SMCLK default: 1.048576 MHz
    // reference on page 162: https://www.ti.com/lit/ug/slau208q/slau208q.pdf?ts=1705354313232
    TA1CCTL0 = CCIE;                        // TA1CCR0 interrupt enabled
    TA1CCR0 = 50000;
    TA1CTL = TASSEL__SMCLK | MC__UP;        // SMCLK, up mode
    __bis_SR_register(GIE);                 // register interrupt
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    configGPIO();
    configTimer();
    while (1)
    {
        testFirstImage();
        __no_operation();
    }

    return 0;
}

// Timer A1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_A0_VECTOR))) Timer1_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
    if (cnt == 20)                          // 1 second for SMCLK = 1 MHz
         cnt = 0;
    else
        cnt += 1;
}
