/**
 * unicorn_blink
 * 
 * initial tests of ...
 *  setting up a new project that isn't one of the pico-examples
 *  including third-party (pimoroni) libraries
 *  using picoprobe to debug / upload the elf to the pico
 *  using the unicorn pack on a pimoroni omnibus
 * 
 * ... that's probably enough for now
 * 
 * will update this to add game of life patterns to the unicorn, rather than random changing colours
 * 
 * but it works, which is something
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico_unicorn.hpp"

using namespace pimoroni;

PicoUnicorn pico_unicorn;

int main()
{
    pico_unicorn.init();
    pico_unicorn.clear();
    
    while(1) {
        for(int row=0;row<=pico_unicorn.HEIGHT;row++) {
            for(int col=0;col<=pico_unicorn.WIDTH;col++) {
                pico_unicorn.set_pixel(col, row, rand() % 100 + 55, rand() % 100 + 55, rand() % 100 + 55);
            }
        }
        sleep_ms(rand() % 100);
    }

    return 0;
}