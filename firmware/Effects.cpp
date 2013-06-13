//Effects file

#include "Effects.h"
#include <math.h>
#include "sinetable.h"
// defines
// taylor series sin expansion
//#define sin_t(a) (a-(pow(a,3.0)/6.0)+(pow(a,5.0)/120.0)-(pow(a,7.0)/5040.0))

Effects::Effects() {
    for (uint8_t i=0; i<15; i++) {
        driver.setDC(i, 5);
    }
    // set some initial values for the leds
    for (uint8_t i=0; i<15; i++) {
        driver.setGS(i, 0);
    }

    // initialize dot correction on the led driver
    driver.init();
}

void Effects::setEffect(uint8_t eff) {
    switch ( eff ) {

    case SUPERDOME:
        //shift
        param[0] = 76;
        
        //speed of functions
        step = 1;
        cF = (void *)Effects::&superDome;
        break;

    case CYLON:
        //current LED
        param[1] = 0;
        //last LED
        param[2] = 0;
        //direction
        param[3] = 1;

        //speed
        step = 1;

        cF = &Effects::cylon;
        break;
    }  
}

void Effects::refresh() {
    count += step;
    (*cF)();
}


void * Effects::superDome(void *) {
    //super dome effect function   

    if (count > 383) {
        count = 0;
    }
    for (uint8_t i=0; i<5; i++) {
        cosineVal(leds[i], count+param[0]*i);
        driver.setGS(i*3, leds[i][0]);
        driver.setGS(i*3+1, leds[i][1]);
        driver.setGS(i*3+2, leds[i][2]);
    }
    driver.refreshGS();
}

void Effects::cylon() {
	//cylon variables
    
    if (count > 10) {
        count = 0;
        param[2] = param[1];
        if (param[2] <=2) {
            param[3] = 1;
            
            // sets next color
            /*
            param[1] = track;
            track = (track < 2) ? (track + 1) : 0;
            */
        }
        else if (param[2] >= 12) {
            param[3] = -1;
        
            /*
            param[1] = 12 + track;
            // sets next color
            track = (track < 2) ? (track + 1) : 0;
            */
        }
        param[1] += 3*param[3];
    }
    driver.setGS(param[2], 0);
    driver.setGS(param[1], 500);
    driver.refreshGS();
}
        
        //bouncing color
        //uint8_t track = 0;
        /*
        // white end clears
        if (last <=2) {
            driver.setGS(0, 0);
            driver.setGS(1, 0);
            driver.setGS(2, 0);
        }
        else if (last >= 12) {
            driver.setGS(12, 0);
            driver.setGS(13, 0);
            driver.setGS(14, 0);
        }
        else { driver.setGS(last, 0); }

        //white end sets
        if (param[1] <= 2) {
            driver.setGS(0, 500);
            driver.setGS(1, 500);
            driver.setGS(2, 500);
        }
        else if (param[1] >= 12) {
            driver.setGS(12, 500);
            driver.setGS(13, 500);
            driver.setGS(14, 500);
        }
        else { driver.setGS(param[1], 500); }
        */



void Effects::rgb(uint16_t r, uint16_t g, uint16_t b) {
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

void Effects::cosineVal(uint8_t* v, uint16_t t) {
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
