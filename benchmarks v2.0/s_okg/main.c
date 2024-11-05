#include <msp430.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <GKR.h>
#include <string.h>

#define MODEL_FILE      "model.dat"

short int i,percent,j,predict;

void main(void)
{
    int cnt = 0;

    __no_operation();
    while(1)
    {
        benchmark();
        cnt += 1;
        if (cnt == 1)
        {
            break;
        }
    }
    __no_operation();
}

void benchmark(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;

    Predict();
}
