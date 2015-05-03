#include "database.h"

#include <QVariant>

QSqlDatabase Database::database;
QSqlQuery Database::query;

Database::Database()
{

}

Database::~Database()
{

}

void Database::connect(QString pathToDatabase)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(pathToDatabase);
    database.open();
    query = QSqlQuery(database);
}

void Database::disconnect()
{
    database.close();
}

void Database::createTable(QString table, QStringList columns, QStringList types)
{
    QString queryString("create table " + table + " (");

    for(int i = 0; i < columns.size(); i++)
    {
        queryString.append(columns.at(i) + " " + types.at(i));

        if(i != columns.size() - 1)
        {
            queryString.append(", ");
        }
    }

    queryString.append(")");
    query.exec();
}

void Database::dropTable(QString table)
{
    query.exec("drop table " + table);
}

QStringList* Database::selectText(QString column, QString table, QString *whereClause)
{
    QStringList *values = new QStringList;

    if(whereClause == 0)
    {
        query.exec("select " + column + " from " + table + ";");
    }
    else
    {
        query.exec("select " + column + " from " + table + " " + *whereClause + ";");
    }
    query.first();

    do
    {
        if(query.isValid())
        {
            values->append(query.value(0).toString());
        }
    } while(query.next());

    return values;
}

QList<int>* Database::selectInteger(QString column, QString table, QString *whereClause)
{
    QList<int> *values = new QList<int>;

    if(whereClause == 0)
    {
        query.exec("select " + column + " from " + table + ";");
    }
    else
    {
        query.exec("select " + column + " from " + table + " " + *whereClause + ";");
    }
    query.first();

    do
    {
        if(query.isValid())
        {
            values->append(query.value(0).toInt());
        }
    } while(query.next());

    return values;
}

void Database::bind(QString column, int value)
{
    query.bindValue(":" + column, value);
}

void Database::bind(QString column, QString value)
{
    query.bindValue(":" + column, value);
}

void Database::prepare(QString prepareText)
{
    query.prepare(prepareText);
}

void Database::exec()
{
    query.exec();
}

void Database::exec(QString queryText)
{
    query.exec(queryText);
}


