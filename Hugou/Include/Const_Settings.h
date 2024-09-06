#pragma once

#include <QString>
#include <QList>
#include <QMap>


const QStringList settingsGroupList = {
	"Common",
	"Export"
};
const QStringList settingsKeyList = {
	{"firstBoot", "theme", "language", "defaultSavePath"}
};
// "invalid"不能是值。
const QMap<QString, QStringList> settingsValueMap = {
	{"firstBoot", {"true", "false"}},
	{"theme", {"Default", "Spring", "Summer", "Autumn", "Winter"}},
	{"language", {"English"}}
};
const QMap<QString, QString> defalutSettingsValueMap = {
	{"firstBoot", "false"},
	{"theme", "Default"},
	{"language", "English"},
	{"defaultSavePath", ""}
};