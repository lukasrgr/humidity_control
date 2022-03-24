/********************************** Includes **********************************/
#include <Arduino.h>
#include <stdbool.h>
#include "configuration.h"
#include "relay_activation.h"
#include "dht_lib/DHT.h"
#include "mysql_connector_lib/src/MySQL_Connection.h"
#include "mysql_connector_lib/src/MySQL_Cursor.h"


/********************************** Defines ***********************************/
#define DHT_PIN D2
#define DHT_TYPE DHT11
#define RELAY_NUM 1


/********************************* Constants **********************************/ 
// Configure your ssid and password here
const char ssid[] = "It hurts when IP";
const char pass[] = "SagIchDirNicht!";


/***************************** Struct definitions *****************************/
/**************************** Prototype functions *****************************/
void error_handler();


/**************************** Variable definitions ****************************/
DHT dht(DHT_PIN, DHT_TYPE);

// Configure the MySQL address
IPAddress server_addr(192,168,178,107);
char user[] = "arduino_user";
char password[] = "secret";

WiFiClient client;
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;

// TODO Replace by modifiable template
char INSERT_SQL[] = "INSERT INTO humidity.measuredData (timestamp, temperature, "
                    "humidity) VALUES (1, 2, 6)";

uint32_t last_executed = 0;
// bc:ff:4d:19:fe:11

/**************************** Function definitions ***************************/
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
    printf("Threshold range error detected, aborting\n\r");
    error_handler();
  }

  dht.begin();

  printf("hum %f temp %f\n\r", dht.readHumidity(), dht.readTemperature());

  printf("Trying to connect to %s", ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print(WiFi.macAddress());
  printf("Connected.\n\r");
  printf("My IP address is: ");
  Serial.println(WiFi.localIP());
  printf("b\n\r");

  Serial.print("Connecting to SQL...  ");
  char default_db[] = "humidity";
  if (conn.connect(server_addr, 3306, user, password))
    Serial.println("OK.");
  else
    Serial.println("FAILED.");

  // create MySQL cursor object
  cursor = new MySQL_Cursor(&conn);

  if (conn.connected())
  {
    printf("Connected and executing sql\n\r");
    cursor->execute(INSERT_SQL);
  }
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

  if (millis() - last_executed > 5000)
  {
    if (conn.connected())
    {
      printf("Connected and executing sql\n\r");
      cursor->execute(INSERT_SQL);
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