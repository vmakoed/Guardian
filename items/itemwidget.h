#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QPushButton>
#include <QLabel>

#include "items/item.h"

class ItemWidget : public QPushButton
{
    Q_OBJECT

private:
    Item *item;

    QLabel *itemPic;
    QLabel *nameLabel;
    QLabel *guardianLabel;

public:
    explicit ItemWidget(QWidget *parent = 0, Item *item = 0);
    ~ItemWidget();

    Item* getItem();
    void setItem(Item *item);
    void paintEvent(QPaintEvent *);

signals:

public slots:
    void uncheck();
    void check();
};

#endif // ITEMWIDGET_H
