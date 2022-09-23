#include <main.h>

void boot(){
    on_start();
    while(1)
        loop();
}