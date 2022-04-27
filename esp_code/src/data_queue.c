#ifdef __cplusplus
extern "C" {
#endif

/********************************** Includes **********************************/
#include "data_queue.h"
#include <string.h>
#ifdef QUEUE_PRINTS
#include <stdio.h>
#endif // QUEUE_PRINTS


/********************************** Defines ***********************************/
#define DATA_QUEUE_SIZE 512

/***************************** Struct definitions *****************************/
typedef struct {
	dht_data_t *buf;
	uint32_t write_i;
	uint32_t read_i;
	uint32_t ring_size;
} ring_buf_t;


/**************************** Prototype functions *****************************/
/**************************** Variable definitions ****************************/
dht_data_t dat_arr[DATA_QUEUE_SIZE] = {0};
ring_buf_t rb = {0};


/**************************** Function definitions ****************************/
/* 
 * Setup the data queue.
 * 
 * @return: Success status.
 */
int setup_data_queue()
{
	memset(dat_arr, 0, sizeof(dht_data_t) * DATA_QUEUE_SIZE);

	rb.buf = dat_arr;
	rb.write_i = 0;
	rb.read_i = 0;
	rb.ring_size = DATA_QUEUE_SIZE;

#ifdef QUEUE_PRINTS
	printf("Initialized dht_data_t queue with %i elements (%iB) sizeof(bool) %i\n\r", 
			DATA_QUEUE_SIZE, DATA_QUEUE_SIZE*sizeof(dht_data_t), sizeof(bool));
#endif // QUEUE_PRINTS
	
	return 0;
}

/* 
 * Add one element to the queue.
 * Copy by value may not be optimal performance wise.
 * 
 * @param dat:  Data to psuh.
 * @return: Success status. 1 if the queue is full.
 */
int push_data_element(dht_data_t dat)
{
	if (space_in_buf() == 0)
		return 1;

	rb.buf[rb.write_i] = dat;
/*
	dht_data_t *new_el = &rb.buf[rb.write_i];

	new_el->timestamp = dat.timestamp;
	new_el->temp = dat.temp;
	new_el->humidity = dat.humidity;
	new_el->relay_active = dat.relay_active;
*/

	rb.write_i = (rb.write_i + 1) % rb.ring_size;

	return 0;
}

/* 
 * Remove one element from the queue.
 * Return a dht_data_t with all zeros if queue empty.
 * Copy by value may slow down performance.
 * 
 * @return: dht_data_t element.
 */
dht_data_t pop_data_element()
{
	dht_data_t dat_to_return = {0};
	if (elements_in_buf() != 0)
	{
		dat_to_return = rb.buf[rb.read_i];
		rb.read_i = (rb.read_i + 1) % rb.ring_size;
		
	}
#ifdef QUEUE_PRINTS
	printf("pop_data_element: Returned [%u, %i, %i, %i]\n\r", 
				dat_to_return.timestamp, dat_to_return.humidity, 
				dat_to_return.temp, dat_to_return.relay_active);
#endif // QUEUE_PRINTS
	return dat_to_return;
}

/* 
 * The space left in the buffer.
 * 
 * @return: The space left in the buffer.
 */
uint16_t space_in_buf()
{
	if (rb.write_i >= rb.read_i)
		return (rb.ring_size - rb.write_i + rb.read_i) - 1;
	else
		return rb.read_i - rb.write_i - 1;
}

/* 
 * The numer of elements in the buffer.
 * 
 * @return: The numer of elements in the buffer.
 */
uint16_t elements_in_buf()
{
	if (rb.write_i >= rb.read_i)
		return rb.write_i - rb.read_i;
	else
		return (rb.ring_size - rb.read_i) + rb.write_i;
}

#ifdef QUEUE_PRINTS
void data_queue_prints()
{
	printf("Data queue write_i %u, read_i %u, size %u:\n\r[", 
			rb.write_i, rb.read_i, rb.ring_size);

	for (int i = 0; i < 5; i++)
	{
		printf("[%u, %i, %i, %i], ", rb.buf[i].timestamp, rb.buf[i].humidity, 
				rb.buf[i].temp, rb.buf[i].relay_active);
	}
	printf("]\n\r");
}
#endif // QUEUE_PRINTS

#ifdef __cplusplus
}
#endif