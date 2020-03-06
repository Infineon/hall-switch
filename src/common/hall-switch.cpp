/** 
 * @file        hall-switch.cpp
 * @brief       Hall Switch Hardware Abstraction Layer
 *              Features: 
 *              - Polling or interrupt based measuring mode
 *              - GPIO controlled power-on/off interface available
 *              - Flexible hardware platform configuration
 * 
 * @date        July 2019
 * @copyright   Copyright (c) 2019 Infineon Technologies AG
 */

#include "hall-switch.h"

/**
 * @addtogroup hallswitchcpphal
 * @{
 */

/**
 * @brief   Hall Switch Default Constructor
 *          - Hardware interfaces pointers set to NULL
 *          - Default modes polling (for measure mode) and main (for switch power mode)      
 */
HallSwitch::HallSwitch()
{
    status           = UNINITED;
    output           = NULL;
    bfieldVal        = B_FIELD_UNDEF;

    cBack            = NULL;
    measMode         = POLLING;
    
    power            = NULL;
    powerMode        = MAIN;
};

/**
 * @brief       Hall Switch Constructor
 * 
 *   Mandatory arguments: 
 *      - sensor output GPIO pointer
 * 
 *   Optional  arguments: 
 *      - interrupt callback. By default NULL. Required to enable interrupt mode.
 *      - sensor power GPIO pointer (only for switch powered mode platform). By default it is NULL.
 * 
 * @param[in]   *output Sensor output GPIO interface pointer
 * @param[in]   cBack   Callback for interrupt mode. When passed, it enables interrupt mode
 * @param[in]   *power  Sensor switch poewr controller GPIO interface pointer. Default NULL will set power mode to MAIN
 */
HallSwitch::HallSwitch(GPIO         *output,
                       CBack_t      cBack,
                       GPIO         *power)
{
    status              = UNINITED;
    this->output        = output;
    bfieldVal           = B_FIELD_UNDEF;

    this->cBack = cBack;
    if(cBack == NULL)
        this->measMode  = POLLING;
    else
        this->measMode  = INTERRUPT;

    this->power         = power;
    if(this->power == NULL)
        this->powerMode = MAIN;
    else
        this->powerMode = SWITCH;
}

/**
 * @brief   Hall Switch Destructor
 *          Disables the sensor:
 *              - If "interrupt measuring mode" is enabled, the interrupt is disabled
 *              - If "switch power mode" is configured, the sensor power is disabled          
 */
HallSwitch::~HallSwitch()
{
    if(status == POWER_ON)
        disable();
    if(status == POWER_OFF)
        end();
}

/**
 * @brief   Initializes the hardware interfaces
 * @return  HallSwitch error code
 * @retval  OK if success
 * @retval  INTF_ERROR if hardware interface error
 */
HallSwitch::Error_t  HallSwitch::begin()
{
    Error_t err = OK;

    if(powerMode == SWITCH)
    {   
        if(power == NULL)
            return INTF_ERROR;
        
        INTF_ASSERT(power->init());        
    }

    if(output == NULL)
      return INTF_ERROR;

    INTF_ASSERT(output->init());
    status = INITED;

    return err;
}

/**
 * @brief   Deinitializes the hardware interfaces
 * @return  HallSwitch error code
 * @retval  OK if success
 * @retval  INTF_ERROR if hardware interface error
 */
HallSwitch::Error_t  HallSwitch::end()
{
    Error_t err = OK;

    if(powerMode == SWITCH)
    {
        if(power == NULL)
            return INTF_ERROR;

        INTF_ASSERT(power->deinit());
    }

    if(output == NULL)
      return INTF_ERROR;

    INTF_ASSERT(output->deinit());

    status    = UNINITED;
    bfieldVal = B_FIELD_UNDEF;

    return err;
}

/**
 * @brief   Enables the sensor
 *          - If "switch power mode " is configured, the sensor is powered up
 *          - If "interrupt measuring mode" is configured, the interrupt is enabled
 * 
 * @return  HallSwitch error code 
 * @retval  OK if success
 * @retval  INTF_ERROR if hardware interface error     
 */
HallSwitch::Error_t  HallSwitch::enable()
{
    Error_t err = OK;

    if(powerMode == SWITCH)
        INTF_ASSERT(power->enable());

    if(measMode == INTERRUPT)
       INTF_ASSERT(output->enableInt(this));

    status = POWER_ON;

    return err;
}

/**
 * @brief   Disables the sensor
 *              - If the "interrupt measuring mode" is configured, the interrupt is disabled 
 *              - If the "switch power mode" is configured, the sensor is powered off
 * @return  HallSwitch error code 
 * @retval  OK if success
 * @retval  INTF_ERROR if hardware interface error     
 */
HallSwitch::Error_t  HallSwitch::disable()
{
    Error_t err = OK;

    if(measMode == INTERRUPT)
        INTF_ASSERT(output->disableInt());

    if(powerMode == SWITCH)
        INTF_ASSERT(power->disable());

    status = POWER_OFF;

    return err;
}

/**
 * @brief   Reads the actual magnetic field value
 * 
 *  - Magnetic field present if the GPIO voltage level is low
 *  - Mangnetic field not present if the GPIO voltage level is high
 * 
 *  The "bfieldVal" object member is updated with the read value.
 * 
 * @return  HallSwitch magnetic field value
 * @retval  B_FIELD_ON if magnetic field present
 * @retval  B_FIELD_OFF if magnetic field NOT present
 */
HallSwitch::Result_t HallSwitch::readBField()
{
	GPIO::VLevel_t gpiolevel = output->read();   

	if(gpiolevel == GPIO::VLevel_t::GPIO_LOW)
    {
        bfieldVal = B_FIELD_ON;
	}
    else if(gpiolevel == GPIO::VLevel_t::GPIO_HIGH)
    {
        bfieldVal = B_FIELD_OFF;
	}

    return bfieldVal;
}

/**
 * @brief   Gets the status
 * @return  HallSwitch status
 */
HallSwitch::Status_t HallSwitch::getStatus()
{
    return status;
}

/**
 * @brief   Gets magnetic field 
 * 
 *  This functions returns the last read value updated in the object member bfieldVal variable,
 *  either from a explicit readBField() call or due to an interrupt event.
 * 
 *  If polling mode is used, readBField() has to be called preivously in order to get the actual value.
 *  
 * @return  HallSwitch magnetic field result
 */
HallSwitch::Result_t HallSwitch::getBField()
{
    return bfieldVal;
}

/**
 * @brief   Interrupt mode callback function
 *  
 *  The class updates on its own bfieldVal member to the when the interrupt occurs
 * 
 * @return  void
 */
void HallSwitch::callback()
{
    GPIO::IntEvent_t event = output->intEvent();

    if(event == GPIO::IntEvent_t::INT_FALLING_EDGE)
    {
        bfieldVal = B_FIELD_ON;
    }
    else if(event == GPIO::IntEvent_t::INT_RISING_EDGE)
    {
       bfieldVal = B_FIELD_OFF;
    }

    cBack(bfieldVal);
}

/** @} */


HallSwitch*  HallSwitch::Interrupt::objPtrVector[GPIO_INT_PINS] = {NULL};
uint8_t      HallSwitch::Interrupt::idxNext    = 0;

/**
 * @brief   Interrupt 0 Handler
 */
void HallSwitch::Interrupt::int0Handler() 
{
    objPtrVector[0]->callback();
}

/**
 * @brief   Interrupt 1 Handler
 */
void HallSwitch::Interrupt::int1Handler()
{
    objPtrVector[1]->callback();
}

/**
 * @brief   Interrupt 2 Handler
 */
void HallSwitch::Interrupt::int2Handler()
{
    objPtrVector[2]->callback();
}

/**
 * @brief   Interrupt 3 Handler
 */
void HallSwitch::Interrupt::int3Handler()
{
    objPtrVector[3]->callback();
}


void *HallSwitch::Interrupt::fnPtrVector[GPIO_INT_PINS] = {(void *)int0Handler,
                                                           (void *)int1Handler,
                                                           (void *)int2Handler,
                                                           (void *)int3Handler};

/**
 * @brief       Register a hardware interrupt on the argument hall switch object
 * @param[in]   *objPtr Hall switch object pointer
 * @return      Pointer to allocated the interrupt function handler 
 */
void *HallSwitch::Interrupt::isrRegister(HallSwitch *objPtr) 
{
    objPtrVector[HallSwitch::Interrupt::idxNext] = objPtr;
    return fnPtrVector[HallSwitch::Interrupt::idxNext++];
}
