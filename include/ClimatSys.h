#ifndef CLIMAT_SYS_H
#define CLIMAT_SYS_H

#include <Arduino.h>
#include <DHT.h>

class ClimatSys
{
public:
    ClimatSys(int pin);
    float GetHouseHumidity();
    float GetHouseTempCelcium();
    float GetHouseTempFahrenheit();

    void SetWEBapiKey(String key);
    void SetCityToMonitor(String cityName);
    float GetTempInCity();
    float GetHumidityInCity();
    void UpdateDataFromWEB();
private:
    DHT sensor;

private:
    String apiKey;
    String nameOfCity;
private:
    float tempInCity = -300;
    float humidityInCity = -300;

};

#endif