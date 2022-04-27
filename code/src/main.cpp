/********************************** Includes **********************************/
#include <Arduino.h>
#include <stdbool.h>
#include "time.h" // setenv(), do not worry about IDE warning, compiles fine
#include "configuration.h"
#include "relay_activation.h"
#include "types_and_enums.h"
#include "data_queue.h"
#include "socket_communication.h"
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
bool check_and_activate_relay(float hum, float temp);
dht_data_t measure_until_data();
void wait_until_round_time();
void error_handler();


/**************************** Variable definitions ****************************/
DHT dht(DHT_PIN, DHT_TYPE);

// Configure the MySQL address
IPAddress server_addr(192,168,178,107);
char user[] = "arduino_user";
char password[] = "secret";

WiFiClient client;
//MySQL_Connection conn(&client);
//MySQL_Cursor* cursor;

// TODO Replace by modifiable template
//char INSERT_SQL[] = "INSERT INTO humidity.measuredData (timestamp, temperature, "
//                    "humidity) VALUES (1, 2, 6)";

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

  setup_data_queue();

  /*
   * This allows the correct timeoffset to be used for localtime().
   * Do not worry about the IDE warning, the function is defined in a macro.
   */
  setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 3);

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
  Serial.println("My IP address is: ");
  Serial.println(WiFi.localIP());
  printf("\n\r");

  /*Serial.print("Connecting to SQL...  ");
  
  char default_db[] = "humidity";
  if (conn.connect(server_addr, 3306, user, password))
    Serial.println("OK.");
  else
    Serial.println("FAILED.");
  */
  // create MySQL cursor object
  //cursor = new MySQL_Cursor(&conn);

  /*
  if (conn.connected())
  {
    printf("Connected and executing sql\n\r");
    //cursor->execute(INSERT_SQL);
  }
  */

  setup_user_comm();
  //dummy_client();

  wait_until_round_time();
}

void loop() {
  const uint32_t DATA_TIME_OFFSET_UNIX = SAMPLE_EVERY_MIN * 60;

  static time_t last_data_time = 0;

  time_t rawtime;
  time(&rawtime);
  
  if (rawtime - DATA_TIME_OFFSET_UNIX > last_data_time)
  {
    dht_data_t new_dat = measure_until_data();
    new_dat.timestamp = (uint32_t)rawtime;

    new_dat.relay_active = check_and_activate_relay(new_dat.humidity, 
                                                    new_dat.temp);

#ifdef PRINTS_IN_MAIN
    printf("Aquired new hum %u, temp %u\n\r", new_dat.humidity, new_dat.temp);
    printf("elements_in_buf() %i \n\r", elements_in_buf());
#endif // PRINTS_IN_MAIN

    push_data_element(new_dat);

    last_data_time = rawtime;
  }

  send_dht_data_from_queue();
}

/* 
 * Keep measuring until data is valid.
 * The dht lib returns 'nan' from time to time, so this function is needed.
 * 
 * @return: A dht_data_t element.
 */
dht_data_t measure_until_data()
{
  dht_data_t new_dat = {0};

  float humid = 0;
  float temp = 0;
  bool data_valid = false;
  while (!data_valid)
  {
    humid = dht.readHumidity();
    temp = dht.readTemperature();

    data_valid = !isnan(humid) && !isnan(temp);
  }

  new_dat.humidity = (uint8_t)humid;
  new_dat.temp = (uint8_t)temp;

  return new_dat;
}

/* 
 * Check if the humidity exceeds the desired threshold.
 * If so activate the relay and thus the dehumidifyer.
 * 
 * @param hum:  The current humidity.
 * @param temp: The current temperature.
 * @return: Relay status.
 */
bool check_and_activate_relay(float hum, __attribute__((unused)) float temp)
{
  if (hum >= ON_HUM_THRES)
  {
    activate_relay(RELAY_NUM);
  } 
  else if (hum <= OFF_HUM_THRES)
  {
    deactivate_relay(RELAY_NUM);
  }
  return get_relay_status(RELAY_NUM);
}

/* 
 * Wait until a multiple of 5 minutes is reached.
 * 
 * @return: None.
 */
void wait_until_round_time()
{
  time_t rawtime;
  time(&rawtime);

  while(rawtime % (5*60) != 0)
  {
    time(&rawtime);
    yield();
  }
}

/* 
 * Infinite loop if an error occurs.
 * 
 * @return: None.
 */
void error_handler()
{
  printf("Error detected, halting.\n\r");
  deactivate_relay(1);
  for(;;)
    yield();
}