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
    // set dc values
    for (uint8_t i=0; i<15; i++) {
        driver.setDC(i, 10);
    }
    // set some initial values for the leds
    //for (uint8_t i=0; i<15; i++) {
    //    driver.setGS(i, 1000);
    //}

    driver.setGS(0,  1000);
    driver.setGS(1,  0   );
    driver.setGS(2,  0   );
    driver.setGS(3,  1000);
    driver.setGS(4,  0   );
    driver.setGS(5,  0   );
    driver.setGS(6,  1000);
    driver.setGS(7,  0   );
    driver.setGS(8,  0   );
    driver.setGS(9,  1000);
    driver.setGS(10, 0   );
    driver.setGS(11, 0   );
    driver.setGS(12, 1000);
    driver.setGS(13, 0   );
    driver.setGS(14, 0   );

    // initialize dot correction on the led driver
    driver.init();

    uint16_t red = 0;
    uint16_t red = 0;
    uint16_t red = 0;

    // OH MY GOD IT'S ENDLESS
    for(;;) {

        rgb(red, grn, blu);
        driver.refreshGS();
    }

    // the answer
    return 42;
}

void rgb(uint16_t r, uint16_t g, uint16_t b) {
    for (uint8_t i = 0; i < 15; i+=3) {
        driver.setGS(i, r);
    }
    for (uint8_t i = 1; i < 15; i+=3) {
        driver.setGS(i, g);
    }
    for (uint8_t i = 2; i < 15; i+=3) {
        driver.setGS(i, b);
    }
}