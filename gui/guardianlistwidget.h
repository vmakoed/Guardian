#ifndef GUARDIANLISTWIDGET_H
#define GUARDIANLISTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "guardian.h"

class GuardianListWidget : public QWidget
{
    Q_OBJECT

private:
    Guardian* guardian;

    QLabel *guardianIconLabel;
    QLabel *guardianNameLabel;
    QPushButton *driveLabel;

public:
    explicit GuardianListWidget(Guardian* guardian);

    Guardian* getGuardian();
    void setGuardian(Guardian *value);

    char getDrive();
    void setDrive(char drive);

signals:

public slots:
};

#endif // GUARDIANLISTWIDGET_H
