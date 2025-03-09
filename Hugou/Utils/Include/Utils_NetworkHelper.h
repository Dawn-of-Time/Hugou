#pragma once
#include <QObject>
#include <QNetworkReply>
#include <QNetWorkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QUrl>
#include <QMap>
#include "Utils_MessegeHelper.h"

class NetworkHelper :
    public QObject
{
    Q_OBJECT

public:
    enum DealReplyMode
    {
        AcknowledgeError, IgnoreError
    };
    static NetworkHelper* getHelper();
    QString dealNetWorkReply(QNetworkReply* reply, DealReplyMode mode = DealReplyMode::AcknowledgeError);

private:
    NetworkHelper() {};
    NetworkHelper(const NetworkHelper&) = delete;
    NetworkHelper& operator=(const NetworkHelper&) = delete;

    const QMap<QNetworkReply::NetworkError, int> m_errorMap =
    {
        {QNetworkReply::ConnectionRefusedError, 30000},
        {QNetworkReply::RemoteHostClosedError, 30001},
        {QNetworkReply::HostNotFoundError, 30002},
        {QNetworkReply::TimeoutError, 30003},
        {QNetworkReply::OperationCanceledError, 30004},
        {QNetworkReply::SslHandshakeFailedError, 30005},
        {QNetworkReply::TemporaryNetworkFailureError, 30006},
        {QNetworkReply::NetworkSessionFailedError, 30007},
        {QNetworkReply::BackgroundRequestNotAllowedError, 30008},
        {QNetworkReply::TooManyRedirectsError, 30009},
        {QNetworkReply::InsecureRedirectError, 30010},
        {QNetworkReply::ProxyConnectionRefusedError, 30011},
        {QNetworkReply::ProxyConnectionClosedError, 30012},
        {QNetworkReply::ProxyNotFoundError, 30013},
        {QNetworkReply::ProxyTimeoutError, 30014},
        {QNetworkReply::ProxyAuthenticationRequiredError, 30015},
        {QNetworkReply::ContentAccessDenied, 30016},
        {QNetworkReply::ContentOperationNotPermittedError, 30017},
        {QNetworkReply::ContentNotFoundError, 30018},
        {QNetworkReply::AuthenticationRequiredError, 30019},
        {QNetworkReply::ContentReSendError, 30020},
        {QNetworkReply::ContentConflictError, 30021},
        {QNetworkReply::ContentGoneError, 30022},
        {QNetworkReply::InternalServerError, 30023},
        {QNetworkReply::OperationNotImplementedError, 30024},
        {QNetworkReply::ServiceUnavailableError, 30025},
        {QNetworkReply::ProtocolUnknownError, 30026},
        {QNetworkReply::ProtocolInvalidOperationError, 30027},
        {QNetworkReply::UnknownNetworkError, 30028},
        {QNetworkReply::UnknownProxyError, 30029},
        {QNetworkReply::UnknownContentError, 30030},
        {QNetworkReply::ProtocolFailure, 30031},
        {QNetworkReply::UnknownServerError, 30032}
    };
};

