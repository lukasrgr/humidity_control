/********************************** Includes **********************************/
#include "socket_communication.h"
#include <string.h>
#include <stdbool.h>
#include "ESP8266WiFi.h"
#include "data_queue.h"


/********************************** Defines **********************************/
#define USER_SCKT_BUF_LEN 256
#define JSON_MAX_LEN 256


/********************************* Constants **********************************/
/***************************** Struct definitions *****************************/
/**************************** Prototype functions *****************************/
int send_one_generic_string(const char *buf, size_t buf_len);


/**************************** Variable definitions ****************************/
WiFiServer wifiServer(23);
WiFiClient tcp_client;
bool connected = false;

char user_socket_buf[USER_SCKT_BUF_LEN] = {};
bool user_data_available = false;

const uint16_t port = SERVER_PORT;
IPAddress ip_to_conn = IPAddress(SERVER_IP);

// TODO Do not fix the size
char json_template[JSON_MAX_LEN] = "{ \"method\":\"sendGeneralData\", "
                                    "\"timestamp\":%u, \"humidity\":%u, "
                                    "\"temperature\":%u , \"relay\":%u }";
char relay_json_template[JSON_MAX_LEN] = "{\"method\": \"sendRelayData\", "
                                    "\"timestamp\": %u, \"relay\": %u }";
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

/* 
 * Send a generic string to the database.
 * TODO These delays seem to be unneccessary or massively overdimensioned. 
 * 
 * @param buf: The string buffer to send.
 * @param buf_len: The length of the string buffer.
 * @return: Success status.
 */
int send_one_generic_string(const char *buf, size_t buf_len)
{
    if (!tcp_client.connect(ip_to_conn, port))
    {
        Serial.println("Connection to host failed");
        delay(1000);
        return 1;
    }
    Serial.println("Connected to server successfully!");
    delay(250);
    tcp_client.print(buf);
    Serial.print('\n');
    tcp_client.stop();
    delay(5000);
    return 0;
}

/* 
 * Try to send one dht_data_t.
 * 
 * @return: Success status, 0 if sent.
 */
int send_one_dht_data(dht_data_t *dat)
{
    snprintf(json_loc, JSON_MAX_LEN, json_template, dat->timestamp, 
                dat->humidity, dat->temp, dat->relay_active);
    return send_one_generic_string(json_loc, strlen(json_loc));
    /*
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
    */
}

/* 
 * Send a relay set message to the database.
 * 
 * @param timestamp: The current time.
 * @retval: Success status.
 */
int send_relay_set(uint32_t timestamp)
{
    snprintf(json_loc, JSON_MAX_LEN, relay_json_template, timestamp, 1);
    return send_one_generic_string(json_loc, strlen(json_loc));
}

/* 
 * Send a relay reset message to the database.
 * 
 * @param timestamp: The current time.
 * @retval: Success status.
 */
int send_relay_reset(uint32_t timestamp)
{
    snprintf(json_loc, JSON_MAX_LEN, relay_json_template, timestamp, 0);
    return send_one_generic_string(json_loc, strlen(json_loc));
}

/* 
 * Send data from the data_queue if available.
 * Needs to be called in a loop.
 * 
 * @return: Success status.
 */
int send_dht_data_from_queue()
{
    static dht_data_t data_to_send = {0};

    int status = 1;

    // No data if timestamp = 0.
    if (data_to_send.timestamp == 0)
    {
        if (elements_in_buf() > 0)
        {
            data_to_send = pop_data_element();
#ifdef SEND_DEBUG
            printf("Fetched new data to send: ");
            printf("[%u, %i, %i, %i]\n\r", data_to_send.timestamp, data_to_send.humidity, 
				data_to_send.temp, data_to_send.relay_active);
#endif // SEND_DEBUG
        }
    }
    else
    {
        status = send_one_dht_data(&data_to_send);
        // Reset static variable if data has been successfully been sent.
        if (status == 0)
        {
            memset(&data_to_send, 0, sizeof(data_to_send));
#ifdef SEND_DEBUG
            printf("Successfully transmitted data.\n\r");
#endif // SEND_DEBUG
        }
    }

    return status;
}
