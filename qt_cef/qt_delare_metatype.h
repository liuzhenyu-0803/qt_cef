#ifndef QT_DECLARE_METATYPE
#define QT_DECLARE_METATYPE


#include "include/cef_browser.h"
#include "include/cef_process_message.h"

#include <QMetaType>


Q_DECLARE_METATYPE(CefRefPtr<CefBrowser>)
Q_DECLARE_METATYPE(CefRefPtr<CefProcessMessage>)


#endif
