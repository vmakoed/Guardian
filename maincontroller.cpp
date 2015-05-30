#include "maincontroller.h"
#include <QDebug>

MainController::MainController(QObject *parent) : QObject(parent)
{
    mainWindow = new MainWindow;
    drivesScanner = new DrivesScanner;

    addGuardianDialog = nullptr;
    addItemDialog = nullptr;

    connect(mainWindow, &MainWindow::addGuardianClicked, this, &MainController::showAddGuardianDialog);
    connect(mainWindow, &MainWindow::addItemClicked, this, &MainController::showAddItemDialog);

    connect(mainWindow, &MainWindow::deleteGuardianClicked, this, &MainController::deleteGuardian);
    connect(mainWindow, &MainWindow::deleteItemClicked, this, &MainController::deleteItem);

    connect(mainWindow, &MainWindow::navigationSwitched, this, &MainController::switchListbox);
    connect(mainWindow, &MainWindow::closeClicked, this, &MainController::close);

    connect(mainWindow, &MainWindow::itemSelected, this, &MainController::setProtection);

    connect(drivesScanner, &DrivesScanner::driveMounted, this, &MainController::driveMounted);
    connect(drivesScanner, &DrivesScanner::driveUnmounted, this, &MainController::driveUnmounted);

    connect(mainWindow, &MainWindow::itemProtectionEnabled, this, &MainController::enableProtection);
    connect(mainWindow, &MainWindow::itemProtectionDisabled, this, &MainController::disableProtection);
}

void MainController::launch()
{
    QPixmap *p = new QPixmap(":/img/guardianIcon.png");
    trayIcon = new QSystemTrayIcon(*p, this);
    trayIcon->show();

    DataManager::connect("C:/Users/Victor Makoed/Google Drive/Qt Creator/GuardianModules/guardian.db");
    setGuardians();

    lockAll();

    if(DataManager::doesSystemKeyExist())
    {
        createSystemLocker();
    }

    char *drives = new char[MAX_NUM_OF_DRIVES];

    drivesScanner->scan(drives);

    for(int i = 0; i < strlen(drives); i++)
    {
        driveMounted(drives[i]);
    }

    if(DataManager::doesSystemKeyExist() == true && DataManager::isSystemKeyMounted() == false
            && DataManager::isSystemProtected() == true)
    {
        emit lockSystemRequest();

        DataManager::setSystemUnlocked(false);
    }

    scanThread = new QThread;
    drivesScanner->moveToThread(scanThread);

    connect(scanThread, &QThread::started, drivesScanner, &DrivesScanner::startScan);
    scanThread->start();

    mainWindow->switchtoGuardians();
    mainWindow->show();
}

void MainController::lockAll()
{
    QList<Item*> *itemsList = new QList<Item*>;

    itemsList = DataManager::getItems();
    ItemsLocker::alterAccess(itemsList, LOCKED);
    DataManager::unmountAll();
    DataManager::setItemsState(itemsList, LOCKED);
    mainWindow->setItemsState(itemsList, LOCKED);
}

void MainController::createSystemLocker()
{
    systemLocker = new SystemLocker;
    systemLockThread = new QThread;

    systemLocker->moveToThread(systemLockThread);

    connect(systemLockThread, &QThread::started, systemLocker, &SystemLocker::lock);
    connect(systemLocker, &SystemLocker::stoplock, systemLockThread, &QThread::quit);

    connect(this, SIGNAL(lockSystemRequest()), systemLockThread, SLOT(start()));
    connect(this, SIGNAL(unlockSystemRequest()), systemLockThread, SLOT(quit()));
}

void MainController::setItems()
{
    mainWindow->setItems(DataManager::getItems());
}

void MainController::setGuardians()
{
    mainWindow->setGuardians(DataManager::getGuardians());
}

void MainController::driveMounted(char drive)
{
    QString *guardianName = new QString;
    guardianName = FileEncryption::defineGuardian(drive);

    if(guardianName == nullptr)
    {
        //NOTAGUARDIAN

        resetAddGuardianDialog();
    }
    else
    {
        QString *encryptedKey = new QString;
        encryptedKey = DataManager::getEncryptedKey(*guardianName);

        if(FileEncryption::authentificate(drive, *encryptedKey))
        {
            mainWindow->setGuardianState(guardianName, MOUNTED, drive);

            DataManager::setGuardianState(guardianName, MOUNTED, drive);

            QList<Item*> *items = new QList<Item*>;

            items = DataManager::getItems(*guardianName);

            ItemsLocker::alterAccess(items, UNLOCKED);
            DataManager::setItemsState(items, UNLOCKED);

            items->append(DataManager::getSystemItem());

            if(DataManager::isSystemKey(*guardianName) == true)
            {
                if(DataManager::isSystemUnlocked() == false && DataManager::isSystemProtected() == true)
                {
                    systemLocker->setIsKeyMounted(true);
                    emit unlockSystemRequest();

                    DataManager::setSystemUnlocked(true);
                }
            }
        }

        mainWindow->clearSelection();

        resetAddItemDialog();
    }
}

void MainController::driveUnmounted(char drive)
{
    QString *guardianName = new QString;
    guardianName = DataManager::getGuardianName(drive);

    if(guardianName == nullptr)
    {
        //NOTAGUARDIAN
    }
    else
    {
        mainWindow->setGuardianState(guardianName, UNMOUNTED, drive);

        DataManager::setGuardianState(guardianName, UNMOUNTED, drive);

        QList<Item*> *items = new QList<Item*>;

        items = DataManager::getItems(*guardianName);

        items->append(DataManager::getSystemItem());

        for(Item *item : *items)
        {
            if(item->getIsProtected() == false)
            {
                items->removeOne(item);
            }
        }

        ItemsLocker::alterAccess(items, LOCKED);
        DataManager::setItemsState(items, LOCKED);

        mainWindow->clearSelection();

        if(DataManager::isSystemKey(*guardianName) == true)
        {
            if(DataManager::isSystemUnlocked() == true && DataManager::isSystemProtected() == true)
            {
                systemLocker->setIsKeyMounted(false);
                emit lockSystemRequest();

                DataManager::setSystemUnlocked(false);
            }
        }
    }
}

void MainController::enableProtection(Item *item)
{
    item->setIsProtected(true);

    if(item->getType() == ITEM_APP)
    {
        DataManager::setSystemProtected(true);

        if(DataManager::isSystemKeyMounted() == false)
        {
            systemLocker->setIsKeyMounted(false);
            emit lockSystemRequest();
            DataManager::setSystemUnlocked(false);
        }
    }
    else
    {
        DataManager::setItemProtected(item->getPath(), true);

        if(DataManager::isGuardianMounted(item->getGuardianName()) == false)
        {
            ItemsLocker::alterAccess(item, LOCKED);
        }
    }
}

void MainController::disableProtection(Item *item)
{
    item->setIsProtected(false);

    if(item->getType() == ITEM_APP)
    {
        DataManager::setSystemProtected(false);
    }
    else
    {
        DataManager::setItemProtected(item->getPath(), false);
    }
}

void MainController::showAddGuardianDialog()
{    
    char *drives = new char[MAX_NUM_OF_DRIVES];
    drivesScanner->scan(drives);

    QStringList *validDrives = new QStringList;
    QStringList *driveNames = new QStringList;

    for(int i = 0, j = 0; i < strlen(drives); i++)
    {
        if(DataManager::getGuardianName(drives[i]) == nullptr)
        {
            validDrives->append(*(new QString(drives[i])));
            driveNames->append(*(drivesScanner->getStorageName(drives[i])));

            j++;
        }
    }

    addGuardianDialog = new AddGuardianDialog(validDrives, driveNames);

    connect(addGuardianDialog, &AddGuardianDialog::guardianInfoAcquired, this, &MainController::addGuardian);
    connect(addGuardianDialog, &AddGuardianDialog::closed, this, &MainController::deleteAddGuardianDialog);

    addGuardianDialog->show();
}

void MainController::showAddItemDialog()
{
    QList<Guardian *> *guardiansList = DataManager::getGuardians(MOUNTED);

    addItemDialog = new AddItemDialog(guardiansList);

    if(DataManager::doesSystemKeyExist() == false)
    {
        addItemDialog->enableSystemCategory();
    }

    connect(addItemDialog, &AddItemDialog::itemInfoAcquired, this, &MainController::addItem);
    connect(addItemDialog, &AddItemDialog::systemKeyRequested, this, &MainController::createSystemKey);
    connect(addItemDialog, &AddItemDialog::closed, this, &MainController::deleteAddItemDialog);

    addItemDialog->show();
}

void MainController::resetAddGuardianDialog()
{
    if(addGuardianDialog != nullptr)
    {
        addGuardianDialog->close();

        showAddGuardianDialog();
    }
}

void MainController::resetAddItemDialog()
{
    if(addItemDialog != nullptr)
    {
        addItemDialog->close();

        showAddItemDialog();
    }
}

void MainController::deleteAddGuardianDialog()
{
    delete[] addGuardianDialog;
    addGuardianDialog = nullptr;
}

void MainController::deleteAddItemDialog()
{
    delete[] addItemDialog;
    addItemDialog = nullptr;
}

void MainController::addGuardian(QString drive, QString name)
{
    Guardian *guardian = new Guardian(name, MOUNTED, *(drive.toStdString().c_str()));

    CryptObject *cryptObject = new CryptObject;
    FileEncryption::newCryptObject(cryptObject);

    FileEncryption::writeCryptInfo(guardian->getDrive(), guardian->getName(), cryptObject->key, cryptObject->inHex);
    DataManager::addGuardian(guardian->getName(), *(new QString(cryptObject->outHex)), guardian->getDrive());

    mainWindow->addGuardian(guardian);
}

void MainController::createSystemKey(QString guardianName)
{
    DataManager::createSystemKey(guardianName);

    createSystemLocker();

    mainWindow->toggleItemSwitch(ITEM_APP);
}

void MainController::addItem(QString category, QString path, QString guardianName)
{
    if(category == "system")
    {
        createSystemLocker();

        return;
    }

    if(DataManager::isPathReserved(path) == true)
    {
        // FILE IS ALREADY PROTECTED

        return;
    }

    ITEM_TYPE type;

    if(category == "file")
    {
        type = ITEM_FILE;
    }
    else if(category == "folder")
    {
        type = ITEM_FOLDER;
    }

    int index;
    for(index = path.length() - 1; path.at(index) != '/'; index--);

    QString name;
    index++;
    while(index < path.length())
    {
        name.append(path.at(index));

        index++;
    }

    Item *item = new Item(name, path, type, UNLOCKED, true, guardianName);

    ItemsLocker::alterAccess(item, UNLOCKED);
    DataManager::addItem(name, path, type, UNLOCKED, true, guardianName);

    mainWindow->toggleItemSwitch(type);
}

void MainController::deleteGuardian()
{
    Guardian *guardian = mainWindow->acquireGuardianToDelete();

    if(guardian->getState() == UNMOUNTED)
    {
        // ERROR: GUARDIAN NOT MOUNTED
        return;
    }

    ItemsLocker::alterAccess(DataManager::getItems(guardian->getName()), UNLOCKED);
    FileManager::deleteFile(guardian->getDrive(), "pass.guardian");
    DataManager::deleteItems(guardian->getName());
    DataManager::deleteGuardian(guardian->getName());

    mainWindow->deleteSelectedGuardian();
}

void MainController::deleteItem()
{
    Item *item = mainWindow->acquireItemToDelete();

    if(item->getItemGuardianState() == LOCKED)
    {
        //ERROR: GUARDIAN NOT MOUNTED
        return;
    }

    if(item->getType() == ITEM_APP)
    {
        systemLockThread->exit(0);
        systemLockThread->wait();
        systemLockThread->deleteLater();

       // delete[] systemLockThread;
        delete[] systemLocker;

        DataManager::deleteSystemKey();
    }
    else
    {
        ItemsLocker::alterAccess(item, UNLOCKED);
        DataManager::deleteItem(item->getPath());
    }

    mainWindow->deleteSelectedItem();
}

void MainController::switchListbox(QAbstractButton *button)
{
    if(button->text() == "Guardians")
    {
        mainWindow->switchtoGuardians();
    }
    else
    {
        if(button->text() == "Files")
        {
            mainWindow->setItems(DataManager::getItems(ITEM_FILE));
        }
        else if(button->text() == "Folders")
        {
            mainWindow->setItems(DataManager::getItems(ITEM_FOLDER));
        }
        else if(button->text() == "System")
        {
            mainWindow->clearItems();
            if(DataManager::doesSystemKeyExist() == true)
            {
                mainWindow->addItem(DataManager::getSystemItem());
            }
        }

        mainWindow->switchtoItems();
    }
}

void MainController::setProtection(Item *item)
{
    if(item == nullptr)
    {
        mainWindow->setLockButton(true);
        mainWindow->enableLockButton(false);
    }
    else
    {
        mainWindow->setLockButton(item->getIsProtected());
        mainWindow->enableLockButton(DataManager::isGuardianMounted(item->getGuardianName()));
    }
}

void MainController::close()
{
    mainWindow->close();
    trayIcon->hide();
    DataManager::unmountAll();
    lockAll();

    exit(0);
}
