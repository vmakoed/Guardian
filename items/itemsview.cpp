#include "itemsview.h"

#include <QVBoxLayout>
#include <QFileDialog>

#include <QStyleOption>
#include <QPainter>

ItemsView::ItemsView(QWidget *parent) : QWidget(parent)
{
    itemsListBox = new QList<ItemWidget*>;

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

Item* ItemsView::getItem(ITEM_TYPE type, Guardian *guardian)
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
        return nullptr;
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

    return (new Item(name, path[0], type, guardian));
}

void ItemsView::clear()
{
    for(auto itemWidget : *itemsListBox)
    {
        this->layout()->removeWidget(itemWidget);
        delete itemWidget;
    }

    itemsListBox->clear();
}

Item* ItemsView::acquireDeleteItem()
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

    return item;
}

void ItemsView::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

