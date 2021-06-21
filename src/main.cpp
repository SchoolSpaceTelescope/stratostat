#include <Arduino.h>
#include "Telemetry.h"
#include "GPS.h"

#include "Current.h"

#include "Barometer.h"

struct Telemetry telemetry;

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



    gps_setup();
    barometer_setup();

    current_setup();

    digitalWrite(32, LOW);  // INIT END
}

void loop() {
    gps_get(&telemetry);
    print_gps_data(&telemetry);

    Serial1.write((byte *) &telemetry, sizeof(telemetry));
}
