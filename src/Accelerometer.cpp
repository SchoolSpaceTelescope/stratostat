#include <MPU6050_tockn.h>
#include <Wire.h>

#include "Telemetry.h"
#include "Accelerometer.h"

// I2C Scanner
// Scanning...
// I2C device found at address 0x1E !
// I2C device found at address 0x68 !
// I2C device found at address 0x77 !
// done

// ========================================
// Calculating gyro offsets
// DO NOT MOVE MPU6050...
// Done!
// X : -3.16
// Y : -0.97

MPU6050 mpu6050(Wire);

unsigned long timer = 0;

void accelerometer_setup(){
    Wire.begin();
    mpu6050.begin();
    // mpu6050.calcGyroOffsets(true);
    mpu6050.setGyroOffsets(-3.16, -0.97, 0.29);
}

void accelerometer_get(struct Telemetry *telemetry){
    mpu6050.update();

    telemetry->gyroTemp = mpu6050.getTemp();
    telemetry->accAngleX = mpu6050.getAccAngleX();
    telemetry->accAngleY = mpu6050.getAccAngleY();

    telemetry->accX = mpu6050.getAccX();
    telemetry->accY = mpu6050.getAccY();
    telemetry->accZ = mpu6050.getAccZ();

    telemetry->gyroX = mpu6050.getGyroX();
    telemetry->gyroY = mpu6050.getGyroY();
    telemetry->gyroZ = mpu6050.getGyroZ();

    telemetry->gyroAngleX = mpu6050.getGyroAngleX();
    telemetry->gyroAngleY = mpu6050.getGyroAngleY();
    telemetry->gyroAngleZ = mpu6050.getGyroAngleZ();

    telemetry->angleX = mpu6050.getAngleX();
    telemetry->angleY = mpu6050.getAngleY();
    telemetry->angleZ = mpu6050.getAngleZ();
}

void print_accelerometer_data(struct Telemetry *telemetry){
    if(millis() - timer > 1000){
        Serial.println("=======================================================");
        Serial.print("temp : ");Serial.println(telemetry->gyroTemp);
        Serial.print("accX : ");Serial.print(telemetry->accAngleX);
        Serial.print("\taccY : ");Serial.print(telemetry->accY);
        Serial.print("\taccZ : ");Serial.println(telemetry->accZ);

        Serial.print("gyroX : ");Serial.print(telemetry->gyroX);
        Serial.print("\tgyroY : ");Serial.print(telemetry->gyroY);
        Serial.print("\tgyroZ : ");Serial.println(telemetry->gyroZ);

        Serial.print("accAngleX : ");Serial.print(telemetry->accAngleX);
        Serial.print("\taccAngleY : ");Serial.println(telemetry->accAngleY);

        Serial.print("gyroAngleX : ");Serial.print(telemetry->gyroAngleX);
        Serial.print("\tgyroAngleY : ");Serial.print(telemetry->gyroAngleY);
        Serial.print("\tgyroAngleZ : ");Serial.println(telemetry->gyroAngleZ);

        Serial.print("angleX : ");Serial.print(telemetry->angleX);
        Serial.print("\tangleY : ");Serial.print(telemetry->angleY);
        Serial.print("\tangleZ : ");Serial.println(telemetry->angleZ);
        Serial.println("=======================================================\n");
        timer = millis();
    }
}