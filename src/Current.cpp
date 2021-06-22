#include "Telemetry.h"
#include "Current.h"


void current_get(struct Telemetry *telemetry){
  //telemetry->vBAT = vBAT;
  //telemetry->v5 = v5;
  //telemetry->v3v3 = v3v3;
}

void current_setup() {

}


void print_current_data(struct Telemetry *telemetry){

}
//void voltage_get(struct Telemetry *telemetry){
//  float vBAT = (float) (analogRead(A14) / 1024.) * ((68 + 11) / 11.) * 2.5;
//  float v5 = (float)  (analogRead(A12) / 1024.) * ((68 + 47) / 47.) * 2.5;
//  float v3v3 = (float) (analogRead(A13) / 1024.) * ((47 + 68) / 68.) * 2.5;
//
//  telemetry->vBAT = vBAT;
//  telemetry->v5 = v5;
//  telemetry->v3v3 = v3v3;
//}
//
//void voltage_setup(void){
//
//}