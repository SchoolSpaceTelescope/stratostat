#include "Telemetry.h"
#include "Voltage.h"


void voltage_get(struct Telemetry *telemetry){
    telemetry->vBAT = (analogRead(A14) / 1024.) * ((68 + 11) / 11.) * 2.5;
    telemetry->v5 = (analogRead(A12) / 1024.) * ((68 + 47) / 47.) * 2.5;
    telemetry->v3v3 = (analogRead(A13) / 1024.) * ((47 + 68) / 68.) * 2.5;
}

//void voltage_setup(){
//
//}

void head_voltage(){
    Serial.print("VBAT,");
    Serial.print("3V3,");
    Serial.print("5V,");
}

void print_voltage(struct Telemetry *telemetry){
    Serial.println(telemetry->vBAT);
    Serial.print(",");
    Serial.println(telemetry->v3v3);
    Serial.print(",");
    Serial.println(telemetry->v5);
    Serial.print(",");
//    Serial.print("Current: "); Serial.println(telemetry->current);
}