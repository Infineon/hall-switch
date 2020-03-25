#include <Arduino.h>
#include <stdint.h>
#include <hall-switch-ino.h>


#ifdef XMC1100_XMC2GO
#define LED1 14             /**< LED1 Pin Allocation for XMC2Go  */
#else
#define LED1 LED_BUILTIN
#endif

/**
 * @brief       Prints the sensor data in JSON format 
 * @param[in]   field B field value
 */
void JSONPrint(int field)
{
  Serial.print("{ \"field_val\" : ");
  Serial.print(field);
  Serial.println(" }");
}

void IntCBack(HallSwitch::Result_t result)
{
	if(result == HallSwitch::Result_t::B_FIELD_ON)
    {
        digitalWrite(LED1, HIGH);
	}
    else if(result == HallSwitch::Result_t::B_FIELD_OFF)
    {
        digitalWrite(LED1, LOW);
	}

    JSONPrint(result);
}


HallSwitchIno hs(TLE4964_3M_S2Go_XMC2Go, IntCBack);  /**< Hall Switch object */

void setup()
{      
    int err = 0;

    delay(1000);

    Serial.begin(115200);
    Serial.println("Serial initialized");

    pinMode(LED1, OUTPUT);
    Serial.println("LED1 initialized");

    err = hs.begin();
    if(0 > err ){ Serial.print("Hall Switch error");}

    Serial.println("Hall Switch started");
}


void loop()
{

}