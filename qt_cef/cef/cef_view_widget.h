#ifndef QT_CEF_VIEW_WIDGET_H
#define QT_CEF_VIEW_WIDGET_H


#include "cef/cef_app_browser.h"
#include "cef/cef_client_base.h"

#include <QtWidgets/QWidget>


// 退出应用时一定要在事件循环中delete CefViewWidget对象（使用delete而不是deleteLater或CloseBrowser），否则会崩溃
// 不能监听aboutToQuit信号，因为该信号发出后后续将退出事件循环，导致CefViewWidget对象中的Cef资源无法正常释放
class CefViewWidget : public QWidget
{
    Q_OBJECT

signals:
    void SignalReceiveJsMessage(QString func_name, QString func_param);

public:
    CefViewWidget(QWidget *parent = nullptr);
    ~CefViewWidget();

    void CallJsFunction(const QString &func_name, const QString &func_param);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void OnBrowserAfterCreated(CefRefPtr<CefBrowser> browser);
    void OnReceiveJsMessage(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId process_id, CefRefPtr<CefProcessMessage> process_message);

private:
    void CreateBrowser();

    void AdjustBrowserSize();

private:
    CefRefPtr<CefBrowser> cef_browser_;
    CefRefPtr<CefClientBase> cef_client_;
    QWidget *widget_;
};


#endif // QT_CEF_VIEW_WIDGET_H
