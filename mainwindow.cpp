#include "mainwindow.h"

#include <QGridLayout>
#include <QDebug>
#include <QThread>

#include "database/database.h"
#include "addguardian/addguardiandialog.h"
#include "guardians/guardiansmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // since database embedding is impossible within Qt project, it is kept externally
    // insert your projects' folder path before /Guardian/
    Database::connect("C:/Users/Victor Makoed/Google Drive/Qt Creator/Guardian/guardian.db");

    setWindowFlags(Qt::FramelessWindowHint);

    items = new ItemsPresenter();
    guardians = new GuardiansPresenter();
    listBox = new QStackedWidget();

    listBox->addWidget(items);
    listBox->addWidget(guardians);
    listBox->setCurrentWidget(items);

    navigation = new Navigation();
    toolbar = new Toolbar();

    auto *rootLayout = new QGridLayout();
    rootLayout->addWidget(toolbar, 0, 0, 1, 2);
    toolbar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    rootLayout->addWidget(navigation, 1, 0);
    rootLayout->addWidget(listBox, 1, 1);
    rootLayout->setSpacing(0);
    rootLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(rootLayout);

    connect(toolbar, &Toolbar::closeClicked, this, &MainWindow::close);
    connect(toolbar, &Toolbar::deleteClicked, items, &ItemsPresenter::deleteItem);
    connect(navigation, &Navigation::typeSwitched, this, &MainWindow::setType);
    connect(navigation, &Navigation::guardiansSwitched, this, &MainWindow::setGuardians);
    connect(items, &ItemsPresenter::itemsRefreshed, navigation, &Navigation::forceCheck);
    connect(navigation, &Navigation::addGuardianClicked, this, &MainWindow::showAddGuardianDialog);

    items->refreshItems(ITEM_FILE);
    scanner = new DrivesScanner();

    QThread *thread = new QThread;
    scanner->moveToThread(thread);

    connect(thread, &QThread::started, scanner, &DrivesScanner::scan);
    connect(scanner, &DrivesScanner::drivesChanged, this, &MainWindow::setGuardians);
    connect(this, &MainWindow::destroyed, thread, &QThread::quit);

    thread->start();
}

MainWindow::~MainWindow()
{

}

void MainWindow::addItem(ITEM_TYPE type, Guardian *guardian)
{
    items->addItem(type, guardian);
    navigation->forceCheck(type);
}

void MainWindow::showAddGuardianDialog()
{
    USBInfo *info = new USBInfo;
    info->storagesCapacity = 0;
    getUSBInfo(info);

    QString *driveLetters = new QString;
    QStringList *productNames = new QStringList;

    for(int i = 0; i < info->storagesCapacity; i++)
    {
        driveLetters->append(info->driveLetters[i]);
        productNames->append(info->productNames[i]);
    }

    AddGuardianDialog *addGuardianDialog = new AddGuardianDialog(this, driveLetters, productNames);
    connect(addGuardianDialog, &AddGuardianDialog::guardianInfoAcquired, this, &MainWindow::addGuardian);
    addGuardianDialog->show();
}

void MainWindow::addGuardian(QString drive, QString name)
{
    guardians->addGuardian(drive, name);
}

void MainWindow::closeEvent(QCloseEvent *)
{
    Database::disconnect();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    clickX = event->x();
    clickY = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX() - clickX, event->globalY() - clickY);
}

void MainWindow::setType(ITEM_TYPE type)
{
    items->refreshItems(type);
    listBox->setCurrentWidget(items);
}


void MainWindow::setGuardians()
{
    guardians->refreshGuardians();
    if(listBox->currentWidget() != guardians)
    {
        listBox->setCurrentWidget(guardians);
    }
}
