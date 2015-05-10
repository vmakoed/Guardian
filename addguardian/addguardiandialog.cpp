#include "addguardiandialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

AddGuardianDialog::AddGuardianDialog(QWidget *parent, QString *driveLetters, QStringList *productNames)
    : QDialog(parent)
{
    setObjectName("dialog");
    setModal(true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    titleLabel = new QLabel("New Guardian");
    titleLabel->setObjectName("titleLabel");

    chooseDriveLabel = new QLabel("Select a storage:");
    chooseDriveLabel->setObjectName("secondaryTextLabel");

    enterNameLabel = new QLabel("Enter Guardian's name:");
    enterNameLabel->setObjectName("secondaryTextLabel");

    nameLineEdit = new QLineEdit;
    nameLineEdit->setObjectName("inputLineEdit");

    cancelButton = new QPushButton("CANCEL");
    cancelButton->setObjectName("cancelButton");

    addButton = new QPushButton("CONFIRM");
    addButton->setObjectName("dialogButton");

    drivesList = new QList<DriveWidget*>;
    for(int i = 0; i < driveLetters->size(); i++)
    {
        drivesList->append(new DriveWidget(0, driveLetters->at(i), productNames->at(i)));
    }

    QVBoxLayout *rootLayout = new QVBoxLayout;
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    rootLayout->addWidget(titleLabel);
    rootLayout->addWidget(chooseDriveLabel);

    for(auto driveWidget : *drivesList)
    {
        rootLayout->addWidget(driveWidget);

        for(auto driveCheckedWidget: *drivesList)
        {
            if(driveWidget != driveCheckedWidget)
            {
                connect(driveWidget, &DriveWidget::clicked, driveCheckedWidget, &DriveWidget::uncheck);
            }
        }
    }

    rootLayout->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));
    rootLayout->addWidget(enterNameLabel);
    rootLayout->addWidget(nameLineEdit);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->setSpacing(0);

    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addWidget(addButton);

    buttonsLayout->setAlignment(Qt::AlignRight);


    rootLayout->addLayout(buttonsLayout);

    setLayout(rootLayout);

    connect(addButton, &QPushButton::clicked, this, &AddGuardianDialog::sendInfo);
    connect(addButton, &QPushButton::clicked, this, &AddGuardianDialog::close);
    connect(cancelButton, &QPushButton::clicked, this, &AddGuardianDialog::close);
}

void AddGuardianDialog::sendInfo()
{
    QString driveLetter;

    for(DriveWidget *driveWidget : *drivesList)
    {
        if(driveWidget->isChecked())
        {
            driveLetter = driveWidget->getDriveLetter();

            break;
        }
    }

    emit guardianInfoAcquired(driveLetter, nameLineEdit->text());
}

