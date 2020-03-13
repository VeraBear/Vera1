#ifndef SECURITY_SYS_H
#define SECURITY_SYS_H

#include <Arduino.h>
#include <EEPROM.h>     // We are going to read and write PICC's UIDs from/to EEPROM
#include <SPI.h>        // RC522 Module uses SPI protocol
#include <MFRC522.h>  // Library for Mifare RC522 Devices

class SecuritySys
{
public:
    SecuritySys();

    void Enable(bool onOff);
    bool IsEnable();

    bool IsRFIDchecked();

    bool RegisterCard();

private:
    MFRC522 mfrc522;
private:
    bool isEnable;
    bool isRFIDchecked;
};

#endif
