#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CACHEMANAGER_LIB)
#  define CACHEMANAGER_EXPORT Q_DECL_EXPORT
# else
#  define CACHEMANAGER_EXPORT Q_DECL_IMPORT
# endif
#else
# define CACHEMANAGER_EXPORT
#endif
