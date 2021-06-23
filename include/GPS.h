

void gps_get(struct Telemetry *telemetry);

void gps_setup();
//void printUnknownSentence(MicroNMEA& nmea);
void print_gps_data(struct Telemetry *telemetry);