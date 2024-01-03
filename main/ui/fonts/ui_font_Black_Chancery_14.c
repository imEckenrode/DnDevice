/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --font C:\Users\brett\OneDrive\Documents\Projects\DnDevice\SquareLine\assets\font\Black Chancery\BLKCHCRY.TTF -o C:\Users\brett\OneDrive\Documents\Projects\DnDevice\SquareLine\assets\font\Black Chancery\ui_font_Black_Chancery_14.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_BLACK_CHANCERY_14
#define UI_FONT_BLACK_CHANCERY_14 1
#endif

#if UI_FONT_BLACK_CHANCERY_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x13, 0x26, 0x66, 0x44, 0x4, 0x40,

    /* U+0022 "\"" */
    0x99, 0x0,

    /* U+0023 "#" */
    0x17, 0x6e, 0x80,

    /* U+0024 "$" */
    0x23, 0xa3, 0x6, 0xc, 0x31, 0x71, 0x0,

    /* U+0025 "%" */
    0xea, 0xab, 0xbc, 0x3d, 0x5d, 0x67,

    /* U+0026 "&" */
    0x38, 0x12, 0x4, 0x81, 0x40, 0x22, 0x1c, 0x49,
    0x92, 0x34, 0x86, 0x30, 0xc7, 0xc4,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x6a, 0xaa, 0x80,

    /* U+0029 ")" */
    0xa5, 0x55, 0x80,

    /* U+002A "*" */
    0x1, 0x29, 0x67, 0x73, 0xb, 0x84, 0x0,

    /* U+002B "+" */
    0x20, 0x2, 0x3f, 0x29, 0x82, 0x0,

    /* U+002C "," */
    0xd0,

    /* U+002D "-" */
    0x78,

    /* U+002E "." */
    0x48,

    /* U+002F "/" */
    0x8, 0x84, 0x42, 0x11, 0x8, 0x84, 0x0,

    /* U+0030 "0" */
    0x74, 0xe3, 0x18, 0xb8,

    /* U+0031 "1" */
    0x49, 0x24, 0x80,

    /* U+0032 "2" */
    0x3a, 0x52, 0x26, 0x3c,

    /* U+0033 "3" */
    0x78, 0x88, 0x60, 0x84, 0x32, 0xe0,

    /* U+0034 "4" */
    0x8, 0x62, 0x8a, 0x49, 0x27, 0xc2, 0x8, 0x70,

    /* U+0035 "5" */
    0x39, 0x4, 0x1e, 0xc, 0x10, 0x51, 0x78,

    /* U+0036 "6" */
    0x31, 0x4, 0x20, 0xbb, 0x38, 0x71, 0x78,

    /* U+0037 "7" */
    0xfc, 0x18, 0x41, 0x2, 0x8, 0x10, 0x30, 0x20,

    /* U+0038 "8" */
    0x74, 0x63, 0xa7, 0x4e, 0x39, 0x70,

    /* U+0039 "9" */
    0x74, 0xe3, 0x1c, 0x84, 0x42, 0x20, 0x0,

    /* U+003A ":" */
    0xf3, 0xc0,

    /* U+003B ";" */
    0x48, 0x2c, 0x80,

    /* U+003C "<" */
    0x29, 0x10,

    /* U+003D "=" */
    0x78, 0x1e,

    /* U+003E ">" */
    0x89, 0xc0,

    /* U+003F "?" */
    0x7d, 0x8e, 0xc, 0x18, 0x49, 0x4, 0x10, 0x28,
    0x70, 0x0, 0x3, 0x0, 0x0,

    /* U+0040 "@" */
    0x1e, 0x30, 0xb3, 0x32, 0x9a, 0x4d, 0xeb, 0x98,
    0xc2, 0x3e, 0x0,

    /* U+0041 "A" */
    0x0, 0x0, 0x4, 0x0, 0x18, 0x0, 0xe0, 0x5,
    0x80, 0x16, 0x3, 0x8c, 0x5, 0xb0, 0x21, 0xc1,
    0x3, 0x88, 0x7, 0x0, 0xc, 0x0, 0xc,

    /* U+0042 "B" */
    0x1f, 0x83, 0x12, 0x21, 0x89, 0xc, 0x48, 0x62,
    0x43, 0x21, 0x18, 0x84, 0xc2, 0x6, 0x18, 0x30,
    0xc1, 0x86, 0x8, 0xe0, 0xfc, 0x0,

    /* U+0043 "C" */
    0x1f, 0x88, 0x64, 0x6, 0x0, 0x80, 0x20, 0x8,
    0x2, 0x0, 0xc0, 0x18, 0x3, 0xc, 0x7e,

    /* U+0044 "D" */
    0x1f, 0xc1, 0x89, 0xc8, 0x61, 0xa1, 0x87, 0x86,
    0xe, 0x18, 0x34, 0x60, 0xcd, 0x83, 0x6, 0xc,
    0x18, 0x30, 0x61, 0x89, 0x1c, 0x1f, 0xc0,

    /* U+0045 "E" */
    0x3f, 0xe4, 0x42, 0x8c, 0x8, 0xcc, 0x8d, 0x48,
    0xe0, 0x4c, 0x2, 0xc0, 0xc, 0x20, 0xc2, 0x1f,
    0xe0,

    /* U+0046 "F" */
    0x1f, 0xf9, 0x88, 0x8, 0x18, 0x20, 0x60, 0x0,
    0xc8, 0x7f, 0xc2, 0xc, 0x10, 0x30, 0x40, 0xc1,
    0x6, 0x6, 0x10, 0xf, 0x80,

    /* U+0047 "G" */
    0x1f, 0x2, 0xc, 0x40, 0x8, 0x0, 0x80, 0x8,
    0x0, 0x8f, 0xe9, 0x4, 0xc0, 0x44, 0x4, 0x30,
    0xc1, 0xf0,

    /* U+0048 "H" */
    0x3c, 0x74, 0xc6, 0x8c, 0x68, 0xc6, 0x8d, 0xe4,
    0xe6, 0xc, 0x60, 0xc6, 0xc, 0x61, 0xc7,

    /* U+0049 "I" */
    0x3f, 0x46, 0x86, 0x86, 0x86, 0xd6, 0x76, 0x6,
    0x6, 0x7,

    /* U+004A "J" */
    0x1f, 0xc8, 0x64, 0x19, 0x6, 0x61, 0x8e, 0x60,
    0x18, 0x6, 0x81, 0xa0, 0x68, 0x1b, 0xc, 0x7e,
    0x4, 0x0,

    /* U+004B "K" */
    0x3f, 0xf8, 0x2, 0x31, 0x0, 0x21, 0x90, 0x1,
    0xd, 0x0, 0x8, 0x78, 0x0, 0x43, 0x60, 0x1,
    0x19, 0x0, 0x0, 0xc4, 0x0, 0x6, 0x30, 0x0,
    0x40, 0x40, 0x0, 0x1, 0x2, 0x0, 0x4, 0x10,
    0x0, 0x1f, 0x0, 0x0, 0x10,

    /* U+004C "L" */
    0x3f, 0x0, 0xc6, 0x0, 0x86, 0x0, 0x86, 0x0,
    0xc6, 0x0, 0x76, 0x0, 0x6, 0x0, 0x6, 0x0,
    0x6, 0x0, 0x79, 0x0, 0x0, 0x81, 0x0, 0x61,
    0x0, 0x1e,

    /* U+004D "M" */
    0x1e, 0xc, 0x31, 0x88, 0x10, 0xcc, 0x10, 0x66,
    0x8, 0x3b, 0x4, 0x16, 0x82, 0xb, 0x40, 0x89,
    0x20, 0x4, 0x98, 0x2, 0xc, 0x2, 0x3, 0x11,
    0x1, 0xc7, 0x0, 0x30,

    /* U+004E "N" */
    0x3c, 0x70, 0x4e, 0x20, 0x8b, 0x20, 0x8b, 0x20,
    0x89, 0x20, 0x89, 0xa0, 0x48, 0xa0, 0x8, 0xe0,
    0x8, 0x60, 0xc, 0x60, 0x0, 0x30, 0x0, 0x18,
    0x0, 0xf,

    /* U+004F "O" */
    0x1f, 0x6, 0x19, 0x81, 0x60, 0x3c, 0x3, 0x80,
    0x70, 0xe, 0x1, 0xe0, 0x2c, 0x9, 0xc2, 0xf,
    0x80,

    /* U+0050 "P" */
    0x1f, 0x8c, 0x4a, 0x18, 0xc3, 0x18, 0x63, 0xc,
    0xd1, 0xb1, 0x30, 0x6, 0x1, 0xe0, 0xc0, 0x20,
    0x4, 0x0,

    /* U+0051 "Q" */
    0x1f, 0x80, 0x43, 0xc2, 0x1, 0x84, 0x3, 0x88,
    0x3, 0x10, 0x6, 0x20, 0xc, 0x4f, 0x18, 0xc3,
    0x20, 0x83, 0x81, 0xc3, 0x0, 0xfa, 0x0, 0x3,
    0xe0, 0x1, 0x0,

    /* U+0052 "R" */
    0x3f, 0xe0, 0x4, 0x23, 0x80, 0x86, 0x18, 0x8,
    0x61, 0x80, 0x86, 0x38, 0x4, 0x6e, 0x0, 0x26,
    0x80, 0x0, 0x64, 0x0, 0x6, 0x60, 0x0, 0x83,
    0x0, 0x0, 0x38, 0x0, 0x1, 0xc0, 0x0, 0xf,
    0xe0, 0x0, 0x10,

    /* U+0053 "S" */
    0x3f, 0x8c, 0x31, 0x1, 0x20, 0x6, 0x0, 0x7c,
    0x0, 0xf4, 0x3, 0x80, 0x30, 0x7, 0x0, 0xb8,
    0x21, 0xf8,

    /* U+0054 "T" */
    0x1f, 0xf9, 0x88, 0x0, 0x18, 0x0, 0x60, 0x1c,
    0xc0, 0x9b, 0x4, 0x2c, 0x10, 0xb0, 0x44, 0xc1,
    0x86, 0x2, 0x18, 0x7, 0x80,

    /* U+0055 "U" */
    0x3f, 0x3a, 0x11, 0xa1, 0xd, 0x18, 0x68, 0x83,
    0x4c, 0x19, 0x60, 0xc3, 0x6, 0x18, 0x30, 0xe3,
    0x83, 0xe2,

    /* U+0056 "V" */
    0x3e, 0x2, 0x13, 0x21, 0xd, 0x8, 0x38, 0xc1,
    0xe6, 0xd, 0xb0, 0x61, 0x83, 0xc, 0x30, 0x71,
    0x1, 0x98, 0x7, 0x0,

    /* U+0057 "W" */
    0x3e, 0x71, 0xc9, 0x84, 0x22, 0x18, 0xc4, 0x43,
    0x18, 0x88, 0x25, 0x21, 0x96, 0xb4, 0x1c, 0xd6,
    0x80, 0xc, 0x60, 0x1, 0x8c, 0x0, 0x10, 0x80,
    0x4, 0x20, 0x0,

    /* U+0058 "X" */
    0x3c, 0x70, 0x23, 0x20, 0x20, 0xe0, 0x10, 0x70,
    0x8, 0x18, 0x4, 0xc, 0x1, 0xe, 0x0, 0x9,
    0x80, 0x8, 0xc0, 0x4, 0x30, 0x0, 0x1c, 0x0,
    0x7, 0x0, 0x0, 0xf8,

    /* U+0059 "Y" */
    0x70, 0x70, 0x46, 0x21, 0x20, 0x2, 0x80, 0x4,
    0x0, 0x10, 0x0, 0x40, 0x1, 0x0, 0x4, 0x0,
    0x18, 0x0,

    /* U+005A "Z" */
    0x3f, 0xc8, 0x20, 0x8, 0x2, 0x0, 0xf0, 0x3,
    0x8f, 0x32, 0x73, 0x82, 0x70, 0x4e, 0x3, 0x60,
    0x67, 0xf8, 0x10, 0x0,

    /* U+005B "[" */
    0xfb, 0x6d, 0xb6, 0xe0,

    /* U+005C "\\" */
    0x84, 0x30, 0x82, 0x10, 0x42, 0x8,

    /* U+005D "]" */
    0xed, 0xb6, 0xdb, 0xe0,

    /* U+005E "^" */
    0x32, 0x40,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0x90,

    /* U+0061 "a" */
    0x39, 0x28, 0xa2, 0xfb, 0x30,

    /* U+0062 "b" */
    0x68, 0x8b, 0xd9, 0x99, 0xe0,

    /* U+0063 "c" */
    0x7c, 0xe1, 0xc, 0xb8,

    /* U+0064 "d" */
    0x6, 0x10, 0x21, 0xc4, 0x91, 0x22, 0x7c, 0xcc,

    /* U+0065 "e" */
    0x74, 0xa9, 0x8c, 0xb8,

    /* U+0066 "f" */
    0xe, 0x20, 0x41, 0xc1, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x40, 0x81, 0xc, 0x0,

    /* U+0067 "g" */
    0x3a, 0x63, 0x1f, 0xf5, 0x31, 0x8f, 0x90,

    /* U+0068 "h" */
    0x64, 0x21, 0x6d, 0x4a, 0x52, 0x98,

    /* U+0069 "i" */
    0x66, 0x6, 0x22, 0x22, 0x20,

    /* U+006A "j" */
    0x8, 0x40, 0x10, 0x84, 0x21, 0x8, 0x63, 0x17,
    0x0,

    /* U+006B "k" */
    0x64, 0x21, 0x2e, 0x72, 0x96, 0x98,

    /* U+006C "l" */
    0x72, 0x49, 0x24, 0xc0,

    /* U+006D "m" */
    0x5b, 0x36, 0x92, 0x49, 0x24, 0x92, 0x4c,

    /* U+006E "n" */
    0x59, 0xa4, 0x92, 0x49, 0x30,

    /* U+006F "o" */
    0x74, 0xe3, 0x18, 0xb8,

    /* U+0070 "p" */
    0x59, 0x94, 0x51, 0x49, 0xc4, 0x10, 0x41, 0x80,

    /* U+0071 "q" */
    0x39, 0x28, 0xa2, 0xfb, 0x20, 0x82, 0x8, 0x0,

    /* U+0072 "r" */
    0x4b, 0x66, 0x90, 0x41, 0x0,

    /* U+0073 "s" */
    0xf8, 0xc3, 0x9f,

    /* U+0074 "t" */
    0xb, 0xa4, 0x93,

    /* U+0075 "u" */
    0xc9, 0x24, 0x92, 0x59, 0xb0,

    /* U+0076 "v" */
    0x4f, 0x92, 0x4e, 0x18, 0x40,

    /* U+0077 "w" */
    0x0, 0xc, 0x4c, 0x8c, 0x8a, 0xa1, 0x5c, 0x11,
    0x2, 0x20,

    /* U+0078 "x" */
    0x64, 0x70, 0x40, 0xc2, 0x89, 0xc0,

    /* U+0079 "y" */
    0x4d, 0xc8, 0x91, 0xc1, 0x82, 0x8, 0x10, 0x20,
    0x78, 0x0,

    /* U+007A "z" */
    0x7d, 0x21, 0x1e, 0x45, 0xf0,

    /* U+007B "{" */
    0x29, 0x25, 0x92, 0x48, 0x80,

    /* U+007C "|" */
    0xff, 0xf8,

    /* U+007D "}" */
    0x89, 0x24, 0xd2, 0x4a, 0x0,

    /* U+007E "~" */
    0xc1, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 56, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 82, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 7, .adv_w = 72, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 9, .adv_w = 100, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 12, .adv_w = 88, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 19, .adv_w = 110, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 146, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 39, .adv_w = 28, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 40, .adv_w = 52, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 43, .adv_w = 52, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 46, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 53, .adv_w = 126, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 59, .adv_w = 54, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 60, .adv_w = 131, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 61, .adv_w = 54, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 62, .adv_w = 104, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 69, .adv_w = 101, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 63, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 95, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 95, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 86, .adv_w = 108, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 94, .adv_w = 104, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 101, .adv_w = 108, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 108, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 116, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 100, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 129, .adv_w = 54, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 131, .adv_w = 54, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 134, .adv_w = 95, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 136, .adv_w = 93, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 138, .adv_w = 82, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 140, .adv_w = 133, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 153, .adv_w = 147, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 164, .adv_w = 176, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 187, .adv_w = 205, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 209, .adv_w = 163, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 224, .adv_w = 224, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 247, .adv_w = 190, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 264, .adv_w = 206, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 285, .adv_w = 190, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 303, .adv_w = 204, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 318, .adv_w = 130, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 328, .adv_w = 150, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 346, .adv_w = 197, .box_w = 21, .box_h = 14, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 383, .adv_w = 129, .box_w = 16, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 409, .adv_w = 218, .box_w = 17, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 437, .adv_w = 184, .box_w = 16, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 463, .adv_w = 198, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 480, .adv_w = 189, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 498, .adv_w = 204, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 525, .adv_w = 206, .box_w = 20, .box_h = 14, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 560, .adv_w = 177, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 578, .adv_w = 168, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 599, .adv_w = 207, .box_w = 13, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 617, .adv_w = 215, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 637, .adv_w = 254, .box_w = 19, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 664, .adv_w = 181, .box_w = 17, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 692, .adv_w = 94, .box_w = 14, .box_h = 10, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 710, .adv_w = 176, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 730, .adv_w = 59, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 734, .adv_w = 102, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 740, .adv_w = 61, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 744, .adv_w = 89, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 746, .adv_w = 102, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 747, .adv_w = 45, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 748, .adv_w = 103, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 753, .adv_w = 83, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 762, .adv_w = 103, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 770, .adv_w = 93, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 774, .adv_w = 64, .box_w = 7, .box_h = 14, .ofs_x = -2, .ofs_y = -5},
    {.bitmap_index = 787, .adv_w = 92, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 794, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 800, .adv_w = 58, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 805, .adv_w = 44, .box_w = 5, .box_h = 14, .ofs_x = -3, .ofs_y = -5},
    {.bitmap_index = 814, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 820, .adv_w = 49, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 153, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 831, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 836, .adv_w = 101, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 97, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 848, .adv_w = 95, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 856, .adv_w = 90, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 861, .adv_w = 74, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 864, .adv_w = 60, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 867, .adv_w = 110, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 872, .adv_w = 106, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 877, .adv_w = 172, .box_w = 11, .box_h = 7, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 887, .adv_w = 110, .box_w = 7, .box_h = 6, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 893, .adv_w = 105, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 903, .adv_w = 92, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 908, .adv_w = 78, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 913, .adv_w = 41, .box_w = 1, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 915, .adv_w = 78, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 920, .adv_w = 102, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 6}
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
    -30, -32, -31, -35, -60, -52, -21, -13,
    -3, -28, -13, -5, -8, -9, -31, 16,
    12, -15, -26, 6, -2, -27, -25, -58,
    -24, 17, -22, -22, -20, 15, 8, -27,
    -26, -27, -24, -15, 46, 64, 54, -15,
    49, -9, 11, -12, -16, -13, 11, -12,
    5, 2, 1, -5, -9, -6, -11, 14,
    -8, -2, -6, -5, -9, -7, 6, 3,
    -15, -6, -6, -58, -55, 7, -51, 4,
    9, 7, 9, 7, 4, 8, 10, 8,
    7, 6, -7, -8, -7, -4, -4, -6,
    5, -7, -9, -17, -13, -20, 5, -20,
    -7, 9, -4, -3, -6, -6, 12, 8,
    -5, 8, -8, 10, 5, 9, 7, 11,
    12, 7, -23, -9, 3, -13, 7, 7,
    4, -7, -3, -21, -17, -28, -25, -1,
    10, -6, 3, -5, -7, -6, 3, -6,
    5, 4, 5, 3, 2, 12, 12, -7,
    9, -6, 9, 4, 10, 9, 14, 9,
    5, 21, -2, -3, -3, -5, 1, 4,
    4, 4, 5, -2, 5, 2, 2, 2,
    2, 2, 5, 12, 7, 6, 6, 7,
    3, 6, 8, 8, 8, 8, 2, 23,
    25, -8, 6, -21, 14, -13, -15, -48,
    -26, 17, -6, -15, -6, -27, -19, 20,
    14, -22, -21, -14, -24, 11, 20, -15,
    -9, -15, -51, -48, -47, 4, 35, 16,
    8, 9, 15, 12, 6, 16, 14, 11,
    9, 14, 5, 5, 17, 5, 3, 5,
    5, 5, 5, 32, 43, 8, 8, 24,
    40, 5, 4, -19, 3, 41, 49, 9,
    4, 34, 7, 4, 51, 40, 9, 6,
    8, 9, -10, 63, 16, 4, 17, 6,
    42, 17, 21, 10, 10, 5, 5, 6,
    -17, -14, 11, 23, 10, 12, -5, -6,
    -6, 8, 8, 8, 8, 22, 6, 8,
    8, 8, 8, -25, 5, 4, -3, 4,
    1, 2, 6, 10, 10, 10, -2, 10,
    -5, 10, 4, 9, 10, 9, 10, 10,
    10, -14, -8, -11, -7, -6, -12, -4,
    -17, -15, -4, 11, 5, 5, -4, 5,
    -17, 7, 6, 18, 6, 7, 6, 11,
    -13, -17, -14, -6, -6, -3, -26, -26,
    -4, -6, 2, -15, 26, 12, 25, 37,
    29, 18, 41, 42, 13, 41, 43, 34,
    48, 12, 30, 17, 33, 18, 21, 39,
    33, 45, 43, 78, 40, 55, -2, 39,
    -3, 58, 53, 50, 58, 60, 5, 23,
    6, 11, 5, 5, 6, 8, 5, 5,
    5, 3, 4, 3, 6, -14, 6, 6,
    6, -4, 6, 6, 9, 8, 8, 6,
    -13, -8, 30, -9, -17, -8, 21, -17,
    35, 34, 26, 36, 35, -8, 7, -13,
    2, -5, 9, 16, 5, 8, 9, -4,
    23, -19, -11, -15, -28, -24, 4, -26,
    4, 26, 21, 6, 5, 25, 27, 33,
    27, 30, 11, 11, 12, 9, 17, 16,
    10, 13, 14, 10, 3, 13, -10, -14,
    5, 6, -5, -5, -6, 2, -8, -4,
    -26, -31, -25, 4, -6, -9, -5, 4,
    -4, -15, -18, -7, 4, 9, -1, -1,
    -2, -1, 11, 8, 10, 9, 3, 8,
    5, -15, -14, 4, -34, 15, 0, 5,
    -21, -2, -26, -7, 9, -18, 11
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
const lv_font_t ui_font_Black_Chancery_14 = {
#else
lv_font_t ui_font_Black_Chancery_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 5,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_BLACK_CHANCERY_14*/

