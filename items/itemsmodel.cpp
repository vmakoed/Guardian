#include "itemsmodel.h"
#include "database/database.h"

ItemsModel::ItemsModel(QObject *parent) : QObject(parent)
{

}

ItemsModel::~ItemsModel()
{

}

void ItemsModel::addItem(Item *item)
{
    //TODO: Acquire item from windows explorer

    Database::prepare("insert into item values(:itemname, :itempath, :itemtype, :itemguardian);");
    Database::bind("itemname", item->getName());
    Database::bind("itempath", item->getPath());
    Database::bind("itemtype", item->getType());
    Database::exec();
}


void ItemsModel::deleteItem(Item *item)
{
    Database::prepare("delete from item where itempath = :itempath;");
    Database::bind("itempath", item->getPath());
    Database::exec();
}

QList<Item*>* ItemsModel::items(ITEM_TYPE type)
{
    QStringList *names = new QStringList;
    QStringList *paths = new QStringList;
    QList<int> *guardianIDs = new QList<int>;

    QString *whereClause = new QString("where itemtype = ");

    if(type == ITEM_FILE)
    {
        whereClause->append("1");
    }
    else if(type == ITEM_FOLDER)
    {
        whereClause->append("2");
    }
    else if(type == ITEM_APP)
    {
        whereClause->append("3");
    }

    names = Database::selectText("itemname", "item", whereClause);
    paths = Database::selectText("itempath", "item", whereClause);
    guardianIDs = Database::selectInteger("itemguardian", "item", whereClause);

    QList<Item*> *itemsList = new QList<Item*>;
    itemsList->clear();

    QStringList *guardianNames = new QStringList;
    guardianNames = Database::selectText("guardianname", "guardian");
    
    QList<Guardian*> *guardians = new QList<Guardian*>;
    
    for(int i = 0; i < guardianNames->size(); i++)
    {
        guardians->append(new Guardian(guardianNames->at(i)));
    }
       
    for(int i = 0; i < names->size(); i++)
    {
        itemsList->append(new Item(names->at(i), paths->at(i), type, guardians->at(guardianIDs->at(i) - 1)));
    }

    return itemsList;
}
