#include "database.h"

#include <QVariant>

QSqlDatabase Database::database;
QSqlQuery Database::query;

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

QStringList* Database::selectStringList(QString column, QString table, QString *whereClause)
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

QString* Database::selectString(QString column, QString table, QString *whereClause)
{
    if(whereClause == 0)
    {
        query.exec("select " + column + " from " + table + ";");
    }
    else
    {
        query.exec("select " + column + " from " + table + " " + *whereClause + ";");
    }

    query.first();

    QString *result = new QString;
    result->clear();
    result->append(query.value(0).toString());
    return result;
}

QList<int>* Database::selectIntegerList(QString column, QString table, QString *whereClause)
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
int Database::selectInteger(QString column, QString table, QString *whereClause)
{
    if(whereClause == 0)
    {
        query.exec("select " + column + " from " + table + ";");
    }
    else
    {
        query.exec("select " + column + " from " + table + " " + *whereClause + ";");
    }

    query.first();
    return query.value(0).toInt();
}

QList<bool>* Database::selectBooleanList(QString column, QString table, QString *whereClause)
{
    QList<bool> *values = new QList<bool>;

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
            values->append(query.value(0).toBool());
        }
    } while(query.next());

    return values;
}

bool Database::selectBoolean(QString column, QString table, QString *whereClause)
{
    if(whereClause == 0)
    {
        query.exec("select " + column + " from " + table + ";");
    }
    else
    {
        query.exec("select " + column + " from " + table + " " + *whereClause + ";");
    }

    query.first();
    return query.value(0).toBool();
}

QString *Database::where(QString column, QString value)
{
    return new QString("where " + column + " = '" + value + "'");
}

QString *Database::where(QString column, int value)
{
    return new QString("where " + column + " = " + QString::number(value));
}

QString *Database::where(QString column, bool value)
{
    if(value == true)
    {
        return new QString("where " + column + " = 1");
    }
    else
    {
        return new QString("where " + column + " = 0");
    }
}

void Database::bind(QString column, int value)
{
    query.bindValue(":" + column, value);
}

void Database::bind(QString column, QString value)
{
    query.bindValue(":" + column, value);
}

void Database::bind(QString column, bool value)
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


