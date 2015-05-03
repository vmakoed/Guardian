#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QButtonGroup>
#include <QPushButton>

class AddItemDialog : public QDialog
{
    Q_OBJECT

private:
    QLabel *title;
    QButtonGroup *options;

    QPushButton *closeButton;

public:
    AddItemDialog(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent *);

signals:
    void optionPicked(QString option);

public slots:
    void sendOption(QAbstractButton *button);
};

#endif // ADDITEMDIALOG_H
