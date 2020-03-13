#include "SecuritySys.h"

const int RST_PIN = 14; // Reset pin
const int NSS_PIN = 12; // Slave select pin

const int MISO_PIN = 19; //
const int MOSI_PIN = 23; //
const int SCK_PIN = 18; //
// IRQ - not connected

SecuritySys::SecuritySys()
    : mfrc522(NSS_PIN, RST_PIN)
    , isEnable(false)
    , isRFIDchecked(false)
{
    SPI.begin(); // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522
    mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
    Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void SecuritySys::Enable(bool onOff)
{
    isEnable = onOff;
}

bool SecuritySys::IsEnable()
{
    return isEnable;
}

bool SecuritySys::IsRFIDchecked()
{
    if (!mfrc522.PICC_IsNewCardPresent())
        isRFIDchecked = true;
    if (!mfrc522.PICC_ReadCardSerial())
        isRFIDchecked = true;
        
    return isRFIDchecked;
}

bool SecuritySys::RegisterCard()
{
    return true;
}