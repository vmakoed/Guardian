#include "guardianspresenter.h"

#include <QHBoxLayout>
#include <QDebug>

GuardiansPresenter::GuardiansPresenter(QWidget *parent) : QScrollArea(parent)
{
    guardiansView = new GuardiansView;
    guardiansModel = new GuardiansModel;

    auto *rootLayout = new QHBoxLayout();
    rootLayout->setSpacing(0);
    rootLayout->setContentsMargins(0, 0, 0, 0);

    rootLayout->addWidget(guardiansView);

    QWidget *content = new QWidget;
    content->setLayout(rootLayout);

    QWidget *container = new QWidget;
    container->setLayout(new QHBoxLayout);
    container->layout()->setContentsMargins(0, 0, 0, 0);
    container->layout()->addWidget(content);

    setWidget(container);
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::NoFrame);
}

GuardiansPresenter::~GuardiansPresenter()
{

}

void GuardiansPresenter::addGuardian(QString drive, QString name)
{
    guardiansModel->addGuardian(drive, name);
    refreshGuardians();
}

void GuardiansPresenter::deleteGuardian()
{

}

void GuardiansPresenter::refreshGuardians()
{
    guardiansModel->unmountAll();
    guardiansModel->scanDrives();
    guardiansView->setGuardians(guardiansModel->guardians());
    emit guardiansRefreshed();
}

