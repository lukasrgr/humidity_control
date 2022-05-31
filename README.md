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
Here are some directories that may contain interesting files. All of these contain a separate, more detailed readme:
* /3d_objects/: The printable case as STLs.
* /esp_code/: The ESP8266 code measuring values and controlling the dehumidifier.
* /tcpSocket/: The Python socket server, that handles incoming data from the ESP. Writes into a database. 
* /ui/: The userinter interface.
* /wiring/: A basic wiring diagram.


## Implementation
### Hardware

### Mounting

### Programming language and environment

### Testing
