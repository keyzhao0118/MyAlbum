#include "databasemanager.h"
#include "singledatabasemanager.h"

bool OpenDatabase(const QString& databaseFilePath)
{
	return DatabaseManager::getInstance()->openDatabase(databaseFilePath);
}

void CloseDatabase()
{
	DatabaseManager::getInstance()->closeDatabase();
}

int InsertAlbum(const QString& name, const QDateTime& lastAccessed, const QDateTime& createdAt)
{
	return DatabaseManager::getInstance()->insertAlbum(name, lastAccessed, createdAt);
}

int InsertImage(int albumID, const QString& path, const QString& format, int size,
	const QString& resolution, const QDateTime& importedAt)
{
	return DatabaseManager::getInstance()->insertImage(
		albumID, path, format, size, resolution, importedAt);
}

bool DeleteAlbum(int albumID)
{
	return DatabaseManager::getInstance()->deleteAlbum(albumID);
}

bool DeleteImage(int imageID)
{
	return DatabaseManager::getInstance()->deleteImage(imageID);
}

int SelectLastAccessedAlbumID()
{
	return DatabaseManager::getInstance()->selectLastAccessedAlbumID();
}

QSqlQuery SelectImagesWithAlbumID(int albumID, int sortType)
{
	return DatabaseManager::getInstance()->selectImagesWithAlbumID(albumID, sortType);
}

QSqlQuery SelectAllAlbums(int sortType)
{
	return DatabaseManager::getInstance()->selectAllAlbums(sortType);
}