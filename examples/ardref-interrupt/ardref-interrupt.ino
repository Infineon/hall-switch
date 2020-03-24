/**
 * @file        ardref-interrupt.ino
 * @brief       GPIO Interrupt Example for TLE4964-3M Shield2Go
 *          
 *              Usage of the Arduino Reference Library Functions.
 *              - How does it work? 
 *              The transition from magnetic field (B) presence to absence will 
 *              generate a Q output signal level change: either high to low 
 *      	    (for no B field to B field), or low to high (for B field to
 *              no B field). The interrupt occurs for any of both events.
 *              The interrupt handler function determines which of the events
 *              have ocurred, and print the event through the serial.
 *              In the presence of magnetic field, the LED1 is turned ON.
 * @copyright   Copyright (c) 2019 Infineon Technologies AG         
 */

#include <Arduino.h> 

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

int     value = HIGH;       /**< Output Value */

/**
 * @brief   hall-switch interrupt handler
 *          
 */
void int_handler()
{
	value = digitalRead(Q_OUTPUT_PIN);   

	if(value == LOW)
    {
		Serial.println("B Field ON");
        digitalWrite(LED1, HIGH);
	}
    else if(value == HIGH)
    {
        Serial.println("B Field OFF");
        digitalWrite(LED1, LOW);
	}
}

void setup()
{
    delay(1000);
    
    Serial.begin(115200);
    Serial.println("Serial Initialized");
    
    pinMode(LED1, OUTPUT);
    Serial.println("LED1 Initialized");
    
    pinMode(Q_OUTPUT_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(Q_OUTPUT_PIN), int_handler, CHANGE);
    Serial.println("Output Pin Initialized as Interrupt");
    Serial.println();
}

void loop()
{

}