#pragma once

#include "databasemanager_global.h"

extern "C" {
	bool DATABASEMANAGER_EXPORT OpenDatabase(const QString& databaseFilePath);
	void DATABASEMANAGER_EXPORT CloseDatabase();
	bool DATABASEMANAGER_EXPORT AddAlbum(const QString& name);
	bool DATABASEMANAGER_EXPORT AddImage(const QString& path);
}