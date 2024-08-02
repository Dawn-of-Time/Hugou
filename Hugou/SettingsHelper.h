#pragma once
#include <QSettings>
#include <QFile>
#include <QSet>
#include "Const.h"
#include "FloatingNoteManager.h"

extern FloatingNoteManager floatingNoteManager;

class SettingsHelper : public QObject
{
	Q_OBJECT

public:
	SettingsHelper(QWidget* Hugou = nullptr);
	bool verifySettings();
	QString readSettings(QString key);
	bool writeSettings(QString key, QString value);
	void syncSettings();
		
signals:
	void triggerError(int errorCode);

protected slots:
	void dealError(int errorCode);

private:
	QWidget* Hugou;
	bool verifyConfINIExist();
	//bool verifyConfINIInvalid();
};

