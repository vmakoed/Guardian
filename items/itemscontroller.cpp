#include "itemscontroller.h"

ItemsController::ItemsController(ItemsModel *itemsModel, ItemsView *itemsView)
{
    this->itemsModel = itemsModel;
    this->itemsView = itemsView;

    connect(itemsView, &ItemsView::itemRetrieved, itemsModel, &ItemsModel::addItem);
    connect(itemsView, &ItemsView::deleteItemAcquired, itemsModel, &ItemsModel::deleteItem);
    connect(itemsModel, &ItemsModel::itemsUpdated, itemsModel, &ItemsModel::acquireItems);
    connect(itemsModel, &ItemsModel::itemsUpdated, this, &ItemsController::itemsUpdated);
    connect(itemsModel, &ItemsModel::itemsAcquired, itemsView, &ItemsView::setItems);
    connect(itemsModel, &ItemsModel::guardiansUpdated, itemsModel, &ItemsModel::acquireGuardians);
    connect(itemsModel, &ItemsModel::guardiansUpdated, this, &ItemsController::guardiansUpdated);
    connect(itemsModel, &ItemsModel::guardiansAcquired, itemsView, &ItemsView::setGuardians);
}

ItemsController::~ItemsController()
{

}

void ItemsController::addItem(ITEM_TYPE type, Guardian *guardian)
{
    itemsView->getItem(type, guardian);
}

void ItemsController::addGuardian(QString guardianName)
{
    itemsModel->addGuardian(guardianName);
}

void ItemsController::deleteItem()
{
    itemsView->acquireDeleteItem();
}

void ItemsController::setType(ITEM_TYPE type)
{
    itemsModel->acquireItems(type);
}

void ItemsController::setGuardians()
{
    itemsModel->acquireGuardians();
}


