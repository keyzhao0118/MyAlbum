#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DATABASEMANAGER_LIB)
#  define DATABASEMANAGER_EXPORT Q_DECL_EXPORT
# else
#  define DATABASEMANAGER_EXPORT Q_DECL_IMPORT
# endif
#else
# define DATABASEMANAGER_EXPORT
#endif
