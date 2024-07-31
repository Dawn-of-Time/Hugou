#include "Settings.h"

Settings::Settings(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	
	// 配置读取和应用
	//QSettings settings("res/conf.ini", QSettings::IniFormat);
}