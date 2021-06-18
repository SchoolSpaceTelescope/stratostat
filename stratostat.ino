#include "Telemetry.h"
#include "GPS.h"

#include "Barometer.h"


#define GPS_SERIAL Serial3

struct Telemetry telemetry;

void setup() {
  Serial.begin(9600);
  gps_setup();
  barometer_setup();
}

void loop() {
  gps_get(&telemetry);
}
  