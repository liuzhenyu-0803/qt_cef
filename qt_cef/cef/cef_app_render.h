#ifndef CEF_APP_RENDER_H_
#define CEF_APP_RENDER_H_


#include "cef_app_impl.h"
#include "include/wrapper/cef_message_router.h"


class ClientAppRender : public CefAppImpl, public CefRenderProcessHandler 
{
public:
    ClientAppRender();

	CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override 
	{
		return this;
	}

	void OnWebKitInitialized() override;

	void OnBrowserCreated(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDictionaryValue> extra_info) override;

	void OnContextCreated(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context) override;

	void OnContextReleased(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context) override;

	bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message);

private:
	CefRefPtr<CefMessageRouterRendererSide> m_message_router;

    IMPLEMENT_REFCOUNTING(ClientAppRender);
};


#endif  // CEF_APP_RENDER_H_
