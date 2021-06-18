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
    
    telemetry->latitude = (float) nmea.getLatitude() / 1000000.;
    telemetry->longitude = (float) nmea.getLongitude() / 1000000.;

    telemetry->speed = nmea.getSpeed() / 1000.;

    long alt;

		if (nmea.getAltitude(alt))
      telemetry->altitude = alt / 1000.;
		else
			telemetry->altitude = 0;



    

    telemetry->second = nmea.getSecond();
    telemetry->minute = nmea.getMinute();
    telemetry->hour = nmea.getHour();
    telemetry->day = nmea.getDay();
    telemetry->month = nmea.getMonth();

    telemetry->year = nmea.getYear();

		// Output GPS information from previous second
		console.print("Valid fix: ");
		console.println(nmea.isValid() ? "yes" : "no");

		console.print("Nav. system: ");
		if (nmea.getNavSystem())
			console.println(nmea.getNavSystem());
		else
			console.println("none");

		console.print("Num. satellites: ");
		console.println(nmea.getNumSatellites());

		console.print("HDOP: ");
		console.println(nmea.getHDOP()/10., 1);

		console.print("Date/time: ");
		console.print(nmea.getYear());
		console.print('-');
		console.print(int(nmea.getMonth()));
		console.print('-');
		console.print(int(nmea.getDay()));
		console.print('T');
		console.print(int(nmea.getHour()));
		console.print(':');
		console.print(int(nmea.getMinute()));
		console.print(':');
		console.println(int(nmea.getSecond()));

		long latitude_mdeg = nmea.getLatitude();
		long longitude_mdeg = nmea.getLongitude();
		console.print("Latitude (deg): ");
		console.println(latitude_mdeg / 1000000., 6);

		console.print("Longitude (deg): ");
		console.println(longitude_mdeg / 1000000., 6);

		// long alt;
		console.print("Altitude (m): ");
		if (nmea.getAltitude(alt))
			console.println(alt / 1000., 3);
		else
			console.println("not available");

		console.print("Speed: ");
		console.println(nmea.getSpeed() / 1000., 3);
		console.print("Course: ");
		console.println(nmea.getCourse() / 1000., 3);
  }
}


void printUnknownSentence(MicroNMEA& nmea){
	console.println();
	console.print("Unknown sentence: ");
	console.println(nmea.getSentence());
}


void gps_setup(void){
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