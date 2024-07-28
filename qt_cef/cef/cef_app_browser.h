#ifndef CEF_APP_BROWSER_H
#define CEF_APP_BROWSER_H

#include "cef_app_impl.h"

#include <QObject>


class ClientAppBrowser : 
    public QObject, 
    public CefAppImpl, 
    public CefBrowserProcessHandler 
{
    Q_OBJECT

signals:
    void SignalContextInitialized();

public:
    ClientAppBrowser();
    ~ClientAppBrowser();

    // CefApp methods:
    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override 
    {
        return this;
    }

    // CefBrowserProcessHandler methods:
    void OnContextInitialized() override;

private:
    IMPLEMENT_REFCOUNTING(ClientAppBrowser);
};

#endif // CEF_APP_BROWSER_H
