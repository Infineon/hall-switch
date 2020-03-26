/** 
 * @file        hall-switch-wiced.h
 * @brief       Hall Switch GPIO WICED Hardware Interface
 * @date        January 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 */

#ifdef HALL_SWITCH_WICED_PLATFORM_ENABLED

#ifndef HALL_SWITCH_WICED_H_
#define HALL_SWITCH_WICED_H_

#include <stdint.h>
#include "hall-switch.h"
#include "wiced_platform.h"
 
class HallSwitchWiced : public HallSwitch
{
    public:
        /**
         * @addtogroup hallswitchwicedhal
         * @{
         */

        /**
         * @brief WICED Hardware Platform
         */
        typedef struct
        {
            wiced_gpio_t output;     /**< Output pin */
            wiced_gpio_t power;      /**< Power pin */
        }WICEDHwPlatf_t;


        HallSwitchWiced(wiced_gpio_t    outputPin,
                        CBack_t         cBack      = NULL,
                        wiced_gpio_t    powerPin   = UNUSED_PIN);
        HallSwitchWiced(WICEDHwPlatf_t  &hwPlatf,
                        CBack_t         cBack      = NULL);
        /** @} */
};

#endif /** HALL_SWITCH_WICED_H_ **/

#endif