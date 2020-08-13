/** 
 * @file        hall-switch-rpi.hpp
 * @brief       Hall Switch Raspberry Pi API
 * @date        August 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef HALL_SWITCH_RPI_H_
#define HALL_SWITCH_RPI_H_

#include "../../../config/hall-conf.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_RPI)

#include <stdint.h>
#include "hall-switch.hpp"
#include "hall-platf-rpi.hpp"

/**
 * @addtogroup hsrpiapi
 * @{
 */
 
class HallSwitchRpi : public HallSwitch
{
    public:

        HallSwitchRpi();
        
        HallSwitchRpi(PlatformRpi_t hwPlatf,
                        CBack_t         cBack      = NULL);

};

/** @} */

#endif /** HALL_SWITCH_FRAMEWORK **/
#endif /** HALL_SWITCH_RPI_HPP_ **/
