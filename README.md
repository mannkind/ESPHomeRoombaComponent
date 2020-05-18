# Unsupported

Due to a botched surgery, I no longer have a Roomba 650. Leaving it for for future DIYers.

# Roomba Component for ESPHome

A barebones bit of glue between ESPHome and Mike McCauley's Roomba library that enables control of a Roomba 650 via MQTT.

Last tested with ESPHome 1.13.x and Mike McCauley's Roomba Library 1.3.

The inspiration is [John Boiles' esp-roomba-mqtt project](https://github.com/johnboiles/esp-roomba-mqtt), but I want all my IoT devices driven by ESPHome.

## Hardware

## Wiring Guide
John Boiles' wiring guide was the basis for my setup.

The main difference is that John Boiles' repo uses a voltage divider on the Roomba's TX pin, while I used a PNP transistor. I used a transistor because the voltage divider was not working for me, and I found a Roomba Create document with the following information:

> In some cases, the drive strength of a Roomba TX line is not enough to drive the RX line of another board (for example, in some revisions of Arduino). In this case, a simple PNP transistor (2N2907A, 2N3906, or 2N4403, among others) can be used to provide enough “drive” for the Arduino.  
> 
> Source: [Roomba Create® 2 to 5V Logic](http://www.irobot.com/~/media/MainSite/PDFs/About/STEM/Create/Create_2_to_5V_Logic.pdf)

## Alternative Wiring Guide
One might find this [alternative wiring guide](https://i.stack.imgur.com/aaifY.jpg) easier to get started with. It has fewer parts required and uses a PNP transistor.

## Special Notes

* Many PNP Transistors will work; **pay attention** to the pinout of the specific transistor you choose to use.
* Many pins can be the BRC pin; update [roomba.yaml](example/roomba.yaml#L13) with the pin you choose.  
  The example matches John Boiles' chosen pin D5/GPIO14.

## Placement

The Wemos D1 mini is small enough to [fit into the compartment by one of the wheels](https://community-home-assistant-assets.s3.dualstack.us-west-2.amazonaws.com/optimized/2X/a/a258c7253f8bd3fe76ad9e7aa1202b60bd113d74_2_496x600.jpg).  
_Source:_ [Add wifi to an older roomba](https://community.home-assistant.io/t/add-wifi-to-an-older-roomba/23282) community project thread on the Home Assistant forum.


## Software Setup/Use

Take a look at the example directory for a fully working example.

* <example/esphome.yaml> - Contains the bits needed for ESPHome.
* <example/homeassistant-vacuum.yaml> - Contains the bits needed to integrate as a "MQTT Vacuum" in Home Assistant.
