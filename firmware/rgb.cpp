// rgb
// daisy-chainable lighting module
// http://github.com/mcous/rgb
//
// copyright 2013 michael cousins
// shared under the terms of the gpl v3 licence

// includes
#include "rgb.h"
#include <math.h>
#include "sinetable.h"

// defines
// taylor series sin expansion
//#define sin_t(a) (a-(pow(a,3.0)/6.0)+(pow(a,5.0)/120.0)-(pow(a,7.0)/5040.0))

int main (void) {
    // set dc values
    for (uint8_t i=0; i<15; i++) {
        driver.setDC(i, 5);
    }
    // set some initial values for the leds
    for (uint8_t i=0; i<15; i++) {
        driver.setGS(i, 0);
    }

    // initialize dot correction on the led driver
    driver.init();

    // superdome variables
    uint16_t tm = 0;
    uint8_t val[5][3];
    uint8_t mag = 16;
    uint8_t shift = 64;

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
    /*
    uint8_t index = 0;
    uint8_t dir = 1;
    uint16_t count = 0;
    */

    // TRIPLE RAINBOW VARIABLES
    /*
    double rA[] = {0, 0, 0, 0, 0};
    double gA[] = {0, 0, 0, 0, 0};
    double bA[] = {0, 0, 0, 0, 0};
    uint16_t count = 0;
    uint16_t mag = 1000;
    float shift = 2;
    uint8_t sDir = 1;
    */

    // OH MY GOD IT'S ENDLESS
    for(;;) {
        // superdome
        if (tm > 384) {
            tm = 0;
        }
        for (uint8_t i=0; i<5; i++) {
            cosineVal(val[i], tm+shift*i);
            driver.setGS(i*3, val[i][0]);
            driver.setGS(i*3+1, val[i][1]);
            driver.setGS(i*3+2, val[i][2]);
        }
        driver.refreshGS();
        tm++;

        // TRIPLE RAINBOW
        /*
        if (count > 5) {
            count = 0;
            if (sDir) {
                shift += 0.02;
            }
            else {
                shift -= 0.02;
            }
            if (shift >= 3.0) {
                sDir = 0;
            }
            else if (shift <= 1.0) {
                sDir = 1;
            }
        }
            
        rA[0] += 0.02;
        if (rA[0] > 6.28) {
            rA[0] = 0;
        }
        driver.setGS(0, (uint16_t)(mag*(1+sin(rA[0]))));

        gA[0] = rA[0] + shift;
        if (gA[0] > 6.28) {
            gA[0] -= 6.28;
        }
        driver.setGS(1, (uint16_t)(mag*(1+sin(gA[0]))));

        bA[0] = rA[0] + (2.0 * shift);
        if (bA[0] > 6.28) {
            bA[0] -= 6.28;
        }
        driver.setGS(2, (uint16_t)(mag*(1+sin(bA[0]))));

        for (uint8_t i=1; i<5; i++) {
            rA[i] = rA[i-1] + 1.26;
            if (rA[i] > 6.28) {
                rA[i] -= 6.28;
            }
            driver.setGS(3*i, (uint16_t)(mag*(1+sin(rA[i]))));

            gA[i] = gA[i-1] + 1.26;
            if (gA[i] > 6.28) {
                gA[i] -= 6.28;
            }
            driver.setGS(3*i+1, (uint16_t)(mag*(1+sin(gA[i]))));

            bA[i] = bA[i-1] + 1.26;
            if (bA[i] > 6.28) {
                bA[i] -= 6.28;
            }
            driver.setGS(3*i+2, (uint16_t)(mag*(1+sin(bA[i]))));
        }

        driver.refreshGS();
        count++;
        */

        // waterfall thingy
        /*
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
        */

        // cylon stuff
        /*
        if (count > 10) {
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

void cosineVal(uint8_t* v, uint16_t t) {
    uint16_t time = t;
    while (time > 383) {
        time -= 384;
    }
    uint8_t zone = time/128;
    while (time > 127) {
        time -= 128;
    }
    uint8_t cosine = sine256(time + 64);
    if (zone == 0) {
        v[0] = cosine;
        v[1] = 255 - cosine;
        v[2] = 0;
    }
    else if (zone == 1) {
        v[0] = 0;
        v[1] = cosine;
        v[2] = 255 - cosine;
    }
    else {
        v[0] = 255 - cosine;
        v[1] = 0;
        v[2] = cosine;
    }
}