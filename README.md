# Roomba Component for ESPHome

A barebones wrapper to enable control of a Roomba via ESPHome.
Tested with ESPHome 1.12.1, and a Roomba 650 w/a Wemos D1 Mini installed.

I apologize for how barebones this repo is; as soon as I got the Roomba/ESPHome component working, I was distracted by other projects. I hope to come back to this someday.

## Hardware

The inspiration for this project is https://github.com/johnboiles/esp-roomba-mqtt. You'll find a detailed wiring guide there. In fact, I originally started off using that project for my Roomba 650. However, as I migrated my custom components to ESPHome, I wanted my Roomba to be on the same platform as the other devices. 

I should note that like others, I initially had trouble reading the sensor data from the Roomba. I posted the solution I found in https://github.com/johnboiles/esp-roomba-mqtt/issues/2#issuecomment-373956173

> For what it's worth, my Wemos D1 Mini couldn't read the Roomba sensors either. I found this snippet in an iRobot Create 2 Doc
>
>> In some cases, the drive strength of a Roomba TX line is not enough to drive the RX line of another board (for example, in some revisions of Arduino). In this case, a simple PNP transistor (2N2907A, 2N3906, or 2N4403, among others) can be used to provide enough “drive” for the Arduino.
> 
> I used a 2N3906 and following the circuit as described in the PDF; I can now read sensor values from the Roomba!

## Software Setup/Use

Take a look at the example directory for a fully working example (very close to my setup).
