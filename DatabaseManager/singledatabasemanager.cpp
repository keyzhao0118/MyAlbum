#include "singledatabasemanager.h"
#include <QFile>
#include <QSqlQuery>
#include <QDateTime>

namespace 
{

QString createAlbumsTable = "CREATE TABLE IF NOT EXISTS Albums ("
	"ID INTEGER PRIMARY KEY,"
	"Name TEXT UNIQUE,"
	"CoverID INTEGER NULL,"
	"LastAccessed DATETIME,"
	"CreatedAt DATETIME,"
	"FOREIGN KEY(CoverID) REFERENCES Images(ID)"
	");";

QString createImagesTable = "CREATE TABLE IF NOT EXISTS Images ("
	"ID INTEGER PRIMARY KEY,"
	"AlbumID INTEGER,"
	"Path TEXT UNIQUE,"
	"Type TEXT NULL,"
	"Size INTEGER NULL,"
	"Resolution TEXT NULL,"
	"LastAccessed DATETIME NULL,"
	"ImportedAt DATETIME,"
	"FOREIGN KEY(AlbumID) REFERENCES Albums(ID)"
	");";

QString insertAlbum = "INSERT INTO Albums (Name, LastAccessed, CreatedAt) "
"VALUES (:name, :lastAccessed, :createdAt)";

QString insertImage = "INSERT INTO Images (AlbumID, Path, Type, Size, Resolution, LastAccessed, ImportedAt) "
"VALUES (:albumID, :path, :type, :size, :resolution, :lastAccessed, :importedAt)";

}

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
		//如果数据库文件不存在，则创建一个数据库文件并且初始化两张表
		QFile databaseFile(databaseFilePath);
		if (!databaseFile.open(QIODevice::WriteOnly))
			return false;
		databaseFile.close();

		if (!m_database.open())
			return false;
		QSqlQuery query;
		if (!query.exec(createAlbumsTable) || !query.exec(createImagesTable))
			return false;
		//添加默认相册和图片
		int albumID = addAlbum("示例相册");
		if (0 == albumID)
			return false;
		return addImage(albumID, ":/PreviewScene/image/示例图片/11月的萧邦_周杰伦.png") &&
			addImage(albumID, ":/PreviewScene/image/示例图片/八度空间_周杰伦.png") &&
			addImage(albumID, ":/PreviewScene/image/示例图片/范特西_周杰伦.png");

	}
	//已经存在数据库文件，直接打开
	return m_database.open();
}

void DatabaseManager::closeDatabase()
{
	m_database.close();
}

int DatabaseManager::addAlbum(const QString& name)
{
	QSqlQuery query;
	query.prepare(insertAlbum);
	query.bindValue(":name", "示例相册");
	query.bindValue(":lastAccessed", QDateTime::currentDateTime());
	query.bindValue(":createdAt", QDateTime::currentDateTime());
	if (!query.exec())
		return 0;
	query.clear();
	query.prepare("SELECT ID FROM Albums WHERE Name = :name");
	query.bindValue(":name", name);
	if (!query.exec() || !query.next())
		return 0;
	return query.value("ID").toInt();
}

int DatabaseManager::addImage(int albumID, const QString& path)
{
	QSqlQuery query;
	query.prepare(insertImage);
	query.bindValue(":albumID", albumID);
	query.bindValue(":path", path);
	query.bindValue(":importedAt", QDateTime::currentDateTime());
	if (!query.exec())
		return 0;
	query.clear();
	query.prepare("SELECT ID FROM Images WHERE Path = :path");
	query.bindValue(":path", path);
	if (!query.exec() || !query.next())
		return 0;
	return query.value("ID").toInt();
}

DatabaseManager::DatabaseManager()
{

}

DatabaseManager* DatabaseManager::s_instance = nullptr;