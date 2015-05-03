#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include <QMouseEvent>

#include "items/itemsmain.h"
#include "navigation/navigation.h"
#include "toolbar/toolbar.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    ItemsMain *items;
    Navigation *navigation;
    Toolbar *toolbar;

    int clickX;
    int clickY;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *);

public slots:
    void setType(QAbstractButton *button);
    void forceNavigation(ITEM_TYPE type);
};

#endif // MAINWINDOW_H
