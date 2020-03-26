
#ifdef HALL_SWITCH_WICED_PLATFORM_ENABLED

#include "hall-cypress-platf.h"

/**
 *  TLE4964 3M Shield 2Go + MyIOT Adapter + CYW943907AEVAL1F Eval Kit
 */
HallSwitchWiced::WICEDHwPlatf_t TLE4964_3M_S2Go_MyIoT_CYW943907AEVAL1F =
{
    .output = WICED_GPIO_9,
    .power  = UNUSED_PIN
};

#endif