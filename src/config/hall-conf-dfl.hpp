/** 
 * @file        hall-conf-dfl.hpp
 * @brief       Hall Switch Default Library Configuration
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */


#ifndef HALL_CONF_DFL_HPP_
#define HALL_CONF_DFL_HPP_

#ifndef HALL_SPEED_ENABLED
#define HALL_SPEED_ENABLED              1           /**< Hall speed functionality enabled (1) / Disabled (0) */
#endif

#ifndef HALL_SWITCH_FRAMEWORK 
#error  "Hall switch error framework undefined"     /**< Hall switch framework must be defined in conf. or at compilation */
#endif

#endif /** HALL_CONF_DFL_HPP_ **/