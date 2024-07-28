#ifndef QT_CEF_VIEW_WIDGET_H
#define QT_CEF_VIEW_WIDGET_H


#include "cef/cef_app_browser.h"
#include "cef/cef_client_impl.h"

#include <QtWidgets/QWidget>


class CefViewWidget : public QWidget
{
    Q_OBJECT

signals:
    void SignalReceiveJsMessage(QString func_name, QString func_param);

public:
    CefViewWidget(QWidget *parent = nullptr);
    ~CefViewWidget();

    void CallJsFunction(const QString &func_name, const QString &func_param);

    void CloseBrowser();

protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void OnCefClientAfterCreated(QVariant var_browser);
    void OnCefClientReceiveJsMessage(QVariant var_messsage);

private:
    void CreateBrowser();
    void UpdateBrowserHostSize();

private:
    CefRefPtr<CefBrowser> cef_browser_;
    CefRefPtr<CefClientImpl> cef_client_;
};


#endif // QT_CEF_VIEW_WIDGET_H
