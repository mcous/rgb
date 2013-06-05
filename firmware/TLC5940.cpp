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

    // initialize variables for safety
    gsFirstCycle = false;
    gsCount = 0;
    dataCount = 0;
}

// fill the dot correction register with 0s
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

// refresh the led display and data
void TLC5940::refreshGS(void) {
    // if vprg is high
    if (PORT_VPRG & (1 << VPRG_PIN)) {
        // set it low
        PORT_VPRG &= ~(1 << VPRG_PIN)
        // set the first cycle flag (just came out of a dc cycle)
        gsFirstCycle = true;
    }
    // reset gs and data counters
    gsCount = 0;
    dataCount = 0;
    // enable leds
    PORT_BLANK &= ~(1 << BLANK_PIN);
    // loop through a gs cycle and post-increment gs counter
    while (gsCount++ < 4095) {
        // if there's data to clock in
        if (dataCount < 191) {
            // get the bit the tlc5940 is expecting from the gs array (tlc expects msb first)
            uint8_t data = (gs[(191 - dataCount)/12]) & (1 << (191 - dataCount)%12);
            // set mosi if bit is high, clear if bit is low
            if (data) {
                PORT_MOSI |= (1 << MOSI_PIN);
            }
            else {
                PORT_MOSI &= ~(1 << MOSI_PIN);
            }
            // pulse the serial clock
            PORT_SCLK |= (1 << SCLK_PIN);
            PORT_SCLK &= ~(1 << SCLK_PIN);
            // increment data counter
            dataCount++;
        }
        // pulse the gs clock
        PORT_GSCLK |= (1 << GSCLK_PIN);
        PORT_GSCLK &= ~(1 << GSCLK_PIN);
    }
    // disable leds before latching in new data
    PORT_BLANK |= (1 << BLANK_PIN);
    // pulse xlat to save new gs data
    PORT_XLAT |= (1 << XLAT_PIN);
    PORT_XLAT &= ~(1 << XLAT_PIN);
    // check if this was the first gs cycle after a dc cycle
    if (gsFirstCycle) {
        // pulse serial clock once if it is (because the datasheet tells us to)
        PORT_SCLK |= (1 << SCLK_PIN);
        PORT_SCLK &= ~(1 << SCLK_PIN);
    }
    gsFirstCycle = false;
}

// set the brightness of an individual led
void TLC5940::setGS(uint8_t led, uint16_t val) {
    // basic parameter checking
    // check if led is inbounds
    if (led < 16) {
        // if value is out of bounds, set to max
        if (val < 4096) {
            gs[led] = val;
        }
        else {
            gs[led] = 4095;
        }
    }
}