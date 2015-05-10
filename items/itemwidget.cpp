#include "itemwidget.h"

#include <QHBoxLayout>

#include <QPainter>
#include <QStyleOption>

#include <QDebug>

ItemWidget::ItemWidget(QWidget *parent, Item *item) : QPushButton(parent)
{
    setObjectName("itemWidget");

    this->item = item;

    itemPic = new QLabel();
    itemPic->setObjectName("itemPic");
    nameLabel = new QLabel(item->getName());
    guardianLabel = new QLabel(item->getGuardian()->getName());

    nameLabel->setObjectName("nameLabel");
    guardianLabel->setObjectName("guardianLabel");

    auto *rootLayout = new QHBoxLayout;
    rootLayout->addWidget(itemPic);
    rootLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    rootLayout->addWidget(nameLabel);
    rootLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    rootLayout->addWidget(guardianLabel);

    rootLayout->setAlignment(Qt::AlignLeft);

    setLayout(rootLayout);
    setCheckable(true);
    setChecked(false);

    connect(this, &ItemWidget::clicked, this, &ItemWidget::check);
}

ItemWidget::~ItemWidget()
{

}

Item* ItemWidget::getItem()
{
    return item;
}

void ItemWidget::setItem(Item *item)
{
    this->item = item;
    nameLabel->setText(item->getName());
    guardianLabel->setText(item->getGuardian()->getName());
}

// Unfortunately, styles for pseudo-states of custom widgets don't work properly when set in a separate file.
void ItemWidget::uncheck()
{
    setChecked(false);
    setStyleSheet(".ItemWidget { background-color: #FFFFFF; }");
}

void ItemWidget::check()
{
    setStyleSheet(".ItemWidget { background-color: #2095F2; }    \
                    #nameLabel { color: #FFFFFF } \
                    #guardianLabel { background-color: #FFFFFF; color: #2095F2; }");
}

void ItemWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
