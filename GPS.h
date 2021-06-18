#include <MicroNMEA.h>

void gps_get(struct Telemetry *telemetry);

void gps_setup(void);
void printUnknownSentence(MicroNMEA& nmea);