#pragma once
#include <QSettings>
#include <QFile>
#include <QSet>
#include <QMutex> 
#include "Const_Settings.h"
#include "Assistance_FloatingNoteManager.h"

class SettingsHelper : public QObject
{
	Q_OBJECT

public:
	QMap<QString, QString> m_settingsMap;

	static SettingsHelper* getHelper();
	void setHugou(QWidget* hugou);
	bool getSettingsValue(QString key, QString& value);
	void setSettingsValue(QString key, QString value);
	bool writeSettings(QString key, QString value);
	void syncSettings();
		
signals:
	void triggerError(QString errorCode, QString otherInfo = "");

protected slots:
	void dealError(QString errorCode, QString otherInfo = "");

private:
	QSettings m_confINI = QSettings("Configuration/conf.ini", QSettings::IniFormat);
	static QWidget* m_hugou;
	static SettingsHelper* m_helper;
	static QMutex m_mutex;
	QList<QPair<QString, QString>> m_errorList;
	
	bool m_isChanged = false;
	// ÖØÔØÔËËã·û
	SettingsHelper(const SettingsHelper&) = delete;
	SettingsHelper& operator=(const SettingsHelper&) = delete;

	SettingsHelper();
	void verifyAndLoadSettings();
	QString readSettings(QString key);
	bool verifyConfINIExist();
};

