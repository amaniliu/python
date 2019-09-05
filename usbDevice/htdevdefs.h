#ifndef HTDEFS_H
#define HTDEFS_H

#if defined(QT_VERSION)
#   include <qglobal.h>
#   if defined(HTDEVICE_LIBRARY)
#       define HTDEVICE_SHARED_EXPORT Q_DECL_EXPORT
#   else
#       define HTDEVICE_SHARED_EXPORT Q_DECL_IMPORT
#   endif
#else
#   if defined(HTDEVICE_LIBRARY)
#       define HTDEVICE_SHARED_EXPORT __declspec(dllexport)
#   else
#       define HTDEVICE_SHARED_EXPORT __declspec(dllimport)
#   endif
#endif

#endif // HTDEFS_H
