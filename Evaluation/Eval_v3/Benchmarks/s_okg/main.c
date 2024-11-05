#include <msp430.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <GKR.h>
#include <string.h>

#define MODEL_FILE      "model.dat"

short int i,percent,j,predict;
int cnt = 0;

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
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;

	configTimer();
    while (1)
    {
        Predict();
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
    if (cnt == 100)                          // cnt = 20 = 1 second for SMCLK = 1 MHz
         cnt = 0;
    else
        cnt += 1;
}
