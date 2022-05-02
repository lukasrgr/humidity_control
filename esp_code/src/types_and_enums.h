#ifndef _TYPES_AND_ENUMS_H
#define _TYPES_AND_ENUMS_H

/********************************** Includes **********************************/
#include <stdint.h>
#include <stdbool.h>


/********************************** Defines ***********************************/
/***************************** Struct definitions *****************************/
typedef struct
{
    uint32_t timestamp;
    uint8_t humidity;
    uint8_t temp;
    bool relay_active;
} dht_data_t;


#endif // _TYPES_AND_ENUMS_H