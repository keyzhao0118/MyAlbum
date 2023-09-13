#pragma once

#include "databasemanager_global.h"
#include <QDateTime>
#include <QSqlQuery>

extern "C" {
	DATABASEMANAGER_EXPORT bool OpenDatabase(const QString& databaseFilePath);
	DATABASEMANAGER_EXPORT void CloseDatabase();

	DATABASEMANAGER_EXPORT int InsertAlbum(const QString& name, const QDateTime& lastAccessed, const QDateTime& createdAt);
	DATABASEMANAGER_EXPORT int InsertImage(int albumID, const QString& path, const QString& format, int size,
		const QString& resolution, const QDateTime& importedAt);
	
	DATABASEMANAGER_EXPORT bool DeleteAlbum(int albumID);
	DATABASEMANAGER_EXPORT bool DeleteImage(int imageID);

	DATABASEMANAGER_EXPORT int SelectLastAccessedAlbumID();
	DATABASEMANAGER_EXPORT QSqlQuery SelectImagesWithAlbumID(int albumID, int format, int sortType);
	DATABASEMANAGER_EXPORT QSqlQuery SelectAllAlbums(int sortType);

}