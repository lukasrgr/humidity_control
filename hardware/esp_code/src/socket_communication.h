/* 
 * Receive user input strings.
 * Respond to a user.
 */

#ifndef _USER_COMMUNICATION_H_
#define _USER_COMMUNICATION_H_

/********************************** Includes **********************************/
#include "types_and_enums.h"


/********************************* Constants **********************************/
#define RECV_DEBUG
#define SEND_DEBUG


/***************************** Struct definitions *****************************/
/**************************** Variable definitions ****************************/
/**************************** Prototype functions *****************************/
/*
 * Setup the user communication.
 * 
 * @return: Success status.
 */
int setup_user_comm();

/* 
 * TODO Remove.
 * 
 * @return: 
 */
int dummy_client();

/* 
 * Try to send one dht_data_t.
 * 
 * @return: Success status, 0 if sent.
 */
int send_one_dht_data(dht_data_t *dat);

/* 
 * Send a relay set message to the database.
 * 
 * @param timestamp: The current time.
 * @retval: Success status.
 */
int send_relay_set(uint32_t timestamp);

/* 
 * Send a relay reset message to the database.
 * 
 * @param timestamp: The current time.
 * @retval: Success status.
 */
int send_relay_reset(uint32_t timestamp);

/* 
 * Send data from the data_queue if available.
 * Needs to be called in a loop.
 * 
 * @return: Success status.
 */
int send_dht_data_from_queue();

#endif // _USER_COMMUNICATION_H_