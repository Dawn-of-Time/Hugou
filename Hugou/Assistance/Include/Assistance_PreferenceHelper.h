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
	// 重载运算符
	PreferenceHelper(const PreferenceHelper&) = delete;
	PreferenceHelper& operator=(const PreferenceHelper&) = delete;

	PreferenceHelper();
	void verifyAndLoadpreference();
	QString readpreference(const QString& key);
	bool verifyConfINIExist();

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
		{20000, {tr("Database error occurred."), tr("It is:")}}
	};

	const QMap<int, QString> successCodeMap = {
		//成功代码：章(0)-节(00)-编号(00)
		//第1章：
		//第0节：
		//10000 主题应用成功。
		{10000, "Apply theme successfully: "},
	};
};

