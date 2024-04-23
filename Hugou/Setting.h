#pragma once

#include <vector>
#include <string>
#include <map>
#include <QString>
#include <QSettings>
#include <QTreeWidget>
#include <QMainWindow>
#include "Const.h"

const std::map<QString, QString> defaultCommonMap = {
			{"theme", "Default"},
			{"language", "English"} };

const std::map<QString, QString> defaultExportMap = {
	{"defaultSavePath", ""} };

extern std::map<QString, QString> settingCommonMap;

extern std::map<QString, QString> settingExportMap;

class Setting
{
public:
	Setting();
	~Setting();
	//ThemeSetting* themeSetting;
	bool searchSetting(QTreeWidget* treeWidget, QTreeWidgetItem* item, QString text);
	void showSetting(QTreeWidget* treeWidget, QTreeWidgetItem* item);
	void notExpandSetting(QTreeWidget* treeWidget);
	bool readSetting();
	//bool applySetting(Hugou* HugouClass, QString objectName = "", QString oldsetting = "");
	//bool saveSetting(Hugou* HugouClass, QString objectName, QString oldsetting);
	//void undoSetting(Hugou* HugouClass, QString objectName, QString oldsetting);
	void resetSetting();
	void resetAllSetting();

signals:
	void settingSavedSignal();
};
