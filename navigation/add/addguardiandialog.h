#ifndef ADDGUARDIANDIALOG_H
#define ADDGUARDIANDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class AddGuardianDialog : public QDialog
{
    Q_OBJECT

private:
    QLabel *title;
    QLineEdit *guardianName;

    QPushButton *closeButton;
    QPushButton *okButton;

public:
    AddGuardianDialog(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);

signals:
    void nameObtained(QString name);

public slots:
    void sendName();
    void setOkButton();
};

#endif // ADDGUARDIANDIALOG_H
