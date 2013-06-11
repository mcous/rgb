#include "TLC5940.h"
TLC5940 driver;
int colors[100];
boolean run = true;
int leds[] = 
{
  255, 0, 0,
  0, 255, 0,
  0, 0, 255,
  255, 255, 0,
  255, 0, 255,
  0
};
int i = 0;
int j = 0;
  

void setup() {
  // set dc values
    allDC(5);
    // set some initial values for the leds
    allGSOff();
    // initialize dot correction on the led driver
    driver.init();
    
    Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    leds[i] = Serial.read();
    i++;
    if(i > 15) {
      i = 0;
      Serial.flush();
    }
  }
  setGS();
  driver.refreshGS();
}

void setGS() {
  for (uint8_t i=0; i<15; i++) {
    driver.setGS(i, leds[i]);
  }
}

void allGSOn(int all) {
  for (uint8_t i=0; i<15; i++) {
    driver.setGS(i, all);
  }
}

void allGSOff() {
  for (uint8_t i=0; i<15; i++) {
    driver.setGS(i, 0);
  }
}

void allDC(int n) {
  for (uint8_t i=0; i<15; i++) {      
    driver.setDC(i, n);
  }
}
