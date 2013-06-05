// rgb
// daisy-chainable lighting module
// http://github.com/mcous/rgb
//
// copyright 2013 michael cousins
// shared under the terms of the gpl v3 licence

// includes
#include "rgb.h"

// defines


int main (void) {
    // set some initial values for the leds
    for (uint8_t i=0; i<15; i++) {
        driver.setGS(i, 2023);
    }
    // initialize dot correction on the led driver
    driver.initDC();

    // OH MY GOD IT'S ENDLESS
    for(;;) {
        driver.refreshGS();
    }

    // the answer
    return 42;
}