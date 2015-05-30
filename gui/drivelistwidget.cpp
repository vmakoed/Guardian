#include "drivelistwidget.h"

#include <QHBoxLayout>

DriveListWidget::DriveListWidget(QString driveLetter, QString driveName)
{
    setObjectName("driveListWidget");

    driveLetterLabel = new QLabel(driveLetter);
    driveLetterLabel->setObjectName("driveLetterLabel");

    driveNameLabel = new QLabel(driveName);
    driveNameLabel->setObjectName("driveNameLabel");

    QHBoxLayout *rootLayout = new QHBoxLayout;
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    rootLayout->addWidget(driveLetterLabel);
    rootLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    rootLayout->addWidget(driveNameLabel);

    setLayout(rootLayout);
}

QString DriveListWidget::getDrive()
{
    return driveLetterLabel->text();
}

QString DriveListWidget::getDriveName()
{
    return driveNameLabel->text();
}

