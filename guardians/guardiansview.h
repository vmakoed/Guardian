#ifndef GUARDIANSVIEW_H
#define GUARDIANSVIEW_H

#include <QWidget>
#include "guardians/guardianwidget.h"

class GuardiansView : public QWidget
{
    Q_OBJECT
private:
    QList<GuardianWidget*> *guardiansListBox;

public:
    explicit GuardiansView(QWidget *parent = 0);
    ~GuardiansView();
    void paintEvent(QPaintEvent *);
    void clear();

signals:

public slots:
    void setGuardians(QList<Guardian *> *guardiansList);
};

#endif // GUARDIANSVIEW_H
