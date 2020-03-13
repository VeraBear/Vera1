#ifndef LOCK_SYS_H
#define LOCK_SYS_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class LockSys
{
public:
    LockSys();

    void Enable(bool onOff);
    bool IsEnable();
    void OpenLock(int LockID);
    void CloseLock(int LockID);

private:
    Adafruit_PWMServoDriver pwm;

private:
    bool isEnable;
};

#endif