//#include <OneWire.h>
//#include <DallasTemperature.h>
//
//#include "Telemetry.h"
//#include "Temperature.h"
//
//// Номер пина Arduino с подключенным датчиком
//#define PIN_DS18B20 10
//
//// Создаем объект OneWire
//OneWire oneWire(PIN_DS18B20);
//
//// Создаем объект DallasTemperature для работы с сенсорами, передавая ему ссылку на объект для работы с 1-Wire.
//DallasTemperature dallasSensors(&oneWire);
//
//// Специальный объект для хранения адреса устройства
//DeviceAddress sensorAddress;
//
//void temperature_setup(){
//
//}
//
//void temperature_get(struct Telemetry *telemetry){
//    dallasSensors.requestTemperatures();
//
//    telemetry->batteryTemp = dallasSensors.getTempC(sensorAddress);
//}
//
//void print_temperature_data(struct Telemetry *telemetry){
//    Serial.print("Battery Temp C: ");
//    Serial.println(telemetry->batteryTemp);
//}
//
//// Вспомогательная функция для отображения адреса датчика ds18b20
//void printAddress(DeviceAddress deviceAddress){
//    for (uint8_t i = 0; i < 8; i++)
//    {
//        if (deviceAddress[i] < 16) Serial.print("0");
//        Serial.print(deviceAddress[i], HEX);
//    }
//}