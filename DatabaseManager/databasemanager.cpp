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

bool AddAlbum(const QString& name)
{
	return DatabaseManager::getInstance()->addAlbum(name);
}

bool AddImage(const QString& path)
{
	return DatabaseManager::getInstance()->addImage(path);
}