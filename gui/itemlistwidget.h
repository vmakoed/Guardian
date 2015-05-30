#ifndef ITEMLISTWIDGET_H
#define ITEMLISTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "item.h"

class ItemListWidget : public QWidget
{
    Q_OBJECT

private:
    Item *item;

    QLabel *itemTypeLabel;
    QLabel *itemNameLabel;
    QPushButton *guardianNameButton;

public:
    explicit ItemListWidget(Item* item);

    Item *getItem();
    void setItem(Item *value);
    void setState(ITEM_GUARDIAN_STATE state);
signals:

public slots:
};

#endif // ITEMLISTWIDGET_H
