#include <Arduino.h>

struct Telemetry{
    //GPS
    int8_t gps_state;
    float latitude, longitude;
    int8_t sat_count;
    float speed, altitude;
//    uint8_t hdop;

    uint8_t second, minute, hour, day, month;
    uint16_t year;

//    bool validFix;
    // GPS

    double pressure, temperatureBar, altitudeBar, altitudeBarCorrected; // barometer

    //GYRO
    float gyroTemp, accAngleX, accAngleY;
    float accX, accY, accZ;
    float gyroX, gyroY, gyroZ;
    float gyroAngleX, gyroAngleY, gyroAngleZ;
    float angleX, angleY, angleZ;
    //GYRO

    //MAGNETOMETER
    float magX, magY, magZ;
    float headingDegrees;


    float batteryTemp;
    bool batteryHeat;


    double vBAT ,v5, v3v3; // voltages

    byte crc;
};