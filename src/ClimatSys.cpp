#include "ClimatSys.h"
#include <ArduinoJSON.h>
#include <WiFiClientSecure.h>

static WiFiClient client;

ClimatSys::ClimatSys(int pin)
{
    sensor.setup(pin);
}

float ClimatSys::GetHouseHumidity()
{
    return sensor.getHumidity();
}

float ClimatSys:: GetHouseTempCelcium()
{
    return sensor.getTemperature();
}
float ClimatSys:: GetHouseTempFahrenheit()
{
    return sensor.toFahrenheit(sensor.getTemperature());
}

void ClimatSys::SetWEBapiKey(String key)
{
    apiKey = key;
}

void ClimatSys::SetCityToMonitor(String cityName)
{
    nameOfCity = cityName;
}

float ClimatSys::GetTempInCity()
{
    return tempInCity;
}

float ClimatSys::GetHumidityInCity()
{
    return humidityInCity;
}

void ClimatSys::UpdateDataFromWEB()
{
    const char server[] = "api.openweathermap.org";
    DynamicJsonBuffer jsonBuffer;
    if(client.connect(server, 80))
    {
        #ifdef DEBUG
        Serial.println("Connected");
        #endif
        client.println("GET /data/2.5/forecast?q=" + nameOfCity + "&APPID=" + apiKey + "&mode= json&units=metric&cnt=2 HTTP/1.1");
        client.println("Host: api.openwathermap.org");
        client.println("User-Agent: ArduinoWiFi/1.1");
        client.println("Connection: close");
        client.println();
        delay(500);
    }
    while(client.available())
    {
        String line = client.readStringUntil('\r');
        JsonObject& root = jsonBuffer.parseObject(line);
        if (root.success())
        {
            JsonArray& list = root["list"];
            JsonObject& nowT = list[0];

            tempInCity = nowT["main"]["temp"];
            humidityInCity = nowT["main"]["humidity"];
        }
        
    }
    #ifdef DEBUG
    Serial.println("closing connection");
    Serial.println();
    #endif
    client.stop();
}