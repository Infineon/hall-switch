

// #ifdef XMC1100_XMC2GO                                       /**< xmc2go + Shield2Go  */ 
// ArdHwPlatfPins_t TLE4964_3M_S2Go_Pins = {9, UNUSED_PIN};    /**< Pin connected to Q1 */                                                      
// #elif ((XMC1100_Boot_Kit) \
//       || (XMC4700_Relax_Kit) \
//       || (ARDUINO_AVR_UNO))                                 /**< xmc arduino and arduino uno boards */  
// ArdHwPlatfPins_t TLE4964_3M_S2Go_Pins = {3, UNUSED_PIN};    /**< Pin connected to Q1 */
// #else
//     # error "Board not yet defined. Please define the specific Arduino boards Pins"
// #endif

// ArdHwPlatfPins_t TLE4922_2GoKit_Pins = {1, UNUSED_PIN};

#include "hall-platf-ino.h"

/**
 * @addtogroup Arduino Platforms
 */
/**
 * @addtogroup tle49643m
 * @{
 */ 

PlatformIno_t TLE4964_3M_S2Go_XMC2Go = {9, UNUSED_PIN};      /**< TLE4964 3M Shield 2Go + XMC2Go Stack */
PlatformIno_t TLE4964_3M_S2Go_ArduinoUno = {3, UNUSED_PIN};   /**< TLE4964 3M Shield 2Go + MyIoT + Arduino Uno Form Factor */

/** @} */

/**
 * @addtogroup tle4922
 * @{
 */ 

/**
 * @name TLE4922
 */
PlatformIno_t TLE4922_2GoKit_Pins = {1, UNUSED_PIN};     /**< TLE4922 Kit 2Go  */

/** @} */
/** @} */