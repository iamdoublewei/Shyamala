/*
 * Original Source: https://github.com/patrickschaumont/msp-aes-accelerator-msp430
 * TI Doc: https://www.ti.com/lit/ug/slau458f/slau458f.pdf?ts=1698952265603&ref_url=https%253A%252F%252Fwww.google.com%252F
 * Description: AES encryption with AES accelerator
 * Instruction: this code is used within Texas Instruction CCS development platform.
 *              Enable clock cycle measurement through Run->Clock->Enable.
 *              Set breakpoint with each __no_operation(); statement to measure the clock cycles.
 * Note: With IV the decrypted data is not matching the original plain text.
 *       Without IV the decrypted data is matching the original plain text.
 *       Also, directly using TI aes256 driverlib is an alternative approach.
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
uint8_t i;

void aes128(void) {
    // ct   69C4E0D8 6A7B0430 D8CDB780 70B4C55A

    uint8_t Key[16]  = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    //------------------------------ Encryption
    __no_operation(); // clock cycle: 1078
    // Reset AES
    AESACTL0=AESSWRST;
    // select encryption
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_0;
    // select key length 128 bit
    AESACTL0 = (AESACTL0 & ~AESKL) | AESKL_0;
    // select CBC
    AESACTL0 = (AESACTL0 & ~AESCM) | AESCM__CBC;
    // load Key
    for (i=0; i<8; i++)
        AESAKEY = ((uint16_t *) Key)[i];
    // load IV
    for (i=0; i<16; i++)
        AESAXIN = ((uint16_t *) IV)[i];
    // Encryption
    for (i=0; i<16; i++)
        AESAXDIN = ((uint16_t *) Data)[i];
    while (AESASTAT & AESBUSY) ;
    for (i=0; i<16; i++)
        ((uint16_t *) DataAESencrypted)[i] = AESADOUT;
    __no_operation(); // clock cycle: 1944

    //------------------------------ Decryption
    __no_operation(); // clock cycle: 1946
    // Reset AES
    AESACTL0=AESSWRST;
    // select key length 128 bit
    AESACTL0 = (AESACTL0 & ~AESKL) | AESKL_0;
    // The provided key is the same key used for encryption
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_1;
    // select CBC
    AESACTL0 = (AESACTL0 & ~AESCM) | AESCM__CBC;
    // Load Key
    for (i=0; i<8; i++)
        AESAKEY = ((uint16_t *) Key)[i];
    // load IV
    for (i=0; i<16; i++)
        AESAXIN = ((uint16_t *) IV)[i];
    // Decryption
    for (i=0; i<16; i++)
        AESADIN = ((uint16_t *) DataAESencrypted)[i];
    while (AESASTAT & AESBUSY);
    for (i=0; i<16; i++)
        ((uint16_t *) DataAESdecrypted)[i] = AESADOUT;
    __no_operation(); // clock cycle: 2865
}

void aes192(void) {
    // ct   DDA97CA4 864CDFE0 6EAF70A0 EC0D7191

    uint8_t Key[24]  = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};

    //------------------------------ Encryption
    __no_operation(); // clock cycle: 1147
    // Reset AES
    AESACTL0=AESSWRST;
    // select encryption
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_0;
    // select key length 192 bit
    AESACTL0 = (AESACTL0 & ~AESKL) | AESKL_1;
    // select CBC
    AESACTL0 = (AESACTL0 & ~AESCM) | AESCM__CBC;
    // load Key
    for (i=0; i<12; i++)
        AESAKEY = ((uint16_t *) Key)[i];
    // load IV
    for (i=0; i<16; i++)
        AESAXIN = ((uint16_t *) IV)[i];
    // Encryption
    for (i=0; i<16; i++)
        AESAXDIN = ((uint16_t *) Data)[i];
    while (AESASTAT & AESBUSY) ;
    for (i=0; i<16; i++)
        ((uint16_t *) DataAESencrypted)[i] = AESADOUT;
    __no_operation(); // clock cycle: 2177

    //------------------------------ Decryption
    __no_operation(); // clock cycle: 2180
    // Reset AES
    AESACTL0=AESSWRST;
    // select key length 192 bit
    AESACTL0 = (AESACTL0 & ~AESKL) | AESKL_1;
    // The provided key is the same key used for encryption
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_1;
    // select CBC
    AESACTL0 = (AESACTL0 & ~AESCM) | AESCM__CBC;
    // Load Key
    for (i=0; i<12; i++)
        AESAKEY = ((uint16_t *) Key)[i];
    // load IV
    for (i=0; i<16; i++)
        AESAXIN = ((uint16_t *) IV)[i];
    // Decryption
    for (i=0; i<16; i++)
        AESADIN = ((uint16_t *) DataAESencrypted)[i];
    while (AESASTAT & AESBUSY);
    for (i=0; i<16; i++)
        ((uint16_t *) DataAESdecrypted)[i] = AESADOUT;
    __no_operation(); // clock cycle: 3263
}

void aes256(void) {
    // ct   8EA2B7CA 516745BF EAFC4990 4B496089

    uint8_t Key[32]  = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};

    //------------------------------ Encryption
    __no_operation(); // clock cycle: 1220
    // Reset AES
    AESACTL0=AESSWRST;
    // select encryption
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_0;
    // select key length 256 bit
    AESACTL0 = (AESACTL0 & ~AESKL) | AESKL_2;
    // select CBC
    AESACTL0 = (AESACTL0 & ~AESCM) | AESCM__CBC;
    // load Key
    for (i=0; i<16; i++)
        AESAKEY = ((uint16_t *) Key)[i];
    // load IV
    for (i=0; i<16; i++)
        AESAXIN = ((uint16_t *) IV)[i];
    // Encryption
    for (i=0; i<16; i++)
        AESAXDIN = ((uint16_t *) Data)[i];
    while (AESASTAT & AESBUSY) ;
    for (i=0; i<16; i++)
        ((uint16_t *) DataAESencrypted)[i] = AESADOUT;
    __no_operation(); // clock cycle: 2391

    //------------------------------ Decryption
    __no_operation(); // clock cycle: 2394
    // Reset AES
    AESACTL0=AESSWRST;
    // select key length 256 bit
    AESACTL0 = (AESACTL0 & ~AESKL) | AESKL_2;
    // The provided key is the same key used for encryption
    AESACTL0 = (AESACTL0 & ~AESOP) | AESOP_1;
    // select CBC
    AESACTL0 = (AESACTL0 & ~AESCM) | AESCM__CBC;
    // Load Key
    for (i=0; i<16; i++)
        AESAKEY = ((uint16_t *) Key)[i];
    // load IV
    for (i=0; i<16; i++)
        AESAXIN = ((uint16_t *) IV)[i];
    // Decryption
    for (i=0; i<16; i++)
        AESADIN = ((uint16_t *) DataAESencrypted)[i];
    while (AESASTAT & AESBUSY);
    for (i=0; i<16; i++)
        ((uint16_t *) DataAESdecrypted)[i] = AESADOUT;
    __no_operation(); // clock cycle: 3624
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

    aes256_repeat();

    __no_operation();
}
