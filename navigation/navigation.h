#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QButtonGroup>
#include <QStackedWidget>

#include "items/item.h"

class Navigation : public QWidget
{
    Q_OBJECT

private:
    QButtonGroup *navButtonGroup;

    QStackedWidget *addButton;
    QPushButton *addItemButton;
    QPushButton *addGuardianButton;

    QToolButton *filesButton;
    QToolButton *foldersButton;
    QToolButton *appsButton;
    QToolButton *guardiansButton;

public:
    explicit Navigation(QWidget *parent = 0);
    ~Navigation();

    void paintEvent(QPaintEvent *);

signals:
    void typeSwitched(ITEM_TYPE type);
    void guardiansSwitched();
    void addGuardianClicked();

public slots:
    void forceCheck(ITEM_TYPE type);
    void switchAddButton(QAbstractButton *navButton);
    void switchCategory(QAbstractButton *navButton);
};

#endif // NAVIGATION_H
