#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QToolButton>

#include "guardian.h"
#include "item.h"
#include "gui/icontextlabel.h"

#include "gui/drivelistwidget.h"

class AddItemDialog : public QDialog
{
    Q_OBJECT

private:
    QLabel *titleLabel;
    QLabel *selectCategoryLabel;
    QLabel *enterPathLabel;
    QLineEdit *pathLineEdit;
    QPushButton *browseButton;

    QList<IconTextLabel*> *categoriesList;
    QListWidget *categoriesListBox;

    QLabel *selectGuardianLabel;

    QList<DriveListWidget*> *guardiansList;
    QListWidget *guardiansListBox;

    QPushButton *cancelButton;
    QPushButton *confirmButton;

public:
    explicit AddItemDialog(QList<Guardian *> *guardiansList);

    void addGuardianToList(Guardian *guardian);
    void enableSystemCategory();
    void closeEvent(QCloseEvent *);

signals:
    void itemInfoAcquired(QString type, QString path, QString guardianName);
    void systemKeyRequested(QString guardianName);
    void closed();

public slots:
    void manageEnabled();
    void sendInfo();
    void browse();
};

#endif // ADDITEMDIALOG_H
