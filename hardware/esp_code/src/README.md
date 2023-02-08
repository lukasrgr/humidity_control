# humidity_control

## Basics
The ESP8266 measures the humidity, controls the dehumidifier and sends data to a TCP socket.


## Features
### Implemented features
* Measuring the humidity and temperature
* Controlling the dehumidifyer
* Transmitting data to the server, writing into the database
* Saving data up to one day on the ESP, if the database is temporarily unavailable
### Possible future work
* Changing the dehumidifier activation threshold using the UI
### Intentional limitations
* No secure communication


## Usage
Enter your networks SSID and password in 'configuration.h'. You also have to enter you TCP sockets IP and port.


## Project structure
Here are some important files. To keep it brief, only the headers are listed:
* /dht_lib/: Here cou have to clone the library for the DHT11 sensor.
* /configuration.h: Configure WIFI settings and .
* /data_queue.h/: A ring buffer to store measured data. 
* /main.cpp/: Initializes hardware and triggers sensor reading and sending.
* /relay_activation.h/: Activate two relays.
* /socket_commun.h/: Writing data to the server.
* /types_and_enums.h/: Contains project wide typedefs.


## Implementation
The mysql connector lib is used. Build using PlatformIO.
