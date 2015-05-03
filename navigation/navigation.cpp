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

    // TODO: separate context dialogs from navigation
    addItemDialog = new AddItemDialog(this);
    addItemDialog->setModal(true);
    addGuardianDialog = new AddGuardianDialog(this);
    addGuardianDialog->setModal(true);
    pickedType = new QString;

    // Qt5-style connects don't work here:
    connect(navButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SIGNAL(navButtonClicked(QAbstractButton*)));
    connect(navButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(switchAddButton(QAbstractButton*)));

    connect(addItemButton, &QPushButton::clicked, addItemDialog, &AddItemDialog::show);
    connect(addGuardianButton, &QPushButton::clicked, addGuardianDialog, &AddGuardianDialog::show);
    connect(addItemDialog, &AddItemDialog::optionPicked, this, &Navigation::selectGuardian);
    connect(addGuardianDialog, &AddGuardianDialog::nameObtained, this, &Navigation::addGuardianRequested);
    connect(addGuardianButton, &QPushButton::clicked, addGuardianDialog, &AddGuardianDialog::show);
}

Navigation::~Navigation()
{

}

void Navigation::forceCheck(QString buttonText)
{
    for(auto navButton : navButtonGroup->buttons())
    {
        if(navButton->text() == buttonText)
        {
            navButton->setChecked(true);
            break;
        }
    }
}

void Navigation::selectGuardian(QString itemType)
{
    pickedType->clear();
    pickedType->append(itemType);

    QStringList *guardianNames = new QStringList;
    guardianNames = Database::selectText("guardianname", "guardian");

    selectGuardianDialog = new SelectGuardian(this, guardianNames);
    selectGuardianDialog->setModal(true);
    connect(selectGuardianDialog, &SelectGuardian::optionPicked, this, &Navigation::sendAddItemSignal);
    selectGuardianDialog->show();
}
void Navigation::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Navigation::sendAddItemSignal(QString guardianName)
{
    QList<int> *id = new QList<int>;
    QString *whereClause = new QString("where guardianname = '");
    whereClause->append(guardianName);
    whereClause->append("'");

    id = Database::selectInteger("guardianid", "guardian", whereClause);

    Guardian *guardian = new Guardian(id->at(0), guardianName);

    if(*pickedType == "File")
    {
        emit addItemRequested(ITEM_FILE, guardian);
    }
    else if(*pickedType == "Folder")
    {
        emit addItemRequested(ITEM_FOLDER, guardian);
    }
    else if(*pickedType == "App")
    {
        emit addItemRequested(ITEM_APP, guardian);
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
