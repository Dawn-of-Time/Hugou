#pragma once

#include <vector>
#include <string>
#include <map>
#include <QString>
#include <QSettings>
#include <QTreeWidget>
#include <QMainWindow>
#include "Const.h"



class Setting
{
public:
	Setting();
	~Setting();
	//bool readSetting();
	//bool applySetting(Hugou* HugouClass, QString objectName = "", QString oldsetting = "");
	//bool saveSetting(Hugou* HugouClass, QString objectName, QString oldsetting);
	//void undoSetting(Hugou* HugouClass, QString objectName, QString oldsetting);
	void resetSetting();
	void resetAllSetting();

signals:
	void settingSavedSignal();
};
