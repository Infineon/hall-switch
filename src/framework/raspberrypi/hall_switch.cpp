#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include "hall-switch-rpi.hpp"

/**
 * Minimal example: Read B field with Raspberry Pi.
 */

//#define HALL_SWITCH_FRAMEWORK HALL_SWITCH_FRMWK_RPI

HallSwitchRpi    hs( TLE4964_3M_S2Go_Rpi2 );

int main() {
	int err = 0;
	err = hs.init();
	if (0 > err) printf( "Hall Switch init error: %d\n", err );

	printf("Hall Switch started.\n");

	while (true) {
		hs.updateBField();
		printf( "Hall switch status: %d\n", hs.getBField() );
		sleep(1);
	}

	return 0;
}
