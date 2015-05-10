#ifndef ITEMSPRESENTER_H
#define ITEMSPRESENTER_H

#include <QScrollArea>

#include "items/itemsmodel.h"
#include "items/itemsview.h"

class ItemsPresenter : public QScrollArea
{
    Q_OBJECT

private:
    ItemsModel *itemsModel;
    ItemsView *itemsView;

public:
    explicit ItemsPresenter(QWidget *parent = 0);
    ~ItemsPresenter();

public slots:
    void addItem(ITEM_TYPE type, Guardian *guardian);
    void deleteItem();
    void refreshItems(ITEM_TYPE type);

signals:
    void itemsRefreshed(ITEM_TYPE type);
    void guardiansRefreshed();
};

#endif // ITEMSPRESENTER_H
