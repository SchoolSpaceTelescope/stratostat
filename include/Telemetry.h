#include <Arduino.h>

struct Telemetry{
  //GPS
  long latitude, longitude;
  uint8_t sat_count;
  long speed, altitude;
  uint8_t hdop;

  uint8_t second, minute, hour, day, month;
  uint16_t year;

  bool validFix;
  // GPS

  double pressure, temperatureBar, altitudeBar, altitudeBarCorrected; // barometer

    double vBAT ,v5, v3v3; // voltages
};