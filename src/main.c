#include "kernel/video/console.h"

void on_start(){
    cs_clear();
    cs_set_color(CS_GRAY, CS_BLACK);
    cs_print("test\nHello, worli\bd!!!");
}
void loop(){}