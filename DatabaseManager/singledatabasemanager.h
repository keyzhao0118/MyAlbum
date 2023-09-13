#pragma once

#include <QSqlDatabase>
#include <QDateTime>

class DatabaseManager
{
public:
    static DatabaseManager* getInstance();
    bool openDatabase(const QString& databaseFilePath);
    void closeDatabase();

    int insertAlbum(const QString& name, const QDateTime& lastAccessed, const QDateTime& createdAt);
    int insertImage(int albumID, const QString& path, const QString& type, int size,
        const QString& resolution, const QDateTime& importedAt);
    
    bool deleteAlbum(int albumID);
    bool deleteImage(int imageID);

    int selectLastAccessedAlbumID();
    QSqlQuery selectImagesWithAlbumID(int albumID, int format, int sortType);
    QSqlQuery selectAllAlbums(int sortType);

private:
    DatabaseManager();
    static DatabaseManager* s_instance;
    QSqlDatabase m_database;
};