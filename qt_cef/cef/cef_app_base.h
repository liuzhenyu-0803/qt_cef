#ifndef CEF_APP_BASE_H
#define CEF_APP_BASE_H


#include "include/cef_app.h"


class CefAppBase : public CefApp 
{
public:
    enum ProcessType 
    {
        BrowserProcess,
        RendererProcess,
        ZygoteProcess,
        OtherProcess,
    };

    static ProcessType GetProcessType(CefRefPtr<CefCommandLine> command_line);

    CefAppBase();
    ~CefAppBase();

private:
    DISALLOW_COPY_AND_ASSIGN(CefAppBase);
};


#endif  // CEF_APP_BASE_H
