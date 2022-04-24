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


/***************************** Struct definitions *****************************/
/**************************** Variable definitions ****************************/
/**************************** Prototype functions *****************************/
int setup_user_comm();
int dummy_client();
int send_one_dht_data(dht_data_t *dat);

#endif // _USER_COMMUNICATION_H_