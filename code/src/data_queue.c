#ifdef __cplusplus
extern "C" {
#endif

/********************************** Includes **********************************/
#include "data_queue.h"
#include <string.h>


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
int setup_data_queue()
{
	memset(dat_arr, 0, sizeof(dht_data_t) * DATA_QUEUE_SIZE);

	rb.buf = dat_arr;
	rb.write_i = 0;
	rb.read_i = 0;
	rb.ring_size = DATA_QUEUE_SIZE;
	
	return 0;
}

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

dht_data_t pop_data_element()
{
	if (elements_in_buf() != 0)
	{
		rb.read_i = (rb.read_i + 1) % rb.ring_size;
	}

	return rb.buf[rb.read_i];
}

uint16_t space_in_buf()
{
	if (rb.write_i >= rb.read_i)
		return (rb.ring_size - rb.write_i + rb.read_i) - 1;
	else
		return rb.read_i - rb.write_i - 1;
}

uint16_t elements_in_buf()
{
	if (rb.write_i >= rb.read_i)
		return rb.write_i - rb.read_i;
	else
		return (rb.ring_size - rb.read_i) + rb.write_i;
}

#ifdef __cplusplus
}
#endif