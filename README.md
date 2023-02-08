# humidity_control <img width="100" height="100" align="right" src="./pics/logo.png">
## Basics
This project aims at regulating our bathrooms humidity by controlling a dehumidifier. 
The humidity, temperature, current timestamp and the dehumidifier status is written into a database.
Using an UI, the user can observe how these values change over time.  
![Rendering of the physical hardware](./pics/case_rendering.PNG "Hardware rendering.")


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
* Add Script for Setup
### Intentional limitations
* No secure communication


## Usage
In the ESP code, you have to setup the WiFi connection and the target TCP socket for the database. Follow the instructions in /esp_code/src/README.md.
Make sure the database and server are setup correctly. Adjust the server IP and port in 'configuration.h'.


## Project structure
Here are some directories that may contain interesting files. All of these contain a separate, more detailed readme:
* /3d_objects/: The printable case as STLs.
* /esp_code/: The ESP8266 code measuring values and controlling the dehumidifier.
* /tcpSocket/:
    - Python socket server, that handles incoming data from the ESP. Writes into a database.
    - Python socket server, that handles incoming requests from Frontend, executes a query in the database, formats the result and sends this back to frontend.
* /ui/: The user interface.
* /wiring/: A basic wiring diagram.
* /pics/: Some images.


## Implementation
### Hardware
We used a ESP8266 NodeMCU board as our microcontroller. An AZ-Delivery relay board is used to turn the dehumidifier on and off. We switch both the neutral and the phase wire. We use a DHT11 humidity and temperature sensor due to its low price and its easy availability. If you want a more accurate reading, you could switch to a DHT22, but this would require a 3D model redesign.  

### Mounting
Please refer to the picture below for installing the components and wiring. You need a few short M3 screws and some cables.  
Mount the ESP using M3 screws. The ESP will be powered or programmed using its USB port.  
To hold the relay board in place, you have to install the board and then melt the mounting pins of the case. Connect the power and GND wires to the ESP. Connect the two signal wires to D2 and D3 of the ESP. One relay is for the phase, the other for neutral. Fix the cables using the wire_lid. Please be careful work when working with mains voltage.  
![Installed hardware.](./pics/hum_control_open.jpg "Installed hardware.")

### Sequencediagramm

##### This Chart visualizes the Communication between all Components

[![](https://mermaid.ink/img/pako:eNqVU7FuwjAQ_RXLU1CTH_DA0NKqSO0A6VRlucaXEDW2g30eIsS_1w4JFASo9WD57t57d8-Jd7w0ErngDrcedYmLBmoLqtAsrFevGtlQn-WonbHZfP5wkRLMIsjDOYnHqZ7M0qH0gapDC-QtJrPZTdlHKL9RS8Fc2BWCC3i5AIKEGoWOQHUp24y8lNFJNbZpoR-lR50oGdlf4FCwRju0FOOlJpO4INZiDEfShMwCLTtN4ssSnat82_ZsOUigvGmAXbmYMFZOYUj3tAFdo0z-6H99Yv62_1-fA_6PNq-5fLFG09jkCK9xaJDcmyNfva082j6523gbIWt0vqVLtYibugtWGauAwlirc8aBc9inxVOuMMAbGf7pXawVnDaosOAiHCVWENgFL_Q-QMGTyXtdckHWY8p9J4GmJ3CefA4fzFguKmhdSHagP41RxxiH8vvhLZVGV03N9z_XXyYm?type=png)](https://mermaid.live/edit#pako:eNqVU7FuwjAQ_RXLU1CTH_DA0NKqSO0A6VRlucaXEDW2g30eIsS_1w4JFASo9WD57t57d8-Jd7w0ErngDrcedYmLBmoLqtAsrFevGtlQn-WonbHZfP5wkRLMIsjDOYnHqZ7M0qH0gapDC-QtJrPZTdlHKL9RS8Fc2BWCC3i5AIKEGoWOQHUp24y8lNFJNbZpoR-lR50oGdlf4FCwRju0FOOlJpO4INZiDEfShMwCLTtN4ssSnat82_ZsOUigvGmAXbmYMFZOYUj3tAFdo0z-6H99Yv62_1-fA_6PNq-5fLFG09jkCK9xaJDcmyNfva082j6523gbIWt0vqVLtYibugtWGauAwlirc8aBc9inxVOuMMAbGf7pXawVnDaosOAiHCVWENgFL_Q-QMGTyXtdckHWY8p9J4GmJ3CefA4fzFguKmhdSHagP41RxxiH8vvhLZVGV03N9z_XXyYm)

### Programming language and environment

Backend, Frontend and Database is running on
**Raspberry Pi 4 Model B 8 GB RAM**

| Component | Programming Language | Framework | In Detail 
| --- | ----------- | --------- | ------- |
| Database | MySQL | |MariaDB
| Backend | Python
| Frontend | Typescript & HTML | Angular & Ionic
| Hardware | C, C++ | Arduino |Esp8266
