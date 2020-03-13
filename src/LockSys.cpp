#include "LockSys.h"

#define SERVOMIN 150
#define SERVOMAX 600

LockSys::LockSys()
    :pwm()
    ,isEnable(false)

{
    Wire.begin(21, 22);
    pwm.begin();
    pwm.setPWMFreq(60);
}

void LockSys::Enable(bool onOff)
{
    isEnable = onOff;
}

bool LockSys::IsEnable()
{
    return isEnable;
}

void LockSys::OpenLock(int LockID)
{
    pwm.setPWM(LockID,0,map(30,0,180,SERVOMIN,SERVOMAX));
}

void LockSys::CloseLock(int LockID)
{
    pwm.setPWM(LockID,0,map(170,0,180,SERVOMIN,SERVOMAX));
}