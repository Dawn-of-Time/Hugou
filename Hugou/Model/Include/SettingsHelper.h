#pragma once
#include <QSettings>
#include <QFile>
#include <QSet>
#include <QMutex> 
#include "Const_Settings.h"
#include "FloatingNoteManager.h"

extern FloatingNoteManager floatingNoteManager;

class SettingsHelper : public QObject
{
	Q_OBJECT

public:
	static SettingsHelper* getHelper();

	QMap<QString, QString> m_settingsMap;
	void setHugou(QWidget* hugou);
	bool writeSettings(QString key, QString value);
	void syncSettings();
		
signals:
	void triggerError(int errorCode);

protected slots:
	void dealError(int errorCode);

private:
	static QWidget* m_hugou;
	static SettingsHelper* m_helper;
	static QMutex m_mutex;
	QList<QPair<QString, QString>> m_errorList;
	// ÖØÔØÔËËã·û
	SettingsHelper(const SettingsHelper&) = delete;
	SettingsHelper& operator=(const SettingsHelper&) = delete;

	SettingsHelper();
	void verifyAndLoadSettings();
	QString readSettings(QString key);
	bool verifyConfINIExist();
};

