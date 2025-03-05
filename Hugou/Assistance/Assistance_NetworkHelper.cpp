#include "Assistance/Include/Assistance_NetworkHelper.h"

NetworkHelper* NetworkHelper::getHelper()
{
	static NetworkHelper helper;
	return &helper;
}

QString NetworkHelper::dealNetWorkReply(QNetworkReply* reply, DealReplyMode mode)
{
	switch (reply->error())
	{
	case QNetworkReply::NoError:
		return QString::fromLocal8Bit(reply->readAll());
	default:
		if (mode == DealReplyMode::AcknowledgeError)
			emit MessegeHelper::getHelper()->trigger(FloatingNote::Error, m_errorMap[reply->error()]);
		return "";
	};
}