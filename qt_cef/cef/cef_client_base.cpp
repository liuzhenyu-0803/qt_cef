#include "cef_client_base.h"

#include <sstream>
#include <string>

#include "include/base/cef_callback.h"
#include "include/cef_app.h"
#include "include/cef_parser.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "log/log.h"


CefClientBase::CefClientBase()
{

}

CefClientBase::~CefClientBase()
{
}

bool CefClientBase::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
    emit SignalReceiveJsMessage(browser, frame, source_process, message);

    return true;

    //CefRefPtr<CefProcessMessage> msg_send = CefProcessMessage::Create("CefClientBase::OnProcessMessageReceived");
    //CefRefPtr<CefListValue> msg_args = msg_send->GetArgumentList();
    //msg_args->SetString(0, "string_param");
    //frame->SendProcessMessage(PID_RENDERER, msg_send);
}

//
//void CefClientBase::OnTitleChange(CefRefPtr<CefBrowser> browser,
//    const CefString &title) {
//    CEF_REQUIRE_UI_THREAD();
//
//    if (auto browser_view = CefBrowserView::GetForBrowser(browser)) {
//        // Set the title of the window using the Views framework.
//        CefRefPtr<CefWindow> window = browser_view->GetWindow();
//        if (window) {
//            window->SetTitle(title);
//        }
//    }
//    else if (is_alloy_style_) {
//        // Set the title of the window using platform APIs.
//        PlatformTitleChange(browser, title);
//    }
//}
//
void CefClientBase::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();

    emit SignalAfterCreated(browser);

    //// Add to the list of existing browsers.
    //browser_list_.push_back(browser);

    //if (!m_message_router) {
    //    // browser进程侧 消息路由配置, renderer进程中JavaScript发出消息和取消消息使用 
    //    // window.cefQuery 和 window.cefQueryCancel , 如果不想使用这两个名字，可以在这里配置
    //    CefMessageRouterConfig config;
    //    //    config.js_query_function = "cefQuery";
    //    //    config.js_cancel_function = "cefQueryCancel";
    //    m_message_router = CefMessageRouterBrowserSide::Create(config);
    //    // 为消息路由设置 消息处理器，即从 render进程发送过来的消息交给谁处理。
    //    m_message_router->AddHandler(m_message_handler.get(), false);
    //}
}
bool CefClientBase::OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString &target_url, const CefString &target_frame_name, CefLifeSpanHandler::WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures &popupFeatures, CefWindowInfo &windowInfo, CefRefPtr<CefClient> &client, CefBrowserSettings &settings, CefRefPtr<CefDictionaryValue> &extra_info, bool *no_javascript_access)
{
    if (!target_url.empty())
    {
        frame->LoadURL(target_url);
    }

    return true;
}
//
//bool CefClientBase::DoClose(CefRefPtr<CefBrowser> browser) {
//    CEF_REQUIRE_UI_THREAD();
//
//    // Closing the main window requires special handling. See the DoClose()
//    // documentation in the CEF header for a detailed destription of this
//    // process.
//    if (browser_list_.size() == 1) {
//        // Set a flag to indicate that the window close should be allowed.
//        is_closing_ = true;
//    }
//
//    // Allow the close. For windowed browsers this will result in the OS close
//    // event being sent.
//    return false;
//}
//
//void CefClientBase::OnBeforeClose(CefRefPtr<CefBrowser> browser)
//{
//    CEF_REQUIRE_UI_THREAD();
//
//    CefQuitMessageLoop();
//}
//
//bool CefClientBase::OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString &target_url, const CefString &target_frame_name, CefLifeSpanHandler::WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures &popupFeatures, CefWindowInfo &windowInfo, CefRefPtr<CefClient> &client, CefBrowserSettings &settings, CefRefPtr<CefDictionaryValue> &extra_info, bool *no_javascript_access)
//{
//    CEF_REQUIRE_UI_THREAD();
//
//    if (!target_url.empty())
//    {
//        browser->GetMainFrame()->LoadURL(target_url);
//        return true;
//    }
//    return false;
//}
//
//void CefClientBase::OnLoadError(CefRefPtr<CefBrowser> browser,
//    CefRefPtr<CefFrame> frame,
//    ErrorCode errorCode,
//    const CefString &errorText,
//    const CefString &failedUrl) {
//    CEF_REQUIRE_UI_THREAD();
//
//    // Allow Chrome to show the error page.
//    if (!is_alloy_style_) {
//        return;
//    }
//
//    // Don't display an error for downloaded files.
//    if (errorCode == ERR_ABORTED) {
//        return;
//    }
//
//    // Display a load error message using a data: URI.
//    std::stringstream ss;
//    ss << "<html><body bgcolor=\"white\">"
//        "<h2>Failed to load URL "
//        << std::string(failedUrl) << " with error " << std::string(errorText)
//        << " (" << errorCode << ").</h2></body></html>";
//
//    frame->LoadURL(GetDataURI(ss.str(), "text/html"));
//}
//
bool CefClientBase::OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent &event, CefEventHandle os_event, bool *is_keyboard_shortcut)
{
    if (event.type == KEYEVENT_RAWKEYDOWN && (event.modifiers & EVENTFLAG_ALT_DOWN) && (event.modifiers & EVENTFLAG_CONTROL_DOWN)) {
        switch (event.windows_key_code) {
        case 'D': 
            CefWindowInfo windowInfo;
            CefBrowserSettings settings;
            windowInfo.SetAsPopup(NULL, "Dev Tools");
            browser->GetHost()->ShowDevTools(windowInfo, this, settings, CefPoint());
            return true;
        }
    }
    return CefKeyboardHandler::OnPreKeyEvent(browser, event, os_event, is_keyboard_shortcut);
}
//
//bool CefClientBase::OnBeforeBrowse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool user_gesture, bool is_redirect)
//{
//    m_message_router->OnBeforeBrowse(browser, frame);
//    return false;
//}
//
//void CefClientBase::ShowMainWindow() {
//    if (!CefCurrentlyOn(TID_UI)) {
//        // Execute on the UI thread.
//        CefPostTask(TID_UI, base::BindOnce(&CefClientBase::ShowMainWindow, this));
//        return;
//    }
//
//    if (browser_list_.empty()) {
//        return;
//    }
//
//    auto main_browser = browser_list_.front();
//
//    if (auto browser_view = CefBrowserView::GetForBrowser(main_browser)) {
//        // Show the window using the Views framework.
//        if (auto window = browser_view->GetWindow()) {
//            window->Show();
//        }
//    }
//    else if (is_alloy_style_) {
//        PlatformShowWindow(main_browser);
//    }
//}
//
//void CefClientBase::CloseAllBrowsers(bool force_close) {
//    if (!CefCurrentlyOn(TID_UI)) {
//        // Execute on the UI thread.
//        CefPostTask(TID_UI, base::BindOnce(&CefClientBase::CloseAllBrowsers, this,
//            force_close));
//        return;
//    }
//
//    if (browser_list_.empty()) {
//        return;
//    }
//
//    BrowserList::const_iterator it = browser_list_.begin();
//    for (; it != browser_list_.end(); ++it) {
//        (*it)->GetHost()->CloseBrowser(force_close);
//    }
//}
//
//HWND CefClientBase::getBrowserWindowHandle()
//{
//    if (!browser_list_.empty()) { //如果集合不为空
//        // 获取集合中的第一个 CefBrowser元素 ,获取它的 CefBrowserHost 对象，然后再获取CefBrowserHost 对象中的 WindowHandle 即窗口句柄
//        return  browser_list_.front()->GetHost()->GetWindowHandle();
//    }
//    return NULL;
//}
//
//#if !defined(OS_MAC)
//void CefClientBase::PlatformTitleChange(CefRefPtr<CefBrowser> browser, const CefString &title)
//{
//}
//void CefClientBase::PlatformShowWindow(CefRefPtr<CefBrowser> browser) {
//    NOTIMPLEMENTED();
//}
//#endif
