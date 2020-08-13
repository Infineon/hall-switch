#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include "hall-switch-rpi.hpp"

//#define HALL_SWITCH_FRAMEWORK HALL_SWITCH_FRMWK_RPI

HallSwitchRpi    hs( TLE4964_3M_S2Go_Rpi4 );

int main() {
	printf( "Setup status: %d\n", hs.init() );
	
	while (true) {
		hs.updateBField();
		printf( "Hall switch status: %d\n", hs.getBField() );
		sleep(1);
	}

	return 0;
}
