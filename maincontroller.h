#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QThread>
#include <QDir>
#include <QSystemTrayIcon>
#include <QMessageBox>

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
    void launchGUI();

    void lockAll();

    void createSystemLocker();

    void setItems();
    void setGuardians();

    void drivesMounted(char *alteredDrives, int alteredDrivesCapacity);
    void drivesUnmounted(char *alteredDrives, int alteredDrivesCapacity);

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

    void showErrorMessageBox(QString text);

signals:
    void lockSystemRequest();
    void unlockSystemRequest();

    void itemAdded(ITEM_TYPE);
    void guardianAdded(Guardian*);

    void selectedItemDeleted();
    void selectedGuardianDeleted();

    void guardianStateChanged(QString*, GUARDIAN_STATE, char);

public slots:
    void switchListbox(QAbstractButton *button);
    void setProtection(Item *item);
    void close();

    void enableProtection(Item *item);
    void disableProtection(Item *item);

    void setDelete(Guardian *guardian);
    void setDelete(Item *item);

    void trayIconAction(QSystemTrayIcon::ActivationReason reason);
};

#endif // MAINCONTROLLER_H
