/* 
 * Activate up to NUM_RELAYS relays.
 */

#ifndef _RELAY_ACTIVATION_H_
#define _RELAY_ACTIVATION_H_

/********************************** Includes **********************************/
#include <stdint.h>
#include "configuration.h"


/********************************* Constants *********************************/
#define NUM_RELAYS 2


/***************************** Struct definitions *****************************/
/**************************** Variable definitions ****************************/
/**************************** Prototype functions *****************************/
/* 
 * Setup outputs. Turn off the relays.
 * 
 * @return: None.
 */
void setup_relays();

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
 * Check if a relay is active.
 * 
 * @param rel_num:  The relay number you want to check.
 * @return: HIGH if active, LOW if not.
 */
int get_relay_status(uint8_t rel_num);

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

/* 
 * Activate the first n relays, deactivate the rest.
 * 
 * @param rel_num:  The number of relays to activate.
 * @return: Success status.
 */
int activate_first_n_relays(uint8_t rel_num);

#endif // _RELAY_ACTIVATION_H_