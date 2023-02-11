
<h1 align="center">
    Humidity_Control
</h1>

## Basics
This project aims at regulating our bathrooms humidity by controlling a dehumidifier. 
The humidity, temperature, current timestamp and the dehumidifier status is written into a database.
Using an UI, the user can observe how these values change over time.

  <img src="./pics/case_rendering.png" width="400" style="display: block;
  margin-left: auto;
  margin-right: auto;
  width: 60%;">

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->

**Table of Contents**
  - [Features](#features)
    - [Implemented features](#implemented-features)
    - [Possible future work](#possible-future-work)
    - [Intentional limitations](#intentional-limitations)
  - [Usage](#usage)
  - [Project structure](#project-structure)
  - [Implementation](#implementation)
    - [Hardware](#hardware)
    - [Mounting](#mounting)
    - [Establishing Communication](#sequencediagramm)
    - [Programming language and environment](#programming-language-and-environment)
  - [Sequencediagramm](#sequencediagramm)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->


## Features
### Implemented features
* Measuring the humidity and temperature
* Controlling the dehumidifyer
* Transmitting data to the server, writing into the database
* Saving data up to one day on the ESP, if the database is temporarily unavailable
* Plotting the time series
* 3D printable housing
### Possible future work
* bidirectional Communication from UI -> Ui-handler -> Backend -> esp
* Backend: 
  * Queue in Backend to what periods have already been sent to UI
  * User authentification
  * Redo in Java
* UI: 
  * Add Global Translationservice
  * Changing the dehumidifier activation threshold using the UI
* Database:
  * dump
  * Setup script
### Intentional limitations
* No secure communication

## Usage
In the ESP code, you have to setup the WiFi connection and the target TCP socket for the database. Follow the instructions provided [here](hardware/esp_code/src/README.md).

Make sure the database and server are setup correctly. Adjust the server IP and port in 'configuration.h'.


## Project structure
Here are some directories that may contain interesting files. All of these contain a separate, more detailed readme:
* [/backend/](backend/README.md):
    - [Backend server](backend/backendServer.py), that handles incoming data from the ESP. Writes into a database.
    - [Middleend server](backend/middleEndServer.py) that handles incoming requests from Frontend, executes a query in the database, formats the result and sends this back to frontend.
* [/ui/](ui/README.md): The user interface.
* [/hardware/](hardware/README.md): Relevant Information for setup of microcontroller
    * [/wiring/](hardware/wiring/README.md): A basic wiring diagram
    * [/esp_code/](hardware/esp_code/): The ESP8266 code measuring values and controlling the dehumidifier.
    * [/3d_objects/](hardware/3d_objects/README.md): The printable case as STLs.
* [/pics/](pics/): Pictures


## Implementation
### Hardware
We used a ESP8266 NodeMCU board as our microcontroller. An AZ-Delivery relay board is used to turn the dehumidifier on and off. We switch both the neutral and the phase wire. We use a DHT11 humidity and temperature sensor due to its low price and its easy availability. If you want a more accurate reading, you could switch to a DHT22, but this would require a 3D model redesign.  

### Mounting
Please refer to the picture below for installing the components and wiring. You need a few short M3 screws and some cables.  
Mount the ESP using M3 screws. The ESP will be powered or programmed using its USB port.  
To hold the relay board in place, you have to install the board and then melt the mounting pins of the case. Connect the power and GND wires to the ESP. Connect the two signal wires to D2 and D3 of the ESP. One relay is for the phase, the other for neutral. Fix the cables using the wire_lid. Please be careful work when working with mains voltage.

  <img src="pics/hum_control_open.jpg" width="400" style="display: block;
  margin-left: auto;
  margin-right: auto;
  width: 60%;">


### Sequencediagramm
##### This Chart visualizes the Communication between all components
\
 ![Installed hardware.](./pics/sequence_diagram.png "Installed hardware.")


### Programming language and environment

Backend, Frontend and Database is running on
**Raspberry Pi 4 Model B 8 GB RAM**

| Component | Programming Language | Framework | In Detail 
| --- | ----------- | --------- | ------- |
| Database | MySQL | |MariaDB
| Backend | Python
| Frontend | Typescript & HTML | Angular & Ionic
| Hardware | C, C++ | Arduino |Esp8266