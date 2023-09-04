#pragma once

#include "databasemanager_global.h"

extern "C" {
	bool DATABASEMANAGER_EXPORT OpenDatabase(const QString& databaseFilePath);
	bool DATABASEMANAGER_EXPORT AddAlbum(const QString& name);
}