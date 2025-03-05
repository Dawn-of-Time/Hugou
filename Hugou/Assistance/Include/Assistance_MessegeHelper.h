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
		// ������룺��(0) - ��(00) - ���(00)
		// ��1�£����������
		// ��0�ڣ��������ô���
		// 10000 ���������ļ������ڡ�
		// 10001 ���������ļ��𻵡�
		// 10002 �����������ֵ���Ϸ���
		{10000, {tr("The basic configuration file does not exist."), tr("We temporarily apply the default configuration to your application for you. Click the Help button in the title bar for a possible solution.")}},
		{10001, {tr("The basic configuration file is damaged."), tr("We temporarily apply the default configuration to your application for you. Click the Help button in the title bar for a possible solution.")}},
		{10002, {tr("The value of the basic configuration item is invalid."), tr("We temporarily apply the default configuration to your application for you. Click the Help button in the title bar for a possible solution.")}},
		// ��1�ڣ��������ô���
		// 10100 �������������ļ������ڡ�
		// 10101 �������������ļ��𻵡�
		// 10102 �������������ļ�Ϊ�ա�
		{10100, {tr("Some theme configuration files do not exist."), tr("We temporarily apply the default theme for your application. Click the Help button in the title bar for a possible solution.")}},
		{10101, {tr("Some theme configuration files are damaged."), tr("We temporarily apply the default theme for your application. Click the Help button in the title bar for a possible solution.")}},
		{10102, {tr("Some theme configuration files are empty."), tr("We temporarily apply the default theme for your application. Click the Help button in the title bar for a possible solution.")}},
		// ��2�£����ݿ������
		// ��0�ڣ����ݿ������
		// 20000 ���ݿ����
		{20000, {tr("Database error occurred."), tr("It is:")}},
		// ��3�£����������
		// ��0�ڣ����������
		// 30000 Զ�̷������ܾ����ӣ����������������󣩡�
		// 30001 Զ�̷��������յ������������ظ�֮ǰ��ǰ�ر������ӡ�
		// 30002 �Ҳ���Զ������������������Ч��
		// 30003 ��Զ�̷����������ӳ�ʱ
		// 30004 �������֮ǰ��ͨ������ ���� �� ���� ȡ���˸�����
		// 30005 SSL / TLS ����ʧ�ܣ��޷���������ͨ�������� �ź�Ӧ���Ѿ�������
		// 30006 �����������ӶϿ��������ѶϿ�����ϵͳ���������ε���һ������㡣Ӧ�����ύ�����󣬲��������½������Ӻ��������д���
		// 30007 ����������Ͽ����ӻ��޷��������磬�����ѶϿ���
		// 30008 ����ƽ̨���ԣ���ǰ�������̨����
		// 30009 �ڸ����ض���ʱ���ﵽ��������ơ�Ĭ������£���������Ϊ 50 ���� QNetworkRequest����setMaxRedirectsAllowed���� ���á�
		// 30010 �ڸ����ض���ʱ��������� API ��⵽�Ӽ���Э�� ��HTTPS�� ��δ����Э�� ��HTTP�� ���ض���
		// 30011 �� Proxy Server �����ӱ��ܾ���Proxy Server ����������
		// 30012 ����������ڽ��պʹ��������ظ�֮ǰ��ǰ�ر�������
		// 30013 �Ҳ���������������������������Ч��
		// 30014 �� Proxy �����ӳ�ʱ�� Proxy δ��ʱ�ظ����͵�����
		// 30015 ������Ҫ�����֤���ܽ������󣬵�δ�����ṩ���κ�ƾ�ݣ�����У�
		// 30016 ��Զ�����ݵķ��ʱ��ܾ�
		// 30017 �������Զ������ִ���������
		// 30018 �ڷ��������Ҳ���Զ������
		// 30019 Զ�̷�������Ҫ�����֤�����ṩ���ݣ����ṩ��ƾ��δ�����ܣ�����У�
		// 30020 ��Ҫ�ٴη������󣬵�ʧ�ܣ����磬��Ϊ�޷��ٴζ�ȡ�ϴ����ݡ�
		// 30021 ��������Դ�ĵ�ǰ״̬��ͻ���޷��������
		// 30022 �������Դ�ڷ������ϲ��ٿ��á�
		// 30023 ��������������������������޷��������
		// 30024 ��������֧��������������Ĺ��ܡ�
		// 30025 ��ʱ���������޷����������
		// 30026 �������API�޷�����������ΪЭ��δ֪
		// 30027 ��������Դ�Э����Ч
		// 30028 ��⵽δ֪��������ش���
		// 30029 ��⵽δ֪�Ĵ�����ش���
		// 30030 ��⵽��Զ��������ص�δ֪����
		// 30031 ��⵽Э����ϣ�����������Ч��������Ӧ�ȣ�
		// 30032 ��⵽���������Ӧ��ص�δ֪����
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
		//�ɹ����룺��(0)-��(00)-���(00)
		//��1�£�
		//��0�ڣ�
		//10000 ����Ӧ�óɹ���
		{10000, tr("Apply theme successfully: ")},
	};
};

