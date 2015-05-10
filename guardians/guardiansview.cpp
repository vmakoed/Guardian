#include "guardiansview.h"

#include <QVBoxLayout>
#include <QFileDialog>

#include <QStyleOption>
#include <QPainter>

GuardiansView::GuardiansView(QWidget *parent) : QWidget(parent)
{
    guardiansListBox = new QList<GuardianWidget*>;

    auto *rootLayout = new QVBoxLayout;
    rootLayout->setSpacing(0);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setAlignment(Qt::AlignTop);

    setLayout(rootLayout);
}

GuardiansView::~GuardiansView()
{

}

void GuardiansView::setGuardians(QList<Guardian *> *guardiansList)
{
    clear();

    for(auto guardian : *guardiansList)
    {
        guardiansListBox->append(new GuardianWidget(0, guardian));
    }

    for(auto guardianWidget : *guardiansListBox)
    {
        this->layout()->addWidget(guardianWidget);

        for(auto guardianCheckedWidget: *guardiansListBox)
        {
            if(guardianWidget != guardianCheckedWidget)
            {
                connect(guardianWidget, &GuardianWidget::clicked, guardianCheckedWidget, &GuardianWidget::uncheck);
            }
        }
    }
}

void GuardiansView::clear()
{
    for(auto guardianWidget: *guardiansListBox)
    {
        this->layout()->removeWidget(guardianWidget);
        delete guardianWidget;
    }

    guardiansListBox->clear();
}


void GuardiansView::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

