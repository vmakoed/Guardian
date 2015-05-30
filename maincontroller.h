#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QSystemTrayIcon>
#include <QMenu>

#include "item.h"
#include "guardian.h"
#include "database/datamanager.h"
#include "gui/mainwindow.h"
#include "gui/addguardiandialog.h"
#include "gui/additemdialog.h"
#include "drivesscanner/drivesscanner.h"
#include "fileencryption/fileencryption.h"
#include "itemslocker/itemslocker.h"
#include "itemslocker/systemlocker.h"

class MainController : public QObject
{
    Q_OBJECT

private:
    MainWindow *mainWindow;
    AddItemDialog *addItemDialog;
    AddGuardianDialog *addGuardianDialog;

    DrivesScanner *drivesScanner;
    QThread *scanThread;

    QThread *systemLockThread;
    SystemLocker *systemLocker;

    QSystemTrayIcon *trayIcon;

public:
    explicit MainController(QObject *parent = 0);

    void launch();

    void lockAll();

    void createSystemLocker();

    void setItems();
    void setGuardians();

    void driveMounted(char drive);
    void driveUnmounted(char drive);

    void createGuardian(QString drive, QString name);
    void createSystemKey(QString guardianName);

    void addItem(QString category, QString path, QString guardianName);
    void addGuardian(QString drive, QString name);

    void deleteGuardian();
    void deleteItem();

    void showAddGuardianDialog();
    void showAddItemDialog();

    void resetAddGuardianDialog();
    void resetAddItemDialog();

    void deleteAddGuardianDialog();
    void deleteAddItemDialog();

    void systemKeyMounted();
    void sytemKeyUnmounted();

    void enableProtection(Item *item);
    void disableProtection(Item *item);


signals:
    void lockSystemRequest();
    void unlockSystemRequest();

public slots:
    void switchListbox(QAbstractButton *button);
    void setProtection(Item *item);
    void close();

};

#endif // MAINCONTROLLER_H
