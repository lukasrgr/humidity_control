/********************************** Includes **********************************/
#include <Arduino.h>
#include <stdbool.h>
#include "configuration.h"
#include "relay_activation.h"
#include "dht_lib/DHT.h"


/********************************** Defines ***********************************/
#define DHT_PIN D2
#define DHT_TYPE DHT11
#define RELAY_NUM 1


/********************************* Constants **********************************/
/***************************** Struct definitions *****************************/
/**************************** Prototype functions *****************************/
void error_handler();


/**************************** Variable definitions ****************************/
DHT dht(DHT_PIN, DHT_TYPE);


/**************************** Function definitions ****************************/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(50);

  printf("\n\rHello\n\r");

  /* 
   * Check for possible errors.
   */
  if (ON_HUM_THRES < OFF_HUM_THRES)
  {
    printf("Error detected, aborting\n\r");
    error_handler();
  }

  dht.begin();

  printf("hum %f temp %f\n\r", dht.readHumidity(), dht.readTemperature());
}

void loop() {
  float humid = dht.readHumidity();
  float temp = dht.readTemperature();
  
  if (!isnan(humid))
  {
    if (humid >= ON_HUM_THRES) 
    {
      activate_relay(RELAY_NUM);
    }
    else if (humid <= OFF_HUM_THRES)
    {
      deactivate_relay(RELAY_NUM);
    }
  }
}

/* 
 * Infinite loop if an error occurs.
 */
void error_handler()
{
  for(;;)
    yield();
}