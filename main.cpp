#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#include "SecuritySys.h"

const char* ssid = "Boteon MikroTik";
const char* password = "Boteon12345";

const char* BotToken = "1014315876:AAEjnmSC1MszGdi04V8VFwoMXEgVbdPjkVA";

SecuritySys secSys;
String chat_id;

WiFiClientSecure net_ssl;
UniversalTelegramBot bot(BotToken, net_ssl);

void setup() 
{
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println(".");
  }
  Serial.println("WiFi con");
}

void loop() 
{
  if(bot.getUpdates(bot.last_message_received + 1))
  {
    chat_id = String(bot.messages[0].chat_id);
    String text = bot.messages[0].text;
    Serial.println(text);
    if(text == "/enable_secure")
    {
      secSys.Enable(true);
      bot.sendMessage(chat_id, "Security system is enabled:");
    }
    if(secSys.IsEnable() && secSys.IsRFIDchecked())
      bot.sendMessage(chat_id, "checked");
  }
}