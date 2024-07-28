#include "app.h"
#include "main_window.h"

#include "cef/cef_global_define.h"

#include "cef/cef_app_browser.h"
#include "cef/cef_app_render.h"

#include <QtWidgets/QApplication>


int main(int argc, char* argv[])
{
    CefMainArgs main_args(GetModuleHandle(nullptr));

    CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
    command_line->InitFromString(::GetCommandLineW());

    CefRefPtr<CefApp> app;
    switch (CefAppBase::GetProcessType(command_line))
    {
    case CefAppBase::BrowserProcess:
        app = new ClientAppBrowser();
        break;
    case CefAppBase::RendererProcess:
        app = new ClientAppRender();
        break;
    default:
        break;
    }

    int exit_code = CefExecuteProcess(main_args, app, nullptr);
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

    RegisterCefMetaType();

    QApplication::setQuitOnLastWindowClosed(false);

    App a(argc, argv);
    MainWindow w;
    w.resize(1600, 1200);
    w.show();
    a.exec();

    CefShutdown();

    return 0;
}
