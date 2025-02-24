#pragma once
#include <QSettings>
#include <QFile>
#include <QSet>
#include <QMutex>
#include "Const_Preference.h"
#include "Assistance_FloatingNoteManager.h"

class PreferenceHelper : public QObject
{
	Q_OBJECT

public:
	QMap<QString, QString> m_preferenceMap;

	static PreferenceHelper* getHelper();
	void setHugou(QWidget* hugou);
	bool getPreferenceValue(const QString& key, QString& value);
	void setPreferenceValue(const QString& key, const QString& value);
	bool writePreference(const QString& key, const QString& value);
	void syncPreference();
		
signals:
	void trigger(FloatingNote::NoteType type, int code, const QString& otherInfo = "");

protected slots:
	void deal(FloatingNote::NoteType type, int code, const QString& otherInfo = "");

private:
	QSettings m_confINI = QSettings("Configuration/conf.ini", QSettings::IniFormat);
	QWidget* m_hugou;
	QList<QPair<FloatingNote::NoteType, QPair<QString, QString>>> m_noteList;
	
	bool m_isChanged = false;
	// ���������
	PreferenceHelper(const PreferenceHelper&) = delete;
	PreferenceHelper& operator=(const PreferenceHelper&) = delete;

	PreferenceHelper();
	void verifyAndLoadpreference();
	QString readpreference(const QString& key);
	bool verifyConfINIExist();

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
		{20000, {tr("Database error occurred."), tr("It is:")}}
	};

	const QMap<int, QString> successCodeMap = {
		//�ɹ����룺��(0)-��(00)-���(00)
		//��1�£�
		//��0�ڣ�
		//10000 ����Ӧ�óɹ���
		{10000, "Apply theme successfully: "},
	};
};

