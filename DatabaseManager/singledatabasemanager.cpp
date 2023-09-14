#include "singledatabasemanager.h"
#include <QFile>
#include <QSqlQuery>
#include <QDateTime>

namespace 
{

QString createAlbumsTableSQL = "CREATE TABLE IF NOT EXISTS Albums ("
	"ID INTEGER PRIMARY KEY,"
	"Name TEXT UNIQUE,"
	"CoverPath TEXT,"
	"LastAccessed DATETIME,"
	"CreatedAt DATETIME"
	");";

QString createImagesTableSQL = "CREATE TABLE IF NOT EXISTS Images ("
	"ID INTEGER PRIMARY KEY,"
	"AlbumID INTEGER,"
	"Path TEXT,"
	"Format TEXT,"
	"Size INTEGER,"
	"Resolution TEXT,"
	"LastAccessed DATETIME NULL,"
	"ImportedAt DATETIME,"
	"FOREIGN KEY(AlbumID) REFERENCES Albums(ID) ON DELETE CASCADE"
	");";

QString insertAlbumSQL = "INSERT INTO Albums (Name, CoverPath, LastAccessed, CreatedAt) "
	"VALUES (:name, :coverPath, :lastAccessed, :createdAt)";

QString insertImageSQL = "INSERT INTO Images (AlbumID, Path, Format, Size, Resolution, LastAccessed, ImportedAt) "
	"VALUES (:albumID, :path, :format, :size, :resolution, :lastAccessed, :importedAt)";

QString deleteAlbumSQL = "DELETE FROM Albums WHERE ID = :albumID";

QString deleteImageSQL = "DELETE FROM Images WHERE ID = :imageID";

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
		if (!query.exec(createAlbumsTableSQL) || !query.exec(createImagesTableSQL))
			return false;
		//添加默认相册和图片
		QDateTime curDateTime = QDateTime::currentDateTime();
		int albumID = insertAlbum("示例相册", curDateTime, curDateTime);
		if (0 == albumID)
			return false;
		return insertImage(albumID, ":/PreviewScene/image/示例图片/11月的萧邦_周杰伦.png", "PNG", 0, "", curDateTime) &&
			insertImage(albumID, ":/PreviewScene/image/示例图片/八度空间_周杰伦.png", "PNG", 0, "", curDateTime) &&
			insertImage(albumID, ":/PreviewScene/image/示例图片/范特西_周杰伦.png", "PNG", 0, "", curDateTime);

	}
	//已经存在数据库文件，直接打开
	return m_database.open();
}

void DatabaseManager::closeDatabase()
{
	m_database.close();
}

int DatabaseManager::insertAlbum(const QString& name, const QDateTime& lastAccessed, 
	const QDateTime& createdAt)
{
	QSqlQuery query;
	query.prepare(insertAlbumSQL);
	query.bindValue(":name", name);
	query.bindValue(":coverPath", "");
	query.bindValue(":lastAccessed", lastAccessed);
	query.bindValue(":createdAt", createdAt);
	if (!query.exec())
		return 0;
	return query.lastInsertId().toInt();
}

int DatabaseManager::insertImage(int albumID, const QString& path, const QString& format, int size,
	const QString& resolution, const QDateTime& importedAt)
{
	QSqlQuery query;
	query.prepare(insertImageSQL);
	query.bindValue(":albumID", albumID);
	query.bindValue(":path", path);
	query.bindValue(":format", format);
	query.bindValue(":size", size);
	query.bindValue(":resolution", resolution);
	query.bindValue(":importedAt", importedAt);
	if (!query.exec())
		return 0;
	return query.lastInsertId().toInt();
}

bool DatabaseManager::deleteAlbum(int albumID)
{
	QSqlQuery query;
	query.prepare(deleteAlbumSQL);
	query.bindValue(":albumID", albumID);
	return query.exec();
}

bool DatabaseManager::deleteImage(int imageID)
{
	QSqlQuery query;
	query.prepare(deleteImageSQL);
	query.bindValue(":imageID", imageID);
	return query.exec();
}

int DatabaseManager::selectLastAccessedAlbumID()
{
	QSqlQuery query;
	if (!query.exec("SELECT ID FROM Albums ORDER BY lastAccessed DESC LIMIT 1") ||
		!query.next())
		return 0;
	return query.value("ID").toInt();

}

QSqlQuery DatabaseManager::selectImagesWithAlbumID(int albumID, int format, int sortType)
{
	QSqlQuery query;
	switch (format)
	{
	case 0:
		query.prepare("SELECT * FROM Images ORDER BY :sortType");
		break;
	case 1:
		query.prepare("SELECT * FROM Images WHERE Format = 'JPG' ORDER BY :sortType");
		break;
	case 2:
		query.prepare("SELECT * FROM Images WHERE Format = 'PNG' ORDER BY :sortType");
		break;
	case 3:
		query.prepare("SELECT * FROM Images WHERE Format = 'GIF' ORDER BY :sortType");
		break;
	case 4:
		query.prepare("SELECT * FROM Images WHERE Format NOT IN ('JPG','PNG','GIF') ORDER BY :sortType");
		break;
	default:
		query.prepare("SELECT * FROM Images ORDER BY :sortType");
	}
	
	switch (sortType)
	{
	case 0:
		query.bindValue(":sortType", "LastAccessed");
		break;
	case 2:
		query.bindValue(":sortType", "ImportedAt");
		break;
	default:
		query.bindValue(":sortType", "LastAccessed");
	}

	query.exec();
	return query;
}

QSqlQuery DatabaseManager::selectAllAlbums(int sortType)
{
	QSqlQuery query;
	query.prepare("SELECT * FROM Albums ORDER BY :sortType");
	switch (sortType)
	{
	case 0:
		query.bindValue(":sortType", "LastAccessed");
		break;
	case 1:
		query.bindValue(":sortType", "CreatedAt");
		break;
	default:
		query.bindValue(":sortType", "ID");
	}
	query.exec();
	return query;
}

DatabaseManager::DatabaseManager()
{

}

DatabaseManager* DatabaseManager::s_instance = nullptr;