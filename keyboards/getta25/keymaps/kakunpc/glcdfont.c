// 'loveLain', 128x32px

#include "progmem.h"

static const unsigned char font[] PROGMEM = {
0x00,0x00,0x00,0x00,0x00,0x00, // 00
0x3E,0x5B,0x4F,0x5B,0x3E,0x00, // 01
0x3E,0x6B,0x4F,0x6B,0x3E,0x00, // 02
0x1C,0x3E,0x7C,0x3E,0x1C,0x00, // 03
0x18,0x3C,0x7E,0x3C,0x18,0x00, // 04
0x1C,0x57,0x7D,0x57,0x1C,0x00, // 05
0x1C,0x5E,0x7F,0x5E,0x1C,0x00, // 06
0x00,0x18,0x3C,0x18,0x00,0x00, // 07
0xFF,0xE7,0xC3,0xE7,0xFF,0x00, // 08
0x00,0x18,0x24,0x18,0x00,0x00, // 09
0xFF,0xE7,0xDB,0xE7,0xFF,0x00, // 0A
0x30,0x48,0x3A,0x06,0x0E,0x00, // 0B
0x26,0x29,0x79,0x29,0x26,0x00, // 0C
0x40,0x7F,0x05,0x05,0x07,0x00, // 0D
0x40,0x7F,0x05,0x25,0x3F,0x00, // 0E
0x5A,0x3C,0xE7,0x3C,0x5A,0x00, // 0F
0x7F,0x3E,0x1C,0x1C,0x08,0x00, // 10
0x08,0x1C,0x1C,0x3E,0x7F,0x00, // 11
0x14,0x22,0x7F,0x22,0x14,0x00, // 12
0x5F,0x5F,0x00,0x5F,0x5F,0x00, // 13
0x06,0x09,0x7F,0x01,0x7F,0x00, // 14
0x00,0x66,0x89,0x95,0x6A,0x00, // 15
0x60,0x60,0x60,0x60,0x60,0x00, // 16
0x94,0xA2,0xFF,0xA2,0x94,0x00, // 17
0x08,0x04,0x7E,0x04,0x08,0x00, // 18
0x10,0x20,0x7E,0x20,0x10,0x00, // 19
0x08,0x08,0x2A,0x1C,0x08,0x00, // 1A
0x08,0x1C,0x2A,0x08,0x08,0x00, // 1B
0x1E,0x10,0x10,0x10,0x10,0x00, // 1C
0x0C,0x1E,0x0C,0x1E,0x0C,0x00, // 1D
0x30,0x38,0x3E,0x38,0x30,0x00, // 1E
0x06,0x0E,0x3E,0x0E,0x06,0x00, // 1F
0x00,0x00,0x00,0x00,0x00,0x00, // 20
0x00,0x00,0x5F,0x00,0x00,0x00, // 21 !
0x00,0x07,0x00,0x07,0x00,0x00, // 22 "
0x14,0x7F,0x14,0x7F,0x14,0x00, // 23 #
0x24,0x2A,0x7F,0x2A,0x12,0x00, // 24 $
0x23,0x13,0x08,0x64,0x62,0x00, // 25 %
0x36,0x49,0x56,0x20,0x50,0x00, // 26 &
0x00,0x08,0x07,0x03,0x00,0x00, // 27 '
0x00,0x1C,0x22,0x41,0x00,0x00, // 28 (
0x00,0x41,0x22,0x1C,0x00,0x00, // 29 )
0x2A,0x1C,0x7F,0x1C,0x2A,0x00, // 2A *
0x08,0x08,0x3E,0x08,0x08,0x00, // 2B +
0x00,0x80,0x70,0x30,0x00,0x00, // 2C ,
0x08,0x08,0x08,0x08,0x08,0x00, // 2D -
0x00,0x00,0x60,0x60,0x00,0x00, // 2E .
0x20,0x10,0x08,0x04,0x02,0x00, // 2F /
0x3E,0x51,0x49,0x45,0x3E,0x00, // 30 0
0x00,0x42,0x7F,0x40,0x00,0x00, // 31 1
0x72,0x49,0x49,0x49,0x46,0x00, // 32 2
0x21,0x41,0x49,0x4D,0x33,0x00, // 33 3
0x18,0x14,0x12,0x7F,0x10,0x00, // 34 4
0x27,0x45,0x45,0x45,0x39,0x00, // 35 5
0x3C,0x4A,0x49,0x49,0x31,0x00, // 36 6
0x41,0x21,0x11,0x09,0x07,0x00, // 37 7
0x36,0x49,0x49,0x49,0x36,0x00, // 38 8
0x46,0x49,0x49,0x29,0x1E,0x00, // 39 9
0x00,0x00,0x14,0x00,0x00,0x00, // 3A :
0x00,0x40,0x34,0x00,0x00,0x00, // 3B ;
0x00,0x08,0x14,0x22,0x41,0x00, // 3C <
0x14,0x14,0x14,0x14,0x14,0x00, // 3D =
0x00,0x41,0x22,0x14,0x08,0x00, // 3E >
0x02,0x01,0x59,0x09,0x06,0x00, // 3F ?
0x3E,0x41,0x5D,0x59,0x4E,0x00, // 40 @
0x7C,0x12,0x11,0x12,0x7C,0x00, // 41 A
0x7F,0x49,0x49,0x49,0x36,0x00, // 42 B
0x3E,0x41,0x41,0x41,0x22,0x00, // 43 C
0x7F,0x41,0x41,0x41,0x3E,0x00, // 44 D
0x7F,0x49,0x49,0x49,0x41,0x00, // 45 E
0x7F,0x09,0x09,0x09,0x01,0x00, // 46 F
0x3E,0x41,0x41,0x51,0x73,0x00, // 47 G
0x7F,0x08,0x08,0x08,0x7F,0x00, // 48 H
0x00,0x41,0x7F,0x41,0x00,0x00, // 49 I
0x20,0x40,0x41,0x3F,0x01,0x00, // 4A J
0x7F,0x08,0x14,0x22,0x41,0x00, // 4B K
0x7F,0x40,0x40,0x40,0x40,0x00, // 4C L
0x7F,0x02,0x1C,0x02,0x7F,0x00, // 4D M
0x7F,0x04,0x08,0x10,0x7F,0x00, // 4E N
0x3E,0x41,0x41,0x41,0x3E,0x00, // 4F O
0x7F,0x09,0x09,0x09,0x06,0x00, // 50 P
0x3E,0x41,0x51,0x21,0x5E,0x00, // 51 Q
0x7F,0x09,0x19,0x29,0x46,0x00, // 52 R
0x26,0x49,0x49,0x49,0x32,0x00, // 53 S
0x03,0x01,0x7F,0x01,0x03,0x00, // 54 T
0x3F,0x40,0x40,0x40,0x3F,0x00, // 55 U
0x1F,0x20,0x40,0x20,0x1F,0x00, // 56 V
0x3F,0x40,0x38,0x40,0x3F,0x00, // 57 W
0x63,0x14,0x08,0x14,0x63,0x00, // 58 X
0x03,0x04,0x78,0x04,0x03,0x00, // 59 Y
0x61,0x59,0x49,0x4D,0x43,0x00, // 5A Z
0x00,0x7F,0x41,0x41,0x41,0x00, // 5B [
0x02,0x04,0x08,0x10,0x20,0x00, // 5C \ .
0x00,0x41,0x41,0x41,0x7F,0x00, // 5D ]
0x04,0x02,0x01,0x02,0x04,0x00, // 5E ^
0x40,0x40,0x40,0x40,0x40,0x00, // 5F _
0x00,0x03,0x07,0x08,0x00,0x00, // 60 `
0x20,0x54,0x54,0x78,0x40,0x00, // 61 a
0x7F,0x28,0x44,0x44,0x38,0x00, // 62 b
0x38,0x44,0x44,0x44,0x28,0x00, // 63 c
0x38,0x44,0x44,0x28,0x7F,0x00, // 64 d
0x38,0x54,0x54,0x54,0x18,0x00, // 65 e
0x00,0x08,0x7E,0x09,0x02,0x00, // 66 f
0x18,0xA4,0xA4,0x9C,0x78,0x00, // 67 g
0x7F,0x08,0x04,0x04,0x78,0x00, // 68 h
0x00,0x44,0x7D,0x40,0x00,0x00, // 69 i
0x20,0x40,0x40,0x3D,0x00,0x00, // 6A j
0x7F,0x10,0x28,0x44,0x00,0x00, // 6B k
0x00,0x41,0x7F,0x40,0x00,0x00, // 6C l
0x7C,0x04,0x78,0x04,0x78,0x00, // 6D m
0x7C,0x08,0x04,0x04,0x78,0x00, // 6E n
0x38,0x44,0x44,0x44,0x38,0x00, // 6F o
0xFC,0x18,0x24,0x24,0x18,0x00, // 70 p
0x18,0x24,0x24,0x18,0xFC,0x00, // 71 q
0x7C,0x08,0x04,0x04,0x08,0x00, // 72 r
0x48,0x54,0x54,0x54,0x24,0x00, // 73 s
0x04,0x04,0x3F,0x44,0x24,0x00, // 74 t
0x3C,0x40,0x40,0x20,0x7C,0x00, // 75 u
0x1C,0x20,0x40,0x20,0x1C,0x00, // 76 v
0x3C,0x40,0x30,0x40,0x3C,0x00, // 77 w
0x44,0x28,0x10,0x28,0x44,0x00, // 78 x
0x4C,0x90,0x90,0x90,0x7C,0x00, // 79 y
0x44,0x64,0x54,0x4C,0x44,0x00, // 7A z
0x00,0x08,0x36,0x41,0x00,0x00, // 7B {
0x00,0x00,0x77,0x00,0x00,0x00, // 7C |
0x00,0x41,0x36,0x08,0x00,0x00, // 7D }
0x02,0x01,0x02,0x04,0x02,0x00, // 7E ~
0x3C,0x26,0x23,0x26,0x3C,0x00, // 7F
0xC7,0xC7,0xC7,0x00,0x00,0x00, // 80
0x00,0x20,0x60,0x60,0x60,0x60, // 81
0x60,0xE0,0x20,0x20,0x20,0x20, // 82
0x20,0x60,0x60,0x00,0x00,0x00, // 83
0x00,0x00,0x00,0xC7,0xC7,0xC7, // 84
0xC7,0xC7,0xC7,0x00,0x00,0x00, // 85
0x00,0xE0,0x70,0x50,0xFE,0x7A, // 86
0x02,0x00,0x20,0x60,0xE0,0xF3, // 87
0x3E,0x30,0x10,0x10,0x00,0x00, // 88
0x00,0x00,0x00,0xC7,0xC7,0xC7, // 89
0xC7,0xC7,0xC7,0x00,0x00,0x80, // 8A
0xC0,0xC3,0xA1,0x90,0x98,0x84, // 8B
0x83,0x00,0x00,0x1E,0x09,0x0C, // 8C
0x04,0xC4,0x7C,0x18,0x00,0x00, // 8D
0x00,0x00,0x00,0xC7,0xC7,0xC7, // 8E
0x00,0x00,0x00,0x00,0x00,0x00, // 8F
0x00,0x00,0x00,0x00,0x00,0x00, // 90
0x00,0x00,0x00,0x00,0x00,0x00, // 91
0x00,0x00,0x00,0x00,0x00,0x00, // 92
0x00,0x00,0x00,0x00,0x00,0x00, // 93
0x00,0x00,0x00,0x00,0x00,0xE0, // 94
0xF0,0xF0,0xF0,0xE0,0xEC,0xEE, // 95
0xF7,0xF3,0x70,0x20,0x00,0x7C, // 96
0x7C,0x7C,0x7E,0x00,0x7E,0x7E, // 97
0x7E,0x7F,0x7F,0x7F,0x00,0x00, // 98
0x80,0xC0,0xE0,0x7E,0x5B,0x4F, // 99
0x5B,0xFE,0xC0,0x00,0x00,0xC0, // 9A
0x00,0xDC,0xD7,0xDE,0xDE,0xDE, // 9B
0xD7,0xDC,0x00,0xC0,0x00,0x00, // 9C
0x00,0x00,0x00,0x00,0x00,0x00, // 9D
0x00,0x00,0x00,0x00,0x00,0x00, // 9E
0x00,0x00,0x00,0x00,0x00,0xFF, // 9F
0x71,0x71,0x71,0x00,0x00,0x00, // A0
0x00,0x00,0x00,0x00,0x00,0x00, // A1 ?
0xC0,0xFF,0x00,0x08,0x0E,0x0E, // A2 ?
0x0C,0x00,0x00,0x00,0x00,0x00, // A3 ?
0x00,0x00,0x00,0x71,0x71,0x71, // A4 ?
0x71,0x71,0x71,0x00,0x00,0x08, // A5 ?
0x08,0x09,0x18,0x25,0x61,0x31, // A6 ?
0x1F,0x06,0x04,0x06,0x13,0x32, // A7 §
0x32,0x62,0x02,0x06,0x0C,0x08, // A8 ¨
0x00,0x00,0x00,0x71,0x71,0x71, // A9 ?
0x71,0x71,0x71,0x00,0x00,0x00, // AA ?
0x00,0x00,0x00,0x00,0x00,0x00, // AB ?
0x09,0x11,0x18,0x08,0x0C,0x06, // AC ?
0x03,0x00,0x00,0x00,0x00,0x00, // AD ?
0x00,0x00,0x00,0x71,0x71,0x71, // AE ?
0x00,0x00,0x00,0x00,0x00,0x00, // AF ?
0x00,0x00,0x00,0x00,0x00,0x00, // B0 °
0x00,0x00,0x00,0x00,0x00,0x00, // B1 ±
0x00,0x00,0x00,0x00,0x00,0x00, // B2 ?
0x00,0x00,0x00,0x00,0x00,0x00, // B3 ?
0x00,0x00,0x00,0x00,0x00,0x0F, // B4 ´
0x1F,0x3F,0x7F,0x7F,0x7F,0x7F, // B5 ?
0x7F,0x3F,0x1E,0x0C,0x00,0x1F, // B6 ¶
0x1F,0x1F,0x3F,0x00,0x3F,0x3F, // B7 ?
0x3F,0x7F,0x7F,0x7F,0x00,0x30, // B8 ?
0x7B,0x7F,0x78,0x30,0x20,0x20, // B9 ?
0x30,0x78,0x7F,0x3B,0x00,0x03, // BA ?
0x00,0x0F,0x7F,0x0F,0x0F,0x0F, // BB ?
0x7F,0x0F,0x00,0x03,0x00,0x00, // BC ?
0x00,0x00,0x00,0x00,0x00,0x00, // BD ?
0x00,0x00,0x00,0x00,0x00,0x00, // BE ?
0x00,0x00,0x00,0x00,0x00,0xFF, // BF ?
0x1C,0x1C,0x1C,0x00,0x00,0x00, // C0 ?
0x00,0x00,0x00,0x00,0x00,0x00, // C1 ?
0x07,0x0F,0x00,0x00,0x00,0x00, // C2 ?
0x00,0x00,0x00,0x00,0x00,0x00, // C3 ?
0x00,0x00,0x00,0x1C,0x1C,0x1C, // C4 ?
0x1C,0x1C,0x1C,0x00,0x00,0x00, // C5 ?
0x00,0x00,0x80,0x80,0xC0,0x40, // C6 ?
0x80,0x00,0x00,0x00,0xC0,0x40, // C7 ?
0x40,0xC0,0xC0,0xC0,0x00,0x00, // C8 ?
0x00,0x00,0x00,0x1C,0x1C,0x1C, // C9 ?
0x1C,0x1C,0x1C,0x00,0x00,0x00, // CA ?
0x00,0x00,0x00,0x00,0x00,0x00, // CB ?
0x00,0x00,0x00,0x00,0x00,0x00, // CC ?
0x00,0x00,0x00,0x00,0x00,0x00, // CD ?
0x00,0x00,0x00,0x1C,0x1C,0x1C, // CE ?
0x00,0x00,0x00,0x00,0x00,0x00, // CF ?
0x00,0x00,0x00,0x00,0x00,0x00, // D0 ?
0x00,0x00,0x00,0x00,0x00,0x00, // D1 ?
0x00,0x00,0x00,0x00,0x00,0x00, // D2 ?
0x00,0x00,0x00,0x00,0x00,0x00, // D3 ?
0x00,0x00,0x00,0x00,0x00,0x00, // D4 ?
0x00,0x00,0x00,0x00,0x00,0x00, // D5 ?
0x00,0x00,0x00,0x00,0x00,0x00, // D6 ?
0x00,0x00,0x00,0x00,0x00,0x00, // D7 ×
0x00,0x00,0x00,0x00,0x00,0x00, // D8 ?
0x00,0x00,0x00,0x00,0x00,0x00, // D9 ?
0x00,0x00,0x00,0x00,0x00,0x00, // DA ?
0x00,0x00,0x00,0x00,0x00,0x00, // DB ?
0x00,0x00,0x00,0x00,0x00,0x00, // DC ?
0x00,0x00,0x00,0x00,0x00,0x00, // DD ?
0x00,0x00,0x00,0x00,0x00,0x00, // DE ?
0x00,0x00,0x00,0x00,0x00,0xFF, // DF ?
};
static const unsigned int  fontLen = 512;
