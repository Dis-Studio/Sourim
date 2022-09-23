#include <main.hpp>

extern "C" void boot(){
    start();
    while(1)
        loop();
}