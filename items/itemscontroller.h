#ifndef ITEMSCONTROLLER_H
#define ITEMSCONTROLLER_H

#include <QObject>

#include "items/itemsmodel.h"
#include "items/itemsview.h"

class ItemsController : public QObject
{
    Q_OBJECT

private:
    ItemsModel *itemsModel;
    ItemsView *itemsView;

public:
    ItemsController(ItemsModel *itemsModel = 0, ItemsView *itemsView = 0);
    ~ItemsController();

public slots:
    void addItem(ITEM_TYPE type, Guardian *guardian);
    void addGuardian(QString guardianName);
    void deleteItem();
    void setType(ITEM_TYPE type);
    void setGuardians();

signals:
    void itemsUpdated(ITEM_TYPE type);
    void guardiansUpdated();
};

#endif // ITEMSCONTROLLER_H
