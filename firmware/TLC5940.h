// header file for TLC5940

class TLC5940 {
public:
    // constructor (don't need a destructor)
    TLC5940();
    // set dot correction - 6 bits per led
    setDC(uint8_t* dc);
    // set greyscale brightness - 12 bits per led
    setGS(uint16_t* gs);

private:


};