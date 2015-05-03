#include "addguardiandialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QStyleOption>
#include <QPainter>

AddGuardianDialog::AddGuardianDialog(QWidget *parent) : QDialog(parent)
{
    setObjectName("addGuardianDialog");
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    title = new QLabel("Enter guardian's name:");
    title->setObjectName("title");
    guardianName = new QLineEdit;
    guardianName->setObjectName("guardianInput");
    okButton = new QPushButton("OK");
    okButton->setObjectName("button");
    okButton->setDisabled(true);
    closeButton = new QPushButton("CLOSE");
    closeButton->setObjectName("button");

    auto buttonsLayout = new QHBoxLayout;
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->setSpacing(0);
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(closeButton);
    buttonsLayout->setAlignment(Qt::AlignRight);

    auto rootLayout = new QVBoxLayout;
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);
    rootLayout->addWidget(title);
    rootLayout->addWidget(guardianName);
    rootLayout->addLayout(buttonsLayout);

    setLayout(rootLayout);

    connect(guardianName, &QLineEdit::textChanged, this, &AddGuardianDialog::setOkButton);
    connect(okButton, &QPushButton::clicked, this, &AddGuardianDialog::sendName);
    connect(okButton, &QPushButton::clicked, this, &AddGuardianDialog::close);
    connect(closeButton, &QPushButton::clicked, this, &AddGuardianDialog::close);
}

void AddGuardianDialog::sendName()
{
    emit nameObtained(guardianName->text());
}


void AddGuardianDialog::setOkButton()
{
    if(guardianName->text().isEmpty())
    {
        okButton->setDisabled(true);
    }
    else
    {
        okButton->setEnabled(true);
    }
}

void AddGuardianDialog::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void AddGuardianDialog::showEvent(QShowEvent *)
{
    move(QCursor::pos());
}


void AddGuardianDialog::closeEvent(QCloseEvent *)
{
    guardianName->clear();
}
