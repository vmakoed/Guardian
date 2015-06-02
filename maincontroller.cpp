#include "maincontroller.h"

MainController::MainController(QObject *parent) : QObject(parent)
{
    drivesScanner = new DrivesScanner;
    mainWindow = nullptr;
    addGuardianDialog = nullptr;
    addItemDialog = nullptr;

    connect(drivesScanner, &DrivesScanner::drivesMounted, this, &MainController::drivesMounted);
    connect(drivesScanner, &DrivesScanner::drivesUnmounted, this, &MainController::drivesUnmounted);
}

void MainController::launchGUI()
{
    if(mainWindow != nullptr)
    {
        return;
    }

    mainWindow = new MainWindow;

    connect(mainWindow, &MainWindow::addGuardianClicked, this, &MainController::showAddGuardianDialog);
    connect(mainWindow, &MainWindow::addItemClicked, this, &MainController::showAddItemDialog);

    connect(mainWindow, &MainWindow::deleteGuardianClicked, this, &MainController::deleteGuardian);
    connect(mainWindow, &MainWindow::deleteItemClicked, this, &MainController::deleteItem);

    connect(mainWindow, &MainWindow::navigationSwitched, this, &MainController::switchListbox);
    connect(mainWindow, &MainWindow::closeClicked, this, &MainController::close);

    connect(mainWindow, &MainWindow::itemSelected, this, &MainController::setProtection);

    connect(mainWindow, SIGNAL(itemSelected(Item*)), this, SLOT(setDelete(Item*)));
    connect(mainWindow, SIGNAL(guardianSelected(Guardian*)), this, SLOT(setDelete(Guardian*)));

    connect(mainWindow, &MainWindow::itemProtectionEnabled, this, &MainController::enableProtection);
    connect(mainWindow, &MainWindow::itemProtectionDisabled, this, &MainController::disableProtection);

    connect(this, &MainController::guardianStateChanged, mainWindow, &MainWindow::setGuardianState);

    connect(this, &MainController::guardianAdded, mainWindow, &MainWindow::addGuardian);
    connect(this, &MainController::itemAdded, mainWindow, &MainWindow::toggleItemSwitch);

    connect(this, &MainController::selectedGuardianDeleted, mainWindow, &MainWindow::deleteSelectedGuardian);
    connect(this, &MainController::selectedItemDeleted, mainWindow, &MainWindow::deleteSelectedItem);

    setGuardians();
    mainWindow->switchtoGuardians();

    mainWindow->show();
}

void MainController::launch()
{
    QPixmap *p = new QPixmap(":/img/guardianIcon.png");
    trayIcon = new QSystemTrayIcon(*p, this);
    trayIcon->show();
    trayIcon->showMessage("Guardian", "Guardian application started", QSystemTrayIcon::Information);

    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainController::trayIconAction);

    DataManager::connect(QDir::currentPath() + "/guardian.db");

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
}

void MainController::lockAll()
{
    QList<Item*> *itemsList = new QList<Item*>;

    itemsList = DataManager::getItems();
    ItemsLocker::alterAccess(itemsList, LOCKED);
    DataManager::unmountAll();
    DataManager::setItemsState(itemsList, LOCKED);
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

void MainController::drivesMounted(char *alteredDrives, int alteredDrivesCapacity)
{
    while(alteredDrivesCapacity > 0)
    {
        driveMounted(alteredDrives[alteredDrivesCapacity - 1]);

        alteredDrivesCapacity--;
    }
}

void MainController::drivesUnmounted(char *alteredDrives, int alteredDrivesCapacity)
{
    while(alteredDrivesCapacity > 0)
    {
        driveUnmounted(alteredDrives[alteredDrivesCapacity - 1]);

        alteredDrivesCapacity--;
    }
}

void MainController::driveMounted(char drive)
{
    QString *guardianName = FileEncryption::defineGuardian(drive);

    if(guardianName == nullptr)
    {
        resetAddGuardianDialog();
    }
    else
    {                                                                     
        QString *encryptedKey = new QString;
        encryptedKey = DataManager::getEncryptedKey(*guardianName);

        if(FileEncryption::authentificate(drive, *encryptedKey))
        {
            trayIcon->showMessage(*guardianName + " mounted", "Unlocking protected items");

            emit guardianStateChanged(guardianName, MOUNTED, drive);

            DataManager::setGuardianState(guardianName, MOUNTED, drive);

            QList<Item*> *items = new QList<Item*>;

            items = DataManager::getItems(*guardianName);

            ItemsLocker::alterAccess(items, UNLOCKED);
            DataManager::setItemsState(items, UNLOCKED);

            if(DataManager::isSystemKey(*guardianName) == true)
            {
                systemLocker->setIsKeyMounted(true);
                DataManager::setSystemUnlocked(true);

                if(DataManager::isSystemProtected() == true)
                {
                    emit unlockSystemRequest();
                }
            }
        }

        resetAddItemDialog();
    }
}

void MainController::driveUnmounted(char drive)
{
    QString *guardianName = new QString;
    guardianName = DataManager::getGuardianName(drive);

    if(guardianName == nullptr)
    {
        resetAddGuardianDialog();
    }
    else
    {
        emit guardianStateChanged(guardianName, UNMOUNTED, drive);

        trayIcon->showMessage(*guardianName + " unmounted", "Locking protected items");

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

        if(DataManager::isSystemKey(*guardianName) == true)
        {
            systemLocker->setIsKeyMounted(false);
            DataManager::setSystemUnlocked(false);

            if(DataManager::isSystemProtected() == true)
            {
                emit lockSystemRequest();
            }
        }
    }
}

void MainController::enableProtection(Item *item)
{
    item->setIsProtected(true);

    if(item->getType() == ITEM_SYSTEM)
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

    if(item->getType() == ITEM_SYSTEM)
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

    emit guardianAdded(guardian);
}

void MainController::createSystemKey(QString guardianName)
{
    DataManager::createSystemKey(guardianName);

    createSystemLocker();

    emit itemAdded(ITEM_SYSTEM);
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
        showErrorMessageBox("The item is already protected");

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

    emit itemAdded(type);
}

void MainController::deleteGuardian()
{
    Guardian *guardian = mainWindow->acquireGuardianToDelete();

    ItemsLocker::alterAccess(DataManager::getItems(guardian->getName()), UNLOCKED);
    FileManager::deleteFile(guardian->getDrive(), "pass.guardian");
    DataManager::deleteItems(guardian->getName());
    DataManager::deleteGuardian(guardian->getName());

    emit selectedGuardianDeleted();

}

void MainController::deleteItem()
{
    Item *item = mainWindow->acquireItemToDelete();

    if(item->getType() == ITEM_SYSTEM)
    {
        systemLockThread->exit(0);
        systemLockThread->wait();
        systemLockThread->deleteLater();

        delete[] systemLocker;

        DataManager::deleteSystemKey();
    }
    else
    {
        ItemsLocker::alterAccess(item, UNLOCKED);
        DataManager::deleteItem(item->getPath());
    }

    emit selectedItemDeleted();
}

void MainController::switchListbox(QAbstractButton *button)
{
    mainWindow->clearSelection();

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

void MainController::setDelete(Guardian *guardian)
{
    if(guardian == nullptr)
    {
        mainWindow->enableDeleteButton(false);
    }
    else if(guardian->getState() == UNMOUNTED)
    {
        mainWindow->enableDeleteButton(false);
    }
    else
    {
        mainWindow->enableDeleteButton(true);
    }
}

void MainController::setDelete(Item *item)
{
    if(item == nullptr)
    {
        mainWindow->enableDeleteButton(false);
    }
    else if(item->getItemGuardianState() == LOCKED)
    {
        mainWindow->enableDeleteButton(false);
    }
    else
    {
        mainWindow->enableDeleteButton(true);
    }
}

void MainController::close()
{
    mainWindow->hide();
    delete[] mainWindow;

    mainWindow= nullptr;

    trayIcon->showMessage("Running in background", "Guardian is keeping your data secured");
}

void MainController::trayIconAction(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger)
    {
        launchGUI();
    }
    else if(reason == QSystemTrayIcon::Context)
    {
        trayIcon->setVisible(false);
        exit(0);
    }
}

void MainController::showErrorMessageBox(QString text)
{
    QMessageBox msgBox;
    msgBox.setWindowFlags(Qt::FramelessWindowHint);
    msgBox.setText(text);
    msgBox.exec();
}
