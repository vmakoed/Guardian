#ifndef ADDGUARDIANDIALOG_H
#define ADDGUARDIANDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QList>

#include "drivewidget.h"

class AddGuardianDialog : public QDialog
{
    Q_OBJECT

private:
    QLabel *titleLabel;
    QLabel *chooseDriveLabel;
    QLabel *enterNameLabel;
    QLineEdit *nameLineEdit;

    QList<DriveWidget*> *drivesList;

    QPushButton *cancelButton;
    QPushButton *addButton;

public:
    explicit AddGuardianDialog(QWidget *parent = 0, QString *driveLetters = 0, QStringList *productNames = 0);

signals:
    void guardianInfoAcquired(QString drive, QString name);
public slots:
    void sendInfo();
};

#endif // ADDGUARDIANDIALOG_H
