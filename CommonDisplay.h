#ifndef __COMMON_DISPLAY_H__
#define __COMMON_DISPLAY_H__

#include <stdint.h>

enum RDCommand {
    RD_DRAW_PIXEL,
    RD_START_WRITE,
    RD_WRITE_PIXEL,
    RD_WRITE_FILL_RECT,
    RD_WRITE_FAST_VLINE,
    RD_WRITE_FAST_HLINE,
    RD_WRITE_LINE,
    RD_END_WRITE,
    RD_SET_ROTATION,
    RD_INVERT_DISPLAY,
    RD_DRAW_FAST_VLINE,
    RD_DRAW_FAST_HLINE,
    RD_FILL_RECT,
    RD_FILL_SCREEN,
    RD_DRAW_LINE,
    RD_DRAW_RECT,
    RD_DRAW_CIRCLE,
    RD_DRAW_CIRCLE_HELPER,
    RD_FILL_CIRCLE,
    RD_FILL_CIRCLE_HELPER,
    RD_FILL_TRIANGLE,
    RD_DRAW_TRIANGLE,
    RD_DRAW_ROUND_RECT,
    RD_FILL_ROUND_RECT,
    RD_DRAW_BITMAP1,
    RD_DRAW_BITMAP2,
    RD_DRAW_X_BITMAP,
    RD_DRAW_GRAYSCALE_BITMAP1,
    RD_DRAW_GRAYSCALE_BITMAP2,
    RD_DRAW_RGB_BITMAP1,
    RD_DRAW_RGB_BITMAP2,
    RD_DRAW_CHAR,
    RD_SET_CURSOR,
    RD_SET_TEXT_COLOR1,
    RD_SET_TEXT_COLOR2,
    RD_SET_TEXT_SIZE,
    RD_SET_TEXT_WRAP,
    RD_CP437,
    RD_SET_FONT,
    RD_GET_TEXT_BOUNDS,
    RD_WRITE,
    RD_HEIGHT,
    RD_WIDTH,
    RD_GET_ROTATION,
    RD_GET_CURSOR_X,
    RD_GET_CURSOR_Y,
    RD_RESET,
    RD_BEGIN,
    RD_VSCROLL,
    RD_HSCROLL,
    RD_SCROLL,
    RD_DATA_MSG,
    RD_DATA_RESET,
    RD_SET_ADDR_WINDOW,
    RD_PUSH_COLORS,
    RD_CACHE_DATA,
    // message from the server to the client
    RD_SCREEN_REFRESH,
    RD_SCREEN_OFF,
    RD_SCREEN_ON,
    // JavaScript specific messages
    RD_JS_SCRIPT,
    // Force the size of the enum to a 4 byte word for ESP8266 compatability
    RD_MAX = 0xFFFFFFFF
};

typedef union _RD_ARG {
    int16_t  x;
    int16_t  y;
    int16_t  width;
    int16_t  height;
    uint16_t color;
    uint16_t radius;
    int16_t  delta;
    uint8_t  rotation;
    uint8_t  cornerName;
    uint8_t  size;
    uint16_t size16;
    uint8_t  c;
    bool     b;
    uint16_t cacheHandle;
}RD_ARG;

typedef struct _RD_ARGS {
   enum RDCommand command;    // sizeof(RDCommand) == 4
   RD_ARG         a1;         // +2 = 6
   RD_ARG         a2;         // +2 = 8
   RD_ARG         a3;         // +2 = 10
   RD_ARG         a4;         // +2 = 12
   RD_ARG         a5;         // +2 = 14
   RD_ARG         a6;         // +2 = 16
   RD_ARG         a7;         // +2 = 18
   uint16_t       length;     // +2 = 20
   uint8_t        data[12];   // +12 = 32
} RD_ARGS;

typedef struct _RD_DATA {
   enum RDCommand command;    // sizeof(RDCommand) == 4
   uint8_t        data[28];   // +28 = 32
} RD_DATA;

typedef struct _RD_WRITE_DATA {
   enum RDCommand command;    // sizeof(RDCommand) == 4
   uint8_t        length;     // +1 = 5
   uint8_t        data[27];   // +27 = 32
} RD_WRITE_DATA;

#endif
