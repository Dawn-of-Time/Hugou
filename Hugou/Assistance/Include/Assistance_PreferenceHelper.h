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
	bool getpreferenceValue(QString key, QString& value);
	void setpreferenceValue(QString key, QString value);
	bool writepreference(QString key, QString value);
	void syncpreference();
		
signals:
	void triggerError(QString errorCode, QString otherInfo = "");

protected slots:
	void dealError(QString errorCode, QString otherInfo = "");

private:
	QSettings m_confINI = QSettings("Configuration/conf.ini", QSettings::IniFormat);
	QWidget* m_hugou;
	QList<QPair<QString, QString>> m_errorList;
	
	bool m_isChanged = false;
	// ÖØÔØÔËËã·û
	PreferenceHelper(const PreferenceHelper&) = delete;
	PreferenceHelper& operator=(const PreferenceHelper&) = delete;

	PreferenceHelper();
	void verifyAndLoadpreference();
	QString readpreference(QString key);
	bool verifyConfINIExist();
};

