# humidity_control

## Basics
This project aims at regulating our bathrooms humidity by controlling a dehumidifyer. 
The humidity, temperature, current timestamp and the dehumidifyer status is written into a database.
Using an UI, the user can observe how these values change over time.
![Rendering of the physical hardware](./pics/physical_mounting_rendering_1.PNG "Hardware rendering.")
![Installed hardware.](./pics/ttttt.jpg "Installed hardware.")


## Features
### Implemented features
* Measuring the humidity and temperature
* Controlling the dehumidifyer
* Transmitting data to the server, writing into the database
* Saving data up to one day on the ESP, if the database is temporarily unavailable
* Plotting the time series
* 3D printable housing
### Possible future work
* Changing the dehumidifier activation threshold using the UI
### Intentional limitations
* No secure communication


## Usage
Enter your networks SSID and password in 'configuration.h'.
Make sure the database and server are setup correctly. Adjust the server IP and port in 'configuration.h'.


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
