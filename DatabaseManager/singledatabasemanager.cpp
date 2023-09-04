#include "singledatabasemanager.h"
#include <QFile>
#include <QSqlQuery>

DatabaseManager* DatabaseManager::getInstance()
{
	if (s_instance == nullptr)
		s_instance = new DatabaseManager;
	return s_instance;
}

bool DatabaseManager::openDatabase(const QString& databaseFilePath)
{
	m_database = QSqlDatabase::addDatabase("QSQLITE");
	m_database.setDatabaseName(databaseFilePath);
	if (!QFile::exists(databaseFilePath))
	{
		QFile databaseFile(databaseFilePath);
		if (!databaseFile.open(QIODevice::WriteOnly))
			return false;
		databaseFile.close();

		QString createAlbumsTable = "CREATE TABLE IF NOT EXISTS Albums ("
			"ID INTEGER PRIMARY KEY,"
			"Name TEXT,"
			"CoverID INTEGER,"
			"LastAccessed DATETIME,"
			"FOREIGN KEY(CoverID) REFERENCES Images(ID)"
			");";

		QString createImagesTable = "CREATE TABLE IF NOT EXISTS Images ("
			"ID INTEGER PRIMARY KEY,"
			"AlbumID INTEGER,"
			"Path TEXT,"
			"Type TEXT,"
			"Size INTEGER,"
			"Resolution TEXT,"
			"LastAccessed DATETIME,"
			"ImportedAt DATETIME,"
			"FOREIGN KEY(AlbumID) REFERENCES Albums(ID)"
			");";

		QSqlQuery query;
		if (!query.exec(createAlbumsTable) || !query.exec(createImagesTable))
			return false;
	}
	if (!m_database.open())
		return false;
	return true;
}

bool DatabaseManager::addAlbum(const QString& name)
{
	return false;
}

DatabaseManager::DatabaseManager()
{

}

DatabaseManager* DatabaseManager::s_instance = nullptr;