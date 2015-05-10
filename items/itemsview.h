#ifndef ITEMSVIEW_H
#define ITEMSVIEW_H

#include <QWidget>
#include <QList>
#include <QButtonGroup>

#include "items/itemwidget.h"

class ItemsView : public QWidget
{
    Q_OBJECT

private:
    QList<ItemWidget*> *itemsListBox;

public:
    explicit ItemsView(QWidget *parent = 0);
    ~ItemsView();
    void paintEvent(QPaintEvent *);
    void clear();

signals:
    void itemRetrieved(Item*);
    void deleteItemAcquired(Item*);

public slots:
    void setItems(QList<Item *> *itemsList);
    Item* getItem(ITEM_TYPE type, Guardian *guardian);
    Item *acquireDeleteItem();

};

#endif // ITEMSVIEW_H
