#include "toolbar.h"

#include <QHBoxLayout>

#include <QStyleOption>
#include <QPainter>

Toolbar::Toolbar(QWidget *parent) : QWidget(parent)
{
    toolButtons = new QButtonGroup;

    appIcon = new QLabel;
    appIcon->setObjectName("appIcon");

    appTitle = new QLabel("Guardian");
    appTitle->setObjectName("appTitle");

    infoButton = new QPushButton();
    infoButton->setObjectName("infoButton");
    toolButtons->addButton(infoButton);

    deleteButton = new QPushButton();
    deleteButton->setObjectName("deleteButton");
    toolButtons->addButton(deleteButton);

    settingsButton = new QPushButton();
    settingsButton->setObjectName("settingsButton");
    toolButtons->addButton(settingsButton);

    closeButton = new QPushButton();
    closeButton->setObjectName("closeButton");
    toolButtons->addButton(closeButton);

    auto rootLayout = new QHBoxLayout;
    rootLayout->setSpacing(0);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setAlignment(Qt::AlignLeft);

    rootLayout->addSpacerItem(new QSpacerItem(30, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    rootLayout->addWidget(appIcon);
    rootLayout->setAlignment(appIcon, Qt::AlignVCenter);

    rootLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    rootLayout->addWidget(appTitle);
    rootLayout->setAlignment(appTitle, Qt::AlignVCenter);

    rootLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    for(auto toolButton : toolButtons->buttons())
    {
        rootLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
        rootLayout->addWidget(toolButton);
        rootLayout->setAlignment(toolButton, Qt::AlignVCenter);
    }

    rootLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));

    setLayout(rootLayout);
    setObjectName("toolbar");

    connect(closeButton, &QPushButton::clicked, this, &Toolbar::closeClicked);
    connect(deleteButton, &QPushButton::clicked, this, &Toolbar::deleteClicked);
}

void Toolbar::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
