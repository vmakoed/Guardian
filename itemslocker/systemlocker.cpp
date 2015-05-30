#include "systemlocker.h"

SystemLocker::SystemLocker()
{
    this->isKeyMounted = false;
}

void SystemLocker::lock()
{
    while(true)
    {
        if(isKeyMounted == true)
        {
            emit stoplock();
            break;
        }

        LockWorkStation();

        Sleep(5000);
    }

}

bool SystemLocker::getIsKeyMounted()
{
    return isKeyMounted;
}

void SystemLocker::setIsKeyMounted(bool value)
{
    isKeyMounted = value;
}
