#ifndef CEF_CLIENT_BASE_H
#define CEF_CLIENT_BASE_H


#include <QObject>
#include <QVariant>
#include <list>

#include "include/cef_client.h"


class CefClientImpl :
    public QObject,
    public CefClient,
    public CefLifeSpanHandler,
    public CefKeyboardHandler,
    public CefRequestHandler
{
    Q_OBJECT

signals:
    void SignalAfterCreated(QVariant var_browser);
    void SignalReceiveJsMessage(QVariant var_message);

public:
    CefClientImpl();
    ~CefClientImpl();

    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override 
    {
        return this;
    }

    CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() override
    {
        return this;
    }

    virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefProcessId source_process,
        CefRefPtr<CefProcessMessage> message) override;

    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
    
    bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        const CefString &target_url,
        const CefString &target_frame_name,
        CefLifeSpanHandler::WindowOpenDisposition target_disposition,
        bool user_gesture,
        const CefPopupFeatures &popupFeatures,
        CefWindowInfo &windowInfo,
        CefRefPtr<CefClient> &client,
        CefBrowserSettings &settings,
        CefRefPtr<CefDictionaryValue> &extra_info,
        bool *no_javascript_access) override;

    bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
        const CefKeyEvent &event,
        CefEventHandle os_event,
        bool *is_keyboard_shortcut) override;


    //virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
    //    CefRefPtr<CefFrame> frame,
    //    CefRefPtr<CefRequest> request,
    //    bool user_gesture,
    //    bool is_redirect) override;

    //void ShowMainWindow();

private:
    //CefRefPtr<CefMessageRouterBrowserSide> m_message_router;
    //std::unique_ptr<CefMessageRouterBrowserSide::Handler> m_message_handler;

    IMPLEMENT_REFCOUNTING(CefClientImpl);
};

#endif  // CEF_CLIENT_BASE_H
