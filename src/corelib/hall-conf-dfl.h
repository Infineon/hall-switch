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

#define HALL_SWITCH_FRAMEWORK_ARDUINO   0x00U
#define HALL_SWITCH_FRAMEWORK_WICED     0x01U

#ifndef HALL_SWITCH_FRAMEWORK 
#error  "Hall switch error framework undefined"
#define HALL_SWITCH_FRAMEWORK 
#endif

#ifndef HALL_SWITCH_PLATFORM    
#define HALL_SWITCH_PLATFORM    HALL_SWITCH_PLATF_ALL
#endif

//#define HALL_SWITCH_FRAMEWORK   HALL_SWITCH_FRAMEWORK_ARDUINO
#define HALL_SWITCH_MCU_BOARD           
#define XMC2GO
#define UNO_PLUS_MY_IOT_ADAPTER_SOCKET23

#define HALL_SWITCH_SENSOR_SHIELD

#define SPEED_SENSOR_2GO_KIT_TLE4922

#define HALL_SWITCH_PLATF_ARD_XM2GO_TLE     0x00U
#define HALL_SWITCH_PLATF_ARD_UNO_          0x
#define HALL_SWITCH_PLATF_KIT2GO_SPEED_
#define HALL_SWITCH_PLAT_WICED_

#endif /** HALL_CONF_DFL_H_ **/