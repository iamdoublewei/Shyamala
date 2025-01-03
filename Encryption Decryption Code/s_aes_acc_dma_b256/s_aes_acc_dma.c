/*
 * Original Source: https://github.com/patrickschaumont/msp-aes-accelerator-msp430
 * TI Doc: https://www.ti.com/lit/ug/slau458f/slau458f.pdf?ts=1698952265603&ref_url=https%253A%252F%252Fwww.google.com%252F
 * Description: AES encryption with AES accelerator
 * Instruction: this code is used within Texas Instruction CCS development platform.
 *              Enable clock cycle measurement through Run->Clock->Enable.
 *              Set breakpoint with each __no_operation(); statement to measure the clock cycles.
 */

#include <msp430.h>
#include <stdint.h>
#include "driverlib/driverlib.h"

uint8_t Data[32] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
                    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f};
uint8_t IV[32]   = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
                    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f};
volatile uint8_t DataAESencrypted[32];
volatile uint8_t DataAESdecrypted[32];
uint16_t i;

void aes128(void) {
    uint8_t Key[16]  = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    //----------------------- Encryption
    __no_operation(); // clock cycle: 1087
    // Reset AES
    AESACTL0=AESSWRST;
    // select encryption
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_0;
    // select key length 128 bit
    AESACTL0 = (AESACTL0 & ~AESKL) | AESKL_0;
    // select CBC
    AESACTL0 = (AESACTL0 & ~AESCM) | AESCM__CBC;
    // enable DMA
    AESACTL0 = (AESACTL0) | AESCMEN__ENABLE;
    // Load Key
    for (i=0; i<8; i++)
        AESAKEY = ((uint16_t *) Key)[i];
    // Load IV
    for (i=0; i<16; i++)
        AESAXIN = ((uint16_t *) IV)[i];
    // DMA trigger source           AES Trigger
    //      11                          0
    //      12                          1
    //      13                          2
    // DMA Triggers
    DMACTL0 = DMA0TSEL_11 | DMA1TSEL_12;
    // Configure Channel 0
    DMA0CTL = DMADT_0 | DMALEVEL | DMASRCINCR_0 | DMADSTINCR_3;
    // Channel 0 Source Address
    __data20_write_long((unsigned long)&DMA0SA, (unsigned long)&AESADOUT);
    // Channel 0 DestinationAddress
    __data20_write_long((unsigned long)&DMA0DA, (unsigned long)DataAESencrypted);
    // Channel 0 Size (Size in words - 16bits)
    DMA0SZ = 16;
    // Enable Channel 0
    DMA0CTL |= DMAEN;
    // Configure Channel 1
    DMA1CTL = DMADT_0 | DMALEVEL | DMASRCINCR_3 | DMADSTINCR_0;
    // Channel 1 Source Address
    __data20_write_long((unsigned long)&DMA1SA, (unsigned long)Data);
    // Channel 1 Destination Address
    __data20_write_long((unsigned long)&DMA1DA, (unsigned long)&AESAXDIN);
    // Channel 1 Size
    DMA1SZ = 16;
    // Enable Channel 1
    DMA1CTL |= DMAEN;
    AESACTL1 = 1;
    while (!(DMA0CTL & DMAIFG)) ;
    DMAIV |= 0;
    // Disable DMA
    DMA0CTL = DMA0CTL & (~DMAEN);
    DMA1CTL = DMA1CTL & (~DMAEN);
    __no_operation(); // clock cycle: 1729

    //----------------------- Decryption
    __no_operation(); // clock cycle: 1732
    // Reset AES
    AESACTL0=AESSWRST;
    // select key length 128 bit
    AESACTL0 = (AESACTL0 & ~AESKL) | AESKL_0;
    // select decryption
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_2;
    // Load Key
    for (i=0; i<8; i++)
        AESAKEY = ((uint16_t *) Key)[i];
    while (AESASTAT & AESBUSY) ;
    // select decryption (use offline roundkeys)
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_3;
    // select CBC
    AESACTL0 = (AESACTL0 & ~AESCM) | AESCM__CBC;
    // enable DMA
    AESACTL0 = (AESACTL0) | AESCMEN__ENABLE;
    AESASTAT|=AESKEYWR;
    // DMA Triggers
    DMACTL0 = DMA0TSEL_11 | DMA1TSEL_12;  // AES Trigger 0 and 1
    DMACTL1 = DMA2TSEL_13;                // AES Trigger 2
    // Configure Channel 0
    DMA0CTL = DMADT_0 | DMALEVEL | DMASRCINCR_3 | DMADSTINCR_0;
    // Channel 0 Source Address
    __data20_write_long((unsigned long)&DMA0SA, (unsigned long)IV);
    // Channel 0 DestinationAddress
    __data20_write_long((unsigned long)&DMA0DA, (unsigned long)&AESAXIN);
    // Channel 0 Size
    DMA0SZ = 16;
    // Enable Channel 0
    DMA0CTL |= DMAEN;
    // Configure Channel 1
    DMA1CTL = DMADT_0 | DMALEVEL | DMASRCINCR_0 | DMADSTINCR_3;
    // Channel 1 Source Address
    __data20_write_long((unsigned long)&DMA1SA, (unsigned long)&AESADOUT);
    // Channel 1 Destination Address
    __data20_write_long((unsigned long)&DMA1DA, (unsigned long)DataAESdecrypted);
    // Channel 1 Size
    DMA1SZ = 16;
    // Enable Channel 1
    DMA1CTL |= DMAEN;
    // Configure Channel 2
    DMA2CTL=DMADT_0 | DMALEVEL | DMASRCINCR_3 | DMADSTINCR_0;
    // Channel 2 Source Address
    __data20_write_long((unsigned long)&DMA2SA, (unsigned long)DataAESencrypted);
    // Channel 2 Destination Address
    __data20_write_long((unsigned long)&DMA2DA, (unsigned long)&AESADIN);
    // Channel 2 Size
    DMA2SZ = 16;
    // Enable Channel 2
    DMA2CTL |= DMAEN;
    // Start AES
    AESACTL1 = 1;
    // Wait for end of first block (IV)
    while(!(DMA0CTL & DMAIFG));
    // Configure Channel 0
    DMA0CTL = DMADT_0 | DMALEVEL | DMASRCINCR_3 | DMADSTINCR_0;
    // Channel 0 Source Address
    __data20_write_long((unsigned long)&DMA0SA, (unsigned long)DataAESencrypted);
    // Channel 0 Destination Address
    __data20_write_long((unsigned long)&DMA0DA, (unsigned long)&AESAXIN);
    // Channel 0 Size
    DMA0SZ = 0;
    // Enable Channel 0
    DMA0CTL |= DMAEN;
    // Wait for end of DMA
    while(!(DMA1CTL & DMAIFG));
    // Disable DMA
    DMA0CTL = DMA0CTL & (~DMAEN);
    DMA1CTL = DMA1CTL & (~DMAEN);
    DMA2CTL = DMA2CTL & (~DMAEN);
    __no_operation(); // clock cycle: 2369
}

void aes192(void) {
    uint8_t Key[24]  = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};

    //----------------------- Encryption
    __no_operation(); // clock cycle: 1159
    // Reset AES
    AESACTL0=AESSWRST;
    // select encryption
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_0;
    // select key length 192 bit
    AESACTL0 = (AESACTL0 & ~AESKL) | AESKL_1;
    // select CBC
    AESACTL0 = (AESACTL0 & ~AESCM) | AESCM__CBC;
    // enable DMA
    AESACTL0 = (AESACTL0) | AESCMEN__ENABLE;
    // Load Key
    for (i=0; i<12; i++)
        AESAKEY = ((uint16_t *) Key)[i];
    // Load IV
    for (i=0; i<16; i++)
        AESAXIN = ((uint16_t *) IV)[i];
    // DMA trigger source           AES Trigger
    //      11                          0
    //      12                          1
    //      13                          2
    // DMA Triggers
    DMACTL0 = DMA0TSEL_11 | DMA1TSEL_12;
    // Configure Channel 0
    DMA0CTL = DMADT_0 | DMALEVEL | DMASRCINCR_0 | DMADSTINCR_3;
    // Channel 0 Source Address
    __data20_write_long((unsigned long)&DMA0SA, (unsigned long)&AESADOUT);
    // Channel 0 DestinationAddress
    __data20_write_long((unsigned long)&DMA0DA, (unsigned long)DataAESencrypted);
    // Channel 0 Size (Size in words - 16bits)
    DMA0SZ = 16;
    // Enable Channel 0
    DMA0CTL |= DMAEN;
    // Configure Channel 1
    DMA1CTL = DMADT_0 | DMALEVEL | DMASRCINCR_3 | DMADSTINCR_0;
    // Channel 1 Source Address
    __data20_write_long((unsigned long)&DMA1SA, (unsigned long)Data);
    // Channel 1 Destination Address
    __data20_write_long((unsigned long)&DMA1DA, (unsigned long)&AESAXDIN);
    // Channel 1 Size
    DMA1SZ = 16;
    // Enable Channel 1
    DMA1CTL |= DMAEN;
    AESACTL1 = 1;
    while (!(DMA0CTL & DMAIFG)) ;
    DMAIV |= 0;
    // Disable DMA
    DMA0CTL = DMA0CTL & (~DMAEN);
    DMA1CTL = DMA1CTL & (~DMAEN);
    __no_operation(); // clock cycle: 1939

    //----------------------- Decryption
    __no_operation(); // clock cycle: 1941
    // Reset AES
    AESACTL0=AESSWRST;
    // select key length 192 bit
    AESACTL0 = (AESACTL0 & ~AESKL) | AESKL_1;
    // select decryption
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_2;
    // Load Key
    for (i=0; i<12; i++)
        AESAKEY = ((uint16_t *) Key)[i];
    while (AESASTAT & AESBUSY) ;
    // select decryption (use offline roundkeys)
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_3;
    // select CBC
    AESACTL0 = (AESACTL0 & ~AESCM) | AESCM__CBC;
    // enable DMA
    AESACTL0 = (AESACTL0) | AESCMEN__ENABLE;
    AESASTAT|=AESKEYWR;
    // DMA Triggers
    DMACTL0 = DMA0TSEL_11 | DMA1TSEL_12;  // AES Trigger 0 and 1
    DMACTL1 = DMA2TSEL_13;                // AES Trigger 2
    // Configure Channel 0
    DMA0CTL = DMADT_0 | DMALEVEL | DMASRCINCR_3 | DMADSTINCR_0;
    // Channel 0 Source Address
    __data20_write_long((unsigned long)&DMA0SA, (unsigned long)IV);
    // Channel 0 DestinationAddress
    __data20_write_long((unsigned long)&DMA0DA, (unsigned long)&AESAXIN);
    // Channel 0 Size
    DMA0SZ = 16;
    // Enable Channel 0
    DMA0CTL |= DMAEN;
    // Configure Channel 1
    DMA1CTL = DMADT_0 | DMALEVEL | DMASRCINCR_0 | DMADSTINCR_3;
    // Channel 1 Source Address
    __data20_write_long((unsigned long)&DMA1SA, (unsigned long)&AESADOUT);
    // Channel 1 Destination Address
    __data20_write_long((unsigned long)&DMA1DA, (unsigned long)DataAESdecrypted);
    // Channel 1 Size
    DMA1SZ = 16;
    // Enable Channel 1
    DMA1CTL |= DMAEN;
    // Configure Channel 2
    DMA2CTL=DMADT_0 | DMALEVEL | DMASRCINCR_3 | DMADSTINCR_0;
    // Channel 2 Source Address
    __data20_write_long((unsigned long)&DMA2SA, (unsigned long)DataAESencrypted);
    // Channel 2 Destination Address
    __data20_write_long((unsigned long)&DMA2DA, (unsigned long)&AESADIN);
    // Channel 2 Size
    DMA2SZ = 16;
    // Enable Channel 2
    DMA2CTL |= DMAEN;
    // Start AES
    AESACTL1 = 1;
    // Wait for end of first block (IV)
    while(!(DMA0CTL & DMAIFG));
    // Configure Channel 0
    DMA0CTL = DMADT_0 | DMALEVEL | DMASRCINCR_3 | DMADSTINCR_0;
    // Channel 0 Source Address
    __data20_write_long((unsigned long)&DMA0SA, (unsigned long)DataAESencrypted);
    // Channel 0 Destination Address
    __data20_write_long((unsigned long)&DMA0DA, (unsigned long)&AESAXIN);
    // Channel 0 Size
    DMA0SZ = 0;
    // Enable Channel 0
    DMA0CTL |= DMAEN;
    // Wait for end of DMA
    while(!(DMA1CTL & DMAIFG));
    // Disable DMA
    DMA0CTL = DMA0CTL & (~DMAEN);
    DMA1CTL = DMA1CTL & (~DMAEN);
    DMA2CTL = DMA2CTL & (~DMAEN);
    __no_operation(); // clock cycle: 2717
}

void aes256(void) {
    uint8_t Key[32]  = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};

    //----------------------- Encryption
    __no_operation(); // clock cycle: 1231
    // Reset AES
    AESACTL0=AESSWRST;
    // select encryption
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_0;
    // select key length 256 bit
    AESACTL0 = (AESACTL0 & ~AESKL) | AESKL_2;
    // select CBC
    AESACTL0 = (AESACTL0 & ~AESCM) | AESCM__CBC;
    // enable DMA
    AESACTL0 = (AESACTL0) | AESCMEN__ENABLE;
    // Load Key
    for (i=0; i<16; i++)
        AESAKEY = ((uint16_t *) Key)[i];
    // Load IV
    for (i=0; i<16; i++)
        AESAXIN = ((uint16_t *) IV)[i];
    // DMA trigger source           AES Trigger
    //      11                          0
    //      12                          1
    //      13                          2
    // DMA Triggers
    DMACTL0 = DMA0TSEL_11 | DMA1TSEL_12;
    // Configure Channel 0
    DMA0CTL = DMADT_0 | DMALEVEL | DMASRCINCR_0 | DMADSTINCR_3;
    // Channel 0 Source Address
    __data20_write_long((unsigned long)&DMA0SA, (unsigned long)&AESADOUT);
    // Channel 0 DestinationAddress
    __data20_write_long((unsigned long)&DMA0DA, (unsigned long)DataAESencrypted);
    // Channel 0 Size (Size in words - 16bits)
    DMA0SZ = 16;
    // Enable Channel 0
    DMA0CTL |= DMAEN;
    // Configure Channel 1
    DMA1CTL = DMADT_0 | DMALEVEL | DMASRCINCR_3 | DMADSTINCR_0;
    // Channel 1 Source Address
    __data20_write_long((unsigned long)&DMA1SA, (unsigned long)Data);
    // Channel 1 Destination Address
    __data20_write_long((unsigned long)&DMA1DA, (unsigned long)&AESAXDIN);
    // Channel 1 Size
    DMA1SZ = 16;
    // Enable Channel 1
    DMA1CTL |= DMAEN;
    AESACTL1 = 1;
    while (!(DMA0CTL & DMAIFG)) ;
    DMAIV |= 0;
    // Disable DMA
    DMA0CTL = DMA0CTL & (~DMAEN);
    DMA1CTL = DMA1CTL & (~DMAEN);
    __no_operation(); // clock cycle: 2125

    //----------------------- Decryption
    __no_operation(); // clock cycle: 2127
    // Reset AES
    AESACTL0=AESSWRST;
    // select key length 256 bit
    AESACTL0 = (AESACTL0 & ~AESKL) | AESKL_2;
    // select decryption
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_2;
    // Load Key
    for (i=0; i<16; i++)
        AESAKEY = ((uint16_t *) Key)[i];
    while (AESASTAT & AESBUSY) ;
    // select decryption (use offline roundkeys)
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_3;
    // select CBC
    AESACTL0 = (AESACTL0 & ~AESCM) | AESCM__CBC;
    // enable DMA
    AESACTL0 = (AESACTL0) | AESCMEN__ENABLE;
    AESASTAT|=AESKEYWR;
    // DMA Triggers
    DMACTL0 = DMA0TSEL_11 | DMA1TSEL_12;  // AES Trigger 0 and 1
    DMACTL1 = DMA2TSEL_13;                // AES Trigger 2
    // Configure Channel 0
    DMA0CTL = DMADT_0 | DMALEVEL | DMASRCINCR_3 | DMADSTINCR_0;
    // Channel 0 Source Address
    __data20_write_long((unsigned long)&DMA0SA, (unsigned long)IV);
    // Channel 0 DestinationAddress
    __data20_write_long((unsigned long)&DMA0DA, (unsigned long)&AESAXIN);
    // Channel 0 Size
    DMA0SZ = 16;
    // Enable Channel 0
    DMA0CTL |= DMAEN;
    // Configure Channel 1
    DMA1CTL = DMADT_0 | DMALEVEL | DMASRCINCR_0 | DMADSTINCR_3;
    // Channel 1 Source Address
    __data20_write_long((unsigned long)&DMA1SA, (unsigned long)&AESADOUT);
    // Channel 1 Destination Address
    __data20_write_long((unsigned long)&DMA1DA, (unsigned long)DataAESdecrypted);
    // Channel 1 Size
    DMA1SZ = 16;
    // Enable Channel 1
    DMA1CTL |= DMAEN;
    // Configure Channel 2
    DMA2CTL=DMADT_0 | DMALEVEL | DMASRCINCR_3 | DMADSTINCR_0;
    // Channel 2 Source Address
    __data20_write_long((unsigned long)&DMA2SA, (unsigned long)DataAESencrypted);
    // Channel 2 Destination Address
    __data20_write_long((unsigned long)&DMA2DA, (unsigned long)&AESADIN);
    // Channel 2 Size
    DMA2SZ = 16;
    // Enable Channel 2
    DMA2CTL |= DMAEN;
    // Start AES
    AESACTL1 = 1;
    // Wait for end of first block (IV)
    while(!(DMA0CTL & DMAIFG));
    // Configure Channel 0
    DMA0CTL = DMADT_0 | DMALEVEL | DMASRCINCR_3 | DMADSTINCR_0;
    // Channel 0 Source Address
    __data20_write_long((unsigned long)&DMA0SA, (unsigned long)DataAESencrypted);
    // Channel 0 Destination Address
    __data20_write_long((unsigned long)&DMA0DA, (unsigned long)&AESAXIN);
    // Channel 0 Size
    DMA0SZ = 0;
    // Enable Channel 0
    DMA0CTL |= DMAEN;
    // Wait for end of DMA
    while(!(DMA1CTL & DMAIFG));
    // Disable DMA
    DMA0CTL = DMA0CTL & (~DMAEN);
    DMA1CTL = DMA1CTL & (~DMAEN);
    DMA2CTL = DMA2CTL & (~DMAEN);
    __no_operation(); // clock cycle: 3027
}

void aes128_repeat(void){
    int cnt = 0;

    while (1){
        aes128();
        cnt += 1;
        if (cnt == 10000){
            break;
        }
    }
}

void aes192_repeat(void){
    int cnt = 0;

    while (1){
        aes192();
        cnt += 1;
        if (cnt == 10000){
            break;
        }
    }
}

void aes256_repeat(void){
    int cnt = 0;

    while (1){
        aes256();
        cnt += 1;
        if (cnt == 10000){
            break;
        }
    }
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;

    // aes128, aes192, aes256 run independently
//    aes128();
//    aes192();
//    aes256();

    aes128_repeat();

    __no_operation();
}
