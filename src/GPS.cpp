#include "Telemetry.h"
#include "GPS.h"

HardwareSerial& console = Serial;
HardwareSerial& gps = Serial3;

char nmeaBuffer[100];
MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));

void gps_get(struct Telemetry *telemetry){
  while (gps.available()) {
    gps.read();

    telemetry->validFix = nmea.isValid();
    telemetry->sat_count = nmea.getNumSatellites();
    
    telemetry->latitude = nmea.getLatitude();
    telemetry->longitude = nmea.getLongitude();

    telemetry->speed = nmea.getSpeed();

    if (!nmea.getAltitude(telemetry->altitude))
        telemetry->altitude = -1;

    telemetry->second = nmea.getSecond();
    telemetry->minute = nmea.getMinute();
    telemetry->hour = nmea.getHour();
    telemetry->day = nmea.getDay();
    telemetry->month = nmea.getMonth();

    telemetry->year = nmea.getYear();

    telemetry->hdop = nmea.getHDOP();
  }
}


void print_gps_data(struct Telemetry *telemetry){
    // Output GPS information from previous second
    console.print("Valid fix: ");
    console.println(telemetry->validFix ? "yes" : "no");

//    console.print("Nav. system: ");
//    if (nmea.getNavSystem())
//        console.println(nmea.getNavSystem());
//    else
//        console.println("none");

    console.print("Num. satellites: ");
    console.println(telemetry->sat_count);

    console.print("HDOP: ");
    console.println(telemetry->hdop/10., 1);

    console.print("Date/time: ");
    console.print(telemetry->year);
    console.print('-');
    console.print(int(telemetry->month));
    console.print('-');
    console.print(int(telemetry->day));
    console.print('T');
    console.print(int(telemetry->hour));
    console.print(':');
    console.print(int(telemetry->minute));
    console.print(':');
    console.println(int(telemetry->second));

    console.print("Latitude (deg): ");
    console.println((double) telemetry->latitude / 1000000., 6);

    console.print("Longitude (deg): ");
    console.println((double) telemetry->longitude / 1000000., 6);

    // long alt;
    console.print("Altitude (m): ");
//    if (nmea.getAltitude(alt))
        console.println((double) telemetry->altitude / 1000., 3);
//    else
//        console.println("not available");

    console.print("Speed: ");
    console.println((double) telemetry->speed/ 1000., 3);
//    console.print("Course: ");
//    console.println(telemetry->course / 1000., 3);
}

void printUnknownSentence(MicroNMEA& nmeaUnknown){
	console.println();
	console.print("Unknown sentence: ");
	console.println(nmeaUnknown.getSentence());
}


void gps_setup(){
	gps.begin(9600); // gps

	nmea.setUnknownSentenceHandler(printUnknownSentence);

	// // Clear the list of messages which are sent.
	// MicroNMEA::sendSentence(gps, "$PORZB");

	// // Send only RMC and GGA messages.
	// MicroNMEA::sendSentence(gps, "$PORZB,RMC,1,GGA,1");

	// // Disable compatability mode (NV08C-CSM proprietary message) and
	// // adjust precision of time and position fields
	// MicroNMEA::sendSentence(gps, "$PNVGNME,2,9,1");
	// // MicroNMEA::sendSentence(gps, "$PONME,2,4,1,0");
}