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

int AddAlbum(const QString& name)
{
	return DatabaseManager::getInstance()->addAlbum(name);
}

int AddImage(int albumID, const QString& path)
{
	return DatabaseManager::getInstance()->addImage(albumID, path);
}