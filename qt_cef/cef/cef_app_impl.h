#ifndef CEF_APP_BASE_H
#define CEF_APP_BASE_H

#include <vector>

#include "include/cef_app.h"

class CefAppImpl : public CefApp 
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

    CefAppImpl();
    ~CefAppImpl();

private:

    DISALLOW_COPY_AND_ASSIGN(CefAppImpl);
};


#endif  // CEF_APP_BASE_H
