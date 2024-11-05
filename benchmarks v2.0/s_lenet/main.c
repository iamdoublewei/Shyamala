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

void testFirstImage()
{

    left = 7;
    predict = Predict(test_data[0], 10);

    if(left == predict)
    {
        printf("Shauo! prediction milse. Ha ha!");
    }

}

//void configGPIO(void)
//{
//    // Configure ports for low power
//    PADIR = 0xFFFF;  PAOUT = 0;
//    PBDIR = 0xFFFF;  PBOUT = 0;
//    PCDIR = 0xFFFF;  PCOUT = 0;
//    PDDIR = 0xFFFF;  PDOUT = 0;
//    PJDIR = 0xFFFF;  PJOUT = 0;
//    P1DIR = 0xFF;  P1OUT = 0;
//    P2DIR = 0xFF;  P2OUT = 0;
//    P3DIR = 0xFF;  P3OUT = 0;
//    P4DIR = 0xFF;  P4OUT = 0;
//    P5DIR = 0xFF;  P5OUT = 0;
//    P6DIR = 0xFF;  P6OUT = 0;
//    P7DIR = 0xFF;  P7OUT = 0;
//    P8DIR = 0xFF;  P8OUT = 0;
//}

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
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

//    configGPIO();
    testFirstImage();
}
