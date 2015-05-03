#include "itemsmodel.h"
#include "database/database.h"

ItemsModel::ItemsModel(QObject *parent) : QObject(parent)
{
    items = new QList<Item*>;
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
    Database::bind("itemguardian", item->getGuardian()->getId());
    Database::exec();

    emit itemsUpdated(item->getType());
}


void ItemsModel::deleteItem(Item *item)
{
    Database::prepare("delete from item where itempath = :itempath;");
    Database::bind("itempath", item->getPath());
    Database::exec();

    emit itemsUpdated(item->getType());

}

void ItemsModel::acquireItems(ITEM_TYPE type)
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

    items->clear();

    QStringList *guardianNames = new QStringList;
    guardianNames = Database::selectText("guardianname", "guardian");
    
    QList<Guardian*> *guardians = new QList<Guardian*>;
    
    for(int i = 0; i < guardianNames->size(); i++)
    {
        guardians->append(new Guardian(i + 1, guardianNames->at(i)));
    }
       
    for(int i = 0; i < names->size(); i++)
    {
        items->append(new Item(names->at(i), paths->at(i), type, guardians->at(guardianIDs->at(i) - 1)));
    }

    emit itemsAcquired(items);
}

void ItemsModel::acquireGuardians()
{
    QStringList *guardians = new QStringList;

    guardians = Database::selectText("guardianname", "guardian");

    emit guardiansAcquired(guardians);
}

void ItemsModel::addGuardian(QString guardianName)
{
    QList<int> *guardians = new QList<int>;
    guardians = Database::selectInteger("guardianid", "guardian");

    Database::prepare("insert into guardian values(:guardianid, :guardianname);");
    Database::bind("guardianid", guardians->last() + 1);
    Database::bind("guardianname", guardianName);
    Database::exec();

    delete guardians;

    emit guardiansUpdated();
}
