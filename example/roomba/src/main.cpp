// Auto generated code by esphomeyaml
#include "esphomelib/application.h"
#include "ESPHomeLibRoombaComponent.h"

using namespace esphomelib;

void setup() {
  // ===== DO NOT EDIT ANYTHING BELOW THIS LINE =====
  // ========== AUTO GENERATED CODE BEGIN ===========
  App.set_name("roomba");
  App.set_compilation_datetime(__DATE__ ", " __TIME__);
  ::LogComponent *_logcomponent = App.init_log(115200);
  _logcomponent->set_global_log_level(ESPHOMELIB_LOG_LEVEL_INFO);
  ::WiFiComponent *_wificomponent = App.init_wifi();
  _wificomponent->set_sta(::WiFiAp{
      .ssid = "My Wifi SSID",
      .password = "My Wifi Password",
      .channel = -1,
  });
  ::OTAComponent *_otacomponent = App.init_ota();
  _otacomponent->start_safe_mode();
  mqtt::MQTTClientComponent *mqtt_mqttclientcomponent = App.init_mqtt("mosquitto.org", 1883, "", "");
  // =========== AUTO GENERATED CODE END ============
  // ========= YOU CAN EDIT AFTER THIS LINE =========

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

  App.setup();
}

void loop() {
  App.loop();
  delay(16);
}