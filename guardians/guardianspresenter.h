#ifndef GUARDIANSPRESENTER_H
#define GUARDIANSPRESENTER_H

#include <QScrollArea>

#include "guardians/guardiansview.h"
#include "guardians/guardiansmodel.h"
#include "mount/getStoragesInfo.h"

class GuardiansPresenter : public QScrollArea
{
    Q_OBJECT

private:
    GuardiansView *guardiansView;
    GuardiansModel *guardiansModel;

public:
    explicit GuardiansPresenter(QWidget *parent = 0);
    ~GuardiansPresenter();

public slots:
    void addGuardian(QString drive, QString name);
    void deleteGuardian();
    void refreshGuardians();

signals:
    void guardiansRefreshed();
};

#endif // GUARDIANSPRESENTER_H
