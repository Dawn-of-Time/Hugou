#pragma once

#include <QString>
#include <QList>
#include <QMap>


const QStringList preferenceGroupList = {
	"Common",
	"Task",
};
const QStringList preferenceKeyList = {
	{"firstBoot", "theme", "language", "recycleBin", "retentionPeriod"}
};
// "invalid"不能是值。
const QMap<QString, QStringList> preferenceValueMap = {
	{"firstBoot", {"true", "false"}},
	{"theme", {"Default", "Spring", "Summer", "Autumn", "Winter"}},
	{"language", {"English"}}, 
	{"recycleBin", {"on", "off"}}
};
const QMap<QString, QString> defalutPreferenceValueMap = {
	{"firstBoot", "false"},
	{"theme", "Default"},
	{"language", "English"},
	{"recycleBin", "on"},
	{"retentionPeriod", "30"}
};