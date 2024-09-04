#pragma once
#include <QSettings>
#include <QFile>
#include <QSet>
#include <QMutex> 
#include "Const.h"
#include "FloatingNoteManager.h"

extern FloatingNoteManager floatingNoteManager;

class SettingsHelper : public QObject
{
	Q_OBJECT

public:
	QMap<QString, QString> settingsMap;
	static SettingsHelper* getHelper();
	static void setHugou(QWidget* hugou) { m_hugou = hugou; }
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
	// ÖØÔØÔËËã·û
	SettingsHelper(const SettingsHelper&) = delete;
	SettingsHelper& operator=(const SettingsHelper&) = delete;

	SettingsHelper();
	void verifyAndLoadSettings();
	QString readSettings(QString key);
	bool verifyConfINIExist();
	//bool verifyConfINIInvalid();
};

