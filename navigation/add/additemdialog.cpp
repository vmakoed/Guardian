#include "additemdialog.h"

#include <QVBoxLayout>

#include <QStyleOption>
#include <QPainter>

AddItemDialog::AddItemDialog(QWidget *parent) : QDialog(parent)
{
    setObjectName("addItemDialog");
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    title = new QLabel("Select type:");
    title->setObjectName("title");

    options = new QButtonGroup();
    options->addButton(new QPushButton("File"));
    options->addButton(new QPushButton("Folder"));
    options->addButton(new QPushButton("App"));

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
    connect(closeButton, &QPushButton::clicked, this, &AddItemDialog::close);
}

void AddItemDialog::sendOption(QAbstractButton *button)
{
    close();

    emit optionPicked(button->text());
}

void AddItemDialog::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void AddItemDialog::showEvent(QShowEvent *)
{
    move(QCursor::pos());
}


