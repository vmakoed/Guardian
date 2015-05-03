#include "mainwindow.h"

#include <QGridLayout>

#include "database/database.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // since database embedding is impossible within Qt project, it is kept externally
    // insert your projects' folder path before /Guardian/
    Database::connect("C:/Users/Victor Makoed/Google Drive/Qt Creator/Guardian/guardian.db");

    setWindowFlags(Qt::FramelessWindowHint);

    items = new ItemsMain();
    navigation = new Navigation();
    toolbar = new Toolbar();

    auto *rootLayout = new QGridLayout();
    rootLayout->addWidget(toolbar, 0, 0, 1, 2);
    toolbar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    rootLayout->addWidget(navigation, 1, 0);
    rootLayout->addWidget(items, 1, 1);
    rootLayout->setSpacing(0);
    rootLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(rootLayout);

    connect(toolbar, &Toolbar::closeClicked, this, &MainWindow::close);
    connect(toolbar, &Toolbar::deleteClicked, items, &ItemsMain::deleteItem);
    connect(navigation, &Navigation::addItemRequested, items, &ItemsMain::addItem);
    connect(navigation, &Navigation::addGuardianRequested, items, &ItemsMain::addGuardian);
    connect(navigation, &Navigation::navButtonClicked, this, &MainWindow::setType);
    connect(items, &ItemsMain::itemsUpdated, this, &MainWindow::forceNavigation);
}

MainWindow::~MainWindow()
{

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

void MainWindow::setType(QAbstractButton *button)
{
    QString type = button->text();

    if(type == "Files")
    {
        items->setType(ITEM_FILE);
    }
    else if(type == "Folders")
    {
        items->setType(ITEM_FOLDER);
    }
    else if(type == "Apps")
    {
        items->setType(ITEM_APP);
    }
    else if(type == "Guardians")
    {
        items->setGuardians();
    }
}

void MainWindow::forceNavigation(ITEM_TYPE type)
{
    if(type == ITEM_FILE)
    {
        navigation->forceCheck("Files");
    }
    else if(type == ITEM_FOLDER)
    {
        navigation->forceCheck("Folders");
    }
    else if(type == ITEM_APP)
    {
        navigation->forceCheck("Apps");
    }
}
