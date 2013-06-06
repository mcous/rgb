// rgb
// daisy-chainable lighting module
// http://github.com/mcous/rgb
//
// copyright 2013 michael cousins
// shared under the terms of the gpl v3 licence

// includes
#include "rgb.h"
#include <math.h>

// defines
// taylor series sin expansion
//#define sin_t(a) (a-(pow(a,3.0)/6.0)+(pow(a,5.0)/120.0)-(pow(a,7.0)/5040.0))

int main (void) {
    // set dc values
    for (uint8_t i=0; i<15; i++) {
        driver.setDC(i, 1);
    }
    // set some initial values for the leds
    for (uint8_t i=0; i<15; i++) {
        driver.setGS(i, 0);
    }

    // initialize dot correction on the led driver
    driver.init();

    // sine wave variables
    /*
    double a = 0;
    uint16_t red;
    uint16_t grn;
    uint16_t blu;
    */

    // two-color-combo variables
    /*
    uint16_t val[3];
    val[0] = 500;
    val[1] = 0;
    val[2] = 0;
    uint8_t dec = 0;
    uint8_t inc = dec + 1;
    uint16_t count = 0;
    */

    // cylon variables
    /*
    uint16_t count = 0;
    uint8_t last = 0;
    uint8_t curr = 0;
    int8_t dir = 1;
    */

    // waterfall thingy variables
    uint8_t index = 0;
    uint8_t dir = 1;
    uint16_t count = 0;


    // OH MY GOD IT'S ENDLESS
    for(;;) {
        // waterfall thingy
        if (count > 9) {
            count = 0;
            driver.setGS(index, dir*500);
            index++;
            if (index > 14) {
                index = 0;
                dir ^= 1;
            }
        }
        driver.refreshGS();
        count++;

        // cylon stuff
        /*
        if (count > 9) {
            count = 0;
            last = curr;
            if (last <=2) {
                dir = 1;
            }
            else if (last >= 12) {
                dir = -1;
            }
            curr += 3*dir;
        }
        driver.setGS(last, 0);
        driver.setGS(curr, 500);
        driver.refreshGS();
        count++;
        */

        // two-color-combo stuff
        /*
        if (count >= 499) {
            count = 0;
            dec++;
            if (dec > 2) {
                dec = 0;
            }
            inc = dec + 1;
            if (inc == 3) {
                inc = 0;
            }
        }
        val[dec]-=1;
        val[inc]+=1;
        rgb(val[0], val[1], val[2]);
        driver.refreshGS();
        count++;
        */

        // sine wave stuff
        /*
        if (a >= 6.28) {
            a = 0;
        }

        red = (uint16_t)(1000 * (1 + sin(a)));
        grn = (uint16_t)(1000 * (1 + sin(a + (3.14/2.0))));
        blu = (uint16_t)(1000 * (1 + sin(a + (3.14))));
        
        rgb(red, grn, blu);
        driver.refreshGS();
        a+=0.01;
        */
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