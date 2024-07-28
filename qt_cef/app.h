#ifndef APP_H
#define APP_H


#include <QApplication>


class App : public QApplication
{
    Q_OBJECT

signals:
    void SignalBeforeQuit();

public:
    App(int &argc, char **argv);
    ~App();

    static App *GetInstance()
    {
        return qobject_cast<App *>(qApp);
    }

    void Quit();

protected:
    

private:
    
};


#endif // APP_H
