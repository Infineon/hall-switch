/** 
 * @file        hall-switch-wiced.h
 * @brief       Hall Switch GPIO WICED Hardware Interface
 * @date        January 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 */

#ifndef HALL_SWITCH_WICED_H_
#define HALL_SWITCH_WICED_H_

#include "../../../config/hall-conf.h"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_WICED)

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

#endif /** HALL_SWITCH_FRAMEWORK **/

#endif