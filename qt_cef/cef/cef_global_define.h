#ifndef CEF_GLOBAL_DEFINE_H
#define CEF_GLOBAL_DEFINE_H


#include "include/cef_browser.h"
#include "include/cef_frame.h"
#include "include/cef_process_message.h"

#include <QMetaType>


Q_DECLARE_METATYPE(CefRefPtr<CefBrowser>)
Q_DECLARE_METATYPE(CefRefPtr<CefFrame>)
Q_DECLARE_METATYPE(CefProcessId)
Q_DECLARE_METATYPE(CefRefPtr<CefProcessMessage>)


static void RegisterCefMetaType()
{
    qRegisterMetaType<CefRefPtr<CefBrowser>>("CefRefPtr<CefBrowser>");
    qRegisterMetaType<CefRefPtr<CefFrame>>("CefRefPtr<CefFrame>");
    qRegisterMetaType<CefProcessId>("CefProcessId");
    qRegisterMetaType<CefRefPtr<CefProcessMessage>>("CefRefPtr<CefProcessMessage>");
}


const char *const RENDER_TO_BROWSER_PROCESS_MESSAGE = "RenderToBrowserProcessMessage";


#endif // CEF_GLOBAL_DEFINE_H
