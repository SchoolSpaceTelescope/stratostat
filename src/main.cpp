#include <Arduino.h>
#include "Telemetry.h"

#include "Accelerometer.h"
#include "Barometer.h"
#include "Current.h"
#include "GPS.h"
#include "Heat.h"
#include "Magnetometer.h"
#include "Temperature.h"
#include "Voltage.h"

struct Telemetry telemetry;

byte crc8_bytes(const byte *buffer, byte size) {
    byte crc = 0;
    for (byte i = 0; i < size; i++) {
        byte data = buffer[i];
        for (int j = 8; j > 0; j--) {
            crc = ((crc ^ data) & 1) ? (crc >> 1) ^ 0x8C : (crc >> 1);
            data >>= 1;
        }
    }
    return crc;
}

void setup() {
    pinMode(31, OUTPUT);  // green
    pinMode(32, OUTPUT);  // orange
    pinMode(33, OUTPUT);  // red
    pinMode(34, OUTPUT);  // ??
    pinMode(35, OUTPUT);  // ??
    pinMode(36, OUTPUT);  // ??
    pinMode(37, OUTPUT);  // ??

    digitalWrite(32, HIGH);  // init started

    analogReference(EXTERNAL);

    // DEBUG
    Serial.begin(9600);

    // RADIO
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    Serial1.begin(9600);

    // OPENLOG
    Serial2.begin(9600);
    delay(5000);


    barometer_setup();
    heat_setup();
    magnetometer_setup();

    gps_setup();
    digitalWrite(32, LOW);  // INIT END

    head_accelerometer_data();
    head_barometer_data();
    head_gps_data();
    head_heat_data();
    head_magnetometer_data();
    head_voltage();

    Serial.println();
}

void loop() {
    digitalWrite(34, HIGH);  // init started
    accelerometer_get(&telemetry);  // ok
    print_accelerometer_data(&telemetry);

    barometer_get(&telemetry);  // ok
    print_barometer_data(&telemetry);

    gps_get(&telemetry);
    print_gps_data(&telemetry);

    temperature_check(&telemetry);
    print_heat_data(&telemetry);

    magnetometer_get(&telemetry);  // ok
    print_magnetometer_data(&telemetry);

    voltage_get(&telemetry);  // ok
    print_voltage(&telemetry);

    Serial.println();

    telemetry.crc = crc8_bytes((byte *) &telemetry, sizeof(telemetry) - 1);

    Serial1.write((byte *) &telemetry, sizeof(telemetry));

    digitalWrite(34, LOW);
    delay(1000);
}
