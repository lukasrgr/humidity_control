/* 
 * Save data elements.
 */

#ifndef _DATA_QUEUE_H_
#define _DATA_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

/********************************** Includes **********************************/
#include <stdint.h>
#include "configuration.h"
#include "types_and_enums.h"


/********************************* Constants *********************************/
#define NEW_ENTRY_EVER_N_MINS 5
#define NUM_ENTRIES ((24 * 60) / (NEW_ENTRY_EVER_N_MINS))


/***************************** Struct definitions *****************************/
/**************************** Variable definitions ****************************/
/**************************** Prototype functions *****************************/
int setup_data_queue();

int push_data_element(dht_data_t dat);

dht_data_t pop_data_element();

uint16_t space_in_buf();

uint16_t elements_in_buf();

#ifdef __cplusplus
}
#endif

#endif // _DATA_QUEUE_H_