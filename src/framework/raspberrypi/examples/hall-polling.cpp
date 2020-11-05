#include <stdint.h>
#include <stdio.h>
#include "hall-switch-rpi.hpp"

/**
 * Raspberry Pi Example
 * 
 * Read B field level continuosly.
 * 
 * Note:
 * Don't forget to define HALL_SWITCH_FRAMEWORK as HALL_SWITCH_FRMWK_RPI
 * in src/config/hall-conf.hpp.
 */

/** Create Hall Switch Object
 * 
 * Frameworks:
 * TLE4964_3M_S2Go_Rpi_Adapter_Slot_1	TLE4964_3M Shield2Go on Slot 1 of Infineon's Shield2Go Adapter on a Raspberry Pi >= 2.
 * TLE4964_3M_S2Go_Rpi_Adapter_Slot_2	TLE4964_3M Shield2Go on Slot 2 of Infineon's Shield2Go Adapter on a Raspberry Pi >= 2.
 * TLE4964_3M_S2Go_Rpi_Adapter_Slot_3	TLE4964_3M Shield2Go on Slot 3 of Infineon's Shield2Go Adapter on a Raspberry Pi >= 2.
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
