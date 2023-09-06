#pragma once

#include "databasemanager_global.h"

extern "C" {
	bool DATABASEMANAGER_EXPORT OpenDatabase(const QString& databaseFilePath);
	void DATABASEMANAGER_EXPORT CloseDatabase();
	int DATABASEMANAGER_EXPORT AddAlbum(const QString& name);
	int DATABASEMANAGER_EXPORT AddImage(int albumID, const QString& path);
}