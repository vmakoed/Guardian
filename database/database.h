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

    static void connect(QString pathToDatabase);
    static void disconnect();

    static void createTable(QString table, QStringList columns, QStringList types);
    static void dropTable(QString table);

    static QStringList* selectStringList(QString column, QString table, QString *whereClause = 0);
    static QString *selectString(QString column, QString table, QString *whereClause = 0);
    static QList<int>* selectIntegerList(QString column, QString table, QString *whereClause = 0);
    static int selectInteger(QString column, QString table, QString *whereClause = 0);
    static QList<bool>* selectBooleanList(QString column, QString table, QString *whereClause = 0);
    static bool selectBoolean(QString column, QString table, QString *whereClause = 0);

    static QString *where(QString column, QString value);
    static QString *where(QString column, int value);
    static QString *where(QString column, bool value);

    static void prepare(QString prepareText);
    static void bind(QString column, int value);
    static void bind(QString column, QString value);
    static void bind(QString column, bool value);
    static void exec();

    static void exec(QString queryText);


};

#endif // DATABASE_H
