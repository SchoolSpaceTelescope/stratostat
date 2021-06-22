#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

#include "Telemetry.h"
#include "Magnetometer.h"


void displaySensorDetails()
{
    sensor_t sensor;
    mag.getSensor(&sensor);
    Serial.println("------------------------------------");
    Serial.print  ("Sensor:       "); Serial.println(sensor.name);
    Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
    Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
    Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
    Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
    Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");
    Serial.println("------------------------------------");
    Serial.println("");
    delay(500);
}


void magnetometer_setup(){
    Serial.println("HMC5883 Magnetometer Test"); Serial.println("");

    /* Initialise the sensor */
    if(!mag.begin())
    {
        /* There was a problem detecting the HMC5883 ... check your connections */
        Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
        while(1);
    }

    /* Display some basic information on this sensor */
    displaySensorDetails();
    delay(5000);
}

void magnetometer_get(struct Telemetry *telemetry){
    /* Get a new sensor event */
    sensors_event_t event;
    mag.getEvent(&event);

    telemetry->magX = event.magnetic.x;
    telemetry->magY = event.magnetic.y;
    telemetry->magZ = event.magnetic.z;

    // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
    // Calculate heading when the magnetometer is level, then correct for signs of axis.
    float heading = atan2(event.magnetic.y, event.magnetic.x);

    // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
    // Find yours here: http://www.magnetic-declination.com/
    // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
    // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
    // float declinationAngle = 0.22;
    // heading += declinationAngle;

    // Correct for when signs are reversed.
    if(heading < 0)
        heading += 2*PI;

    // Check for wrap due to addition of declination.
    if(heading > 2*PI)
        heading -= 2*PI;

    // Convert radians to degrees for readability.
    float headingDegrees = heading * 180/M_PI;

    telemetry->headingDegrees = headingDegrees;

    delay(500);
}


void print_magnetometer_data(struct Telemetry *telemetry){
    /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
    Serial.print("X: "); Serial.print(telemetry->magX); Serial.print("  ");
    Serial.print("Y: "); Serial.print(telemetry->magY); Serial.print("  ");
    Serial.print("Z: "); Serial.print(telemetry->magZ); Serial.print("  ");Serial.println("uT");

    Serial.print("Heading (degrees): "); Serial.println(telemetry->headingDegrees);
}

