#include "icontextlabel.h"

#include <QHBoxLayout>

IconTextLabel::IconTextLabel(QString iconName, QString text)
{
    setObjectName("iconTextLabel");

    iconLabel = new QLabel;
    iconLabel->setObjectName(iconName);

    textLabel = new QLabel(text);
    textLabel->setObjectName("textLabel");

    auto *rootLayout = new QHBoxLayout;
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    rootLayout->addWidget(iconLabel);
    rootLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    rootLayout->addWidget(textLabel);
    rootLayout->setAlignment(Qt::AlignLeft);

    setLayout(rootLayout);
}

QString IconTextLabel::getIconName()
{
    return iconLabel->objectName();
}

QString IconTextLabel::getText()
{
    return textLabel->text();
}
