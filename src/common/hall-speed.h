/** 
 * @file        hall-speed.h
 * @brief       Hall Switch Speed Sensor
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 */

#include "hall-switch.h"

class HallSpeed: protected HallSwitch
{           
    public:
        
        /**
         * @name Speed units
         * @{
         */
         enum SpeedUnit_t
         {
            HERTZ   = 0,    /**< cps - Hertz */
            RADS    = 1,    /**< rads/s */  
            RPM     = 2     /**< RPM */
         };
         /** @} */

        /**
         * @brief Timer Interface
         */
        class Timer;

                    HallSpeed   (GPIO        *output,
                                 Timer       *timer   = NULL,
                                 uint8_t     polesNum = 1,
                                 SpeedUnit_t units    = HERTZ,
                                 CBack_t     cBack    = NULL,
                                 GPIO        *power   = NULL);
        Error_t     begin        ();
        Error_t     end          ();
        Error_t     enable       ();
        Error_t     disable      ();                         
        Error_t     updateSpeed  ();
        double      getSpeed     ();

    private:
        Timer       *timer;             /**< Timer interface pointer */
        bool        speedEnabled;       /**< Speed enabled flag */
        uint8_t     polesPair;          /**< Rotor poles pair number */
        SpeedUnit_t sUnits;             /**< Speed units */
        double      speed;              /**< Rotating speed */

        static const double speedCoeff[3] =
        {
            1000.0,  /**< Hertz - cps (1000 ms)*/
            6283.2,  /**< Rad/s (2pi x 1000 ms) */
            60000.0  /**< RPM  (60 x 1000 ms)*/
        };

        void        callback        ();
        void        calculateSpeed  ();
};


class HallSpeed::Timer
{
    public: 

        /**
         * @brief   Initialiazes the timer
         * @return  Timer error code
         * @retval  OK if success
         * @retval  INIT_ERROR if hardware interface error
         */
        virtual  HallSwitch::Error_t         init    () = 0;

        /**
         * @brief   Deinitialiazes the timer
         * @return  Timer error code
         * @retval  OK if success
         * @retval  INIT_ERROR if hardware interface error
         */
        virtual  HallSwitch::Error_t         deinit   () = 0;

        /**
         * @brief   Starts the timer
         * @return  Timer error code
         * @retval  OK if success
         * @retval  INIT_ERROR if hardware interface error
         */
        virtual  HallSwitch::Error_t         start   () = 0;

        /**
         * @brief       Elapsed time since the timer was started 
         * @param[out]  elapsed Time in milliseconds 
         * @return      Timer error code
         * @retval      OK if success
         * @retval      INIT_ERROR if hardware interface error    
         */
        virtual  HallSwitch::Error_t         elapsed (uint32_t &elapsed) = 0;
        
        /**
         * @brief   Stops the timer
         * @return  Timer error code
         * @retval  OK if success
         * @retval  INIT_ERROR if hardware interface error
         */
         virtual  HallSwitch::Error_t         stop    () = 0;
        
        /**
         * @brief       Introduces a delay during the specified time    
         * @param[in]   timeout    Delay time in milliseconds   
         * @return      Timer error code
         * @retval      OK if success
         * @retval      INIT_ERROR if hardware interface error
         */
        virtual  HallSwitch::Error_t         delay   (uint32_t timeout) = 0;
};