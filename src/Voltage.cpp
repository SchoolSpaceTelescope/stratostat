#include "Telemetry.h"
#include "Voltage.h"


void voltage_get(struct Telemetry *telemetry){
  double vBAT = (analogRead(A14) / 1024.) * ((68 + 11) / 11.) * 2.5;
  double v5 = (analogRead(A12) / 1024.) * ((68 + 47) / 47.) * 2.5;
  double v3v3 = (analogRead(A13) / 1024.) * ((47 + 68) / 68.) * 2.5;

  telemetry->vBAT = vBAT;
  telemetry->v5 = v5;
  telemetry->v3v3 = v3v3;
}

//void voltage_setup(){
//
//}