/********************************** Includes **********************************/
#include "relay_activation.h"

#include <Arduino.h>


/********************************** Defines ***********************************/
#define R1PIN D3
#define R2PIN D2
#define R3PIN D5
#define R4PIN D6

#define RELAY_ACTIVE_LEVEL LOW
#define RELAY_INACTIVE_LEVEL HIGH


/********************************* Constants **********************************/
/***************************** Struct definitions *****************************/
/**************************** Prototype functions *****************************/
void write_single_relay(uint8_t rel_num, int write_level);
int write_n_relays(uint8_t rel_num, int write_val);


/**************************** Variable definitions ****************************/
/* 
 * This is ugly but works, lol.
 */
uint8_t relay_pins[NUM_RELAYS] = 
    {
#if ((NUM_RELAYS) >= 1)
    R1PIN
#endif
#if ((NUM_RELAYS) >= 2)
    , R2PIN
#endif
#if ((NUM_RELAYS) >= 3)
    , R3PIN
#endif
#if ((NUM_RELAYS) >= 4)
    , R4PIN
#endif
    };


/**************************** Function definitions ****************************/
/* 
 * Setup outputs. Turn off the relays.
 * 
 * @return: None.
 */
void setup_relays()
{
    for (uint16_t pin = 0; pin < NUM_RELAYS; pin++)
    {
        pinMode(relay_pins[pin], OUTPUT);
        digitalWrite(relay_pins[pin], RELAY_INACTIVE_LEVEL);
    }
}

/* 
 * Turn on a single relay.
 * 
 * @param rel_num:  The relay number you want to activate.
 * @return: None.
 */
void activate_relay(uint8_t rel_num)
{
    write_single_relay(rel_num, RELAY_ACTIVE_LEVEL);
}

/* 
 * Turn off a single relay.
 * 
 * @param rel_num:  The relay number you want to deactivate.
 * @return: None.
 */
void deactivate_relay(uint8_t rel_num)
{
    write_single_relay(rel_num, RELAY_INACTIVE_LEVEL);
}

/* 
 * Check if a relay is active.
 * 
 * @param rel_num:  The relay number you want to check.
 * @return: HIGH if active, LOW if not.
 */
int get_relay_status(uint8_t rel_num)
{
    return digitalRead(relay_pins[rel_num]);
}

/* 
 * Switch a single relay.
 * 
 * @param rel_num:      The relay number you want to switch.
 * @param write_level:  The logic lever to set.
 * @return: None.
 */
void write_single_relay(uint8_t rel_num, int write_level)
{
    if (rel_num >= NUM_RELAYS)
        return;
    
    digitalWrite(relay_pins[rel_num], write_level);
}

/* 
 * Turn on the first n relays.
 * 
 * @param rel_n:    The relay number you want to activate.
 * @return: Success status.
 */
int activate_n_relays(uint8_t rel_n)
{
    return write_n_relays(rel_n, RELAY_ACTIVE_LEVEL);
}

/* 
 * Turn off the first n relays.
 * 
 * @param rel_n:    The relay number you want to deactivate.
 * @return: Success status.
 */
int deactivate_n_relays(uint8_t rel_n)
{
    return write_n_relays(rel_n, RELAY_INACTIVE_LEVEL);
}

/* 
 * Switch the first n relays.
 * 
 * @param rel_num:      The relay number you want to switch.
 * @param write_level:  The logic lever to set.
 * @return: Success status.
 */
int write_n_relays(uint8_t rel_num, int write_level)
{
    if (rel_num > NUM_RELAYS)
        return 1;

    for (uint16_t pin = 0; pin < rel_num; pin++)
    {
        digitalWrite(relay_pins[pin], write_level);
    }

    return 0;
}

/* 
 * Activate the first n relays, deactivate the rest.
 * 
 * @param rel_num:  The number of relays to activate.
 * @return: Success status.
 */
int activate_first_n_relays(uint8_t rel_num)
{
    if (rel_num >= NUM_RELAYS)
        return 1;

    for (uint16_t pin = 0; pin < rel_num; pin++)
    {
        digitalWrite(relay_pins[pin], RELAY_ACTIVE_LEVEL);
    }
    for (uint16_t pin = rel_num; pin < NUM_RELAYS; pin++)
    {
        digitalWrite(relay_pins[pin], RELAY_INACTIVE_LEVEL);
    }

    return 0;
}
