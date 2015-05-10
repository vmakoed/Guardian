#include "guardianwidget.h"

#include <QHBoxLayout>

#include <QPainter>
#include <QStyleOption>

GuardianWidget::GuardianWidget(QWidget *parent, Guardian *guardian) : QPushButton(parent)
{
    setObjectName("guardianWidget");

    this->guardian = guardian;

    nameLabel = new QLabel(guardian->getName());
    nameLabel->setObjectName("nameLabel");

    if(guardian->getState() == MOUNTED)
    {
        stateLabel = new QLabel("Mounted");
    }
    else
    {
        stateLabel = new QLabel("Unmounted");
    }

    stateLabel->setObjectName("stateLabel");

    QHBoxLayout *rootLayout = new QHBoxLayout;
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    rootLayout->addWidget(nameLabel);
    rootLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    rootLayout->addWidget(stateLabel);
    rootLayout->setAlignment(Qt::AlignLeft);

    setLayout(rootLayout);

    setCheckable(true);
    setChecked(false);

    connect(this, &GuardianWidget::clicked, this, &GuardianWidget::check);
}


// Unfortunately, styles for pseudo-states of custom widgets don't work properly when set in a separate file.
void GuardianWidget::uncheck()
{
    setChecked(false);
    setStyleSheet(".GuardianWidget { background-color: #FFFFFF; }");
}

void GuardianWidget::check()
{
    setStyleSheet(".GuardianWidget { background-color: #2095F2; } \
                    #nameLabel { color: #FFFFFF } \
                    #stateLabel { background-color: #FFFFFF; color: #2095F2; }");
}

void GuardianWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
