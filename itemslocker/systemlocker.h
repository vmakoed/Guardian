#ifndef SYSTEMLOCKER_H
#define SYSTEMLOCKER_H

#include <QObject>

#include "Windows.h"
#pragma comment(lib, "user32.lib")

class SystemLocker : public QObject
{
    Q_OBJECT

private:
    bool isKeyMounted;

public:
   SystemLocker();

   void lock();

   bool getIsKeyMounted();
   void setIsKeyMounted(bool value);

signals:
   void stoplock();

};

#endif // SYSTEMLOCKER_H
