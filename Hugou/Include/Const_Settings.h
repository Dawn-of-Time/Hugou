#pragma once

#include <QString>
#include <QList>
#include <QMap>


const QStringList settingsGroupList = {
	"Common",
	"Task",
};
const QStringList settingsKeyList = {
	{"firstBoot", "theme", "language", "recycleBin", "retentionPeriod"}
};
// "invalid"不能是值。
const QMap<QString, QStringList> settingsValueMap = {
	{"firstBoot", {"true", "false"}},
	{"theme", {"Default", "Spring", "Summer", "Autumn", "Winter"}},
	{"language", {"English"}}, 
	{"recycleBin", {"on", "off"}}
};
const QMap<QString, QString> defalutSettingsValueMap = {
	{"firstBoot", "false"},
	{"theme", "Default"},
	{"language", "English"},
	{"recycleBin", "on"},
	{"retentionPeriod", "30"}
};