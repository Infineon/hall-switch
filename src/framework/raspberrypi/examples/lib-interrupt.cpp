#include <stdint.h>
#include <stdio.h>
#include "hall-switch-rpi.hpp"

/**
 * Use interrupt to trigger on change of Bfield (Raspberry Pi).
 * 
 * Note:
 * Don't forget to define HALL_SWITCH_FRAMEWORK as HALL_SWITCH_FRMWK_RPI
 * in src/config/hall-conf.hpp.
 */

void IntCBack(HallSwitch::Result_t result)
{
	if(result == HallSwitch::Result_t::B_FIELD_ON)
    {
		printf( "Interrupt: B Field on.\n");
	}
    else if(result == HallSwitch::Result_t::B_FIELD_OFF)
    {
		printf( "Interrupt: B Field off.\n");
	}
}

HallSwitchRpi hs( TLE4964_3M_S2Go_Rpi2, IntCBack );

int main() {
	int err = 0;
	
	err = hs.init();
	if (0 > err)
		printf( "Hall Switch init error: %d\n", err );
	else
		printf("Hall Switch started.\n");

	err = hs.enable();
	if (0 > err)
		printf( "Hall Switch interrupt error: %d\n", err );
	else
		printf("Hall Switch interrupt enabled.\n");

	while (true) {}

	return 0;
}