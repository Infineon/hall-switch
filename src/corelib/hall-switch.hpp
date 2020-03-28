/** 
 * @file        hall-switch.hpp
 * @brief       Hall Switch API
 * @date        July 2019
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef HALL_SWITCH_HPP_
#define HALL_SWITCH_HPP_

#include <stdlib.h>
#include <stdint.h>


/**
 * @addtogroup hscorelib
 * @{
 */

class HallSwitch
{
    public:

        /**
         * @name    Error codes
         * @{
         */
        enum Error_t
        {
            OK           =  0,      /**< No error */
            INTF_ERROR   = -1,      /**< Interface error */
            CONF_ERROR   = -2,      /**< Configuration error */
        };
        /** @} */

        /**
         * @name    Power modes
         * @{
         */
        enum PowerMode_t
        {
            MAIN         = 1,    /**< Same as MCU VDD supply signal */
            SWITCH       = 2,    /**< Switched controlled power from MCU */
        };
        /** @} */

        /**
         * @name   Status
         * @{
         */
        enum Status_t
        {
            UNINITED    = 0,         /**< Not initialized */
            INITED      = 1,         /**< Initialized (external interfaces initialized) */
            POWER_ON    = 2,         /**< Power on */  
            POWER_OFF   = 3,         /**< Power off */
        };
        /** @} */

        /**
         * @name    Measuring mode
         * @{
         */
        enum MeasMode_t
        {
            POLLING     = 1,    /**< Polling mode */
            INTERRUPT   = 2,    /**< Interrupt mode */
        };
        /** @} */

        /**
         * @name  Magnetic field value
         * @{
         */
        enum Result_t
        {
            B_FIELD_UNDEF = -1,     /**< Output default high. Undefined at initialization */
            B_FIELD_OFF   =  0,     /**< No magnetic field present. Off. Q output high */
            B_FIELD_ON    =  1,     /**< Magnetic field present. On. Q output low */
        };
        /** @} */

        /**
         * @brief       Callback function type for interrupt mode 
         * @param[in]   Result_t B field value. The interrupt read the B field value and will
         *              pass it to the callback
         * @return      void
         */
        typedef void (*CBack_t)(Result_t);

        /**
         * @brief   GPIO Hardware Interface
         */
        class GPIO;

        /**
         * @brief   Interrupt Handler
         */
        class Interrupt;

                    HallSwitch   ();
                    HallSwitch   (GPIO        *output,
                                  CBack_t     cBack   = NULL,
                                  GPIO        *power  = NULL);
                   ~HallSwitch   ();
        Error_t     init         ();
        Error_t     deinit       ();
        Error_t     enable       ();
        Error_t     disable      ();
        Status_t    getStatus    ();
        Error_t     updateBField ();
        Result_t    getBField    ();

    protected:

        Status_t    status;             /**< Status */
        GPIO        *output;            /**< Output GPIO hardware interface pointer */
        Result_t    bfieldVal;          /**< Magnetic field value */
        
        CBack_t     cBack;              /**< Interrupt mode callback function  */
        MeasMode_t  measMode;           /**< Measuring mode */
        
        GPIO        *power;             /**< Power switch controller mode GPIO hardware interface pointer */
        PowerMode_t powerMode;          /**< Power mode */

        virtual void callback   ();
      
};

/** @} */

#endif /** HALL_SWTICH_HPP_ **/
