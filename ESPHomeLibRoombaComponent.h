#include "esphomelib/application.h"
#include <Roomba.h>

using namespace esphomelib;

static const char *TAG = "component.Roomba";

Roomba roomba(&Serial, Roomba::Baud115200);
void roombaWakeup(uint8_t pin)
{
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    delay(500);
    digitalWrite(pin, HIGH);
    delay(100);
}

class RoombaOnSwitch : public switch_::Switch
{
  protected:
    uint8_t brcPin;

  public:
    RoombaOnSwitch(const std::string &name, uint8_t brcPin) : switch_::Switch(name)
    {
        this->brcPin = brcPin;
    }

    void write_state(bool state) override
    {
        this->publish_state(true);
        roombaWakeup(this->brcPin);
        roomba.cover();
        this->publish_state(false);
    }
};

class RoombaOffSwitch : public switch_::Switch
{
  protected:
    uint8_t brcPin;

  public:
    RoombaOffSwitch(const std::string &name, uint8_t brcPin) : switch_::Switch(name)
    {
        this->brcPin = brcPin;
    }

    void write_state(bool state) override
    {
        this->publish_state(true);
        roombaWakeup(this->brcPin);
        roomba.cover();
        this->publish_state(false);
    }
};

class RoombaDockSwitch : public switch_::Switch
{
  protected:
    uint8_t brcPin;

  public:
    RoombaDockSwitch(const std::string &name, uint8_t brcPin) : switch_::Switch(name)
    {
        this->brcPin = brcPin;
    }

    void write_state(bool state) override
    {
        this->publish_state(true);
        roombaWakeup(this->brcPin);
        roomba.dock();
        this->publish_state(false);
    }
};

class RoombaLocateSwitch : public switch_::Switch
{
  protected:
    uint8_t brcPin;
    uint8_t song;

  public:
    RoombaLocateSwitch(const std::string &name, uint8_t brcPin, uint8_t song) : switch_::Switch(name)
    {
        this->brcPin = brcPin;
    }

    void write_state(bool state) override
    {
        this->publish_state(true);
        roombaWakeup(this->brcPin);
        roomba.playSong(this->song);
        this->publish_state(false);
    }
};

class RoombaSpotSwitch : public switch_::Switch
{
  protected:
    uint8_t brcPin;

  public:
    RoombaSpotSwitch(const std::string &name, uint8_t brcPin) : switch_::Switch(name)
    {
        this->brcPin = brcPin;
    }

    void write_state(bool state) override
    {
        this->publish_state(true);
        roombaWakeup(this->brcPin);
        roomba.spot();
        this->publish_state(false);
    }
};

class RoombaDistanceSensor : public sensor::Sensor
{
  public:
    RoombaDistanceSensor(const std::string &name) : sensor::Sensor(name) {}
    std::string unit_of_measurement() override { return "mm"; }
    int8_t accuracy_decimals() override { return 1; }
};

class RoombaVoltageSensor : public sensor::Sensor
{
  public:
    RoombaVoltageSensor(const std::string &name) : sensor::Sensor(name) {}
    std::string unit_of_measurement() override { return "mV"; }
    int8_t accuracy_decimals() override { return 1; }
};

class RoombaCurrentSensor : public sensor::Sensor
{
  public:
    RoombaCurrentSensor(const std::string &name) : sensor::Sensor(name) {}
    std::string unit_of_measurement() override { return "mA"; }
    int8_t accuracy_decimals() override { return 1; }
};

class RoombaChargeSensor : public sensor::Sensor
{
  public:
    RoombaChargeSensor(const std::string &name) : sensor::Sensor(name) {}
    std::string unit_of_measurement() override { return "mAh"; }
    int8_t accuracy_decimals() override { return 1; }
};

class RoombaCapacitySensor : public sensor::Sensor
{
  public:
    RoombaCapacitySensor(const std::string &name) : sensor::Sensor(name) {}
    std::string unit_of_measurement() override { return "mAh"; }
    int8_t accuracy_decimals() override { return 1; }
};

class RoombaChargingStateSensor : public binary_sensor::BinarySensor
{
  public:
    RoombaChargingStateSensor(const std::string &name) : binary_sensor::BinarySensor(name) {}
};

class RoombaDockedStateSensor : public binary_sensor::BinarySensor
{
  public:
    RoombaDockedStateSensor(const std::string &name) : binary_sensor::BinarySensor(name) {}
};

class RoombaCleaningStateSensor : public binary_sensor::BinarySensor
{
  public:
    RoombaCleaningStateSensor(const std::string &name) : binary_sensor::BinarySensor(name) {}
};

class RoombaComponent : public PollingComponent
{
  protected:
    uint8_t brcPin;
    std::string commandTopic;

  public:
    RoombaDistanceSensor *distance_sensor;
    RoombaVoltageSensor *voltage_sensor;
    RoombaCurrentSensor *current_sensor;
    RoombaChargeSensor *charge_sensor;
    RoombaCapacitySensor *capacity_sensor;
    RoombaChargingStateSensor *chargingState_sensor;
    RoombaDockedStateSensor *dockedState_sensor;
    RoombaCleaningStateSensor *cleaningState_sensor;
    RoombaOnSwitch *on_switch;
    RoombaOffSwitch *off_switch;
    RoombaDockSwitch *dock_switch;
    RoombaLocateSwitch *locate_switch;
    RoombaSpotSwitch *spot_switch;

    RoombaComponent(
        const std::string &distanceName,
        const std::string &voltageName,
        const std::string &currentName,
        const std::string &chargeName,
        const std::string &capacityName,
        const std::string &chargingStateName,
        const std::string &dockedStateName,
        const std::string &cleaningStateName,
        const std::string &onSwitchName,
        const std::string &offSwitchName,
        const std::string &dockSwitchName,
        const std::string &locateSwitchName,
        const std::string &spotSwitchName,
        const std::string &commandTopic,
        uint8_t brcPin,
        uint32_t update_interval)
        : PollingComponent(update_interval)
    {
        this->brcPin = brcPin;
        this->distance_sensor = new RoombaDistanceSensor(distanceName);
        this->voltage_sensor = new RoombaVoltageSensor(voltageName);
        this->current_sensor = new RoombaCurrentSensor(currentName);
        this->charge_sensor = new RoombaChargeSensor(chargeName);
        this->capacity_sensor = new RoombaCapacitySensor(capacityName);
        this->chargingState_sensor = new RoombaChargingStateSensor(chargingStateName);
        this->dockedState_sensor = new RoombaDockedStateSensor(dockedStateName);
        this->cleaningState_sensor = new RoombaCleaningStateSensor(cleaningStateName);
        this->on_switch = new RoombaOnSwitch(onSwitchName, brcPin);
        this->off_switch = new RoombaOffSwitch(offSwitchName, brcPin);
        this->dock_switch = new RoombaDockSwitch(dockSwitchName, brcPin);
        this->locate_switch = new RoombaLocateSwitch(locateSwitchName, brcPin, 1);
        this->spot_switch = new RoombaSpotSwitch(spotSwitchName, brcPin);

        this->commandTopic = commandTopic;
    }

    void setup() override
    {
        ESP_LOGD(TAG, "Setting up Roomba.");
        pinMode(this->brcPin, OUTPUT);
        digitalWrite(this->brcPin, HIGH);

        roomba.start();

        ESP_LOGD(TAG, "Attempting to subscribe to MQTT.");
        mqtt::global_mqtt_client->subscribe(this->commandTopic, [&](const std::string &payload) {
            ESP_LOGD(TAG, "Got values %s", payload.c_str());
            if (payload == "turn_on")
            {
                this->on_switch->turn_on();
            }
            else if (payload == "turn_off")
            {
                this->off_switch->turn_on();
            }
            else if (payload == "dock")
            {
                this->dock_switch->turn_on();
            }
            else if (payload == "locate")
            {
                this->locate_switch->turn_on();
            }
            else if (payload == "spot")
            {
                this->spot_switch->turn_on();
            }
            else
            {
                ESP_LOGW(TAG, "Received unknown status payload: %s", payload.c_str());
                this->status_momentary_warning("state", 5000);
            }
        });
    }

    void update() override
    {
        ESP_LOGD(TAG, "Attempting to update sensor values.");

        int16_t distance;
        uint16_t voltage;
        int16_t current;
        uint16_t charge;
        uint16_t capacity;
        uint8_t charging;
        bool cleaningState;
        bool dockedState;
        bool chargingState;
        // Flush serial buffers
        while (Serial.available())
        {
            Serial.read();
        }

        uint8_t sensors[] = {
            Roomba::SensorDistance,       // 2 bytes, mm, signed
            Roomba::SensorChargingState,  // 1 byte
            Roomba::SensorVoltage,        // 2 bytes, mV, unsigned
            Roomba::SensorCurrent,        // 2 bytes, mA, signed
            Roomba::SensorBatteryCharge,  // 2 bytes, mAh, unsigned
            Roomba::SensorBatteryCapacity // 2 bytes, mAh, unsigned
        };
        uint8_t values[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        // Serial reading timeout -- https://community.home-assistant.io/t/add-wifi-to-an-older-roomba/23282/52
        bool success = roomba.getSensorsList(sensors, sizeof(sensors), values, sizeof(values));
        if (!success)
        {
            ESP_LOGD(TAG, "Unable to read sensors from the Roomba.");
            return;
        }

        distance = values[0] * 256 + values[1];
        voltage = values[3] * 256 + values[4];
        current = values[5] * 256 + values[6];
        charge = values[7] * 256 + values[8];
        capacity = values[9] * 256 + values[10];
        charging = values[2];

        cleaningState = current < -300;
        dockedState = current > -50;
        chargingState = charging == Roomba::ChargeStateReconditioningCharging || charging == Roomba::ChargeStateFullChanrging || charging == Roomba::ChargeStateTrickleCharging;

        this->distance_sensor->publish_state(distance);
        this->voltage_sensor->publish_state(voltage);
        this->current_sensor->publish_state(current);
        this->charge_sensor->publish_state(charge);
        this->capacity_sensor->publish_state(capacity);
        this->chargingState_sensor->publish_state(chargingState);
        this->dockedState_sensor->publish_state(dockedState);
        this->cleaningState_sensor->publish_state(cleaningState);
    }
};
