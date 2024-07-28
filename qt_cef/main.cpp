#include "main_window.h"

#include "qt_delare_metatype.h"

#include "cef/cef_app_impl.h"
#include "cef/cef_app_browser.h"
#include "cef/cef_app_render.h"

#include <QtWidgets/QApplication>


int main(int argc, char* argv[])
{
    CefMainArgs main_args(GetModuleHandle(nullptr));

    CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
    command_line->InitFromString(::GetCommandLineW());

    CefRefPtr<CefApp> app;
    switch (CefAppImpl::GetProcessType(command_line))
    {
    case CefAppImpl::BrowserProcess:
        app = new ClientAppBrowser();
        break;
    case CefAppImpl::RendererProcess:
        app = new ClientAppRender();
        break;
    default:
        break;
    }

    int exit_code = CefExecuteProcess(main_args, nullptr, nullptr);
    if (exit_code >= 0)
    {
        return exit_code;
    }

    CefSettings settings;
    settings.multi_threaded_message_loop = true;

    if (!CefInitialize(main_args, settings, app.get(), nullptr))
    {
        return CefGetExitCode();
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();

    CefShutdown();

    return 0;
}
