/** 
 * @file        hall-switch-wiced.hpp
 * @brief       Hall Switch WICED API
 * @date        January 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef HALL_SWITCH_WICED_H_
#define HALL_SWITCH_WICED_H_

#include "../../../config/hall-conf.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_WICED)

#include <stdint.h>
#include "hall-switch.hpp"
#include "hall-platf-wiced.hpp"
#include "wiced_platform.h"

/**
 * @addtogroup hswicedapi
 * @{
 */
 
class HallSwitchWiced : public HallSwitch
{
    public:

        HallSwitchWiced(wiced_gpio_t    outputPin,
                        CBack_t         cBack      = NULL,
                        wiced_gpio_t    powerPin   = UNUSED_PIN);
        HallSwitchWiced(PlatformWICED_t hwPlatf,
                        CBack_t         cBack      = NULL);

};

/** @} */

#endif /** HALL_SWITCH_FRAMEWORK **/
#endif /** HALL_SWITCH_WICED_HPP_ **/
