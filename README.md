# Roomba Component for ESPHomeLib

A barebones wrapper to enable control of a Roomba via ESPHomeLib.
Tested with ESPHomeLib 1.9.1, and a Roomba 650 w/a Wemos D1 Mini installed.

## Setup/Use

I've included my `roomba.yaml`, `roomba/src/main.cpp`, and `roomba/platformio.ini` files as examples. My changes are isolated between:

* `; // Start Roomba Component Addition`
* `; // End Roomba Component Addition`.

### roomba.yaml

```yaml
esphomeyaml:
  use_custom_code: True
  name: Roomba
  platform: ESP8266
  board: esp01_1m

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

mqtt:
  broker: !secret mqtt_broker
  discovery: true

logger:
  level: info

ota:

binary_sensor:
  - platform: status
    name: "Roomba Status"
```

### roomba/platformio.ini

```ini
; Auto generated code by esphomeyaml

[common]
; // Start Roomba Component Addition
lib_deps = 
  ESPHomeLibRoombaComponent=https://github.com/mannkind/ESPHomeLibRoombaComponent
  Roomba=http://www.airspayce.com/mikem/arduino/Roomba/Roomba-1.4.zip
build_flags =
upload_flags =
; // End Roomba Component Addition

; ===== DO NOT EDIT ANYTHING BELOW THIS LINE =====
; ========== AUTO GENERATED CODE BEGIN ===========
[env:roomba]
platform = espressif8266@>=1.8.0
board = esp01_1m
framework = arduino
lib_deps =
    ArduinoOTA
    ESP8266WiFi
    ESP8266mDNS
    Hash
    https://github.com/OttoWinter/esphomelib.git#v1.9.1
    ${common.lib_deps}
build_flags =
    -DESPHOMELIB_LOG_LEVEL=ESPHOMELIB_LOG_LEVEL_INFO
    -DUSE_NEW_OTA
    ${common.build_flags}
upload_speed = 115200
; =========== AUTO GENERATED CODE END ============
; ========= YOU CAN EDIT AFTER THIS LINE =========
```

### roomba/src/main.cpp

```c++
// Auto generated code by esphomeyaml
#include "esphomelib/application.h"
; // Start Roomba Component Addition
#include "ESPHomeLibRoombaComponent.h"
; // End Roomba Component Addition

using namespace esphomelib;

void setup() {
  // ===== DO NOT EDIT ANYTHING BELOW THIS LINE =====
  // ========== AUTO GENERATED CODE BEGIN ===========
  App.set_name("Roomba");
  App.set_compilation_datetime(__DATE__ ", " __TIME__);
  ::LogComponent *_logcomponent = App.init_log(115200);
  _logcomponent->set_global_log_level(ESPHOMELIB_LOG_LEVEL_INFO);
  ::WiFiComponent *_wificomponent = App.init_wifi();
  _wificomponent->set_sta(::WiFiAp{
      .ssid = "",
      .password = "",
      .channel = -1,
  });
  ::OTAComponent *_otacomponent = App.init_ota();
  _otacomponent->start_safe_mode();
  mqtt::MQTTClientComponent *mqtt_mqttclientcomponent = App.init_mqtt("", 1883, "", "");
  ::Application::MakeStatusBinarySensor _application_makestatusbinarysensor = App.make_status_binary_sensor("Roomba Status");
  binary_sensor::StatusBinarySensor *binary_sensor_statusbinarysensor = _application_makestatusbinarysensor.status;
  binary_sensor::MQTTBinarySensorComponent *binary_sensor_mqttbinarysensorcomponent = _application_makestatusbinarysensor.mqtt;
  // =========== AUTO GENERATED CODE END ============
  // ========= YOU CAN EDIT AFTER THIS LINE =========
  ; // Start Roomba Component Addition
  auto *custom_roomba = new RoombaComponent(
      "Distance",
      "Voltage",
      "Current",
      "Charge",
      "Capacity",
      "Charging",
      "Docked",
      "Cleaning",
      "On",
      "Off",
      "Dock",
      "Locate",
      "Spot Clean",
      "Roomba/command", /* command_topic */
      4,                /* BRC Pin */
      5000              /* Update Interval */
    );

  App.register_component(custom_roomba);
  App.register_sensor(custom_roomba->distance_sensor);
  App.register_sensor(custom_roomba->voltage_sensor);
  App.register_sensor(custom_roomba->current_sensor);
  App.register_sensor(custom_roomba->charge_sensor);
  App.register_sensor(custom_roomba->capacity_sensor);
  App.register_binary_sensor(custom_roomba->chargingState_sensor);
  App.register_binary_sensor(custom_roomba->dockedState_sensor);
  App.register_binary_sensor(custom_roomba->cleaningState_sensor);
  App.register_switch(custom_roomba->on_switch);
  App.register_switch(custom_roomba->off_switch);
  App.register_switch(custom_roomba->dock_switch);
  App.register_switch(custom_roomba->locate_switch);
  App.register_switch(custom_roomba->spot_switch);
  ; // End Roomba Component Addition
  App.setup();
}

void loop() {
  App.loop();
  delay(16);
}
```
