#include "mainwindow.h"

#include <QHBoxLayout>
#include <QGridLayout>

#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    createToolbar();
    createNavigation();
    createListBoxes();
    composeMainWindow();

    setWindowFlags(Qt::FramelessWindowHint);
    setObjectName("mainWindow");
}

MainWindow::~MainWindow()
{

}

void MainWindow::createToolbar()
{
    toolButtons = new QButtonGroup;

    appIcon = new QLabel;
    appIcon->setObjectName("appIcon");

    appTitle = new QLabel("Guardian");
    appTitle->setObjectName("appTitle");

    lockManageButton = new QStackedWidget;
    lockManageButton->setObjectName("lockManageButton");
    lockButton = new QPushButton;
    lockButton->setObjectName("lockButton");
    unlockButton = new QPushButton;
    unlockButton->setObjectName("unlockButton");
    lockManageButton->addWidget(lockButton);
    lockManageButton->addWidget(unlockButton);

    connect(lockButton, &QPushButton::pressed, this, &MainWindow::setUnlockButtonOn);
    connect(unlockButton, &QPushButton::pressed, this, &MainWindow::setLockButtonOn);

    deleteButton = new QPushButton();
    deleteButton->setObjectName("deleteButton");
    deleteButton->setDisabled(true);
    connect(deleteButton, &QPushButton::pressed, this, &MainWindow::deleteClicked);
    toolButtons->addButton(deleteButton);

    closeButton = new QPushButton();
    closeButton->setObjectName("closeButton");
    connect(closeButton, &QPushButton::clicked, this, &MainWindow::closeClicked);
    toolButtons->addButton(closeButton);

    auto toolbarLayout = new QHBoxLayout;
    toolbarLayout->setSpacing(0);
    toolbarLayout->setContentsMargins(0, 0, 0, 0);
    toolbarLayout->setAlignment(Qt::AlignLeft);

    toolbarLayout->addSpacerItem(new QSpacerItem(30, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    toolbarLayout->addWidget(appIcon);
    toolbarLayout->setAlignment(appIcon, Qt::AlignVCenter);

    toolbarLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    toolbarLayout->addWidget(appTitle);
    toolbarLayout->setAlignment(appTitle, Qt::AlignVCenter);

    toolbarLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    toolbarLayout->addWidget(lockManageButton);
    toolbarLayout->setAlignment(lockManageButton, Qt::AlignVCenter);

    for(auto toolButton : toolButtons->buttons())
    {
        toolbarLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
        toolbarLayout->addWidget(toolButton);
        toolbarLayout->setAlignment(toolButton, Qt::AlignVCenter);
    }

    toolbarLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));

    toolbar = new QWidget;
    toolbar->setLayout(toolbarLayout);
    toolbar->setObjectName("toolbar");
}

void MainWindow::createNavigation()
{
    addItemButton = new QPushButton("+ ITEM");
    addItemButton->setObjectName("addItemButton");

    connect(addItemButton, &QPushButton::clicked, this, &MainWindow::addItemClicked);

    addGuardianButton = new QPushButton("+ GUARDIAN");
    addGuardianButton->setObjectName("addGuardianButton");

    connect(addGuardianButton, &QPushButton::clicked, this, &MainWindow::addGuardianClicked);

    addButton = new QStackedWidget;
    addButton->addWidget(addItemButton);
    addButton->addWidget(addGuardianButton);
    addButton->setObjectName("addButton");

    navButtonGroup = new QButtonGroup();

    filesButton = new QToolButton;
    filesButton->setText("Files");
    filesButton->setObjectName("filesButton");
    filesButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    navButtonGroup->addButton(filesButton);

    foldersButton = new QToolButton;
    foldersButton->setText("Folders");
    foldersButton->setObjectName("foldersButton");
    foldersButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    navButtonGroup->addButton(foldersButton);

    systemButton = new QToolButton;
    systemButton->setText("System");
    systemButton->setObjectName("systemButton");
    systemButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    navButtonGroup->addButton(systemButton);

    guardiansButton = new QToolButton;
    guardiansButton->setText("Guardians");
    guardiansButton->setObjectName("guardiansButton");
    guardiansButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    navButtonGroup->addButton(guardiansButton);

    connect(navButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SIGNAL(navigationSwitched(QAbstractButton*)));

    auto navigationLayout = new QVBoxLayout();
    navigationLayout->setSpacing(0);
    navigationLayout->setContentsMargins(0, 0, 0, 0);
    navigationLayout->setAlignment(Qt::AlignTop);

    navigationLayout->addSpacerItem(new QSpacerItem(0, 20));
    navigationLayout->addWidget(addButton);
    navigationLayout->setAlignment(addButton, Qt::AlignTop);
    navigationLayout->addSpacerItem(new QSpacerItem(0, 20));

    for(auto navButton : navButtonGroup->buttons())
    {
        navButton->setCheckable(true);
        navigationLayout->addWidget(navButton);
    }

    navigation = new QWidget;
    navigation->setLayout(navigationLayout);
    navigation->setObjectName("navigation");

    guardiansButton->setChecked(true);
}

void MainWindow::createListBoxes()
{
    itemsListBox = new QListWidget;
    itemsListBox->setObjectName("itemslistbox");

    guardiansListBox = new QListWidget;
    guardiansListBox->setObjectName("guardianslistbox");

    itemsList = new QList<ItemListWidget*>;
    guardiansList = new QList<GuardianListWidget*>;

    listBox = new QStackedWidget;
    listBox->addWidget(itemsListBox);
    listBox->addWidget(guardiansListBox);
    listBox->setCurrentWidget(guardiansListBox);
    listBox->setObjectName("listboxstacked");

    connect(itemsListBox, &QListWidget::itemSelectionChanged, this, &MainWindow::sendItemSelection);
    connect(guardiansListBox, &QListWidget::itemSelectionChanged, this, &MainWindow::sendGuardianSelection);
}

void MainWindow::composeMainWindow()
{
    auto rootLayout = new QGridLayout;
    rootLayout->addWidget(toolbar, 0, 0, 1, 2);
    toolbar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    rootLayout->addWidget(navigation, 1, 0);
    rootLayout->addWidget(listBox, 1, 1);
    rootLayout->setSpacing(0);
    rootLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(rootLayout);
}


void MainWindow::setGuardians(QList<Guardian*> *srcGuardiansList)
{
    guardiansListBox->clear();

    for(int i = 0; i < srcGuardiansList->size(); i++)
    {
        addGuardian(srcGuardiansList->at(i));
    }
}

void MainWindow::setItemsState(QList<Item *> *srcItemsList, ITEM_GUARDIAN_STATE state)
{
    for(auto item : *srcItemsList)
    {
        setItemState(item, state);
    }
}

void MainWindow::setItemState(Item *item, ITEM_GUARDIAN_STATE state)
{
    int i = 0;
    while(itemsListBox->item(i))
    {
        if(itemsList->at(i)->getItem()->getPath().compare(item->getPath()) == 0)
        {
            itemsList->at(i)->setState(state);
            break;
        }

        i++;
    }
}

void MainWindow::setGuardianState(QString *guardianName, GUARDIAN_STATE state, char driveLetter)
{
    int i = 0;
    while(guardiansListBox->item(i))
    {
        if(guardiansList->at(i)->getGuardian()->getName() == guardianName)
        {
            if(state == UNMOUNTED)
            {
                guardiansList->at(i)->setDrive('0');
                break;
            }
            else
            {
                guardiansList->at(i)->setDrive(driveLetter);
                break;
            }
        }

        i++;
    }

    i = 0;
    while(itemsListBox->item(i))
    {
        if(itemsList->at(i)->getItem()->getGuardianName() == guardianName)
        {
            if(state == UNMOUNTED)
            {
                itemsList->at(i)->setState(LOCKED);
            }
            else
            {
                itemsList->at(i)->setState(UNLOCKED);
            }
        }

        i++;
    }

    clearSelection();
}

void MainWindow::setItems(QList<Item*> *srcItemsList)
{
    clearItems();

    for(int i = 0; i < srcItemsList->size(); i++)
    {
        addItem(srcItemsList->at(i));
    }
}

void MainWindow::addItem(Item* item)
{
    itemsList->append(new ItemListWidget(item));
    itemsListBox->addItem(new QListWidgetItem);
    itemsListBox->setItemWidget(itemsListBox->item(itemsListBox->count() - 1), itemsList->at(itemsListBox->count() - 1));

    clearSelection();
}

void MainWindow::clearItems()
{
    itemsListBox->clear();
    itemsList->clear();
}

void MainWindow::addGuardian(Guardian *guardian)
{
    guardiansList->append(new GuardianListWidget(guardian));
    guardiansListBox->addItem(new QListWidgetItem);   
    guardiansListBox->setItemWidget(guardiansListBox->item(guardiansListBox->count() - 1), guardiansList->at(guardiansListBox->count() - 1));

    clearSelection();
}

Guardian* MainWindow::acquireGuardianToDelete()
{
    return guardiansList->at(guardiansListBox->currentRow())->getGuardian();
}

void MainWindow::deleteSelectedGuardian()
{
    guardiansList->removeAt(guardiansListBox->currentRow());
    delete guardiansListBox->item(guardiansListBox->currentRow());

    clearSelection();
}

Item *MainWindow::acquireItemToDelete()
{
    return itemsList->at(itemsListBox->currentRow())->getItem();
}

void MainWindow::deleteSelectedItem()
{
    itemsList->removeAt(itemsListBox->currentRow());
    delete itemsListBox->item(itemsListBox->currentRow());

    clearSelection();
}

void MainWindow::toggleItemSwitch(ITEM_TYPE type)
{
    switch(type)
    {
    case ITEM_FILE:
        filesButton->setChecked(true);
        emit navigationSwitched(filesButton);
        break;

    case ITEM_FOLDER:
        foldersButton->setChecked(true);
        emit navigationSwitched(foldersButton);
        break;

    case ITEM_SYSTEM:
        systemButton->setChecked(true);
        emit navigationSwitched(systemButton);
        break;
    }
}

void MainWindow::switchtoItems()
{
    lockManageButton->setDisabled(true);
    lockManageButton->show();

    listBox->setCurrentWidget(itemsListBox);
    addButton->setCurrentWidget(addItemButton);
}

void MainWindow::switchtoGuardians()
{
    lockManageButton->hide();
    listBox->setCurrentWidget(guardiansListBox);
    addButton->setCurrentWidget(addGuardianButton);
}

void MainWindow::deleteClicked()
{
    if(listBox->currentWidget() == guardiansListBox)
    {
        emit deleteGuardianClicked();
    }
    else
    {
        emit deleteItemClicked();
    }
}

void MainWindow::enableLockButton(bool value)
{
    if(lockManageButton->currentWidget() == lockButton)
    {
        lockManageButton->setEnabled(value);
    }
    else
    {
        lockManageButton->setEnabled(true);
    }
}

void MainWindow::enableDeleteButton(bool value)
{
    deleteButton->setEnabled(value);
}

void MainWindow::setLockButtonOn()
{
    lockManageButton->setCurrentWidget(lockButton);

    if(itemsList->at(itemsListBox->currentRow())->getItem()->getItemGuardianState() == LOCKED)
    {
        lockManageButton->setEnabled(false);
    }

    emit itemProtectionEnabled(itemsList->at(itemsListBox->currentRow())->getItem());
}

void MainWindow::setUnlockButtonOn()
{
    lockManageButton->setCurrentWidget(unlockButton);
    emit itemProtectionDisabled(itemsList->at(itemsListBox->currentRow())->getItem());
}

void MainWindow::setLockButton(bool value)
{
    if(value == true)
    {
        lockManageButton->setCurrentWidget(lockButton);
    }
    else
    {
        lockManageButton->setCurrentWidget(unlockButton);
    }
}

void MainWindow::sendItemSelection()
{
    if(itemsListBox->selectedItems().isEmpty() == false && itemsListBox->currentRow() >= 0 && itemsListBox->currentRow() < itemsList->count())
    {
        emit itemSelected(itemsList->at(itemsListBox->currentRow())->getItem());
    }
    else
    {
        emit itemSelected(nullptr);
    }
}

void MainWindow::sendGuardianSelection()
{
    if(guardiansListBox->selectedItems().isEmpty() == false && guardiansListBox->currentRow() >= 0 && guardiansListBox->currentRow() < guardiansList->count())
    {
        emit guardianSelected(guardiansList->at(guardiansListBox->currentRow())->getGuardian());
    }
    else
    {
        emit guardianSelected(nullptr);
    }
}

void MainWindow::clearSelection()
{
    itemsListBox->clearSelection();
    guardiansListBox->clearSelection();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    clickX = event->x();
    clickY = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX() - clickX, event->globalY() - clickY);
}
