// low level tlc5940 class for atmega microcontrollers

#include "TLC5940.h"

// initilize pin modes and values in constructor
TLC5940::TLC5940(void) {
    // set control pins to outputs and initial values
    // gsclk
    DDR_GSLCK |= (1 << GSCLK_PIN);
    PORT_GSLCK &= ~(1 << GSCLK_PIN);
    // sclk
    DDR_SCLK |= (1 << SCLK_PIN);
    PORT_SCLK &= ~(1 << SCLK_PIN);
    // dcprg
    DDR_DCPRG |= (1 << DCPRG_PIN);
    PORT_DCPRG &= ~(1 << DCPRG_PIN);
    // vprg
    DDR_VPRG |= (1 << VPRG_PIN);
    PORT_VPRG |= (1 << VPRG_PIN);
    // xlat
    DDR_XLAT |= (1 << XLAT_PIN);
    PORT_XLAT &= ~(1 << XLAT_PIN);
    // blank
    DDR_BLANK |= (1 << BLANK_PIN);
    PORT_BLANK |= (1 << BLANK_PIN);
    // serial data master out slave in
    DDR_MOSI |= (1 << MOSI_PIN);
    PORT_MOSI &= ~(1 << MOSI_PIN);
}

void TLC5940::initDC(void) {
    // set dcprg to 1 (don't use eeprom data)
    PORT_DCPRG |= (1 << DCPRG_PIN);
    // set vprg to 1 (program dc data)
    PORT_VPRG |= (1 << VPRG_PIN);
    // set serial data to low (setting dc to 0)
    PORT_MOSI &= ~(1 << MOSI_PIN)
    // pulse the serial clock 96 times to write in dc data
    for (uint8_t i=0; i<96; i++) {
        PORT_SCLK |= (1 << SCLK_PIN);
        PORT_SCLK &= ~(1 << SCLK_PIN);
    }
    // pulse xlat to latch the data
    PORT_XLAT |= (1 << XLAT_PIN);
    PORT_XLAT &= ~(1 << XLAT_PIN);
}