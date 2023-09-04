#include "databasemanager.h"
#include "singledatabasemanager.h"

bool OpenDatabase(const QString& databaseFilePath)
{
	return DatabaseManager::getInstance()->openDatabase(databaseFilePath);
}

bool AddAlbum(const QString& name)
{
	return DatabaseManager::getInstance()->addAlbum(name);
}