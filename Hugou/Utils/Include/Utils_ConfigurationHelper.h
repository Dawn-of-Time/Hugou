#pragma once
#include <QSettings>
#include <QFile>
#include "Utils_MessegeHelper.h"

class ConfigurationHelper : public QObject
{
	Q_OBJECT

public:
	static ConfigurationHelper* getHelper();
	
	bool getBasisValue(const QString& key, QString& value);
	bool getPreferenceValue(const QString& key, QString& value);
	bool getRecordValue(const QString& key, QString& value);
	void setBasisValue(const QString& key, const QString& value);
	void setPreferenceValue(const QString& key, const QString& value);
	void setRecordValue(const QString& key, const QString& value);
	bool writeConfiguration(const QString& section, const QString& key, const QString& value);
	void syncConfiguration();

	// "invalid"不能是值。
	const QMap<QString, QMap<QString, QStringList>> configurationValidValueMap =
	{
		{
			"Basis",
			{
				{"firstBoot", {"true", "false"}}
			}
		},
		{
			"Preference",
			{
				{"theme", {"Default", "Spring", "Summer", "Autumn", "Winter"}},
				{"language", {"English"}},
				{"recycleBin", {"on", "off"}},
				{"retentionPeriod", {}}
			}
		},
		{
			"Record",
			{
				{"location_ID", {}},
				{"location_region", {}},
				{"weathercard_observationTime", {}},
				{"weathercard_temperature", {}},
				{"weathercard_sensibleTemperature", {}},
				{"weathercard_icon", {}},
				{"weathercard_weather", {}},
				{"weathercard_wind360", {}},
				{"weathercard_windDirection", {}},
				{"weathercard_windScale", {}},
				{"weathercard_windSpeed", {}},
				{"weathercard_humidity", {}},
				{"weathercard_precipitationLastHour", {}},
				{"weathercard_pressure", {}},
				{"weathercard_visibility", {}},
				{"weathercard_cloud", {}},
				{"weathercard_dewPointTemperature", {}}
			}
		}
	};

private:
	QSettings m_confINI = QSettings("Configuration/conf.ini", QSettings::IniFormat);
	bool m_isChanged = false;
	const QStringList m_preferenceGroupList = 
	{
		"Common",
		"Task",
	};
	const QMap<QString, QMap<QString, QString>> m_defalutValueMap =
	{
		{
			"Basis", 
			{
				{"firstBoot", "false"}
			}
		},
		{
			"Preference", 
			{
				{"theme", "Default"},
				{"language", "English"},
				{"recycleBin", "on"},
				{"retentionPeriod", "30"}
			}
		},
		{
			"Record",
			{
				{"location_ID", ""},
				{"location_region", ""},
				{"weathercard_observationTime", ""},
				{"weathercard_temperature", ""},
				{"weathercard_sensibleTemperature", ""},
				{"weathercard_icon", ""},
				{"weathercard_weather", ""},
				{"weathercard_wind360", ""},
				{"weathercard_windDirection", ""},
				{"weathercard_windScale", ""},
				{"weathercard_windSpeed", ""},
				{"weathercard_humidity", ""},
				{"weathercard_precipitationLastHour", ""},
				{"weathercard_pressure", ""},
				{"weathercard_visibility", ""},
				{"weathercard_cloud", ""},
				{"weathercard_dewPointTemperature", ""}
			}
		}
	};
	QMap<QString, QMap<QString, QString>> m_configurationMap =
	{
		{"Basis", {}},
		{"Preference", {}},
		{"Record", {}}
	};

	// 重载运算符
	ConfigurationHelper(const ConfigurationHelper&) = delete;
	ConfigurationHelper& operator=(const ConfigurationHelper&) = delete;

	ConfigurationHelper();
	void verifyAndLoadConfiguration();
	QString readPreference(const QString& key);
	bool verifyConfINIExist();
};

