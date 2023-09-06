#pragma once

#include <QSqlDatabase>

class DatabaseManager
{
public:
    static DatabaseManager* getInstance();
    bool openDatabase(const QString& databaseFilePath);
    void closeDatabase();
    int addAlbum(const QString& name);
    int addImage(int albumID, const QString& path);

private:
    DatabaseManager();
    static DatabaseManager* s_instance;
    QSqlDatabase m_database;
};