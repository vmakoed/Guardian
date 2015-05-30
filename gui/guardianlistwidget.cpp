#include "guardianlistwidget.h"

#include <QHBoxLayout>

GuardianListWidget::GuardianListWidget(Guardian *guardian)
{
    this->guardian = guardian;

    guardianIconLabel = new QLabel();
    guardianIconLabel->setObjectName("guardianiconlabel");

    guardianNameLabel = new QLabel(guardian->getName());
    guardianNameLabel->setObjectName("namelabel");

    driveLabel = new QPushButton();
    driveLabel->setObjectName("drivelabel");

    setDrive(guardian->getDrive());

    auto *rootLayout = new QHBoxLayout;
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    rootLayout->addWidget(guardianIconLabel);
    rootLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    rootLayout->addWidget(guardianNameLabel);
    rootLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    rootLayout->addWidget(driveLabel);
    rootLayout->setAlignment(Qt::AlignLeft);

    setLayout(rootLayout);

    setObjectName("guardianlistwidget");
}

Guardian *GuardianListWidget::getGuardian()
{
    return guardian;
}

void GuardianListWidget::setGuardian(Guardian *value)
{
    guardian = value;
}

char GuardianListWidget::getDrive()
{
    return guardian->getDrive();
}

void GuardianListWidget::setDrive(char drive)
{
    guardian->setDrive(drive);

    if(drive == '0')
    {
        guardian->setState(UNMOUNTED);
        driveLabel->setText(nullptr);
        driveLabel->setDisabled(true);
    }
    else
    {
        guardian->setState(MOUNTED);
        driveLabel->setText(*(new QString(drive)));
        driveLabel->setEnabled(true);
    }
}
