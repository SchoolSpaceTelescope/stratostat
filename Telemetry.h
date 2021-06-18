#include <stdint.h>

struct Telemetry{
  //GPS
  int8_t latitude, longitude;
  int8_t sat_count;
  float speed, altitude;

  int8_t second, minute, hour, day, month;
  uint16_t year;

  bool validFix;
  // GPS

  float pressure, temperatureBar, altitudeBar, atitudeBarCorrected; // barometer

   float vBAT ,v5, v3v3; // voltages
};