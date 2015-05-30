#include "addguardiandialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QDebug>

AddGuardianDialog::AddGuardianDialog(QStringList *drives, QStringList *driveNames)
{
    setObjectName("addGuardianDialog");
    setModal(true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    titleLabel = new QLabel("New Guardian");
    titleLabel->setObjectName("titleLabel");

    selectDriveLabel = new QLabel("Select a storage:");
    selectDriveLabel->setObjectName("secondaryTextLabel");

    enterNameLabel = new QLabel("Enter Guardian's name:");
    enterNameLabel->setObjectName("secondaryTextLabel");

    nameLineEdit = new QLineEdit;
    nameLineEdit->setObjectName("inputLineEdit");
    nameLineEdit->setDisabled(true);

    cancelButton = new QPushButton("CANCEL");
    cancelButton->setObjectName("cancelButton");

    confirmButton = new QPushButton("CONFIRM");
    confirmButton->setObjectName("dialogButton");

    confirmButton->setDisabled(true);

    drivesList = new QList<DriveListWidget*>;
    drivesListBox = new QListWidget;
    drivesListBox->setObjectName("list");

    for(int i = 0; i < drives->size(); i++)
    {
        addDriveToList(drives->at(i), driveNames->at(i));
    }

    // TODO: remove hardcoded '48'.
    // The issue here is that we apply all widgets' sizes when applying a stylesheet
    // which occurs after all the widgets are constructed.
    drivesListBox->setFixedHeight(drivesListBox->count() * 48);

    QVBoxLayout *rootLayout = new QVBoxLayout;
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    rootLayout->addWidget(titleLabel);
    rootLayout->addWidget(selectDriveLabel);
    rootLayout->addWidget(drivesListBox);
    rootLayout->addWidget(enterNameLabel);
    rootLayout->addWidget(nameLineEdit);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->setSpacing(0);

    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addWidget(confirmButton);

    buttonsLayout->setAlignment(Qt::AlignRight);

    rootLayout->addLayout(buttonsLayout);
    setLayout(rootLayout);

    connect(drivesListBox, &QListWidget::itemClicked, this, &AddGuardianDialog::enableNameLineEdit);
    connect(confirmButton, &QPushButton::clicked, this, &AddGuardianDialog::sendInfo);
    connect(confirmButton, &QPushButton::clicked, this, &AddGuardianDialog::close);
    connect(cancelButton, &QPushButton::clicked, this, &AddGuardianDialog::close);
    connect(nameLineEdit, &QLineEdit::textChanged, this, &AddGuardianDialog::manageConfirm);
}

void AddGuardianDialog::addDriveToList(QString drive, QString driveName)
{
    drivesList->append(new DriveListWidget(drive, driveName));
    drivesListBox->addItem(new QListWidgetItem);
    drivesListBox->setItemWidget(drivesListBox->item(drivesList->size() - 1), drivesList->last());
}

void AddGuardianDialog::closeEvent(QCloseEvent *)
{
    emit closed();
}

void AddGuardianDialog::sendInfo()
{
    emit guardianInfoAcquired(drivesList->at(drivesListBox->currentRow())->getDrive(), nameLineEdit->text());
}

void AddGuardianDialog::enableNameLineEdit(QListWidgetItem *item)
{
    nameLineEdit->setEnabled(true);
}

void AddGuardianDialog::manageConfirm(QString text)
{
    if(text.isEmpty() == true)
    {
        confirmButton->setDisabled(true);
    }
    else
    {
        confirmButton->setEnabled(true);
    }
}

