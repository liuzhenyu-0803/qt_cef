#ifndef CEF_APP_BROWSER_H
#define CEF_APP_BROWSER_H


#include "cef_app_base.h"

#include <QObject>


class ClientAppBrowser : 
    public QObject, 
    public CefAppBase
{
    Q_OBJECT

public:
    ClientAppBrowser();
    ~ClientAppBrowser();


private:
    IMPLEMENT_REFCOUNTING(ClientAppBrowser);
};


#endif // CEF_APP_BROWSER_H
