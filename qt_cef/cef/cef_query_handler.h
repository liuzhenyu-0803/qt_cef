#pragma once

#include <QObject>

#include "include/wrapper/cef_message_router.h"


class CefQueryHandler : public QObject, 
	public CefMessageRouterBrowserSide::Handler
{
	Q_OBJECT

signals:
	void signalQuery();

public:
	explicit CefQueryHandler() {
	}

	virtual bool OnQuery(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		int64_t query_id,
		const CefString &request,
		bool persistent,
		CefRefPtr<Callback> callback) override;

	virtual void OnQueryCanceled(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		int64_t query_id)  override;

	void callback();

private:
	// 用来保存 query_id 和 callback之间的映射关系
	std::map<int64_t, CefRefPtr<Callback>> m_pendings;
	CefRefPtr<Callback> callback_;
};
