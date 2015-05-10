#include "itemspresenter.h"

#include <QHBoxLayout>

ItemsPresenter::ItemsPresenter(QWidget *parent) : QScrollArea(parent)
{
    itemsModel = new ItemsModel;
    itemsView = new ItemsView;

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
}

ItemsPresenter::~ItemsPresenter()
{

}

void ItemsPresenter::addItem(ITEM_TYPE type, Guardian *guardian)
{
    itemsModel->addItem(itemsView->getItem(type, guardian));
    refreshItems(type);
}

void ItemsPresenter::deleteItem()
{
    Item *item;
    item = itemsView->acquireDeleteItem();
    itemsModel->deleteItem(item);
    refreshItems(item->getType());
}

void ItemsPresenter::refreshItems(ITEM_TYPE type)
{
    itemsView->setItems(itemsModel->items(type));
    emit itemsRefreshed(type);
}
