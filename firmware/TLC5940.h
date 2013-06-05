// header file for tlc5940 class for atmega chips

// headers necessary for this file
#include <avr/io.h>

// communication pins - set appropriately
// greyscale clock - B0
#define DDR_GSCLK  DDRB
#define PORT_GSCLK PORTB
#define GSCLK_PIN  0
// serial clock - B5
#define DDR_SCLK  DDRB
#define PORT_SCLK PORTB
#define SCLK_PIN  5
// dc programming select - D4
#define DDR_DCPRG  DDRD
#define PORT_DCPRG PORTD
#define DCPRG_PIN  4
// programming select - D5
#define DDR_VPRG  DDRD
#define PORT_VPRG PORTD
#define VPRG_PIN  5
// latch - B2
#define DDR_XLAT  DDRB
#define PORT_XLAT PORTB
#define XLAT_PIN  2
// blank outputs - B1
#define DDR_BLANK  DDRB
#define PORT_BLANK PORTB
#define BLANK_PIN  1
// serial data master out slave in - B3
#define DDR_MOSI  DDRB
#define PORT_MOSI PORTB
#define MOSI_PIN  3


class TLC5940 {
public:
    // constructor (don't need a destructor)
    TLC5940();
    // initialize dot correction to 0
    initDC();

private:


};