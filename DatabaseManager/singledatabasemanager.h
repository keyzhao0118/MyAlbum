#pragma once

#include <QSqlDatabase>

class DatabaseManager
{
public:
    static DatabaseManager* getInstance();
    bool openDatabase(const QString& databaseFilePath);
    void closeDatabase();
    bool addAlbum(const QString& name);
    bool addImage(const QString& path);

private:
    DatabaseManager();
    static DatabaseManager* s_instance;
    QSqlDatabase m_database;
};