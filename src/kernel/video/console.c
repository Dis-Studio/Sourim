#include <kernel/video/console.h>

#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 25

enum cs_colors {
    CS_BLACK = 0,
    CS_BLUE = 1,
    CS_GREEN = 2,
    CS_CYAN = 3,
    CS_RED = 4,
    CS_PURPLE = 5,
    CS_BROWN = 6,
    CS_GRAY = 7,
    CS_DARKGRAY = 8,
    CS_LIGHTBLUE = 9,
    CS_LIGHTGREEN = 10,
    CS_LIGHTCYAN = 11,
    CS_LIGHTRED = 12,
    CS_LIGHTPURPLE = 13,
    CS_YELLOW = 14,
    CS_WHITE = 15,
};

volatile char *buffer = (volatile char*) 0xb8000;
int color = 0x0F;
int curx = 0;
int cury = 0;

void cs_cur_set(const int x, const int y){
	uint16_t pos = y * CONSOLE_WIDTH + x;
	port_byte_out(0x3D4, 0x0F);
	port_byte_out(0x3D5, (uint8_t) (pos & 0xFF));
	port_byte_out(0x3D4, 0x0E);
	port_byte_out(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void cs_clear(){
    buffer = (volatile char*) 0xb8000;
    for(size_t i = 0; i < CONSOLE_WIDTH * CONSOLE_HEIGHT; i++){
        *buffer++ = 0;
        *buffer++ = color;
    }
    buffer = (volatile char*) 0xb8000;
    cs_cur_set(0, 0);
}
void cs_set_color(enum cs_colors fg, enum cs_colors bg){
    color = fg | bg << 4;
}
void cs_putchar(const char ch){
    switch(ch){
        case '\n':
            for(; curx < CONSOLE_WIDTH; curx++){
                *buffer++ = 0;
                *buffer++ = color;
            }
            curx = 0;
            cury++;
            break;
        case '\b':
            buffer -= 3;
            *buffer = 0;
            *buffer++ = color;
            curx--;
            break;
        default:
            *buffer++ = ch;
            *buffer++ = color;
            curx++;
            break;
    }
    cs_cur_set(curx, cury);
}
void cs_print(const char *text){
    for(; *text; text++)
        cs_putchar(*text);
}