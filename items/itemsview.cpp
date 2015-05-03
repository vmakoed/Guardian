#include "itemsview.h"

#include <QHBoxLayout>
#include <QFileDialog>

#include <QStyleOption>
#include <QPainter>

ItemsView::ItemsView(QWidget *parent) : QWidget(parent)
{
    itemsListBox = new QList<ItemWidget*>;
    guardiansListBox = new QButtonGroup;

    auto *rootLayout = new QVBoxLayout;
    rootLayout->setSpacing(0);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setAlignment(Qt::AlignTop);

    setLayout(rootLayout);
}

ItemsView::~ItemsView()
{

}

void ItemsView::setItems(QList<Item *> *itemsList)
{
    clear();

    for(auto item : *itemsList)
    {
        itemsListBox->append(new ItemWidget(0, item));
    }

    for(auto itemWidget : *itemsListBox)
    {
        this->layout()->addWidget(itemWidget);

        if(itemWidget->getItem()->getType() == ITEM_FILE)
        {
            itemWidget->setObjectName("fileItemWidget");
        }
        else if(itemWidget->getItem()->getType() == ITEM_FOLDER)
        {
            itemWidget->setObjectName("folderItemWidget");
        }
        else if(itemWidget->getItem()->getType() == ITEM_APP)
        {
            itemWidget->setObjectName("appItemWidget");
        }

        for(auto itemCheckedWidget: *itemsListBox)
        {
            if(itemWidget != itemCheckedWidget)
            {
                connect(itemWidget, &ItemWidget::clicked, itemCheckedWidget, &ItemWidget::uncheck);
            }
        }
    }
}

void ItemsView::setGuardians(QStringList *guardians)
{
    clear();

    for(auto guardian : *guardians)
    {
        guardiansListBox->addButton(new QPushButton(guardian));
    }

    for(auto guardianWidget : guardiansListBox->buttons())
    {
        this->layout()->addWidget(guardianWidget);
        guardianWidget->setObjectName("guardianWidget");

        for(auto guardianCheckedWidget: guardiansListBox->buttons())
        {
            if(guardianWidget != guardianCheckedWidget)
            {
                //TODO: check-uncheck

                //connect(guardianWidget, &QPushButton::clicked, guardianCheckedWidget, &QPushButton::setChecked);
            }
        }
    }
}

void ItemsView::getItem(ITEM_TYPE type, Guardian *guardian)
{
    QFileDialog dialog;
    dialog.setParent(this);
    dialog.setDirectory("%USERPROFILE%\Desktop");

    QStringList path;

    if(type == ITEM_FILE)
    {
        dialog.setWindowTitle("Select File");
        dialog.setFileMode(QFileDialog::AnyFile);
        dialog.exec();
        path = dialog.selectedFiles();
    }

    else if(type == ITEM_FOLDER)
    {
        dialog.setWindowTitle("Select Folder");
        dialog.setFileMode(QFileDialog::Directory);
        dialog.setOption(QFileDialog::ShowDirsOnly);
        dialog.exec();
        path = dialog.selectedFiles();
    }

    if(path.isEmpty())
    {
        return;
    }

    int index;
    for(index = path[0].length() - 1; path[0].at(index) != '/'; index--);

    QString name;
    index++;
    while(index < path[0].length())
    {
        name.append(path[0].at(index));

        index++;
    }

    emit itemRetrieved(new Item(name, path[0], type, guardian));
}

void ItemsView::clear()
{
    for(auto guardianWidget: guardiansListBox->buttons())
    {
        this->layout()->removeWidget(guardianWidget);
        delete guardianWidget;
    }

    for(auto itemWidget : *itemsListBox)
    {
        this->layout()->removeWidget(itemWidget);
        delete itemWidget;
    }

    itemsListBox->clear();
}

void ItemsView::acquireDeleteItem()
{
    Item *item;

    for(auto itemWidget : *itemsListBox)
    {
        if(itemWidget->isChecked())
        {
            item = itemWidget->getItem();
            itemWidget->setChecked(false);
            break;
        }
    }

    emit deleteItemAcquired(item);
}

void ItemsView::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

