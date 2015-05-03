#ifndef SELECTGUARDIAN_H
#define SELECTGUARDIAN_H

#include <QDialog>
#include <QLabel>
#include <QButtonGroup>
#include <QPushButton>

class SelectGuardian : public QDialog
{
    Q_OBJECT

private:
    QLabel *title;
    QButtonGroup *options;

    QPushButton *closeButton;

public:
    SelectGuardian(QWidget *parent = 0, QStringList *guardianNames = 0);

    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent *);

signals:
    void optionPicked(QString option);

public slots:
    void sendOption(QAbstractButton *button);
};
#endif // SELECTGUARDIAN_H
