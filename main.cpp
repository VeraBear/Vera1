#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday","Wednesday", "Thursday", "Friday", "Saturday"};
const char* ssid = "Boteon MikroTik";
const char* password = "Boteon12345";
const char* BotToken = "1014315876:AAEjnmSC1MszGdi04V8VFwoMXEgVbdPjkVA";

WiFiClientSecure net_ssl;
UniversalTelegramBot bot(BotToken, net_ssl);

int alarmHour = 0;
int alarmMin = 0;
bool alarmIsSet = false;
const String alarmCmd = "/alarm";
const int Buz = 23;

bool FindAlarmCmd(String input)
{
    bool res = false;
    char buf[7];
    input.toCharArray(buf, 7);
    Serial.print("Parse command: ");
    Serial.println(buf);
    if (alarmCmd == buf) res = true;
    else res = false;

    char timeBuf[6];
    input.toCharArray(buf, 7);
    Serial.print("Parse time: ");
    Serial.println(timeBuf);
    if (res)
    {
        String hour;
        if(timeBuf[0] != '0')
           hour +=timeBuf[0];
        hour +=timeBuf[1];
        alarmHour = hour.toInt();

        String min;
        if(timeBuf[3] != '0')
           hour +=timeBuf[3];
        hour +=timeBuf[4];
        alarmHour = hour.toInt();
    }

}

void setup()
{
   pinMode(Buz, OUTPUT);
   Serial.begin(115200);
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   while(WiFi.status() != WL_CONNECTED)
   {
       delay(1000);
       Serial.print(".");
   }
   Serial.println("WiFi con");
   if(!rtc.isrunning())
   {
       Serial.println("RTC is NOT running");
       rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
   }
}


void loop()
{
   if (bot.getUpdates(bot.last_message_received + 1))
   {
       String chat_id = String(bot.messages[0].chat_id);
       String text = bot.messages[0].text;
       alarmIsSet = FindAlarmCmd("/alarm 04:45");
       if(alarmIsSet)
       {
           Serial.println("alarm is setted");
           bot.sendMessage(chat_id, "alarm setted");

       }
   }
   DateTime now = rtc.now();
   Serial.print(now.year(), DEC);
   Serial.print('/');
   Serial.print(now.month(), DEC);
   Serial.print('/');
   Serial.print(now.day(), DEC);
   Serial.print('(');
   Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
   Serial.print(')');
   Serial.print(now.hour(), DEC);
   Serial.print(':');
   Serial.print(now.minute(), DEC);

    if(alarmIsSet)
    {
        if(now.hour() == alarmHour && now.minute() == alarmMin)
        {
            Serial.println("ALARM");
            digitalWrite(Buz,HIGH);

        }
    }
}