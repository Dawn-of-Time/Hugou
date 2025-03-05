#pragma once
#include <QSettings>
#include <QFile>
#include <QSet>
#include <QMutex>
#include "Include/Const_Preference.h"
#include "Assistance_MessegeHelper.h"

class PreferenceHelper : public QObject
{
	Q_OBJECT

public:
	QMap<QString, QString> m_preferenceMap;

	static PreferenceHelper* getHelper();
	
	bool getPreferenceValue(const QString& key, QString& value);
	void setPreferenceValue(const QString& key, const QString& value);
	bool writePreference(const QString& key, const QString& value);
	void syncPreference();

private:
	QSettings m_confINI = QSettings("Configuration/conf.ini", QSettings::IniFormat);
	
	bool m_isChanged = false;
	// ÖØÔØÔËËã·û
	PreferenceHelper(const PreferenceHelper&) = delete;
	PreferenceHelper& operator=(const PreferenceHelper&) = delete;

	PreferenceHelper();
	void verifyAndLoadpreference();
	QString readpreference(const QString& key);
	bool verifyConfINIExist();
};

