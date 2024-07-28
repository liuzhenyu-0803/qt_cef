#include "main_window.h"

#include "cef/cef_view_widget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QCloseEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    ui_.setupUi(this);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    auto cef_view_widget = new CefViewWidget(this);
    layout->addWidget(cef_view_widget);

    auto call_js_function = new QPushButton("Call JS function", this);
    connect(call_js_function, &QPushButton::clicked, [cef_view_widget]() {
        cef_view_widget->CallJsFunction("test", "Hello from C++");
    });

    auto button = new QPushButton("Close", this);
    layout->addWidget(button);

    //connect(button, &QPushButton::clicked, [=]() {
    //    cef_view_widget->deleteLater();
    //});
}

MainWindow::~MainWindow()
{}

void MainWindow::closeEvent(QCloseEvent * event)
{
    QWidget::closeEvent(event);

    //event->ignore();

    // 找到 CefViewWidget 对象，调用 CloseBrowser 方法
    //auto cef_view_widget = findChild<CefViewWidget*>();
    //if (cef_view_widget)
    //{
    //    cef_view_widget->CloseBrowser();
    //}

    //QTimer::singleShot(0, this, [=] {
    //    qApp->quit();
    //});
}
