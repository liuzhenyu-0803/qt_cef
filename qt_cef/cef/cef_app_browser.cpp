#include "cef_app_browser.h"

#include <string>

#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
#include "cef/cef_client_impl.h"


ClientAppBrowser::ClientAppBrowser()
{

}

ClientAppBrowser::~ClientAppBrowser()
{

}

void ClientAppBrowser::OnContextInitialized()
{
  CEF_REQUIRE_UI_THREAD();

  emit SignalContextInitialized();
}