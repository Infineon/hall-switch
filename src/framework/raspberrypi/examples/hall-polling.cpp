#include <stdint.h>
#include <stdio.h>
#include "hall-switch-rpi.hpp"

/**
 * Minimal example: Read B field with Raspberry Pi.
 * 
 * Note:
 * Don't forget to define HALL_SWITCH_FRAMEWORK as HALL_SWITCH_FRMWK_RPI
 * in src/config/hall-conf.hpp.
 */

HallSwitchRpi    hs( TLE4964_3M_S2Go_Rpi_Adapter_Slot_1 );

int main() {
	int err = 0;
	err = hs.init();
	if (0 > err) printf( "Hall Switch init error: %d\n", err );

	printf("Hall Switch started.\n");

	while (true) {
		hs.updateBField();
		printf( "Hall switch status: %d\n", hs.getBField() );
		delay(500);
	}

	return 0;
}
