#include <Wire.h>
#include <MS5x.h>

#include "Telemetry.h"
#include "Barometer.h"

MS5x barometer(&Wire);

bool barometerConnected = false;

uint32_t prevConnectionAttempt = 0;
uint32_t connectionAttemptDelay = 500; // Time in ms to wait between connection attempts to the sensor
uint32_t prevTime = 0; // The time, in MS the device was last polled

double prevPressure=0; // The value of the pressure the last time the sensor was polled
double prevTemperature=0; // The value of the temperature the last time the sensor was polled
double seaLevelPressure=0;

void barometer_setup() {
	barometer.setI2Caddr(I2C_HIGH); 
	
	/* This will set oversampling ratio, acceptable values are:
	   MS5xxx_CMD_ADC_256 (Resolution RMS Temp=0.012°C/Press=0.065mbar)
	   MS5xxx_CMD_ADC_512 (Resolution RMS Temp=0.008°C/Press=0.042mbar)
	   MS5xxx_CMD_ADC_1024 (Resolution RMS Temp=0.005°C/Press=0.027mbar)
	   MS5xxx_CMD_ADC_2048 (Resolution RMS Temp=0.003°C/Press=0.018mbar)
	   MS5xxx_CMD_ADC_4096 (Resolution RMS Temp=0.002°C/Press=0.012mbar) <- Default
	*/
	barometer.setSamples(MS5xxx_CMD_ADC_2048);
	/*
	Set the time between readings.  Make sure that as you do testing with the sensor you check for
	it self heating from reading too quickly.  Once a second polls and maximum oversampling didn't create
	any observable issues when used indoors during testing, but make sure to test for yourself and adjust these
	two settings as required.
	*/
	barometer.setDelay(1000); 
  
    barometer.setPressHg();

    // Temperature and Pressure offsets will always be in degrees Celcius and Pascals regardless of what temperature and pressure units are selected
    // This is intentional based on the way temperature and pressure calculations are performed.
    barometer.setTOffset(-200); // Decreases temperature reading by 2.00°C
    barometer.setPOffset(5); // Increases pressure reading by 5 Pascals

  
    if(barometer.connect()>0) { // barometer.connect starts wire and attempts to connect to sensor
        barometerConnected = true;
    }
}

void barometer_get(struct Telemetry *telemetry) {
    double pressure = 0;
	double temperature = 0;
	
	if (!barometerConnected) {
		if (millis() - prevConnectionAttempt >= connectionAttemptDelay) {
			
			if(barometer.connect()>0) {
				prevConnectionAttempt = millis();
			} else {
				barometerConnected = true;
			}
		}
	} else {
		/* In order to not have any delays used in code, checkUpdates cycles through sensor read process
			Step 1: Ask for raw temperature calculation to be performed
			Step 2: Once enough time has passed for calculation ask sensor to send results
			Step 3: Ask for raw pressure calculation to be performed
			Step 4: Once enough time has passed for calculation ask sensor to send results
			At this point checkUpdates returns true, but no new sensor readings will be performed until Readout function is called. */
		barometer.checkUpdates();

		if (barometer.isReady()) { // Barometer has performed inital calculations and data exists for  Temperature and Pressure 	
			temperature = barometer.GetTemp(); // Returns temperature in selected units
			pressure = barometer.GetPres(); // Returns pressure in selected units
			
			// New temperature and/or pressure values exist
			if ((temperature != prevTemperature) || (pressure != prevPressure)) {
				// If Sea Level Pressure has not been calculated, do so now.
				if (seaLevelPressure == 0) seaLevelPressure = barometer.getSeaLevel(217.3);
				
                telemetry->pressure = pressure * 25.4;
                telemetry->temperatureBar = temperature;

				telemetry->altitudeBar = barometer.getAltitude();
				
				// Calculate current altitude performing temperature corrections
				telemetry->altitudeBarCorrected = barometer.getAltitude(true);
				
				prevTemperature = temperature;
				prevPressure = pressure;				
			}
		}
	}
}

void print_barometer_data(struct Telemetry *telemetry){
    Serial.print("Pressure: ");  Serial.println(telemetry->pressure);
    Serial.print("Temperature barometer: ");  Serial.println(telemetry->temperatureBar);
    Serial.print("Temperature barometer: ");  Serial.println(telemetry->temperatureBar);
}