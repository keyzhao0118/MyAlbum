#pragma once

#include <QSqlDatabase>

class DatabaseManager
{
public:
    static DatabaseManager* getInstance();
    bool openDatabase(const QString& databaseFilePath);
    bool addAlbum(const QString& name);

private:
    DatabaseManager();
    static DatabaseManager* s_instance;
    QSqlDatabase m_database;
};