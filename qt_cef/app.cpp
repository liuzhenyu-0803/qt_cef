#include "app.h"


App::App(int &argc, char **argv)
    : QApplication(argc, argv)
{
}

App::~App()
{
}

void App::Quit()
{
    emit SignalBeforeQuit();

    quit();
}
