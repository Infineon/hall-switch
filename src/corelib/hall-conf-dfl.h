/** 
 * @file        hall-conf-dfl.h
 * @brief       Hall Switch Default Library Configuration
 *              Preprocessor library configuration. 
 *              Enables conditional compiling of relevant library modules.
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 */


#ifndef HALL_CONF_DFL_H_
#define HALL_CONF_DFL_H_

/**
 * @ 
 */
#ifndef HALL_SPEED_ENABLED
#define HALL_SPEED_ENABLED  1
#endif

#define HALL_SWITH_DEVICE       

#define HALL_SWITCH_PLATFORM    HALL_SWITCH_WICED

#define HALL_SWITCH_FRAMEWORK_ARDUINO   0x00U
#define HALL_SWITCH_FRAMEWORK_WICED     0x01U

#define HALL_SWITCH_FRAMEWORK   HALL_SWITCH_FRAMEWORK_ARDUINO

#endif /** HALL_CONF_DFL_H_ **/