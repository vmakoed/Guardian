#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>

class Database
{
public:
    static QSqlDatabase database;
    static QSqlQuery query;

    Database();
    ~Database();

    static void connect(QString pathToDatabase);
    static void disconnect();
    static void createTable(QString table, QStringList columns, QStringList types);
    static void dropTable(QString table);
    static QStringList* selectText(QString column, QString table, QString *whereClause = 0);
    static QList<int>* selectInteger(QString column, QString table, QString *whereClause = 0);
    static void prepare(QString prepareText);
    static void bind(QString column, int value);
    static void bind(QString column, QString value);
    static void exec();
    static void exec(QString queryText);

};

#endif // DATABASE_H
