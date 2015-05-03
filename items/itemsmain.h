#ifndef ITEMS_H
#define ITEMS_H

#include <QScrollArea>

#include "items/itemsmodel.h"
#include "items/itemsview.h"
#include "items/itemscontroller.h"

class ItemsMain : public QScrollArea
{
    Q_OBJECT

private:
    ItemsModel *itemsModel;
    ItemsView *itemsView;
    ItemsController *itemsController;

public:
    explicit ItemsMain(QWidget *parent = 0);
    ~ItemsMain();

signals:
    void itemsUpdated(ITEM_TYPE type);

public slots:
    void addItem(ITEM_TYPE type, Guardian *guardian);
    void addGuardian(QString guardianName);
    void deleteItem();
    void setType(ITEM_TYPE type);
    void setGuardians();
};

#endif // ITEMS_H
