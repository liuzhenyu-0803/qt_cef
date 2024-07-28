#include "cef_view_widget.h"

#include "app.h"
#include "cef/cef_client_base.h"

#include <QVBoxLayout>
#include <QWindow>
#include <QApplication>
#include <QMessageBox>
#include <QWindow>

#include <QPainter>
#include <QTimer>
#include <QLabel>


CefViewWidget::CefViewWidget(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    connect(App::GetInstance(), &App::SignalBeforeQuit, this, [=] {
        delete this;
    });

    //connect(qApp, &QApplication::aboutToQuit, this, [=] {
    //    delete this;
    //});

    CreateBrowser();
}

CefViewWidget::~CefViewWidget()
{

}

void CefViewWidget::CallJsFunction(const QString &func_name, const QString &func_param)
{
    if (cef_browser_)
    {
        if (auto frame = cef_browser_->GetMainFrame())
        {
            auto code = QString("callJsFunction('%1');").arg(func_name).toStdString();

            cef_browser_->GetMainFrame()->ExecuteJavaScript(code, frame->GetURL(), 0);
        }
    }
}

void CefViewWidget::CloseBrowser()
{
    if (cef_browser_)
    {
        cef_browser_ = nullptr;
    }

    if (cef_client_)
    {
        cef_client_ = nullptr;
    }
}

void CefViewWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.drawRect(rect());
}

void CefViewWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    AdjustBrowserSize();
}

void CefViewWidget::OnBrowserAfterCreated(CefRefPtr<CefBrowser> browser)
{
    cef_browser_ = browser;

    AdjustBrowserSize();
}

void CefViewWidget::OnReceiveJsMessage(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId process_id, CefRefPtr<CefProcessMessage> process_message)
{
    auto function_name = process_message->GetName();

    auto argument = process_message->GetArgumentList()->GetString(0);

    emit SignalReceiveJsMessage(QString::fromStdString(function_name.ToString()), QString::fromStdString(argument.ToString()));

    QLabel *label = new QLabel(this);
    label->setText(QString::fromStdString(function_name.ToString()) + " : " + QString::fromStdString(argument.ToString()));

    QTimer::singleShot(4000, [=] {
        QMessageBox::information(this, QString::fromStdString(function_name.ToString()), QString::fromStdString(argument.ToString()));
    });
}

void CefViewWidget::CreateBrowser()
{
    CefWindowInfo window_info;
    window_info.SetAsChild((HWND)winId(), { 0, 0, (int)(width() * devicePixelRatioF()), (int)(height() * devicePixelRatioF()) });

    // SimpleHandler implements browser-level callbacks.
    //auto queryHandler = new CefQueryHandler;
    //connect(queryHandler, &CefQueryHandler::signalQuery, this, [=] {
    //    queryHandler->callback();
    //});

    cef_client_ = new CefClientBase(/*queryHandler nullptr*/);

    //auto url = "https://www.baidu.com";
    auto url = (QCoreApplication::applicationDirPath() + "/test.html").toStdString();

    CefBrowserSettings browser_settings;

    CefBrowserHost::CreateBrowser(window_info, cef_client_, url, browser_settings,
        nullptr, nullptr);

    connect(cef_client_.get(), &CefClientBase::SignalAfterCreated, this, &CefViewWidget::OnBrowserAfterCreated);
    connect(cef_client_.get(), &CefClientBase::SignalReceiveJsMessage, this, &CefViewWidget::OnReceiveJsMessage);
}

void CefViewWidget::AdjustBrowserSize()
{
    if (cef_browser_)
    {
        ::MoveWindow(cef_browser_->GetHost()->GetWindowHandle(), 0, 0, (int)(width() * devicePixelRatioF()), (int)(height() * devicePixelRatioF()), true);
    }
}

