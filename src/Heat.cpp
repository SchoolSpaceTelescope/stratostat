#include <OneWire.h>
#include <DallasTemperature.h>

#include "Telemetry.h"
#include "Heat.h"

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 10

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress insideThermometer; //, outsideThermometer;

void printAddress(const DeviceAddress deviceAddress)
{
    Serial.print("Address: ");
    for (uint8_t i = 0; i < 8; i++)
    {
        if (deviceAddress[i] < 16) Serial.print("0");
        Serial.print(deviceAddress[i], HEX);
    }
    Serial.print(" ");
}

void printAlarmInfo(const DeviceAddress deviceAddress)
{
    char temp;
    printAddress(deviceAddress);
    temp = sensors.getHighAlarmTemp(deviceAddress);
    Serial.print("High Alarm: ");
    Serial.print(temp, DEC);
    Serial.print("C");
    Serial.print(" Low Alarm: ");
    temp = sensors.getLowAlarmTemp(deviceAddress);
    Serial.print(temp, DEC);
    Serial.print("C");
    Serial.print(" ");
}

void heat_setup(){
    // Start up the library
    sensors.begin();

    // locate devices on the bus
    Serial.print("Found ");
    Serial.print(sensors.getDeviceCount(), DEC);
    Serial.println(" devices.");

    // search for devices on the bus and assign based on an index
    if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");

    Serial.print("Device insideThermometer ");
    printAlarmInfo(insideThermometer);
    Serial.println();

    // set alarm ranges
    Serial.println("Setting alarm temps...");
    sensors.setHighAlarmTemp(insideThermometer, 127);
    sensors.setLowAlarmTemp(insideThermometer, 15);

    Serial.print("New insideThermometer ");
    printAlarmInfo(insideThermometer);
    Serial.println();
}

void temperature_check(struct Telemetry *telemetry){
    sensors.requestTemperatures();

    float tempC = sensors.getTempC(insideThermometer);
    telemetry->batteryTemp = tempC;

    if (sensors.hasAlarm())
    {
        if (tempC != DEVICE_DISCONNECTED_C && tempC < 15) {
            telemetry->batteryHeat = true;
        }
    } else {
        telemetry->batteryHeat = false;
    }

    digitalWrite(11, telemetry->batteryHeat);
}

void head_heat_data(){
    Serial.print("Battery Temp,");
    Serial.print("IsHeat,");
}

void print_heat_data(struct Telemetry *telemetry){
    Serial.print(telemetry->batteryTemp);
    Serial.print(",");
    Serial.print(telemetry->batteryHeat);
    Serial.print(",");
}