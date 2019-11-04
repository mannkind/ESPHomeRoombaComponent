# Roomba Component for ESPHome

A barebones wrapper to enable control of a Roomba via MQTT with ESPHome.
Tested with ESPHome 1.13.x, and a Roomba 650 w/a Wemos D1 Mini installed.

## Hardware

The inspiration for this project is https://github.com/johnboiles/esp-roomba-mqtt. You'll find a detailed wiring guide there. In fact, I originally started off using that project for my Roomba 650. However, as I migrated my custom components to ESPHome, I wanted my Roomba to be on the same platform as the other devices. 

I should note that like others, I initially had trouble reading the sensor data from the Roomba. I posted the solution I found in https://github.com/johnboiles/esp-roomba-mqtt/issues/2#issuecomment-373956173

> For what it's worth, my Wemos D1 Mini couldn't read the Roomba sensors either. I found this snippet in an iRobot Create 2 Doc
>
>> In some cases, the drive strength of a Roomba TX line is not enough to drive the RX line of another board (for example, in some revisions of Arduino). In this case, a simple PNP transistor (2N2907A, 2N3906, or 2N4403, among others) can be used to provide enough “drive” for the Arduino.
> 
> I used a 2N3906 and following the circuit as described in the PDF; I can now read sensor values from the Roomba!

The D1 mini is small enough to fit into the compartment by the wheel. The [example image of D1 mini inside Roomba compartment](https://community-home-assistant-assets.s3.dualstack.us-west-2.amazonaws.com/optimized/2X/a/a258c7253f8bd3fe76ad9e7aa1202b60bd113d74_2_496x600.jpg) image is not a photo of mine specifically, but it's useful to see where the components fit inside the Roomba. It was sourced from a [community project thread on the Home Assistant forums](https://community.home-assistant.io/t/add-wifi-to-an-older-roomba/23282).

## Software Setup/Use

Take a look at the example directory for a fully working example.

* <example/esphome.yaml> - Contains the bits needed for ESPHome.
* <example/homeassistant-vacuum.yaml> - Contains the bits needed to integrate as a "MQTT Vacuum" in Home Assistant
