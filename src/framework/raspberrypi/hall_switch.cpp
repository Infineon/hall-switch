#include <stdint.h>
#include <iostream>
#include "hall-switch-rpi.hpp"

//#define HALL_SWITCH_FRAMEWORK HALL_SWITCH_FRMWK_RPI

HallSwitchRpi    hallSwitch;

int main() {
	hallSwitch.init();
}
