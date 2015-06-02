#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QButtonGroup>
#include <QStackedWidget>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QListWidget>

#include "item.h"
#include "guardian.h"

#include "itemlistwidget.h"
#include "guardianlistwidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QLabel *appIcon;
    QLabel *appTitle;

    QButtonGroup *toolButtons;

    QStackedWidget *lockManageButton;
    QPushButton *lockButton;
    QPushButton *unlockButton;

    QPushButton *deleteButton;
    QPushButton *closeButton;

    QWidget *navigation;

    QButtonGroup *navButtonGroup;
    QStackedWidget *addButton;
    QPushButton *addItemButton;
    QPushButton *addGuardianButton;
    QToolButton *filesButton;
    QToolButton *foldersButton;
    QToolButton *systemButton;
    QToolButton *guardiansButton;
    QWidget *toolbar;

    QList<ItemListWidget*> *itemsList;
    QListWidget *itemsListBox;

    QList<GuardianListWidget*> *guardiansList;
    QListWidget *guardiansListBox;

    QStackedWidget *listBox;

    int clickX;
    int clickY;

    void createToolbar();
    void createNavigation();
    void createListBoxes();
    void composeMainWindow();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void sendItemSelection();
    void sendGuardianSelection();

    void enableLockButton(bool value);
    void enableDeleteButton(bool value);

    void clearSelection();
    void setLockButtonOn();
    void setUnlockButtonOn();
    void clearItems();

signals:
    void navigationSwitched(QAbstractButton *button);

    void closeClicked();

    void addGuardianClicked();
    void addItemClicked();

    void deleteGuardianClicked();
    void deleteItemClicked();

    void itemSelected(Item *item);
    void guardianSelected(Guardian *guardian);

    void itemProtectionEnabled(Item *item);
    void itemProtectionDisabled(Item *item);

public slots:
    void setItems(QList<Item*>* items);
    void setGuardians(QList<Guardian*>* guardians);

    void setItemsState(QList<Item *> *itemsList, ITEM_GUARDIAN_STATE state);
    void setItemState(Item *item, ITEM_GUARDIAN_STATE state);
    void setGuardianState(QString *guardianName, GUARDIAN_STATE state, char driveLetter);

    void addGuardian(Guardian* guardian);
    void addItem(Item *item);

    Guardian* acquireGuardianToDelete();
    void deleteSelectedGuardian();

    Item *acquireItemToDelete();
    void deleteSelectedItem();

    void toggleItemSwitch(ITEM_TYPE type);

    void switchtoItems();
    void switchtoGuardians();

    void deleteClicked();

    void setLockButton(bool value);

};

#endif // MAINWINDOW_H
