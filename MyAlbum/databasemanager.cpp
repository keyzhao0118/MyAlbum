#include "databasemanager.h"

DatabaseManager::DatabaseManager(const QString& databaseFilePath)
	: m_databaseFilePath(databaseFilePath)
{
}

bool DatabaseManager::initDatabase()
{
	if (!QFile::exists(m_databaseFilePath))
	{
		QFile databaseFile(m_databaseFilePath);
		if (!databaseFile.open(QIODevice::WriteOnly))
			return false;
		else
			databaseFile.close();
		//ToDo：初始化数据库内容，创建相册信息的数据表
		
	}
	//ToDo：打开数据库并进行关联
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName(m_databaseFilePath);
	if (!m_db.open())
		return false;
	return true;

}