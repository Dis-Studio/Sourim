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

void cs_set_color(enum cs_colors fg, enum cs_colors bg);
void cs_cur_set(const int x, const int y);
void cs_clear();
void cs_putchar(const char ch);
void cs_print(const char *text);