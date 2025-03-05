#pragma once
#include <QObject>
#include <QMap>
#include "Assistance_FloatingNoteManager.h"
class MessegeHelper :
    public QObject
{
    Q_OBJECT
public:
	enum MessegeHelperMode {
		UIPreparedMode, UINotPreparedMode
	};
	static MessegeHelper* getHelper();
	void setMode(const MessegeHelperMode& mode);

signals:
	void trigger(FloatingNote::NoteType type, int code, const QString& otherInfo = "");

protected slots:
	void deal(FloatingNote::NoteType type, int code, const QString& otherInfo = "");

private:
	MessegeHelper(const MessegeHelper&) = delete;
	MessegeHelper& operator=(const MessegeHelper&) = delete;
	MessegeHelper();
	MessegeHelperMode m_mode = MessegeHelperMode::UINotPreparedMode;
	QList<QPair<FloatingNote::NoteType, QPair<QString, QString>>> m_noteList;

	const QMap<int, QList<QString>> errorCodeMap =
	{
		// 错误代码：章(0) - 节(00) - 编号(00)
		// 第1章：配置类错误
		// 第0节：基本配置错误
		// 10000 基本配置文件不存在。
		// 10001 基本配置文件损坏。
		// 10002 基本配置项的值不合法。
		{10000, {tr("The basic configuration file does not exist."), tr("We temporarily apply the default configuration to your application for you. Click the Help button in the title bar for a possible solution.")}},
		{10001, {tr("The basic configuration file is damaged."), tr("We temporarily apply the default configuration to your application for you. Click the Help button in the title bar for a possible solution.")}},
		{10002, {tr("The value of the basic configuration item is invalid."), tr("We temporarily apply the default configuration to your application for you. Click the Help button in the title bar for a possible solution.")}},
		// 第1节：主题配置错误
		// 10100 部分主题配置文件不存在。
		// 10101 部分主题配置文件损坏。
		// 10102 部分主题配置文件为空。
		{10100, {tr("Some theme configuration files do not exist."), tr("We temporarily apply the default theme for your application. Click the Help button in the title bar for a possible solution.")}},
		{10101, {tr("Some theme configuration files are damaged."), tr("We temporarily apply the default theme for your application. Click the Help button in the title bar for a possible solution.")}},
		{10102, {tr("Some theme configuration files are empty."), tr("We temporarily apply the default theme for your application. Click the Help button in the title bar for a possible solution.")}},
		// 第2章：数据库类错误
		// 第0节：数据库类错误
		// 20000 数据库错误。
		{20000, {tr("Database error occurred."), tr("It is:")}},
		// 第3章：网络类错误
		// 第0节：网络类错误
		// 30000 远程服务器拒绝连接（服务器不接受请求）。
		// 30001 远程服务器在收到并处理整个回复之前提前关闭了连接。
		// 30002 找不到远程主机名（主机名无效）
		// 30003 与远程服务器的连接超时
		// 30004 在作完成之前，通过调用 （） 或 （） 取消了该作。
		// 30005 SSL / TLS 握手失败，无法建立加密通道。（） 信号应该已经发出。
		// 30006 由于网络连接断开，连接已断开，但系统已启动漫游到另一个接入点。应重新提交该请求，并将在重新建立连接后立即进行处理。
		// 30007 由于与网络断开连接或无法启动网络，连接已断开。
		// 30008 由于平台策略，当前不允许后台请求。
		// 30009 在跟踪重定向时，达到了最大限制。默认情况下，限制设置为 50 或由 QNetworkRequest：：setMaxRedirectsAllowed（） 设置。
		// 30010 在跟踪重定向时，网络访问 API 检测到从加密协议 （HTTPS） 到未加密协议 （HTTP） 的重定向。
		// 30011 与 Proxy Server 的连接被拒绝（Proxy Server 不接受请求）
		// 30012 代理服务器在接收和处理整个回复之前提前关闭了连接
		// 30013 找不到代理主机名（代理主机名无效）
		// 30014 与 Proxy 的连接超时或 Proxy 未及时回复发送的请求
		// 30015 代理需要身份验证才能接受请求，但未接受提供的任何凭据（如果有）
		// 30016 对远程内容的访问被拒绝
		// 30017 不允许对远程内容执行请求的作
		// 30018 在服务器上找不到远程内容
		// 30019 远程服务器需要身份验证才能提供内容，但提供的凭据未被接受（如果有）
		// 30020 需要再次发送请求，但失败，例如，因为无法再次读取上传数据。
		// 30021 由于与资源的当前状态冲突，无法完成请求。
		// 30022 请求的资源在服务器上不再可用。
		// 30023 服务器遇到意外情况，导致其无法完成请求。
		// 30024 服务器不支持满足请求所需的功能。
		// 30025 此时，服务器无法处理该请求。
		// 30026 网络访问API无法接受请求，因为协议未知
		// 30027 请求的作对此协议无效
		// 30028 检测到未知的网络相关错误
		// 30029 检测到未知的代理相关错误
		// 30030 检测到与远程内容相关的未知错误
		// 30031 检测到协议故障（解析错误、无效或意外响应等）
		// 30032 检测到与服务器响应相关的未知错误
		{30000, {tr(""), tr("")}},
		{30001, {tr("The remote server closed the connection prematurely, before the entire reply was received and processed."), tr("")}},
		{30002, {tr(""), tr("")}},
		{30003, {tr(""), tr("")}},
		{30004, {tr(""), tr("")}},
		{30005, {tr(""), tr("")}},
		{30006, {tr(""), tr("")}},
		{30007, {tr(""), tr("")}},
		{30008, {tr(""), tr("")}},
		{30009, {tr(""), tr("")}},
		{30010, {tr(""), tr("")}},
		{30011, {tr(""), tr("")}},
		{30012, {tr(""), tr("")}},
		{30013, {tr(""), tr("")}},
		{30014, {tr(""), tr("")}},
		{30015, {tr(""), tr("")}},
		{30016, {tr(""), tr("")}},
		{30017, {tr(""), tr("")}},
		{30018, {tr(""), tr("")}},
		{30019, {tr("The remote server requires authentication to serve the content but the credentials provided were not accepted (if any)."), tr("")}},
		{30020, {tr(""), tr("")}},
		{30021, {tr(""), tr("")}},
		{30022, {tr(""), tr("")}},
		{30023, {tr(""), tr("")}},
		{30024, {tr(""), tr("")}},
		{30025, {tr("The server is unable to handle the request at this time."), tr("")}},
		{30026, {tr("The Network Access API cannot honor the request because the protocol is not known."), tr("")}},
		{30027, {tr(""), tr("")}},
		{30028, {tr(""), tr("")}},
		{30029, {tr(""), tr("")}},
		{30030, {tr(""), tr("")}},
		{30031, {tr(""), tr("")}},
		{30032, {tr(""), tr("")}}
	};

	const QMap<int, QString> successCodeMap = {
		//成功代码：章(0)-节(00)-编号(00)
		//第1章：
		//第0节：
		//10000 主题应用成功。
		{10000, tr("Apply theme successfully: ")},
	};
};

