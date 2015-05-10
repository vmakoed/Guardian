#ifndef ITEMSMODEL_H
#define ITEMSMODEL_H

#include <QObject>
#include <QList>

#include "items/item.h"
#include "guardians/guardian.h"

class ItemsModel : public QObject
{
    Q_OBJECT

public:
    explicit ItemsModel(QObject *parent = 0);
    ~ItemsModel();
    QList<Item *> *items(ITEM_TYPE type);
    void addItem(Item *item);
    void deleteItem(Item *item);

signals:
    void itemsAcquired(QList<Item*>*);
    void itemsUpdated(ITEM_TYPE);

public slots:
};

#endif // ITEMSMODEL_H
