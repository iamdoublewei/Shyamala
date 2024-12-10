/*
 * Original Source: https://github.com/patrickschaumont/msp-aes-accelerator-msp430
 * Description: software AES encryption
 * Instruction: this code is used within Texas Instruction CCS development platform.
 *              Enable clock cycle measurement through Run->Clock->Enable.
 *              Set breakpoint with each __no_operation(); statement to measure the clock cycles.
 */
#include <msp430.h>
#include <stdint.h>
#include "driverlib/driverlib.h"
#include "aes.h"

uint8_t Data[32] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
                    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f};
uint8_t IV[32]   = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
                    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f};
uint8_t DataAESencrypted[32];

void aes128(void) {
    // ct   1ECA870F FEA114B7 FD6CF363 C30B96B1

    struct AES_ctx SWAES;
    uint8_t Key[16]  = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    //----------------------- Encryption
    __no_operation(); // clock cycle: 871
    AES_init_ctx_iv(&SWAES, Key, IV);
    AES_CBC_encrypt_buffer(&SWAES, Data, 32);
    __no_operation(); // clock cycle: 36779

    memcpy(DataAESencrypted, Data, 32);

    //----------------------- Decryption
    __no_operation(); // clock cycle: 36946
    AES_init_ctx_iv(&SWAES, Key, IV);
    AES_CBC_decrypt_buffer(&SWAES, DataAESencrypted, 32);
    __no_operation(); // clock cycle: 134765
}

void aes192(void) {
    // ct   85AD183F B866F818 2DBAFA82 EF7E9FC0

    struct AES_ctx SWAES;
    uint8_t Key[24]  = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};

    //----------------------- Encryption
    __no_operation(); // clock cycle: 946
    AES_init_ctx_iv(&SWAES, Key, IV);
    AES_CBC_encrypt_buffer(&SWAES, Data, 32);
    __no_operation(); // clock cycle: 51536

    memcpy(DataAESencrypted, Data, 32);

    //----------------------- Decryption
    __no_operation(); // clock cycle: 51703
    AES_init_ctx_iv(&SWAES, Key, IV);
    AES_CBC_decrypt_buffer(&SWAES, DataAESencrypted, 32);
    __no_operation(); // clock cycle: 177884
}

void aes256(void) {
    // ct   0E2392DD 6F690B44 A5A1B4FD FF3B7F83

    struct AES_ctx SWAES;
    uint8_t Key[32]  = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};

    //----------------------- Encryption
    __no_operation(); // clock cycle: 1018
    AES_init_ctx_iv(&SWAES, Key, IV);
    AES_CBC_encrypt_buffer(&SWAES, Data, 32);
    __no_operation(); // clock cycle: 51116

    memcpy(DataAESencrypted, Data, 32);

    //----------------------- Decryption
    __no_operation(); // clock cycle: 51283
    AES_init_ctx_iv(&SWAES, Key, IV);
    AES_CBC_decrypt_buffer(&SWAES, DataAESencrypted, 32);
    __no_operation(); // clock cycle: 190628
}

void aes128_repeat(void){
    int cnt = 0;

    while (1){
        aes128();
        cnt += 1;
        if (cnt == 1000){
            break;
        }
    }
}

void aes192_repeat(void){
    int cnt = 0;

    while (1){
        aes192();
        cnt += 1;
        if (cnt == 1000){
            break;
        }
    }
}

void aes256_repeat(void){
    int cnt = 0;

    while (1){
        aes256();
        cnt += 1;
        if (cnt == 1000){
            break;
        }
    }
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;

    // aes128, aes192, aes256 need to run independently
//    aes128(); // select #define AES128 1 in aes.h
//    aes192(); // select #define AES192 1 in aes.h
//    aes256(); // select #define AES256 1 in aes.h

    aes256_repeat();

    __no_operation();
}
