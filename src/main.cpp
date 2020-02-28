#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ClimatSys.h>

const char* ssid = "Boteon MikroTik";
const char* password = "Boteon12345";

const char* BotToken = "1014315876:AAEjnmSC1MszGdi04V8VFwoMXEgVbdPjkVA";

ClimatSys climatSys(2);
WiFiClientSecure net_ssl;
UniversalTelegramBot bot(BotToken, net_ssl);

void setup() 
{
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println(".");
  }
  Serial.println("WiFi con");
  climatSys.SetWEBapiKey("cc01853162e4684150d5bea65ca0bbfa");
  climatSys.SetCityToMonitor("Chernivtsi,UA");
  
}

void loop()
{
  if(bot.getUpdates(bot.last_message_received + 1))
  {
    String chat_id = String(bot.messages[0].chat_id);
    String text = bot.messages[0].text;
    Serial.println(text);

    if (text == "/getht")
    {
      String temp(climatSys.GetHouseTempCelcium());
      String humidity(climatSys.GetHouseHumidity());
      String msg = "temp: " + temp + "humidity: " + humidity;
      bot.sendMessage(chat_id,msg);
    }
    else if (text == "/getct")
    {
      climatSys.UpdateDataFromWEB();
      String temp(climatSys.GetTempInCity());
      String humidity(climatSys.GetHumidityInCity());
      String msg = "temp: " + temp + "humidity: " + humidity;
      bot.sendMessage(chat_id,msg);
    }
  }
}