#include "Settings.h"

Settings::Settings(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	
	// ���ö�ȡ��Ӧ��
	//QSettings settings("res/conf.ini", QSettings::IniFormat);
}