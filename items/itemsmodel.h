#ifndef ITEMSMODEL_H
#define ITEMSMODEL_H

#include <QObject>
#include <QList>

#include "items/item.h"


class ItemsModel : public QObject
{
    Q_OBJECT

private:
    QList<Item*> *items;

public:
    explicit ItemsModel(QObject *parent = 0);
    ~ItemsModel();
    void acquireItems(ITEM_TYPE type);
    void acquireGuardians();
    void addItem(Item *item);
    void addGuardian(QString guardianName);
    void deleteItem(Item *item);

signals:
    void itemsAcquired(QList<Item*>*);
    void guardiansAcquired(QStringList*);
    void itemsUpdated(ITEM_TYPE);
    void guardiansUpdated();

public slots:
};

#endif // ITEMSMODEL_H
