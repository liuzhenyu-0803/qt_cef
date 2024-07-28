#include "cef_view_widget.h"

#include "cef/cef_client_impl.h"
#include "qt_delare_metatype.h"

#include <QVBoxLayout>
#include <QWindow>
#include <QApplication>
#include <QMessageBox>

#include <QPainter>
#include <QTimer>


CefViewWidget::CefViewWidget(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    CreateBrowser();

    connect(qApp, &QApplication::aboutToQuit, this, [=] {
        CloseBrowser();
    });
}

CefViewWidget::~CefViewWidget()
{
    CloseBrowser();
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
        //cef_browser_->GetHost()->CloseBrowser(true);
        cef_browser_ = nullptr;

        //CefQuitMessageLoop();
    }
}

void CefViewWidget::showEvent(QShowEvent *event)
{
    //UpdateBrowserHostSize();

    QWidget::showEvent(event);
}

void CefViewWidget::resizeEvent(QResizeEvent *event)
{
    UpdateBrowserHostSize();

    QWidget::resizeEvent(event);
}

void CefViewWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.drawRect(0, 0, width(), height());
}

void CefViewWidget::OnCefClientAfterCreated(QVariant var_browser)
{
    cef_browser_ = var_browser.value<CefRefPtr<CefBrowser>>();

    UpdateBrowserHostSize();
}

void CefViewWidget::OnCefClientReceiveJsMessage(QVariant var_message)
{
    auto message = var_message.value<CefRefPtr<CefProcessMessage>>();

    auto function_name = message->GetName();
    auto arguments = message->GetArgumentList()->GetString(0);

    emit SignalReceiveJsMessage(QString::fromStdString(function_name.ToString()), QString::fromStdString(arguments.ToString()));

    QMessageBox::information(this, QString::fromStdString(function_name.ToString()), QString::fromStdString(function_name.ToString() + "\n" + arguments.ToString()));
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

    cef_client_ = new CefClientImpl(/*queryHandler nullptr*/);

    auto url = "https://www.baidu.com";
    //auto url = (QCoreApplication::applicationDirPath() + "/resources/test.html").toStdString();

    CefBrowserSettings browser_settings;

    CefBrowserHost::CreateBrowser(window_info, cef_client_, url, browser_settings,
        nullptr, nullptr);

    connect(cef_client_.get(), &CefClientImpl::SignalAfterCreated, this, &CefViewWidget::OnCefClientAfterCreated);
    connect(cef_client_.get(), &CefClientImpl::SignalReceiveJsMessage, this, &CefViewWidget::OnCefClientReceiveJsMessage);
}

void CefViewWidget::UpdateBrowserHostSize()
{
    if (cef_browser_)
    {
        ::MoveWindow(cef_browser_->GetHost()->GetWindowHandle(), 0, 0, (int)(width() * devicePixelRatioF()), (int)(height() * devicePixelRatioF()), true);
    }
}
