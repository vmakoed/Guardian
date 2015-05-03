#include "selectguardian.h"

#include <QVBoxLayout>

#include <QStyleOption>
#include <QPainter>

SelectGuardian::SelectGuardian(QWidget *parent, QStringList *guardianNames) : QDialog(parent)
{
    setObjectName("addItemDialog");
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    title = new QLabel("Select guardian:");
    title->setObjectName("title");

    options = new QButtonGroup();
    for(auto guardianName : *guardianNames)
    {
        options->addButton(new QPushButton(guardianName));
    }

    closeButton = new QPushButton("CLOSE");
    closeButton->setObjectName("closeButton");

    auto rootLayout = new QVBoxLayout;
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    rootLayout->addWidget(title);

    for(auto option : options->buttons())
    {
        option->setObjectName("optionButton");
        rootLayout->addWidget(option);
        rootLayout->setAlignment(option, Qt::AlignLeft);
    }

    rootLayout->addSpacerItem(new QSpacerItem(0, 10, QSizePolicy::Fixed, QSizePolicy::Fixed));

    rootLayout->addWidget(closeButton);
    rootLayout->setAlignment(closeButton, Qt::AlignRight | Qt::AlignBottom);

    setLayout(rootLayout);

    connect(options, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(sendOption(QAbstractButton*)));
    connect(closeButton, &QPushButton::clicked, this, &SelectGuardian::close);
}

void SelectGuardian::sendOption(QAbstractButton *button)
{
    close();

    emit optionPicked(button->text());
}

void SelectGuardian::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SelectGuardian::showEvent(QShowEvent *)
{
    move(QCursor::pos());
}
