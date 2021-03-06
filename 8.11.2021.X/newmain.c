/*
 * File:   newmain.c
 * Author: OAKBATI-HPW
 *
 * Created on 08 Kas?m 2021 Pazartesi, 09:57
 */


#include <stdio.h>
#include <stdlib.h>
#include <pic18f45k22.h>
#include <htc.h>
#define _XTAL_FREQ 8000000
#pragma config FOSC = HSHP
#pragma config WDTEN = OFF

#define CS1 PORTBbits.RB0
#define CS2 PORTBbits.RB1
#define RS PORTBbits.RB2
#define RW PORTBbits.RB3
#define EN PORTBbits.RB4
#define RST PORTBbits.RB5
#define RD7 PORTDbits.RD7
#define LCD_DATA PORTD

void trig();
void glcd_init();
void clr_scr();
void print_logo();
void dama(char theme);
void place_text(unsigned int start_char, unsigned int page, unsigned char *s);

const unsigned char ytulogo [1024] = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F,
0x3F, 0x3F, 0xBF, 0x9F, 0x9F, 0xDF, 0xDF, 0xCF, 0xCF, 0xCF, 0x6F, 0xEF, 0xE7, 0xE7, 0x67, 0x77,
0xF7, 0xF7, 0xD7, 0x13, 0x33, 0xF3, 0xF3, 0xFB, 0x1B, 0x1B, 0x7B, 0x3B, 0x1B, 0x5B, 0xDB, 0xFB,
0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0x3B, 0x1B, 0x9B, 0xEB, 0xF3, 0x73, 0x13, 0x33, 0xF7, 0xF7,
0xF7, 0x77, 0x67, 0x67, 0xE7, 0xEF, 0xEF, 0xCF, 0xCF, 0xDF, 0xDF, 0xDF, 0x9F, 0x9F, 0xBF, 0x3F,
0x3F, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F,
0x3F, 0x9F, 0x8F, 0xCF, 0xE7, 0xE7, 0x73, 0xF3, 0xB9, 0x99, 0x1D, 0x4C, 0x2E, 0xBE, 0xDE, 0x77,
0x73, 0x27, 0xC7, 0xC1, 0xD1, 0xF7, 0xF7, 0x67, 0x6F, 0x6E, 0x38, 0xB0, 0xB2, 0x9D, 0x9D, 0xD8,
0xD8, 0xC9, 0xCF, 0xCF, 0xEC, 0xEC, 0xEF, 0xEF, 0xE4, 0xE4, 0xE7, 0xE7, 0xE7, 0xE6, 0x26, 0x06,
0x07, 0x07, 0x27, 0xE7, 0xE7, 0xE7, 0xE6, 0xE4, 0xE5, 0xED, 0xED, 0xEC, 0xEE, 0xCF, 0xCF, 0xC9,
0xD8, 0xDE, 0x9E, 0x98, 0xB3, 0x31, 0x3C, 0x6E, 0x67, 0x63, 0xF3, 0xF9, 0xFC, 0x9E, 0x87, 0x83,
0xD3, 0xDF, 0xCE, 0x6E, 0x6E, 0x3C, 0x3D, 0xB9, 0xB9, 0x73, 0x73, 0xE7, 0xE7, 0xCF, 0x8F, 0x9F,
0x3F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x1F, 0x87, 0xC3, 0xE1, 0xF9, 0x7C, 0x3C, 0x9E,
0x9F, 0x3F, 0x7F, 0xF9, 0xFD, 0x7C, 0x3C, 0xF9, 0xF9, 0xFB, 0x73, 0x3B, 0x1E, 0x9E, 0xCE, 0xC6,
0xE7, 0xF3, 0xF1, 0xF9, 0xFC, 0xFC, 0xFE, 0xFE, 0xFE, 0xFE, 0xF8, 0xF1, 0xC1, 0x81, 0x1B, 0x33,
0xF3, 0xF7, 0xE7, 0xE7, 0xEF, 0xCF, 0xCF, 0x9F, 0x9F, 0x3F, 0x1F, 0x07, 0x41, 0x70, 0x78, 0xFE,
0xFF, 0xFE, 0x78, 0x70, 0x43, 0x07, 0x1F, 0x3F, 0x9F, 0x9F, 0xDF, 0xCF, 0xEF, 0xE7, 0xE7, 0xF7,
0xF3, 0x33, 0x1B, 0x09, 0xC1, 0xE1, 0xF8, 0xFC, 0xFE, 0xFE, 0xFE, 0xFC, 0xFD, 0xF9, 0xF1, 0xF3,
0xE7, 0xC6, 0xCE, 0x9C, 0x19, 0x3B, 0x76, 0xF6, 0xF7, 0x93, 0xC3, 0x6B, 0x6B, 0xC9, 0x63, 0x27,
0x3F, 0x3E, 0x7C, 0x7C, 0xF9, 0xE3, 0xC3, 0x8F, 0x1F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x01, 0x00, 0xF8, 0xFE, 0xFF, 0xFF, 0x1F, 0x1B, 0x5A, 0x5A, 0x5B,
0x53, 0x57, 0x16, 0xB4, 0xFC, 0xFE, 0xFF, 0x0F, 0x03, 0x80, 0xF8, 0xF8, 0xFB, 0xFB, 0xF3, 0xF3,
0xF3, 0xE3, 0xEB, 0xCB, 0xCB, 0xDB, 0x9B, 0x9B, 0xBB, 0x3B, 0x3B, 0x7B, 0x7B, 0x7B, 0x7A, 0x38,
0x30, 0x81, 0x83, 0x8B, 0xFB, 0xFB, 0xFB, 0xF9, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE,
0xFC, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF9, 0xFB, 0xFB, 0xFB, 0x9B, 0x83, 0x81,
0x30, 0x38, 0x78, 0x7B, 0x7B, 0x7B, 0x3B, 0x3B, 0xBB, 0x9B, 0x9B, 0xDB, 0xCB, 0xEB, 0xE3, 0xE3,
0xF3, 0xF3, 0xF3, 0xFB, 0xFB, 0xF8, 0xF8, 0x80, 0x03, 0x0F, 0xFF, 0xFC, 0xFC, 0x69, 0x24, 0x24,
0x25, 0x37, 0x34, 0x36, 0x17, 0x17, 0xF7, 0xFF, 0xFE, 0xF8, 0x00, 0x03, 0x1F, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x80, 0x00, 0x1F, 0x7F, 0xFF, 0xFF, 0xEF, 0xEF, 0x2E, 0x2E, 0xA6,
0xA6, 0xA6, 0xB2, 0xB3, 0xBF, 0xFF, 0xFF, 0xF0, 0xC0, 0x03, 0x1F, 0x3F, 0x9F, 0x9F, 0x9F, 0x8F,
0x8F, 0x87, 0x87, 0x97, 0x93, 0x93, 0x9B, 0x99, 0x99, 0x9D, 0x9C, 0x9C, 0x9E, 0x9E, 0x1E, 0x1C,
0x0D, 0x81, 0x81, 0x93, 0x9F, 0x9F, 0xDF, 0x9F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F,
0x3F, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF, 0x7F, 0x3F, 0x1F, 0x9F, 0xDF, 0xDF, 0xDF, 0xD3, 0xC1, 0x81,
0x0D, 0x1C, 0x1E, 0xDE, 0xDE, 0xDE, 0xDC, 0xDD, 0xD9, 0xD9, 0xDB, 0xD3, 0xD3, 0xD7, 0xC7, 0xC7,
0xCF, 0xCF, 0xCF, 0xDF, 0xDF, 0x3F, 0x1F, 0x03, 0xC0, 0xF0, 0xFF, 0x3F, 0x3F, 0x81, 0x71, 0x79,
0x39, 0xA1, 0x3B, 0x7B, 0xE3, 0xE2, 0xFF, 0xFF, 0x7F, 0x1F, 0x00, 0x80, 0xF0, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF0, 0xE1, 0xC3, 0x8F, 0x1F, 0x3F, 0x7D, 0x7D,
0xF5, 0xF1, 0xF9, 0xF9, 0xFD, 0xFD, 0xFD, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xF3, 0xE7,
0xC7, 0xCF, 0x9F, 0x9F, 0x3F, 0x3F, 0x7F, 0x7F, 0xFF, 0x7F, 0x1F, 0x0F, 0x83, 0x80, 0xD8, 0xCC,
0xCF, 0xEF, 0xE7, 0xE7, 0xF7, 0xF3, 0xF3, 0xFB, 0xF9, 0xF8, 0xF0, 0xE0, 0x86, 0x0E, 0x3E, 0x7F,
0xFF, 0x7F, 0x3E, 0x0E, 0x82, 0xE0, 0xF8, 0xFC, 0xF9, 0xFB, 0xF3, 0xF3, 0xF7, 0xE7, 0xE7, 0xEF,
0xCF, 0xCC, 0xD8, 0x80, 0x83, 0x0F, 0x1F, 0x7F, 0xFF, 0x7F, 0x7F, 0x3F, 0x3F, 0x9F, 0x9F, 0xCF,
0xC7, 0xE7, 0xF3, 0xF1, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFB, 0xFB, 0xFA, 0xF2, 0xF6, 0xF6, 0xF6,
0xF7, 0x6D, 0x6E, 0x3E, 0x1F, 0x8F, 0xC3, 0xE1, 0xF0, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC,
0xF8, 0xF9, 0xF3, 0xF3, 0xE7, 0xE7, 0xCF, 0xDF, 0x9F, 0x9F, 0x3F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFC, 0xFC, 0xFD, 0xF9, 0xF9, 0xFB, 0xFB,
0xF3, 0xF3, 0xF3, 0xF7, 0xF7, 0xF7, 0x27, 0x27, 0xE7, 0xE7, 0x67, 0x6F, 0xEF, 0x6F, 0x6C, 0x60,
0xE1, 0xE8, 0x6C, 0x6F, 0x6F, 0x6F, 0xE7, 0x67, 0x67, 0x27, 0x27, 0xF7, 0xF7, 0xF7, 0xF3, 0xF3,
0xF3, 0xFB, 0xFB, 0xF9, 0xF9, 0xFD, 0xFC, 0xFC, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x3F, 0x9F, 0x9F, 0xDF, 0xCF, 0xE7, 0xE7, 0xF3, 0xF3, 0xF9,
0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC,
0xFC, 0xFD, 0xFD, 0xF9, 0xF9, 0xFB, 0xFB, 0xF3, 0xF3, 0xF7, 0xF7, 0xE7, 0xE7, 0xE7, 0xEF, 0xEF,
0xEF, 0xEF, 0xCF, 0xCF, 0xCF, 0xD9, 0xD8, 0xDE, 0xDF, 0xDF, 0xDA, 0xD8, 0xDB, 0xDA, 0xD8, 0xDC,
0xDF, 0xDF, 0xDF, 0xDF, 0xD8, 0xD8, 0xDF, 0xDF, 0xDF, 0xDF, 0xDC, 0xD8, 0xCF, 0xCF, 0xCF, 0xEF,
0xEF, 0xEF, 0xEF, 0xE7, 0xE7, 0xE7, 0xF7, 0xF7, 0xF3, 0xF3, 0xFB, 0xFB, 0xF9, 0xF9, 0xFD, 0xFD,
0xFC, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
const unsigned char charset[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, // SPACE
    0x00, 0x00, 0x5F, 0x00, 0x00, // !
    0x00, 0x03, 0x00, 0x03, 0x00, // "
    0x14, 0x3E, 0x14, 0x3E, 0x14, // #
    0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
    0x43, 0x33, 0x08, 0x66, 0x61, // %
    0x36, 0x49, 0x55, 0x22, 0x50, // &
    0x00, 0x05, 0x03, 0x00, 0x00, // '
    0x00, 0x1C, 0x22, 0x41, 0x00, // (
    0x00, 0x41, 0x22, 0x1C, 0x00, // )
    0x14, 0x08, 0x3E, 0x08, 0x14, // *
    0x08, 0x08, 0x3E, 0x08, 0x08, // +
    0x00, 0x50, 0x30, 0x00, 0x00, // ,
    0x08, 0x08, 0x08, 0x08, 0x08, // -
    0x00, 0x60, 0x60, 0x00, 0x00, // .
    0x20, 0x10, 0x08, 0x04, 0x02, // /

    0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
    0x00, 0x04, 0x02, 0x7F, 0x00, // 1
    0x42, 0x61, 0x51, 0x49, 0x46, // 2
    0x22, 0x41, 0x49, 0x49, 0x36, // 3
    0x18, 0x14, 0x12, 0x7F, 0x10, // 4
    0x27, 0x45, 0x45, 0x45, 0x39, // 5
    0x3E, 0x49, 0x49, 0x49, 0x32, // 6
    0x01, 0x01, 0x71, 0x09, 0x07, // 7
    0x36, 0x49, 0x49, 0x49, 0x36, // 8
    0x26, 0x49, 0x49, 0x49, 0x3E, // 9
    0x00, 0x36, 0x36, 0x00, 0x00, // :
    0x00, 0x56, 0x36, 0x00, 0x00, // ;
    0x08, 0x14, 0x22, 0x41, 0x00, // <
    0x14, 0x14, 0x14, 0x14, 0x14, // =
    0x00, 0x41, 0x22, 0x14, 0x08, // >
    0x02, 0x01, 0x51, 0x09, 0x06, // ?

    0x3E, 0x41, 0x59, 0x55, 0x5E, // @
    0x7E, 0x09, 0x09, 0x09, 0x7E, // A
    0x7F, 0x49, 0x49, 0x49, 0x36, // B
    0x3E, 0x41, 0x41, 0x41, 0x22, // C
    0x7F, 0x41, 0x41, 0x41, 0x3E, // D
    0x7F, 0x49, 0x49, 0x49, 0x41, // E
    0x7F, 0x09, 0x09, 0x09, 0x01, // F
    0x3E, 0x41, 0x41, 0x49, 0x3A, // G
    0x7F, 0x08, 0x08, 0x08, 0x7F, // H
    0x00, 0x41, 0x7F, 0x41, 0x00, // I
    0x30, 0x40, 0x40, 0x40, 0x3F, // J
    0x7F, 0x08, 0x14, 0x22, 0x41, // K
    0x7F, 0x40, 0x40, 0x40, 0x40, // L
    0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
    0x7F, 0x02, 0x04, 0x08, 0x7F, // N
    0x3E, 0x41, 0x41, 0x41, 0x3E, // O

    0x7F, 0x09, 0x09, 0x09, 0x06, // P
    0x1E, 0x21, 0x21, 0x21, 0x5E, // Q
    0x7F, 0x09, 0x09, 0x09, 0x76, // R
    0x26, 0x49, 0x49, 0x49, 0x32, // S
    0x01, 0x01, 0x7F, 0x01, 0x01, // T
    0x3F, 0x40, 0x40, 0x40, 0x3F, // U
    0x1F, 0x20, 0x40, 0x20, 0x1F, // V
    0x7F, 0x20, 0x10, 0x20, 0x7F, // W
    0x41, 0x22, 0x1C, 0x22, 0x41, // X
    0x07, 0x08, 0x70, 0x08, 0x07, // Y
    0x61, 0x51, 0x49, 0x45, 0x43, // Z
    0x00, 0x7F, 0x41, 0x00, 0x00, // [
    0x02, 0x04, 0x08, 0x10, 0x20, // backslash
    0x00, 0x00, 0x41, 0x7F, 0x00, // ]
    0x04, 0x02, 0x01, 0x02, 0x04, // ^
    0x40, 0x40, 0x40, 0x40, 0x40, // _

    0x00, 0x01, 0x02, 0x04, 0x00, // `
    0x20, 0x54, 0x54, 0x54, 0x78, // a
    0x7F, 0x44, 0x44, 0x44, 0x38, // b
    0x38, 0x44, 0x44, 0x44, 0x44, // c
    0x38, 0x44, 0x44, 0x44, 0x7F, // d
    0x38, 0x54, 0x54, 0x54, 0x18, // e
    0x04, 0x04, 0x7E, 0x05, 0x05, // f
    0x08, 0x54, 0x54, 0x54, 0x3C, // g
    0x7F, 0x08, 0x04, 0x04, 0x78, // h
    0x00, 0x44, 0x7D, 0x40, 0x00, // i
    0x20, 0x40, 0x44, 0x3D, 0x00, // j
    0x7F, 0x10, 0x28, 0x44, 0x00, // k
    0x00, 0x41, 0x7F, 0x40, 0x00, // l
    0x7C, 0x04, 0x78, 0x04, 0x78, // m
    0x7C, 0x08, 0x04, 0x04, 0x78, // n
    0x38, 0x44, 0x44, 0x44, 0x38, // o

    0x7C, 0x14, 0x14, 0x14, 0x08, // p
    0x08, 0x14, 0x14, 0x14, 0x7C, // q
    0x00, 0x7C, 0x08, 0x04, 0x04, // r
    0x48, 0x54, 0x54, 0x54, 0x20, // s
    0x04, 0x04, 0x3F, 0x44, 0x44, // t
    0x3C, 0x40, 0x40, 0x20, 0x7C, // u
    0x1C, 0x20, 0x40, 0x20, 0x1C, // v
    0x3C, 0x40, 0x30, 0x40, 0x3C, // w
    0x44, 0x28, 0x10, 0x28, 0x44, // x
    0x0C, 0x50, 0x50, 0x50, 0x3C, // y
    0x44, 0x64, 0x54, 0x4C, 0x44, // z
    0x00, 0x08, 0x36, 0x41, 0x41, // {
    0x00, 0x00, 0x7F, 0x00, 0x00, // |
    0x41, 0x41, 0x36, 0x08, 0x00, // }
    0x02, 0x01, 0x02, 0x04, 0x02 // ~
};


void main(void) {
    ANSELB=0;
    TRISB=0xC0;
    
    ANSELD=0;
    TRISD=0xFF;
    RST=1;
    __delay_us(1);
    glcd_init();
    clr_scr();
    print_logo();
    while(1){
        __delay_ms(1000);
        __delay_ms(1000);
        dama(0);
        __delay_ms(1000);
        __delay_ms(1000);
        dama(1);
        __delay_ms(1000);
        __delay_ms(1000);
        place_text(0,0,"KOM4670 MCU-2 CLASS");
        __delay_ms(1000);
        __delay_ms(1000);
        place_text(2,7,"KOM4670 MCU-2 CLASS");
    }
}

void trig(){
    unsigned char k=0;
    EN=0;
    RW=0;
    EN=1;
    __delay_us(1);
    EN=0;
    __delay_us(1);
    TRISD=0xFF;
    RS=0;
    RW=1;
    EN=1;
    __delay_us(1);
    EN=0;
    __delay_us(1);
    while(RD7 && k<50){
        __delay_us(1);
        k++;
    }
    RW=0;
}

void glcd_init(){
    CS1=1;
    CS2=0;
    
    RS=0;
    RW=0;
    TRISD=0x00;
    LCD_DATA=0x3F;
    trig();
    
    RS=0;
    RW=0;
    TRISD=0x00;
    LCD_DATA=0x40;
    trig();
    
    CS1=0;
    CS2=1;
    
    RS=0;
    RW=0;
    TRISD=0x00;
    LCD_DATA=0x3F;
    trig();
    
    RS=0;
    RW=0;
    TRISD=0x00;
    LCD_DATA=0x40;
    trig();
}

void clr_scr(){
    unsigned int k=0;
    while (k<1024){
        CS2=(k & 0x0040)>0;
        CS1=!CS2;
        
    RS=0;
    RW=0;
    TRISD=0x00;
    LCD_DATA=(0xB8) + k/128;
    trig();
    
    RS=0;
    RW=0;
    TRISD=0x00;
    LCD_DATA=(0x40) + k%64;
    trig();
    
    RS=1;
    RW=0;
    TRISD=0x00;
    LCD_DATA=0x00;
    trig();
    
    k++;
    }
}

void print_logo(){
    unsigned int k=0;
    while (k<1024){
        CS2=(k & 0x0040)>0;
        CS1=!CS2;
        
    RS=0;
    RW=0;
    TRISD=0x00;
    LCD_DATA=(0xB8) + k/128;
    trig();
    
    RS=0;
    RW=0;
    TRISD=0x00;
    LCD_DATA=(0x40) + k%64;
    trig();
    
    RS=1;
    RW=0;
    TRISD=0x00;
    LCD_DATA=ytulogo[k];
    trig();
    
    k++;
    }
}

void dama(char theme){
    unsigned int k=0;
    while (k<1024){
        CS2=(k & 0x0040)>0;
        CS1=!CS2;
        
    RS=0;
    RW=0;
    TRISD=0x00;
    LCD_DATA=(0xB8) + k/128;
    trig();
    
    RS=0;
    RW=0;
    TRISD=0x00;
    LCD_DATA=(0x40) + k%64;
    trig();
    
    RS=1;
    RW=0;
    TRISD=0x00;
    LCD_DATA=(((k%16)<8)^((k/128)%2)^(theme==1))*0xFF;
    trig();
    
    k++;
    }
}

void place_text(unsigned int start_char, unsigned int page, unsigned char *s) {
    unsigned int k;
    unsigned k_start;
    unsigned int j = 0;
    k = (page * 128) + start_char * 6;
    k_start = k;
    while (s[j]) {
        CS2 = (k & 0x0040) > 0;
        CS1 = !CS2;

        RS = 0;
        RW = 0;
        TRISD = 0x00;
        LCD_DATA = (0xB8) + k / 128;
        trig();

        RS = 0;
        RW = 0;
        TRISD = 0x00;
        LCD_DATA = (0x40) + k % 64;
        trig();

        RS = 1;
        RW = 0;
        TRISD = 0x00;

        if ((k % 128) >= 126) {
            LCD_DATA = 0x00;
        } else if (((k % 128) % 6) == 0) {
            LCD_DATA = 0x00;
        } else {
            LCD_DATA = charset[(s[(((k - k_start) % 128) / 6)+((k - k_start) / 128)*21] - 0x20)*5 + (((k - k_start) % 128) % 6) - 1];
        }

        trig();
        k++;
        if ((k - k_start) % 6 == 0) {
            j++;
        }
    }
}
