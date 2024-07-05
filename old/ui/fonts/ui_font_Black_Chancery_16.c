/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --font C:\Users\brett\OneDrive\Documents\Projects\DnDevice\SquareLine\All Screens\assets\font\Black Chancery\BLKCHCRY.TTF -o C:\Users\brett\OneDrive\Documents\Projects\DnDevice\SquareLine\All Screens\assets\font\Black Chancery\ui_font_Black_Chancery_16.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_BLACK_CHANCERY_16
#define UI_FONT_BLACK_CHANCERY_16 1
#endif

#if UI_FONT_BLACK_CHANCERY_16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x8, 0x8c, 0x66, 0x31, 0x8c, 0x40, 0x0, 0xc6,
    0x0,

    /* U+0022 "\"" */
    0x99, 0x90,

    /* U+0023 "#" */
    0x33, 0xd5, 0xe2, 0x0,

    /* U+0024 "$" */
    0x21, 0x1d, 0x18, 0x20, 0xc1, 0xc, 0x5c, 0x42,
    0x0,

    /* U+0025 "%" */
    0xe3, 0x4a, 0xb7, 0x41, 0x5, 0xd2, 0xe5, 0x8e,

    /* U+0026 "&" */
    0x30, 0x4, 0x80, 0x48, 0x5, 0x0, 0x62, 0x7,
    0x18, 0x98, 0x88, 0xc8, 0x86, 0x88, 0x30, 0xc3,
    0x87, 0xc2,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x6a, 0xaa, 0xa4,

    /* U+0029 ")" */
    0xa5, 0x55, 0x60,

    /* U+002A "*" */
    0x0, 0x4a, 0x2c, 0xf7, 0x28, 0x3c, 0x4a, 0x8,

    /* U+002B "+" */
    0x10, 0x10, 0x40, 0xae, 0xe2, 0x8c, 0x8,

    /* U+002C "," */
    0x34,

    /* U+002D "-" */
    0x7c,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x4, 0x20, 0x84, 0x10, 0x82, 0x10, 0x41, 0x8,
    0x20,

    /* U+0030 "0" */
    0x39, 0x38, 0x61, 0x87, 0x27, 0x0,

    /* U+0031 "1" */
    0x59, 0x24, 0x90,

    /* U+0032 "2" */
    0x39, 0x14, 0x42, 0x11, 0x87, 0xc0,

    /* U+0033 "3" */
    0x3c, 0x21, 0x6, 0xc, 0x10, 0x41, 0x5, 0x27,
    0x0,

    /* U+0034 "4" */
    0x8, 0x30, 0xa1, 0x44, 0x89, 0x22, 0x7e, 0x8,
    0x10, 0x20,

    /* U+0035 "5" */
    0x3c, 0x81, 0x3, 0xc0, 0x40, 0x60, 0xc1, 0x64,
    0x78,

    /* U+0036 "6" */
    0x10, 0x41, 0x2, 0x8, 0x17, 0xb1, 0xc1, 0x82,
    0x84, 0xf0,

    /* U+0037 "7" */
    0x7f, 0x82, 0x4, 0x8, 0x10, 0x20, 0x20, 0x20,
    0x30, 0x10,

    /* U+0038 "8" */
    0x32, 0x52, 0xe3, 0x2a, 0x31, 0xcb, 0x80,

    /* U+0039 "9" */
    0x7a, 0x38, 0x61, 0xc5, 0x13, 0x42, 0x8, 0x42,
    0x0,

    /* U+003A ":" */
    0x4d, 0x4, 0xc0,

    /* U+003B ";" */
    0x58, 0xc, 0x90,

    /* U+003C "<" */
    0x24, 0x84, 0x20,

    /* U+003D "=" */
    0x78, 0x7, 0x80,

    /* U+003E ">" */
    0x42, 0x12, 0x40,

    /* U+003F "?" */
    0x3e, 0x47, 0x83, 0x83, 0x83, 0x83, 0x46, 0xc,
    0x18, 0x10, 0x24, 0x24, 0x38, 0x0, 0x0, 0x38,
    0x10,

    /* U+0040 "@" */
    0x1f, 0x19, 0xe5, 0xae, 0x49, 0xa6, 0x69, 0x1b,
    0xc9, 0xdc, 0x60, 0x87, 0xc0,

    /* U+0041 "A" */
    0x0, 0x0, 0x0, 0x80, 0x0, 0x80, 0x0, 0xc0,
    0x1, 0xc0, 0x1, 0xc0, 0x2, 0xc0, 0x4, 0x60,
    0x3c, 0x60, 0xa, 0x60, 0x11, 0xf0, 0x20, 0x70,
    0xc0, 0x38, 0x0, 0x18, 0x0, 0xc, 0x0, 0x3,

    /* U+0042 "B" */
    0x1f, 0xe1, 0x84, 0x44, 0x10, 0xa0, 0xc2, 0x83,
    0xa, 0xc, 0x2c, 0x33, 0x10, 0xc6, 0x33, 0x8,
    0xc, 0x30, 0x30, 0xc0, 0xc3, 0x3, 0x1c, 0x8,
    0xe0, 0xfe, 0x0,

    /* U+0043 "C" */
    0xf, 0xc6, 0x19, 0x80, 0xa0, 0xc, 0x1, 0x80,
    0x30, 0x6, 0x0, 0xc0, 0x1c, 0x1, 0x80, 0x38,
    0x13, 0x84, 0x1f, 0x0,

    /* U+0044 "D" */
    0x1f, 0xc0, 0xc4, 0x62, 0x8, 0x74, 0x30, 0x68,
    0x60, 0xf0, 0xc0, 0xe1, 0x81, 0xa3, 0x3, 0x16,
    0x6, 0xc, 0xc, 0x18, 0x18, 0x30, 0x60, 0x60,
    0xc2, 0x87, 0x3, 0xf8, 0x0,

    /* U+0045 "E" */
    0x1f, 0xf3, 0x20, 0xa3, 0x3, 0x18, 0x8, 0xce,
    0x46, 0x92, 0x38, 0x19, 0xc0, 0x4c, 0x1, 0x60,
    0x3, 0x2, 0x18, 0x31, 0xff, 0x0,

    /* U+0046 "F" */
    0x1f, 0xfe, 0x63, 0x0, 0x81, 0x80, 0x80, 0xc0,
    0x0, 0x60, 0x0, 0x64, 0x1f, 0xfc, 0x20, 0x60,
    0x40, 0x60, 0x40, 0x60, 0x40, 0x40, 0x60, 0xc0,
    0x31, 0x80, 0x1f, 0x0,

    /* U+0047 "G" */
    0xf, 0x81, 0x87, 0x18, 0x10, 0x80, 0xc, 0x0,
    0x60, 0x3, 0x0, 0x18, 0xff, 0xc8, 0x27, 0x1,
    0x18, 0x8, 0xe0, 0x43, 0x84, 0xf, 0xc0,

    /* U+0048 "H" */
    0x3e, 0x3c, 0x98, 0x32, 0x30, 0x64, 0x60, 0xc8,
    0xcf, 0xf9, 0xa3, 0x13, 0x86, 0x6, 0xc, 0xc,
    0x18, 0x18, 0x30, 0x78, 0xf0,

    /* U+0049 "I" */
    0x3f, 0xa1, 0xa0, 0xd0, 0x68, 0x34, 0x1b, 0x2c,
    0xe6, 0x3, 0x1, 0x80, 0xc0, 0xf0,

    /* U+004A "J" */
    0xf, 0xe2, 0x18, 0x83, 0x10, 0x62, 0xc, 0x41,
    0x8c, 0xb0, 0xe6, 0x0, 0xc0, 0x19, 0x3, 0x40,
    0x68, 0xd, 0x3, 0x30, 0x63, 0xf8, 0x10, 0x0,

    /* U+004B "K" */
    0x3f, 0xfc, 0x0, 0x86, 0x20, 0x2, 0xc, 0x80,
    0x4, 0x1a, 0x0, 0x8, 0x38, 0x0, 0x10, 0x70,
    0x0, 0x30, 0xf0, 0x0, 0x21, 0xb0, 0x0, 0x23,
    0x30, 0x0, 0x6, 0x30, 0x0, 0xc, 0x30, 0x0,
    0x7c, 0x20, 0x0, 0x0, 0x20, 0x20, 0x0, 0x20,
    0x40, 0x0, 0x20, 0x80, 0x0, 0x3e, 0x0, 0x0,
    0x0,

    /* U+004C "L" */
    0x3f, 0xc0, 0x10, 0xc0, 0x8, 0x30, 0x2, 0xc,
    0x0, 0x83, 0x0, 0x20, 0xc0, 0xc, 0xb0, 0x1,
    0xcc, 0x0, 0x3, 0x0, 0x0, 0xc0, 0x0, 0x30,
    0x0, 0x7e, 0x0, 0x20, 0xc0, 0xc0, 0x18, 0x10,
    0x3, 0x84, 0x0, 0x3e,

    /* U+004D "M" */
    0x1f, 0x3, 0x4, 0x30, 0x81, 0x6, 0x20, 0x40,
    0xe4, 0x8, 0x1d, 0x81, 0x3, 0xd0, 0x20, 0x5a,
    0x6, 0x13, 0x60, 0x62, 0x6c, 0x0, 0x48, 0x80,
    0x8, 0x18, 0x2, 0x3, 0x88, 0xc0, 0x31, 0xf0,
    0x7, 0x1c, 0x0, 0x30,

    /* U+004E "N" */
    0x3e, 0x38, 0x11, 0x84, 0x8, 0x71, 0x2, 0x16,
    0x40, 0x84, 0x90, 0x21, 0x24, 0x4, 0x45, 0x1,
    0x91, 0x40, 0x4, 0x70, 0x1, 0xc, 0x0, 0x41,
    0x0, 0x78, 0x60, 0x0, 0x8, 0x0, 0x3, 0x0,
    0x0, 0x3c,

    /* U+004F "O" */
    0xf, 0xc1, 0x87, 0x18, 0x1c, 0x80, 0x6c, 0x3,
    0xe0, 0xf, 0x0, 0x78, 0x3, 0xc0, 0x1f, 0x0,
    0xf8, 0x4, 0xe0, 0x63, 0x86, 0xf, 0xc0,

    /* U+0050 "P" */
    0x1f, 0xc3, 0x11, 0x91, 0x85, 0xc, 0x18, 0x60,
    0xc3, 0x6, 0x18, 0x28, 0xc2, 0x66, 0xe0, 0x30,
    0x1, 0x80, 0x1e, 0x1, 0x80, 0x18, 0x0, 0x80,
    0x4, 0x0,

    /* U+0051 "Q" */
    0xf, 0xc0, 0x18, 0x70, 0x18, 0x1c, 0x8, 0x7,
    0xc, 0x3, 0x86, 0x0, 0xc3, 0x0, 0x61, 0x80,
    0x30, 0xce, 0x18, 0x70, 0xc8, 0x18, 0x24, 0xe,
    0x1c, 0x3, 0x86, 0x0, 0xfd, 0x0, 0x0, 0xc0,
    0x0, 0x3f, 0x0, 0x4, 0x0,

    /* U+0052 "R" */
    0x1f, 0xf0, 0x3, 0x11, 0xc0, 0x31, 0x83, 0x1,
    0xc, 0x18, 0x8, 0x60, 0xc0, 0x43, 0x6, 0x2,
    0x18, 0x60, 0x8, 0xde, 0x0, 0x26, 0xc0, 0x0,
    0x33, 0x0, 0x1, 0x98, 0x0, 0x1e, 0x60, 0x0,
    0x1, 0x80, 0x0, 0xe, 0x0, 0x0, 0x38, 0x0,
    0x0, 0x7f, 0x0, 0x0, 0x80,

    /* U+0053 "S" */
    0x1f, 0xc2, 0xc, 0x40, 0x44, 0x2, 0x60, 0x3,
    0x80, 0x1f, 0x80, 0x3e, 0x80, 0x78, 0x1, 0x80,
    0x1c, 0x1, 0xe0, 0x27, 0x2, 0x1f, 0xc0,

    /* U+0054 "T" */
    0x1f, 0xff, 0x10, 0xc0, 0x10, 0x30, 0x0, 0xc,
    0x0, 0x2, 0x0, 0xe1, 0x80, 0x98, 0xc0, 0x84,
    0x60, 0x42, 0x30, 0x22, 0x18, 0x10, 0x18, 0x4,
    0xc, 0x3, 0xc, 0x0, 0xfc, 0x0,

    /* U+0055 "U" */
    0x1f, 0x8e, 0x61, 0xc, 0x43, 0xc, 0x82, 0xc,
    0x86, 0xc, 0x84, 0xc, 0x8c, 0xc, 0x4c, 0xc,
    0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xe, 0x1c,
    0x7, 0xe2, 0x3, 0xc0,

    /* U+0056 "V" */
    0x1f, 0x80, 0xc2, 0x33, 0xc, 0xf4, 0x10, 0x68,
    0x60, 0xf0, 0xc0, 0xf1, 0x81, 0xb3, 0x3, 0x6,
    0x6, 0xc, 0x8, 0x1c, 0x30, 0x18, 0x40, 0x39,
    0x0, 0x3c, 0x0,

    /* U+0057 "W" */
    0x3f, 0x38, 0xf2, 0x30, 0xc3, 0x21, 0xc6, 0x11,
    0x6, 0x18, 0x88, 0x30, 0xc4, 0x42, 0xce, 0x41,
    0x16, 0x9a, 0x7, 0x3c, 0xd0, 0x0, 0xe7, 0x0,
    0x7, 0x18, 0x0, 0x10, 0xc0, 0x0, 0x84, 0x0,
    0x4, 0x0, 0x0,

    /* U+0058 "X" */
    0x3e, 0x18, 0x4, 0x72, 0x0, 0x83, 0xa0, 0x8,
    0x1c, 0x0, 0x81, 0xc0, 0x8, 0xc, 0x0, 0x80,
    0xc0, 0x4, 0x3c, 0x0, 0x2, 0x60, 0x0, 0x46,
    0x0, 0x4, 0x70, 0x0, 0xc3, 0x80, 0x0, 0x1c,
    0x0, 0x0, 0xe0, 0x0, 0x7, 0xe0,

    /* U+0059 "Y" */
    0x78, 0x3c, 0x10, 0x42, 0x8, 0x82, 0x5, 0x0,
    0x5, 0x0, 0x2, 0x0, 0x2, 0x0, 0x2, 0x0,
    0x2, 0x0, 0x2, 0x0, 0x2, 0x0, 0x7, 0x0,

    /* U+005A "Z" */
    0x3f, 0xec, 0xc, 0x1, 0x80, 0x30, 0x4, 0x0,
    0xf0, 0x0, 0xc0, 0x6, 0x3c, 0x34, 0x63, 0x83,
    0x38, 0x13, 0x80, 0x78, 0x6, 0x40, 0xc7, 0xf8,
    0x8, 0x0,

    /* U+005B "[" */
    0xfb, 0x6d, 0xb6, 0xdb, 0x80,

    /* U+005C "\\" */
    0x2, 0x8, 0x10, 0x40, 0x82, 0x4, 0x10, 0x20,
    0x80,

    /* U+005D "]" */
    0xed, 0xb6, 0xdb, 0x6f, 0x80,

    /* U+005E "^" */
    0x0, 0xc4, 0x80,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0x34,

    /* U+0061 "a" */
    0x39, 0x28, 0xa2, 0x8b, 0xe4, 0xc0,

    /* U+0062 "b" */
    0x74, 0x21, 0x9, 0xdf, 0x31, 0x8c, 0x5c,

    /* U+0063 "c" */
    0x39, 0x38, 0x20, 0x83, 0x7, 0x80,

    /* U+0064 "d" */
    0x6, 0x10, 0x20, 0x43, 0x89, 0x22, 0x44, 0x89,
    0xf1, 0x30,

    /* U+0065 "e" */
    0x3a, 0x69, 0x28, 0xc3, 0x7, 0x80,

    /* U+0066 "f" */
    0xe, 0x10, 0x10, 0x10, 0x38, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xe0,

    /* U+0067 "g" */
    0x3a, 0x63, 0x18, 0xff, 0xa9, 0x8c, 0x65, 0xe4,
    0x0,

    /* U+0068 "h" */
    0x72, 0x8, 0x20, 0x9a, 0xec, 0xa2, 0x8a, 0x28,
    0xc0,

    /* U+0069 "i" */
    0x66, 0x0, 0x62, 0x22, 0x22, 0x20,

    /* U+006A "j" */
    0xc, 0x30, 0x0, 0xc, 0x10, 0x41, 0x4, 0x10,
    0x41, 0x4, 0x18, 0xbc, 0x0,

    /* U+006B "k" */
    0x62, 0x8, 0x20, 0x9a, 0x8c, 0x38, 0xb2, 0x49,
    0x80,

    /* U+006C "l" */
    0x72, 0x49, 0x24, 0x93, 0x0,

    /* U+006D "m" */
    0x4c, 0xce, 0xe9, 0x11, 0x22, 0x24, 0x44, 0x88,
    0x91, 0x18,

    /* U+006E "n" */
    0x4c, 0xe9, 0x12, 0x24, 0x48, 0x91, 0x80,

    /* U+006F "o" */
    0x39, 0x38, 0x61, 0x87, 0x27, 0x0,

    /* U+0070 "p" */
    0x59, 0x94, 0x51, 0x45, 0x27, 0x10, 0x41, 0x4,
    0x20,

    /* U+0071 "q" */
    0x39, 0x28, 0xa2, 0x8b, 0xe4, 0x82, 0x8, 0x20,
    0xc0,

    /* U+0072 "r" */
    0x4f, 0x76, 0x90, 0x41, 0x4, 0x0,

    /* U+0073 "s" */
    0xfc, 0x30, 0xe1, 0xc7, 0xc0,

    /* U+0074 "t" */
    0x4, 0x4e, 0x44, 0x44, 0x46,

    /* U+0075 "u" */
    0xc4, 0x44, 0x44, 0x44, 0x44, 0x5c, 0x76,

    /* U+0076 "v" */
    0x66, 0xe6, 0x32, 0x12, 0x1c, 0x8, 0x8,

    /* U+0077 "w" */
    0x0, 0x6, 0x33, 0x23, 0x13, 0x3a, 0x15, 0xa1,
    0xcc, 0x8, 0xc0, 0x8c,

    /* U+0078 "x" */
    0xe4, 0x38, 0x30, 0x10, 0x38, 0x48, 0x4e,

    /* U+0079 "y" */
    0x26, 0x73, 0x13, 0x1a, 0xa, 0xc, 0x8, 0x8,
    0x10, 0x10, 0x10, 0x1f, 0x0,

    /* U+007A "z" */
    0x7e, 0x88, 0x23, 0xc4, 0x8, 0x5f, 0x80,

    /* U+007B "{" */
    0x24, 0x44, 0x44, 0xc4, 0x44, 0x44, 0x20,

    /* U+007C "|" */
    0xff, 0xfe,

    /* U+007D "}" */
    0x44, 0x22, 0x22, 0x32, 0x22, 0x24, 0x40,

    /* U+007E "~" */
    0xe0, 0x60
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 64, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 93, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 10, .adv_w = 83, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 12, .adv_w = 114, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 16, .adv_w = 100, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 25, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 166, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 51, .adv_w = 32, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 52, .adv_w = 59, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 55, .adv_w = 59, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 58, .adv_w = 147, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 66, .adv_w = 144, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 61, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 74, .adv_w = 150, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 75, .adv_w = 61, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 76, .adv_w = 119, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 85, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 72, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 109, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 109, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 109, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 119, .adv_w = 119, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 128, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 123, .box_w = 8, .box_h = 10, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 148, .adv_w = 102, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 115, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 164, .adv_w = 61, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 167, .adv_w = 61, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 170, .adv_w = 109, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 173, .adv_w = 106, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 176, .adv_w = 93, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 179, .adv_w = 152, .box_w = 8, .box_h = 17, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 196, .adv_w = 168, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 209, .adv_w = 201, .box_w = 16, .box_h = 16, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 241, .adv_w = 234, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 268, .adv_w = 186, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 288, .adv_w = 256, .box_w = 15, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 317, .adv_w = 217, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 339, .adv_w = 235, .box_w = 16, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 367, .adv_w = 217, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 390, .adv_w = 233, .box_w = 15, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 149, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 425, .adv_w = 172, .box_w = 11, .box_h = 17, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 449, .adv_w = 225, .box_w = 23, .box_h = 17, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 498, .adv_w = 148, .box_w = 18, .box_h = 16, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 534, .adv_w = 249, .box_w = 19, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 570, .adv_w = 210, .box_w = 18, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 604, .adv_w = 226, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 627, .adv_w = 216, .box_w = 13, .box_h = 16, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 653, .adv_w = 233, .box_w = 17, .box_h = 17, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 690, .adv_w = 236, .box_w = 21, .box_h = 17, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 735, .adv_w = 202, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 758, .adv_w = 192, .box_w = 17, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 788, .adv_w = 236, .box_w = 16, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 816, .adv_w = 246, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 843, .adv_w = 290, .box_w = 21, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 878, .adv_w = 207, .box_w = 20, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 916, .adv_w = 107, .box_w = 16, .box_h = 12, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 940, .adv_w = 201, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 966, .adv_w = 67, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 971, .adv_w = 116, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 980, .adv_w = 70, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 985, .adv_w = 102, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 988, .adv_w = 116, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 989, .adv_w = 52, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 990, .adv_w = 118, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 996, .adv_w = 95, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1003, .adv_w = 101, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1009, .adv_w = 117, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1019, .adv_w = 106, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1025, .adv_w = 73, .box_w = 8, .box_h = 16, .ofs_x = -2, .ofs_y = -5},
    {.bitmap_index = 1041, .adv_w = 105, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 1050, .adv_w = 110, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1059, .adv_w = 67, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1065, .adv_w = 50, .box_w = 6, .box_h = 17, .ofs_x = -3, .ofs_y = -6},
    {.bitmap_index = 1078, .adv_w = 110, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1087, .adv_w = 56, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1092, .adv_w = 174, .box_w = 11, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1102, .adv_w = 114, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1109, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1115, .adv_w = 111, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1124, .adv_w = 109, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1133, .adv_w = 103, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1139, .adv_w = 84, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1144, .adv_w = 68, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1149, .adv_w = 125, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1156, .adv_w = 121, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1163, .adv_w = 196, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1175, .adv_w = 126, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1182, .adv_w = 120, .box_w = 8, .box_h = 13, .ofs_x = -1, .ofs_y = -6},
    {.bitmap_index = 1195, .adv_w = 105, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1202, .adv_w = 90, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1209, .adv_w = 47, .box_w = 1, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1211, .adv_w = 90, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1218, .adv_w = 117, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 7}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    16, 17,
    16, 18,
    16, 19,
    16, 20,
    16, 21,
    16, 22,
    16, 23,
    16, 24,
    16, 25,
    16, 26,
    17, 16,
    18, 16,
    19, 16,
    23, 16,
    24, 16,
    34, 15,
    34, 34,
    34, 35,
    34, 38,
    34, 39,
    34, 40,
    34, 41,
    34, 42,
    34, 43,
    34, 44,
    34, 46,
    34, 47,
    34, 49,
    34, 51,
    34, 52,
    34, 53,
    34, 54,
    34, 55,
    34, 56,
    34, 57,
    34, 58,
    34, 59,
    34, 71,
    34, 72,
    34, 74,
    34, 75,
    34, 80,
    34, 81,
    34, 87,
    34, 88,
    34, 90,
    35, 15,
    35, 74,
    35, 75,
    35, 76,
    35, 78,
    35, 80,
    35, 87,
    35, 88,
    35, 90,
    36, 15,
    36, 68,
    36, 69,
    36, 70,
    36, 71,
    36, 74,
    36, 75,
    36, 76,
    36, 77,
    36, 80,
    36, 85,
    36, 86,
    36, 87,
    36, 88,
    36, 89,
    36, 90,
    37, 15,
    37, 78,
    37, 79,
    37, 81,
    37, 83,
    37, 86,
    37, 87,
    37, 88,
    37, 89,
    37, 90,
    38, 15,
    38, 71,
    38, 74,
    38, 75,
    38, 78,
    38, 81,
    38, 83,
    38, 84,
    38, 86,
    38, 87,
    38, 88,
    38, 89,
    38, 90,
    38, 91,
    39, 15,
    39, 66,
    39, 67,
    39, 68,
    39, 69,
    39, 70,
    39, 72,
    39, 73,
    39, 74,
    39, 80,
    39, 81,
    39, 82,
    39, 83,
    39, 85,
    39, 86,
    39, 87,
    39, 88,
    39, 89,
    39, 90,
    40, 15,
    40, 71,
    40, 73,
    40, 74,
    40, 76,
    40, 77,
    40, 84,
    40, 85,
    40, 86,
    40, 87,
    40, 88,
    40, 89,
    40, 90,
    40, 91,
    41, 15,
    41, 66,
    41, 67,
    41, 68,
    41, 69,
    41, 70,
    41, 71,
    41, 72,
    41, 73,
    41, 74,
    41, 75,
    41, 76,
    41, 77,
    41, 78,
    41, 79,
    41, 80,
    41, 81,
    41, 82,
    41, 83,
    41, 84,
    41, 86,
    41, 87,
    41, 88,
    41, 89,
    41, 90,
    42, 15,
    42, 67,
    42, 68,
    42, 69,
    42, 70,
    42, 71,
    42, 73,
    42, 76,
    42, 78,
    42, 79,
    42, 80,
    42, 81,
    42, 83,
    42, 87,
    42, 88,
    42, 89,
    42, 90,
    42, 91,
    43, 15,
    43, 75,
    43, 78,
    43, 79,
    43, 81,
    43, 83,
    43, 86,
    43, 87,
    43, 88,
    43, 89,
    43, 90,
    43, 91,
    44, 15,
    44, 34,
    44, 35,
    44, 37,
    44, 38,
    44, 39,
    44, 41,
    44, 42,
    44, 43,
    44, 44,
    44, 45,
    44, 46,
    44, 47,
    44, 48,
    44, 49,
    44, 51,
    44, 52,
    44, 53,
    44, 54,
    44, 55,
    44, 56,
    44, 57,
    44, 58,
    44, 59,
    44, 80,
    44, 85,
    44, 86,
    44, 87,
    44, 88,
    44, 90,
    44, 91,
    45, 15,
    45, 34,
    45, 39,
    45, 45,
    45, 46,
    45, 52,
    45, 53,
    45, 58,
    45, 59,
    45, 73,
    45, 76,
    45, 77,
    45, 78,
    45, 79,
    45, 81,
    45, 83,
    45, 86,
    45, 87,
    45, 88,
    45, 89,
    45, 90,
    46, 15,
    46, 34,
    46, 35,
    46, 36,
    46, 37,
    46, 39,
    46, 40,
    46, 41,
    46, 43,
    46, 44,
    46, 45,
    46, 46,
    46, 47,
    46, 48,
    46, 49,
    46, 50,
    46, 51,
    46, 52,
    46, 53,
    46, 54,
    46, 55,
    46, 56,
    46, 57,
    46, 58,
    46, 59,
    46, 67,
    46, 71,
    46, 73,
    46, 74,
    46, 75,
    46, 76,
    46, 77,
    46, 78,
    46, 79,
    46, 81,
    46, 83,
    46, 84,
    46, 87,
    46, 88,
    46, 89,
    46, 90,
    46, 91,
    47, 15,
    47, 80,
    47, 82,
    47, 84,
    48, 75,
    48, 78,
    48, 79,
    48, 81,
    48, 83,
    48, 86,
    48, 87,
    48, 88,
    48, 89,
    48, 90,
    49, 15,
    49, 67,
    49, 71,
    49, 72,
    49, 73,
    49, 74,
    49, 75,
    49, 76,
    49, 77,
    49, 78,
    49, 79,
    49, 80,
    49, 81,
    49, 82,
    49, 83,
    49, 84,
    49, 85,
    49, 86,
    49, 87,
    49, 88,
    49, 89,
    49, 90,
    50, 15,
    50, 66,
    50, 70,
    50, 74,
    50, 80,
    51, 15,
    51, 66,
    51, 68,
    51, 69,
    51, 70,
    51, 74,
    51, 78,
    51, 79,
    51, 80,
    51, 81,
    51, 82,
    51, 83,
    51, 85,
    51, 86,
    51, 87,
    51, 88,
    51, 89,
    52, 15,
    52, 71,
    52, 74,
    52, 75,
    52, 83,
    52, 85,
    52, 86,
    52, 87,
    52, 88,
    52, 89,
    52, 90,
    52, 91,
    53, 34,
    53, 35,
    53, 36,
    53, 37,
    53, 38,
    53, 39,
    53, 40,
    53, 41,
    53, 42,
    53, 43,
    53, 44,
    53, 45,
    53, 46,
    53, 47,
    53, 48,
    53, 49,
    53, 50,
    53, 51,
    53, 52,
    53, 53,
    53, 54,
    53, 55,
    53, 56,
    53, 57,
    53, 58,
    53, 59,
    53, 67,
    53, 69,
    53, 71,
    53, 72,
    53, 73,
    53, 74,
    53, 75,
    53, 76,
    53, 77,
    53, 85,
    54, 15,
    54, 67,
    54, 73,
    54, 74,
    54, 75,
    54, 76,
    54, 77,
    54, 78,
    54, 79,
    54, 81,
    54, 83,
    54, 88,
    54, 89,
    54, 90,
    55, 15,
    55, 78,
    55, 79,
    55, 81,
    55, 82,
    55, 83,
    55, 86,
    55, 87,
    55, 88,
    55, 89,
    55, 90,
    56, 15,
    56, 66,
    56, 67,
    56, 68,
    56, 69,
    56, 70,
    56, 71,
    56, 72,
    56, 73,
    56, 74,
    56, 75,
    56, 76,
    56, 77,
    56, 80,
    56, 81,
    56, 82,
    56, 83,
    56, 84,
    56, 85,
    56, 86,
    56, 87,
    56, 88,
    56, 89,
    56, 91,
    57, 15,
    57, 80,
    57, 85,
    57, 86,
    57, 87,
    57, 88,
    57, 89,
    57, 90,
    57, 91,
    58, 15,
    58, 67,
    58, 71,
    58, 72,
    58, 73,
    58, 74,
    58, 75,
    58, 76,
    58, 77,
    58, 78,
    58, 79,
    58, 81,
    58, 83,
    58, 85,
    58, 86,
    58, 87,
    58, 88,
    58, 89,
    58, 90,
    58, 91,
    59, 15,
    59, 71,
    59, 74,
    59, 75,
    59, 76,
    59, 80,
    59, 81,
    59, 83,
    59, 84,
    59, 85,
    59, 86,
    59, 87,
    59, 88,
    59, 90,
    59, 91,
    66, 70,
    67, 15,
    68, 15,
    69, 15,
    70, 15,
    71, 15,
    71, 70,
    71, 77,
    72, 15,
    73, 15,
    73, 66,
    73, 70,
    73, 74,
    73, 80,
    74, 15,
    74, 70,
    75, 15,
    76, 15,
    77, 15,
    78, 15,
    79, 15,
    80, 15,
    81, 15,
    82, 15,
    83, 15,
    83, 83,
    84, 90,
    86, 15,
    87, 15,
    87, 70,
    88, 15,
    88, 70,
    89, 15,
    90, 15,
    91, 15
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -35, -36, -36, -40, -68, -59, -24, -15,
    -4, -32, -15, -6, -9, -10, -36, 18,
    14, -17, -30, 7, -3, -31, -28, -66,
    -27, 20, -25, -25, -23, 17, 9, -31,
    -30, -31, -27, -17, 53, 73, 62, -17,
    56, -10, 13, -14, -19, -14, 12, -14,
    6, 2, 1, -6, -10, -7, -13, 16,
    -9, -2, -7, -6, -10, -8, 7, 3,
    -17, -7, -7, -67, -63, 8, -58, 5,
    10, 8, 10, 8, 5, 9, 12, 9,
    8, 7, -8, -9, -8, -5, -5, -7,
    6, -8, -10, -19, -14, -23, 6, -23,
    -8, 10, -5, -3, -7, -7, 14, 9,
    -6, 9, -9, 12, 6, 10, 8, 13,
    14, 8, -26, -11, 3, -15, 8, 8,
    5, -8, -4, -24, -19, -32, -29, -1,
    11, -7, 3, -6, -8, -7, 3, -7,
    6, 5, 6, 3, 2, 14, 14, -8,
    10, -7, 10, 5, 12, 10, 16, 10,
    6, 24, -3, -3, -3, -6, 1, 5,
    5, 5, 6, -2, 6, 2, 2, 2,
    2, 2, 6, 13, 8, 7, 7, 8,
    3, 7, 9, 9, 9, 9, 2, 26,
    28, -9, 7, -24, 16, -15, -17, -55,
    -30, 20, -7, -17, -7, -31, -22, 23,
    16, -25, -24, -16, -27, 13, 23, -18,
    -10, -18, -58, -55, -54, 5, 40, 19,
    9, 10, 18, 14, 7, 18, 16, 13,
    10, 16, 6, 6, 20, 6, 3, 6,
    6, 6, 6, 37, 49, 9, 9, 27,
    46, 6, 5, -22, 3, 47, 56, 10,
    5, 39, 8, 4, 58, 45, 11, 7,
    9, 10, -11, 72, 19, 5, 20, 7,
    48, 20, 24, 12, 12, 6, 6, 7,
    -20, -16, 13, 26, 12, 14, -6, -7,
    -7, 9, 9, 9, 9, 26, 7, 9,
    9, 9, 9, -29, 6, 5, -3, 5,
    1, 2, 7, 12, 12, 12, -3, 12,
    -6, 12, 5, 10, 12, 10, 12, 12,
    12, -16, -9, -13, -8, -7, -14, -5,
    -20, -18, -5, 12, 6, 6, -5, 6,
    -19, 8, 7, 20, 7, 8, 7, 12,
    -15, -19, -16, -7, -7, -3, -29, -30,
    -5, -7, 2, -18, 29, 14, 28, 43,
    33, 20, 47, 48, 14, 47, 49, 38,
    55, 14, 34, 19, 38, 20, 24, 45,
    38, 51, 50, 89, 46, 63, -3, 44,
    -4, 67, 60, 57, 67, 69, 6, 26,
    7, 13, 6, 6, 7, 9, 6, 6,
    6, 3, 5, 3, 7, -16, 7, 7,
    7, -5, 7, 7, 10, 9, 9, 7,
    -15, -9, 35, -11, -20, -9, 24, -19,
    40, 39, 30, 41, 40, -9, 8, -15,
    2, -6, 10, 18, 6, 9, 10, -5,
    26, -21, -13, -18, -32, -27, 5, -30,
    5, 30, 24, 7, 6, 28, 31, 38,
    31, 35, 13, 13, 14, 10, 19, 19,
    12, 14, 16, 12, 3, 15, -12, -16,
    6, 7, -6, -6, -7, 2, -9, -5,
    -29, -36, -28, 5, -7, -10, -6, 5,
    -5, -17, -21, -8, 5, 10, -1, -1,
    -3, -1, 12, 9, 11, 10, 4, 9,
    6, -17, -16, 5, -38, 17, 0, 6,
    -24, -2, -30, -8, 10, -21, 12
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 511,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t ui_font_Black_Chancery_16 = {
#else
lv_font_t ui_font_Black_Chancery_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 6,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_BLACK_CHANCERY_16*/

