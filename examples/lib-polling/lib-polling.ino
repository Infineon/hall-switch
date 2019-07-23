#include <Arduino.h>
#include <stdint.h>
#include <hall-switch-ino.h>


#ifdef XMC1100_XMC2GO
#define LED1 14             /**< LED1 Pin Allocation for XMC2Go  */
#else
#define LED1 LED_BUILTIN
#endif

#ifdef XMC1100_XMC2GO 
#define Q_OUTPUT_PIN    9   /**< Hall Switch Output Pin  */
#elif ((XMC1100_Boot_Kit) ||  \
      (XMC4700_Relax_Kit) ||  \
      (ARDUINO_AVR_UNO))
#define Q_OUTPUT_PIN    3   /**< Hall Switch Output Pin  */
#endif

HallSwitch::Status_t stat  = HallSwitch::Status_t::UNINITED;
HallSwitch::Result_t field = HallSwitch::Result_t::B_FIELD_UNDEF;
HallSwitchIno        hs(Q_OUTPUT_PIN);

/**
 * @brief       Prints the sensor data in JSON format 
 * @param[in]   stat  status
 * @param[in]   field B field value

 */
void JSONPrint(HallSwitch::Status_t stat,
               HallSwitch::Result_t field)
{
  Serial.print("{ \"status\" : ");
  Serial.print(stat);
  Serial.print(", \"field_val\" : ");
  Serial.print(field);
  Serial.println(" }");
}

void setup()
{      
  HallSwitch::Error_t errCode = HallSwitch::Error_t::OK;

  delay(1000);

  Serial.begin(115200);
  Serial.println("Serial initialized");

  pinMode(LED1, OUTPUT);
  Serial.println("LED1 Initialized");

  /* Begin switch hardware interfaces */ 
  errCode = hs.begin();
  if(errCode != HallSwitch::Error_t::OK)
  {
      Serial.print("Hall Switch error: ");
      Serial.println(errCode);
  }
  Serial.println("Hall Switch initialized");

  /* Enable the switch */
  errCode = hs.enable();
  if(errCode != HallSwitch::Error_t::OK)
  {
      Serial.print("Hall Switch error: ");
      Serial.println(errCode);
  }
  Serial.println("Hall Switch enabled");

  JSONPrint(stat, field);
}

HallSwitch::Status_t curStat  = stat;
HallSwitch::Result_t curField = field;

void loop()
{
  curStat  = hs.getStatus();
  curField = hs.readBField();

  if (curStat != stat || curField != field)
  {
    stat  = curStat;
    field = curField;
    if(field == HallSwitch::Result_t::B_FIELD_ON)
    {
        digitalWrite(LED1, HIGH);
	  }
    else if(field == HallSwitch::Result_t::B_FIELD_OFF)
    {
        digitalWrite(LED1, LOW);
	  }
    JSONPrint(stat,field); 
  }
}