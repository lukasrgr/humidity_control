/* 
 * Save data elements.
 */

#ifndef _DATA_QUEUE_H_
#define _DATA_QUEUE_H_

/********************************** Includes **********************************/
#include <stdint.h>
#include "configuration.h"


/********************************* Constants *********************************/
#define NEW_ENTRY_EVER_N_MINS 5
#define NUM_ENTRIES ((24 * 60) / (NEW_ENTRY_EVER_N_MINS))


/***************************** Struct definitions *****************************/
/* 
 * Try to keep this structure small to save space.
 * For this reason we do not use the default C tm struct.
 */
typedef struct
{
    uint8_t hour;
    uint8_t min;
    uint8_t humidity;
    uint8_t temp;
} hum_data_t;



/**************************** Variable definitions ****************************/
/**************************** Prototype functions *****************************/
int push_data_element(uint8_t hour, uint8_t min, 
                        uint8_t humidity, uint8_t temp);

hum_data_t pop_data_element(uint8_t hour, uint8_t min, 
                        uint8_t humidity, uint8_t temp);

uint16_t num_entries();


#endif // _DATA_QUEUE_H_