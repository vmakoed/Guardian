#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QButtonGroup>
#include <QStackedWidget>

#include "add/additemdialog.h"
#include "add/addguardiandialog.h"
#include "add/selectguardian.h"
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

    // TODO: separate context dialogs from navigation
    AddItemDialog *addItemDialog;
    AddGuardianDialog *addGuardianDialog;
    SelectGuardian *selectGuardianDialog;
    QString *pickedType;

public:
    explicit Navigation(QWidget *parent = 0);
    ~Navigation();

    void paintEvent(QPaintEvent *);

signals:
    void navButtonClicked(QAbstractButton *navButton);
    void addItemRequested(ITEM_TYPE type, Guardian *guardian);
    void addGuardianRequested(QString guardianName);

public slots:
    void forceCheck(QString buttonText);
    void selectGuardian(QString itemType);
    void sendAddItemSignal(QString guardianName);
    void switchAddButton(QAbstractButton *navButton);
};

#endif // NAVIGATION_H
