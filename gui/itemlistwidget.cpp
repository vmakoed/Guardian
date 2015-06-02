#include "itemlistwidget.h"

#include <QHBoxLayout>

ItemListWidget::ItemListWidget(Item *item)
{
    this->item = item;

    itemTypeLabel = new QLabel;

    switch(item->getType())
    {
    case ITEM_FILE:
        itemTypeLabel->setObjectName("fileLabel");
        break;

    case ITEM_FOLDER:
        itemTypeLabel->setObjectName("folderLabel");
        break;

    case ITEM_SYSTEM:
        itemTypeLabel->setObjectName("appLabel");
        break;
    }

    itemNameLabel = new QLabel(item->getName());
    itemNameLabel->setObjectName("nameLabel");

    guardianNameButton = new QPushButton(item->getGuardianName());
    guardianNameButton->setObjectName("guardianButton");

    setState(item->getItemGuardianState());

    auto *rootLayout = new QHBoxLayout;
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    rootLayout->addWidget(itemTypeLabel);
    rootLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    rootLayout->addWidget(itemNameLabel);
    rootLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    rootLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    rootLayout->addWidget(guardianNameButton);

    rootLayout->setAlignment(Qt::AlignLeft);
    setLayout(rootLayout);

    setObjectName("itemListWidget");
}

Item *ItemListWidget::getItem()
{
    return item;
}

void ItemListWidget::setItem(Item *value)
{
    item = value;
}

void ItemListWidget::setState(ITEM_GUARDIAN_STATE state)
{
    item->setItemGuardianState(state);

    switch(state)
    {
    case LOCKED:
        guardianNameButton->setDisabled(true);
        break;

    case UNLOCKED:
        guardianNameButton->setEnabled(true);
        break;
    }
}

