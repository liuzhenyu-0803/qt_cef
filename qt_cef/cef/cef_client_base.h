#ifndef CEF_CLIENT_BASE_H
#define CEF_CLIENT_BASE_H


#include <QObject>
#include <QVariant>
#include <list>

#include "include/cef_client.h"


class CefClientBase :
    public QObject,
    public CefClient,
    public CefLifeSpanHandler,
    public CefKeyboardHandler,
    public CefRequestHandler
{
    Q_OBJECT

signals:
    void SignalAfterCreated(CefRefPtr<CefBrowser> browser);
    void SignalReceiveJsMessage(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId process_id, CefRefPtr<CefProcessMessage> process_message);
    void SignalOnBeforeClose(CefRefPtr<CefBrowser> browser);

public:
    CefClientBase();
    ~CefClientBase();

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

    virtual bool DoClose(CefRefPtr<CefBrowser> browser) { return true; }


private:
    //CefRefPtr<CefMessageRouterBrowserSide> m_message_router;
    //std::unique_ptr<CefMessageRouterBrowserSide::Handler> m_message_handler;

    IMPLEMENT_REFCOUNTING(CefClientBase);
};


#endif  // CEF_CLIENT_BASE_H
