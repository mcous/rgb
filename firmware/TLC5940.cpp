// low level tlc5940 class for atmega microcontrollers

#include "TLC5940.h"

// initilize pin modes and values in constructor
TLC5940::TLC5940(void) {
    // set control pins to outputs and initial values
    // gsclk
    DDR_GSLCK |= (1 << GSCLK);
    PORT_GSLCK &= ~(1 << GSCLK);
    // sclk
    DDR_SCLK |= (1 << SCLK);
    PORT_SCLK &= ~(1 << SCLK);
    // dcprg
    DDR_DCPRG |= (1 << DCPRG);
    PORT_DCPRG &= ~(1 << DCPRG);
    // vprg
    DDR_VPRG |= (1 << VPRG);
    PORT_VPRG |= (1 << VPRG);
    // xlat
    DDR_XLAT |= (1 << XLAT);
    PORT_XLAT &= ~(1 << XLAT);
    // blank
    DDR_BLANK |= (1 << BLANK);
    PORT_BLANK |= (1 << BLANK);
}

void TLC5940::initDC(void) {
    
}