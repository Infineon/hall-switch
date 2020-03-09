/** 
 * @file        hall-switch.h
 * @brief       Hall Switch Hardware Abstraction Layer
 * @date        July 2019
 * @copyright   Copyright (c) 2019 Infineon Technologies AG
 */

#ifndef HALL_SWITCH_H_
#define HALL_SWITCH_H_

#include <stdlib.h>
#include <stdint.h>

/**
 * @class HallSwitch
 */

class HallSwitch
{
    public:
        /**
         * @addtogroup hallswitchdatat
         * @{
         */

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

        /** @} */

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
                                ~HallSwitch  ();
        HallSwitch::Error_t     begin        ();
        HallSwitch::Error_t     end          ();
        HallSwitch::Error_t     enable       ();
        HallSwitch::Error_t     disable      ();
        HallSwitch::Status_t    getStatus    ();
        HallSwitch::Result_t    readBField   ();
        HallSwitch::Result_t    getBField    ();
        void                    callback     ();

    protected:

        Status_t    status;             /**< Status */
        GPIO        *output;            /**< Output GPIO hardware interface pointer */
        Result_t    bfieldVal;          /**< Magnetic field value */
        
        CBack_t     cBack;              /**< Interrupt mode callback function  */
        MeasMode_t  measMode;           /**< Measuring mode */
        
        GPIO        *power;             /**< Power switch controller mode GPIO hardware interface pointer */
        PowerMode_t powerMode;          /**< Power mode */
        
    /**
     * @brief       Asserts the hall switch hardware interface functions 
     * @param[in]   _f  Function call
     * @retval      INTF_ERROR if hardware interface error
     */ 
    #define INTF_ASSERT(_f)  {GPIO::Error_t err = _f; \
                             if(err != GPIO::Error_t::OK) return HallSwitch::Error_t::INTF_ERROR;}
            
};

/**
 * @class GPIO
 */
/**
 * @addtogroup hallswitchhwi
 * @{
 */ 
class HallSwitch::GPIO
{    
    public:  
        /**
         * @name    Error codes
         * @{
         */
        enum Error_t
        {
            OK               =  0,      /**< No error */
            INIT_ERROR       = -1,      /**< Initialization error */
            READ_ERROR       = -2,      /**< Read error */
            WRITE_ERROR      = -3,      /**< Write error */
        };
        /** @} */
        
        /**
         * @name   Interrupt event
         * @{
         */
        enum IntEvent_t
        {
            INT_FALLING_EDGE   = 0,     /**< Interrupt on falling edge */
            INT_RISING_EDGE    = 1,     /**< Interrupt on rising edge */
        };
        /** @} */
        
        /**
         * @name    Voltage level
         * @{
         */
        enum VLevel_t
        {
            GPIO_LOW   = 0,        /**< Level low */
            GPIO_HIGH  = 1         /**< Level high */
        };        
        /** @} */      
        
        /**
         * @name    Voltage logic
         * @{
         */
        enum VLogic_t
        {
            NEGATIVE = 1,       /**< Negative logic. 0 on voltage level high, 1 on voltage low */
            POSITIVE = 2,       /**< Positive logic. 1 on voltage level high, 0 on voltage low */
        };
        /** @} */

        /**
         * @brief       Initializes the GPIO
         * @return      GPIO error code
         * @retval      OK if success
         * @retval      INIT_ERROR if initialization error
         */
        virtual Error_t        init        () = 0;
        
        /**
          * @brief       Deinitializes the GPIO
          * @return      GPIO error code
          * @retval      OK if success
          * @retval      INIT_ERROR if deinitialization error
         */
         virtual Error_t       deinit      () = 0;

        /**
         * @brief       Enables the hardware interrupt
         * @param[in]   *ptr HallSwith object pointer which holds the interrupt
         * @return      GPIO error code
         * @retval      OK if success
         * @retval      INIT_ERROR if initialization error
         */
        virtual Error_t        enableInt   (HallSwitch *ptr) = 0;
        
        /**
         * @brief       Disables the hardware interrupt
         * @return      GPIO error code
         * @retval      OK if success
         * @retval      INIT_ERROR if disable error
         */
        virtual Error_t        disableInt  () = 0;

        /**
         * @brief       Gets the latest interrupt event 
         * @return      GPIO interrupt event
         * @retval      INT_FALLING_EDGE if falling edge event
         * @retval      INT_RISING_EDGE if rising edge event
         */
        virtual IntEvent_t     intEvent    () = 0;
        
        /**
         * @brief       Reads the GPIO voltage level
         * @return      GPIO voltage level
         * @retval      GPIO_LOW if voltage low
         * @retval      GPIO_HIGH if voltage high
         */
        virtual VLevel_t       read        () = 0;
        
        /**
         * @brief       Writes the GPIO output voltage level
         * @param[in]   level  Voltage level
         * @return      GPIO error code
         * @retval      OK if success
         * @retval      WRITE_ERROR if write error
         */
        virtual Error_t        write       (VLevel_t level) = 0;

        /**
         * @brief       Enables the GPIO output according to the GPIO logic
         *              - Low if negative
         *              - High if positive
         * @return      GPIO interrupt event
         * @retval      OK if success
         * @retval      WRITE_ERROR if write error
         */
        virtual Error_t        enable      () = 0;

        /**
         * @brief       Disables the GPIO output according to the GPIO logic
         *              - Low if positive
         *              - High if negative
         * @return      GPIO error code
         * @retval      OK if success
         * @retval      WRITE_ERROR if write error
         */
        virtual Error_t        disable     () = 0;
};
/** @} */



/**
 * @class Interrupt
 */ 
/**
 * @addtogroup hallswitchhwi
 * @{
 */ 
class HallSwitch::Interrupt
{
    private:
        #define             GPIO_INT_PINS       4           /**< Maximum hardware interrupt signals */
        static uint8_t      idxNext;                        /**< Interrupt array allocation index*/
        static HallSwitch   *objPtrVector[GPIO_INT_PINS];   /**< Hall switch object pointers vector */
        static void         *fnPtrVector[GPIO_INT_PINS];    /**< Hall switch interrupt function handlers vector */
        static void         int0Handler ();
        static void         int1Handler ();
        static void         int2Handler ();
        static void         int3Handler ();
    public:
        static void         *isrRegister(HallSwitch *objPtr);
};
/** @} */

        
#endif /** HALL_SWTICH_H_ **/
