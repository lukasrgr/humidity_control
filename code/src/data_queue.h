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
#undef QUEUE_PRINTS
#define NUM_ENTRIES ((24 * 60) / (SAMPLE_EVERY_MIN))


/***************************** Struct definitions *****************************/
/**************************** Variable definitions ****************************/
/**************************** Prototype functions *****************************/
/* 
 * Setup the data queue.
 * 
 * @return: Success status.
 */
int setup_data_queue();

/* 
 * Add one element to the queue.
 * Copy by value may not be optimal performance wise.
 * 
 * @param dat:  Data to psuh.
 * @return: Success status. 1 if the queue is full.
 */
int push_data_element(dht_data_t dat);

/* 
 * Remove one element from the queue.
 * Return a dht_data_t with all zeros if queue empty.
 * Copy by value may slow down performance.
 * 
 * @return: dht_data_t element.
 */
dht_data_t pop_data_element();

/* 
 * The space left in the buffer.
 * 
 * @return: The space left in the buffer.
 */
uint16_t space_in_buf();

/* 
 * The numer of elements in the buffer.
 * 
 * @return: The numer of elements in the buffer.
 */
uint16_t elements_in_buf();

#ifdef QUEUE_PRINTS
void data_queue_prints();
#endif // QUEUE_PRINTS

#ifdef __cplusplus
}
#endif

#endif // _DATA_QUEUE_H_