/** 
 * @file        hall-platf-rpi.cpp
 * @brief       Hall Raspberry Pi Hardware Platforms
 * @date        August 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "hall-platf-rpi.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_RPI)

/**
 * @addtogroup hsrpihw
 */

PlatformRpi_t TLE4964_3M_S2Go_Rpi4     =  {4, UNUSED_PIN};    /**< Raspberry Pi 4 with Shield2Go Adapter and Hall Switch Shield2Go. */

#endif /** HALL_SWITCH_FRAMEWORK **/
/** @} */