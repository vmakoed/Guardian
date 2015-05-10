#ifndef GUARDIANWIDGET_H
#define GUARDIANWIDGET_H

#include <QPushButton>
#include <QLabel>

#include "guardians/guardian.h"

class GuardianWidget : public QPushButton
{
    Q_OBJECT

private:
    Guardian *guardian;

    QLabel *nameLabel;
    QLabel *stateLabel;

public:
    explicit GuardianWidget(QWidget *parent = 0, Guardian *guardian = 0);
    void paintEvent(QPaintEvent *);

signals:

public slots:
    void check();
    void uncheck();
};

#endif // GUARDIANWIDGET_H
