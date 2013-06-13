// rgb
// daisy-chainable lighting module
// http://github.com/mcous/rgb
//
// copyright 2013 michael cousins and authors listed in http://github.com/mcous/rgb/AUTHORS.md
// shared under the terms of the mit licence

// header file for light effects class using a tlc5940

#ifndef EFFECTS_H
#define EFFECTS_H

// includes necessary for this header
#include "TLC5940.h"

// effect defines
#define SUPERDOME 1
#define CYLON 2

class Effects {
public:
    // constructor
    Effects();
    // set the current effect
    void setEffect(uint8_t eff);
    // refresh the display
    void refresh();

private:
    // TLC5940 led driver
    TLC5940 driver;
    // overflow counter
    uint16_t count;
    // 5x3 array for led values (5x RGB led, where each RGB is 3 leds)
    uint8_t leds[5][3];
    // counter step for effects (bigger step = faster effects)
    uint8_t step;   
    // custom parameters for effects
    uint8_t param[4];

    // current effect function handle
    void (Effects::*cF)(void);
    // superdome show
    void superDome(void);
    // cylon
    void cylon(void);

    // effect helper functions
    // sets all leds to the same color
    void rgb(uint16_t r, uint16_t g, uint16_t b);
    // saves to v the rgb values for a cosine-wave based rainbow given a time t (T = 384)
    void cosineVal(uint8_t* v, uint16_t t);
};

#endif