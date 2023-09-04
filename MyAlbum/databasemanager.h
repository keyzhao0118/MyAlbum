#pragma once

#include <QString>
#include <qdir.h>
#include <QtSql/qsqldatabase.h>

class DatabaseManager
{
public:
	explicit DatabaseManager(const QString& databasePath);
	bool initDatabase();

private:
	QString m_databaseFilePath;
	QSqlDatabase m_db;
};

