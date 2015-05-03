#include "itemsmain.h"

#include <QHBoxLayout>

ItemsMain::ItemsMain(QWidget *parent) : QScrollArea(parent)
{
    itemsModel = new ItemsModel;
    itemsView = new ItemsView;
    itemsController = new ItemsController(itemsModel, itemsView);

    auto *rootLayout = new QHBoxLayout();
    rootLayout->setSpacing(0);
    rootLayout->setContentsMargins(0, 0, 0, 0);

    rootLayout->addWidget(itemsView);

    QWidget *content = new QWidget;
    content->setLayout(rootLayout);

    QWidget *container = new QWidget;
    container->setLayout(new QHBoxLayout);
    container->layout()->setContentsMargins(0, 0, 0, 0);
    container->layout()->addWidget(content);

    setWidget(container);
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::NoFrame);

    connect(itemsController, &ItemsController::itemsUpdated, this, &ItemsMain::itemsUpdated);
    setType(ITEM_FILE);
}

ItemsMain::~ItemsMain()
{

}

void ItemsMain::addItem(ITEM_TYPE type, Guardian *guardian)
{
    itemsController->addItem(type, guardian);
}

void ItemsMain::addGuardian(QString guardianName)
{
    itemsController->addGuardian(guardianName);
}

void ItemsMain::deleteItem()
{
    itemsController->deleteItem();
}

void ItemsMain::setType(ITEM_TYPE type)
{
    itemsController->setType(type);
}

void ItemsMain::setGuardians()
{
    itemsController->setGuardians();
}


