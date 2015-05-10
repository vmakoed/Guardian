#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QMouseEvent>

#include "items/itemspresenter.h"
#include "guardians/guardianspresenter.h"
#include "navigation/navigation.h"
#include "toolbar/toolbar.h"
#include "drivesscanner/drivesscanner.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    ItemsPresenter *items;
    GuardiansPresenter *guardians;
    QStackedWidget *listBox;

    Navigation *navigation;
    Toolbar *toolbar;

    DrivesScanner *scanner;

    int clickX;
    int clickY;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *);

public slots:
    void addItem(ITEM_TYPE type, Guardian *guardian);
    void setType(ITEM_TYPE type);
    void setGuardians();
    void showAddGuardianDialog();
    void addGuardian(QString drive, QString name);
};

#endif // MAINWINDOW_H
