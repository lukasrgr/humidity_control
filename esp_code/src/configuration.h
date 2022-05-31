/* 
 * Configure project build and settings.
 */
// Configure your ssid and password here
#define YOUR_SSID "It hurts when IP"
#define YOUR_PASSWORD "SagIchDirNicht!"

// Where should the ESP send its data? Mind the commas.
#define SERVER_IP 192,168,178,107
#define SERVER_PORT 65435

// Humidity thresholds
#define ON_HUM_THRES 70
#define OFF_HUM_THRES 65

// Sampling interval
#define SAMPLE_EVERY_MIN 5

#define PRINTS_IN_MAIN
