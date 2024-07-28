#include "cef_query_handler.h"

#include <QTimer>

bool CefQueryHandler::OnQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64_t query_id, const CefString &request, bool persistent, CefRefPtr<Callback> callback)
{
	const std::string &message_name = request;
	if (message_name == "my_request") {
		//这里需要将 对象和 callback对象暂时保存到map中
		//以便线程执行完毕之后，能够找到它们
		m_pendings.insert(std::make_pair(query_id, callback));
		// 发射信号给UI线程
		//emit  onReadFile(query_id);
		callback_ = callback;
		emit signalQuery();

		return true;
	}
	return false;
}

void CefQueryHandler::OnQueryCanceled(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64_t query_id)
{
	auto it = m_pendings.find(query_id);
	if (it != m_pendings.end())
	{
		it->second->Failure(-1, "canceled");
		m_pendings.erase(it);
	}
}

void CefQueryHandler::callback()
{
	callback_->Success("heha");
}
