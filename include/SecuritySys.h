#ifndef SECURITY_SYS_H
#define SECURITY_SYS_H

#include <Arduino.h>
#include <EEPROM.h>
#include <SPI.h>
#include <MFRC522.h>

class SecuritySys
{
public:
    SecuritySys();
    
    void Enable(bool onOff);
    bool IsEnable();
    bool IsRFIDchecked();

private:
    MFRC522 mfrc522;

private:
    bool isEnable;
    bool isRFIDchecked;
};

#endif