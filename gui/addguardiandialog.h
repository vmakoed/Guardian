#ifndef ADDGUARDIANDIALOG_H
#define ADDGUARDIANDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QList>
#include <QListWidget>

#include "gui/drivelistwidget.h"

class AddGuardianDialog : public QDialog
{
    Q_OBJECT

private:
    QLabel *titleLabel;
    QLabel *selectDriveLabel;
    QLabel *enterNameLabel;
    QLineEdit *nameLineEdit;

    QList<DriveListWidget*> *drivesList;
    QListWidget *drivesListBox;

    QPushButton *cancelButton;
    QPushButton *confirmButton;

public:
    explicit AddGuardianDialog(QStringList *drives, QStringList *driveNames);

    void addDriveToList(QString drive, QString driveName);

    void closeEvent(QCloseEvent *);

signals:
    void guardianInfoAcquired(QString drive, QString name);
    void closed();

public slots:
    void sendInfo();
    void enableNameLineEdit(QListWidgetItem * item);
    void manageConfirm(QString text);
};

#endif // ADDGUARDIANDIALOG_H
