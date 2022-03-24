/* 
 * Activate up to NUM_RELAYS relays.
 */

#ifndef _RELAY_ACTIVATION_H_
#define _RELAY_ACTIVATION_H_

/********************************** Includes **********************************/
#include <stdint.h>
#include "configuration.h"


/********************************* Constants *********************************/
#define NUM_RELAYS 1


/***************************** Struct definitions *****************************/
/**************************** Variable definitions ****************************/
/**************************** Prototype functions *****************************/
/* 
 * Turn on a single relay.
 * 
 * @param rel_num:  The relay number you want to activate.
 * @return: None.
 */
void activate_relay(uint8_t rel_num);

/* 
 * Turn off a single relay.
 * 
 * @param rel_num:  The relay number you want to deactivate.
 * @return: None.
 */
void deactivate_relay(uint8_t rel_num);

/* 
 * Turn on the first n relays.
 * 
 * @param rel_n:    The relay number you want to activate.
 * @return: Success status.
 */
int activate_n_relays(uint8_t rel_n);

/* 
 * Turn off the first n relays.
 * 
 * @param rel_n:    The relay number you want to deactivate.
 * @return: Success status.
 */
int deactivate_n_relays(uint8_t rel_n);

#endif // _RELAY_ACTIVATION_H_