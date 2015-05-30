#include "additemdialog.h"

#include <QHBoxLayout>
#include <QFileDialog>

AddItemDialog::AddItemDialog(QList<Guardian *> *guardiansList)
{   
    setObjectName("addItemDialog");
    setModal(true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    titleLabel = new QLabel("New Item");
    titleLabel->setObjectName("titleLabel");

    selectCategoryLabel = new QLabel("Select a category:");
    selectCategoryLabel->setObjectName("secondaryTextLabel");

    categoriesList = new QList<IconTextLabel*>;

    categoriesList->append(new IconTextLabel("fileIcon", "File"));
    categoriesList->append(new IconTextLabel("folderIcon", "Folder"));

    categoriesListBox = new QListWidget;
    categoriesListBox->setObjectName("list");

    for(auto widget : *categoriesList)
    {
        categoriesListBox->addItem(new QListWidgetItem);
        categoriesListBox->setItemWidget(categoriesListBox->item(categoriesListBox->count() - 1), widget);
    }

    // TODO: remove hardcoded '48'.
    // The issue here is that we apply all widgets' sizes when applying a stylesheet
    // which occurs after all the widgets are constructed.
    categoriesListBox->setFixedHeight(48 * 2);
    categoriesListBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    enterPathLabel = new QLabel("Enter path:");
    enterPathLabel->setObjectName("secondaryTextLabel");
    pathLineEdit = new QLineEdit;
    pathLineEdit->setObjectName("inputLineEdit");
    pathLineEdit->setDisabled(true);

    browseButton = new QPushButton("BROWSE");
    browseButton->setObjectName("flatButton");
    browseButton->setDisabled(true);

    selectGuardianLabel = new QLabel("Select a Guardian:");
    selectGuardianLabel->setObjectName("secondaryTextLabel");

    this->guardiansList = new QList<DriveListWidget*>;
    guardiansListBox = new QListWidget;
    guardiansListBox->setObjectName("list");

    for(int i = 0; i < guardiansList->size(); i++)
    {
        addGuardianToList(guardiansList->at(i));
    }

    guardiansListBox->setDisabled(true);

    cancelButton = new QPushButton("CANCEL");
    cancelButton->setObjectName("cancelButton");

    confirmButton = new QPushButton("CONFIRM");
    confirmButton->setObjectName("dialogButton");

    confirmButton->setDisabled(true);

    QVBoxLayout *rootLayout = new QVBoxLayout;
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);
    rootLayout->addWidget(titleLabel);
    rootLayout->addWidget(selectCategoryLabel);
    rootLayout->addWidget(categoriesListBox);
    rootLayout->addSpacerItem(new QSpacerItem(0, 15, QSizePolicy::Fixed, QSizePolicy::Fixed));
    rootLayout->addWidget(enterPathLabel);
    rootLayout->addWidget(pathLineEdit);
    rootLayout->addWidget(browseButton);
    rootLayout->setAlignment(browseButton, Qt::AlignRight);
    rootLayout->addSpacerItem(new QSpacerItem(0, 15, QSizePolicy::Fixed, QSizePolicy::Fixed));
    rootLayout->addWidget(selectGuardianLabel);
    rootLayout->addWidget(guardiansListBox);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->setSpacing(0);

    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addWidget(confirmButton);

    buttonsLayout->setAlignment(Qt::AlignRight);

    rootLayout->addLayout(buttonsLayout);
    setLayout(rootLayout);

    connect(categoriesListBox, &QListWidget::itemSelectionChanged, this, &AddItemDialog::manageEnabled);
    connect(pathLineEdit, &QLineEdit::textChanged, this, &AddItemDialog::manageEnabled);
    connect(guardiansListBox, &QListWidget::itemSelectionChanged, this, &AddItemDialog::manageEnabled);
    connect(browseButton, &QPushButton::clicked, this, &AddItemDialog::browse);
    connect(confirmButton, &QPushButton::clicked, this, &AddItemDialog::sendInfo);
    connect(confirmButton, &QPushButton::clicked, this, &AddItemDialog::close);
    connect(cancelButton, &QPushButton::clicked, this, &AddItemDialog::close);
}

void AddItemDialog::browse()
{
    QFileDialog *dialog = new QFileDialog;
    dialog->setParent(this);
    dialog->setDirectory("%USERPROFILE%");

    QStringList path;

    if(categoriesList->at(categoriesListBox->currentRow())->getText() == "File")
    {
        dialog->setFileMode(QFileDialog::AnyFile);
        dialog->setWindowTitle("Select File");
    }
    else if(categoriesList->at(categoriesListBox->currentRow())->getText() == "Folder")
    {
        dialog->setFileMode(QFileDialog::DirectoryOnly);
        dialog->setWindowTitle("Select Folder");
    }


    if(dialog->exec() == QFileDialog::Accepted)
    {
        path = dialog->selectedFiles();
    }

    if(path.isEmpty() == false)
    {
        pathLineEdit->setText(path.at(0));
    }
}

void AddItemDialog::sendInfo()
{
    QString category;

    if(categoriesList->at(categoriesListBox->currentRow())->getIconName() == "fileIcon")
    {
        category = "file";
    }
    else if(categoriesList->at(categoriesListBox->currentRow())->getIconName() == "folderIcon")
    {
        category = "folder";
    }
    else if(categoriesList->at(categoriesListBox->currentRow())->getIconName() == "appIcon")
    {
        emit systemKeyRequested(guardiansList->at(guardiansListBox->currentRow())->getDriveName());

        return;
    }

    emit itemInfoAcquired(category, pathLineEdit->text(),
                     guardiansList->at(guardiansListBox->currentRow())->getDriveName());
}

void AddItemDialog::addGuardianToList(Guardian *guardian)
{
    guardiansList->append(new DriveListWidget(*(new QString(guardian->getDrive())), guardian->getName()));
    guardiansListBox->addItem(new QListWidgetItem);
    guardiansListBox->setItemWidget(guardiansListBox->item(guardiansList->size() - 1), guardiansList->last());

    // TODO: remove hardcoded '48'.
    // The issue here is that we apply all widgets' sizes when applying a stylesheet
    // which occurs after all the widgets are constructed.
    guardiansListBox->setFixedHeight(guardiansListBox->count() * 48);
}

void AddItemDialog::enableSystemCategory()
{

    categoriesList->append(new IconTextLabel("appIcon", "System"));

    categoriesListBox->addItem(new QListWidgetItem);
    categoriesListBox->setItemWidget(categoriesListBox->item(categoriesListBox->count() - 1), categoriesList->last());
    categoriesListBox->setFixedHeight(48 * 3);

}

void AddItemDialog::closeEvent(QCloseEvent *)
{
    emit closed();
}

void AddItemDialog::manageEnabled()
{
    if(categoriesListBox->selectedItems().isEmpty() == false)
    {
        if(categoriesList->at(categoriesListBox->currentRow())->getText() != "System")
        {
            browseButton->setEnabled(true);
        }
        else
        {
            browseButton->setDisabled(true);
            guardiansListBox->setEnabled(true);
        }
    }

    if(guardiansListBox->isEnabled() == false && pathLineEdit->text().isEmpty() == false)
    {
        guardiansListBox->setEnabled(true);
    }

    if(guardiansListBox->selectedItems().isEmpty() == false)
    {
        confirmButton->setEnabled(true);
    }
}
