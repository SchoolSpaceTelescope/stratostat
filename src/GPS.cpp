#include <TroykaGPS.h>

#include "Telemetry.h"
#include "GPS.h"

HardwareSerial& console = Serial;

#define GPS_SERIAL Serial3

GPS gps(GPS_SERIAL);

void gps_setup()
{
    GPS_SERIAL.begin(9600);
}

void gps_get(struct Telemetry *telemetry)
{
    if (gps.available()) {
        gps.readParsing();

        telemetry->gps_state = gps.getState();

        telemetry->sat_count = gps.getSat();

        telemetry->latitude = gps.getLatitudeBase10();
        telemetry->longitude = gps.getLongitudeBase10();

        telemetry->speed = gps.getSpeedKm();

        telemetry->altitude = gps.getAltitude();

        telemetry->second = gps.getSecond();
        telemetry->minute = gps.getMinute();
        telemetry->hour = gps.getHour();
        telemetry->day = gps.getDay();
        telemetry->month = gps.getMonth();

        telemetry->year = gps.getYear();
    }
}

void head_gps_data(){
    console.print("GPS state,");
    console.print("Satellite count,");
    console.print("Year,");
    console.print("Month,");
    console.print("Day,");
    console.print("Hour,");
    console.print("Minute,");
    console.print("Second,");
    console.print("Latitude,");
    console.print("Longitude,");
    console.print("Altitude,");
    console.print("Speed,");
}

void print_gps_data(struct Telemetry *telemetry){
    switch (telemetry->gps_state) {
        case GPS_OK:
            Serial.println("GPS_OK,");
            break;
        case GPS_ERROR_DATA:
            Serial.println("GPS_ERROR_DATA,");
            break;
        case GPS_ERROR_SAT:
            Serial.println("GPS_ERROR_SAT,");
            break;
    }

    console.println(telemetry->sat_count);
    console.print(",");

    console.print(telemetry->year);
    console.print(",");
    console.print(int(telemetry->month));
    console.print(",");
    console.print(int(telemetry->day));
    console.print(",");
    console.print(int(telemetry->hour));
    console.print(",");
    console.print(int(telemetry->minute));
    console.print(",");
    console.println(int(telemetry->second));
    console.print(",");

//    console.print("Latitude: ");
    console.println(telemetry->latitude, 6);
    console.print(",");

//    console.print("Longitude: ");
    console.println(telemetry->longitude, 6);
    console.print(",");


//    console.print("Altitude (m): ");
    console.println(telemetry->altitude, 3);
    console.print(",");

//    console.print("Speed: ");
    console.println(telemetry->speed, 3);
    console.print(",");
}
