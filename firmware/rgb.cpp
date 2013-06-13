// rgb
// daisy-chainable lighting module
// http://github.com/mcous/rgb
//
// copyright 2013 michael cousins and authors listed in http://github.com/mcous/rgb/AUTHORS.md
// shared under the terms of the mit licence

// main project source file

// includes
#include "rgb.h"

int main (void) {

    // set the desired effect
	lightShow.setEffect(2);

    // back in my day all the pits were bottomless
	for(;;) {
        // refresh the lightshow
		lightShow.refresh();
	}

    // the answer
    return 42;
}
