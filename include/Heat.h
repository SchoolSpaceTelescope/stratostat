#include <DallasTemperature.h>

void heat_setup();

void temperature_check(struct Telemetry *telemetry);

void print_heat_data(struct Telemetry *telemetry);


void newAlarmHandler(const uint8_t* deviceAddress);
void printCurrentTemp(DeviceAddress deviceAddress);
void printAddress(const DeviceAddress deviceAddress);
void printTemp(const DeviceAddress deviceAddress);
void printAlarmInfo(const DeviceAddress deviceAddress);