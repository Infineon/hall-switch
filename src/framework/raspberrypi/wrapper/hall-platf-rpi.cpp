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

PlatformRpi_t TLE4964_3M_S2Go_Rpi_Adapter_Slot_1             =  {4, UNUSED_PIN}; /**< Raspberry Pi >=2 with Shield2Go Adapter and Hall Switch Shield2Go on Slot 1. */
PlatformRpi_t TLE4964_3M_S2Go_Rpi_Adapter_Slot_2             =  {5, UNUSED_PIN}; /**< Raspberry Pi >=2 with Shield2Go Adapter and Hall Switch Shield2Go on Slot 2. */
PlatformRpi_t TLE4964_3M_S2Go_Rpi_Adapter_Slot_3             =  {0, UNUSED_PIN}; /**< Raspberry Pi >=2 with Shield2Go Adapter and Hall Switch Shield2Go on Slot 3. */

#endif /** HALL_SWITCH_FRAMEWORK **/
/** @} */