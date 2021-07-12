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

void head_accelerometer_data(){
    Serial.print("Accelerometer Temp,");

    Serial.print("AccelX,");
    Serial.print("AccelY,");
    Serial.print("AccelZ,");

    Serial.print("GyroX,");
    Serial.print("GyroY,");
    Serial.print("GyroZ,");

    Serial.print("AccelAngleX,");
    Serial.print("AccelAngleY,");

    Serial.print("GyroAngleX,");
    Serial.print("GyroAngleY,");
    Serial.print("GyroAngleZ,");

    Serial.print("AngleX,");
    Serial.print("AngleY,");
    Serial.print("AngleZ,");
}

void print_accelerometer_data(struct Telemetry *telemetry){
//        Serial.println("=======================================================");
//        Serial.print("temp : ");
    Serial.print(telemetry->gyroTemp);
    Serial.print(",");
    Serial.print(telemetry->accX);
    Serial.print(",");
    Serial.print(telemetry->accY);
    Serial.print(",");
    Serial.print(telemetry->accZ);
    Serial.print(",");

//    Serial.print("gyroX : ");
    Serial.print(telemetry->gyroX);
    Serial.print(",");
    Serial.print(telemetry->gyroY);
    Serial.print(",");
    Serial.print(telemetry->gyroZ);
    Serial.print(",");

//    Serial.print("accAngleX : ");
    Serial.print(telemetry->accAngleX);
    Serial.print(",");
    Serial.print(telemetry->accAngleY);
    Serial.print(",");

//    Serial.print("gyroAngleX : ");
    Serial.print(telemetry->gyroAngleX);
    Serial.print(",");
    Serial.print(telemetry->gyroAngleY);
    Serial.print(",");
    Serial.print(telemetry->gyroAngleZ);
    Serial.print(",");

//    Serial.print("angleX : ");
    Serial.print(telemetry->angleX);
    Serial.print(",");
    Serial.print(telemetry->angleY);
    Serial.print(",");
    Serial.print(telemetry->angleZ);
    Serial.print(",");
}