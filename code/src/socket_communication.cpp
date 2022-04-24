/********************************** Includes **********************************/
#include "socket_communication.h"
#include <string.h>
#include <stdbool.h>
#include "ESP8266WiFi.h"

/********************************** Defines **********************************/
#define USER_SCKT_BUF_LEN 256
#define JSON_MAX_LEN 256


/********************************* Constants **********************************/
/***************************** Struct definitions *****************************/
/**************************** Prototype functions *****************************/
/**************************** Variable definitions ****************************/
WiFiServer wifiServer(23);
WiFiClient tcp_client;
bool connected = false;

char user_socket_buf[USER_SCKT_BUF_LEN] = {};
bool user_data_available = false;

const uint16_t port = 65432;
IPAddress ip_to_conn = IPAddress(192,168,178,29);

// TODO Do not fix the size
char json_template[JSON_MAX_LEN] = "{ \"timestamp\":%u, \"humidity\":%u, \"temperature\":%u }";
char json_loc[JSON_MAX_LEN];

/**************************** Function definitions ****************************/
/*
 * Setup the user communication.
 * 
 * @return: Success status.
 */
int setup_user_comm()
{
    wifiServer.begin();
    return 0;
}

int dummy_client()
{
    snprintf(json_loc, JSON_MAX_LEN, json_template, 1234, 1, 2);
    if (!tcp_client.connect(ip_to_conn, port))
    {
        Serial.println("Connection to host failed");
        delay(1000);
        return 1;
    }
    Serial.println("Connected to server successful!");
    delay(250);
    tcp_client.print(json_loc);
    Serial.print('\n');
    tcp_client.stop();
    delay(5000);
    return 0;
}

int send_one_dht_data(dht_data_t *dat)
{
    snprintf(json_loc, JSON_MAX_LEN, json_template, dat->timestamp, 
                dat->humidity, dat->temp);
    if (!tcp_client.connect(ip_to_conn, port))
    {
        Serial.println("Connection to host failed");
        delay(1000);
        return 1;
    }
    Serial.println("Connected to server successfully!");
    delay(250);
    tcp_client.print(json_loc);
    Serial.print('\n');
    tcp_client.stop();
    delay(5000);
    return 0;
}
