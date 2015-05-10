#include "navigation.h"

#include <QVBoxLayout>

#include <QStyleOption>
#include <QPainter>

#include "database/database.h"

Navigation::Navigation(QWidget *parent) : QWidget(parent)
{
    setObjectName("navigation");

    addItemButton = new QPushButton("ADD ITEM");
    addItemButton->setObjectName("addItemButton");
    addGuardianButton = new QPushButton("ADD GUARDIAN");
    addGuardianButton->setObjectName("addGuardianButton");

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

    appsButton = new QToolButton;
    appsButton->setText("Apps");
    appsButton->setObjectName("appsButton");
    appsButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    navButtonGroup->addButton(appsButton);

    guardiansButton = new QToolButton;
    guardiansButton->setText("Guardians");
    guardiansButton->setObjectName("guardiansButton");
    guardiansButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    navButtonGroup->addButton(guardiansButton);

    auto rootLayout = new QVBoxLayout();
    rootLayout->setSpacing(0);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setAlignment(Qt::AlignTop);

    rootLayout->addSpacerItem(new QSpacerItem(0, 20));
    rootLayout->addWidget(addButton);
    rootLayout->setAlignment(addButton, Qt::AlignTop);
    rootLayout->addSpacerItem(new QSpacerItem(0, 20));

    for(auto navButton : navButtonGroup->buttons())
    {
        navButton->setCheckable(true);
        rootLayout->addWidget(navButton);
    }

    filesButton->setChecked(true);

    setLayout(rootLayout);


    // Qt5-style connects don't work here:
    connect(navButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(switchCategory(QAbstractButton*)));
    connect(navButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(switchAddButton(QAbstractButton*)));

    connect(addGuardianButton, &QPushButton::clicked, this, &Navigation::addGuardianClicked);
}

Navigation::~Navigation()
{

}

void Navigation::forceCheck(ITEM_TYPE type)
{
    QString buttonText;

    if(type == ITEM_FILE)
    {
        buttonText = "Files";
    }
    else if(type == ITEM_FOLDER)
    {
        buttonText = "Folders";
    }
    else if(type == ITEM_APP)
    {
        buttonText = "Apps";
    }

    for(auto navButton : navButtonGroup->buttons())
    {
        if(navButton->text() == buttonText)
        {
            navButton->setChecked(true);
            break;
        }
    }
}

void Navigation::switchCategory(QAbstractButton *button)
{
    if(button->text() == "Files")
    {
        emit typeSwitched(ITEM_FILE);
    }
    else if(button->text() == "Folders")
    {
        emit typeSwitched(ITEM_FOLDER);
    }
    else if(button->text() == "Apps")
    {
        emit typeSwitched(ITEM_APP);
    }
    else if(button->text() == "Guardians")
    {
        emit guardiansSwitched();
    }
}

void Navigation::switchAddButton(QAbstractButton *navButton)
{
    if(navButton == guardiansButton)
    {
        addButton->setCurrentWidget(addGuardianButton);
    }
    else
    {
        addButton->setCurrentWidget(addItemButton);
    }
}

void Navigation::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

