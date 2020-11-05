/** 
 * @file        hall-platf-rpi.hpp
 * @brief       Hall Raspberry Pi Hardware Platforms
 * @date        August 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef HALL_PLATF_RPI_HPP_
#define HALL_PLATF_RPI_HPP_

#include "../pal/hall-pal-rpi.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_RPI)

/**
 * @addtogroup hsrpihw
 * @{
 */

/**
 * @brief Raspberry Pi Hardware Platform Pins
 */
typedef struct 
{
    uint8_t output;     /**< Output pin */
    uint8_t power;      /**< Power pin */
} PlatformRpi_t;

extern PlatformRpi_t TLE4964_3M_S2Go_Rpi_Adapter_Slot_1;            /**< Raspberry Pi >=2 with Shield2Go Adapter and Hall Switch Shield2Go on Slot 1. */
extern PlatformRpi_t TLE4964_3M_S2Go_Rpi_Adapter_Slot_2;            /**< Raspberry Pi >=2 with Shield2Go Adapter and Hall Switch Shield2Go on Slot 2. */
extern PlatformRpi_t TLE4964_3M_S2Go_Rpi_Adapter_Slot_3;            /**< Raspberry Pi >=2 with Shield2Go Adapter and Hall Switch Shield2Go on Slot 3. */

/** @} */

#endif /** HALL_SWITCH_FRAMEWORK **/
#endif /** HALL_PLATF_RPI_HPP_ **/