#include <Arduino.h>
#include <stdint.h>
#include <hall-switch-ino.h>


#ifdef XMC1100_XMC2GO
#define Q_OUTPUT_PIN    9   /**< Hall Switch Output Pin  */
#define LED1 14             /**< LED1 Pin Allocation for XMC2Go  */
#else
#define LED1 LED_BUILTIN
#endif

HallSwitchIno        hs(Q_OUTPUT_PIN);  /**< Hall Switch object */
int                  bfield = 0;        /**< B Field value: (0) no field, (1) field present */

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

  JSONPrint(bfield);
}

int curbfield = bfield;

void loop()
{
  curbfield = hs.getBField();

  /** Only update LED and data when B field changes */
  if (curbfield != bfield)
  {
    bfield = curbfield;
    if(1 == bfield)
    {
        digitalWrite(LED1, HIGH);
	  }
    else if(0 == bfield)
    {
        digitalWrite(LED1, LOW);
	  }
    else if(0 > bfield)
    {
        Serial.println("Hall swith error.");
    }
    JSONPrint(bfield); 
  }
}