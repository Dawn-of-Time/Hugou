//#include "ThemeSetting.h"
//
//void ThemeSetting::initTheme(Hugou* HugouClass)
//{
//	/*HugouClass->setProperty("themeColor", QColor(255, 0, 0));*/
//	// 主体
//	
//}
//
//void ThemeSetting::setTheme(Hugou* HugouClass, QString themeName)
//{
//	if (themeList.contains(themeName)) this->theme = themeName;
//	else this->theme = "Default";
//	QStringList themeColor = themeMap[theme];
//	// 设置页
//	QString searchLineEditStyleSheet = QString(
//		"QLineEdit {border-radius: 10px; padding-left: 10px; padding-top: 10px; padding-bottom: 5px; margin: 5px}"
//		"QLineEdit:hover {border: 1px solid %1}"
//		"QLineEdit:focus {border: 1px solid %1}").arg(themeColor.at(0));
//	QString settingTreeWidgetStyleSheet = QString(
//		".QTreeWidget {background-color:white; border: none; outline: none; padding: 0px; margin: 0px}"
//		".QTreeWidget::item:selected{background-color: %1}"
//		".QTreeWidget::item:hover{ background-color: %2; color: white }").arg(themeColor.at(0)).arg(themeColor.at(1));
//	QString settingTreeWidgetScrollBarStyleSheet = QString(
//		"QScrollBar {background-color: transparent; border: none; width: 5px}"
//		"QScrollBar::handle {background-color: %1; width: 5px}"
//		"QScrollBar::sub-line {background:none; border:none}"
//		"QScrollBar::add-line {background:none; border:none}").arg(themeColor.at(0));
//	QString settingContentListWidgetScrollBarStyleSheet = QString(
//		"QScrollBar {background-color: transparent; border: none; width: 5px;}"
//		"QScrollBar::handle {background-color: transparent; background-color: %1; width: 5px}"
//		"QScrollBar::sub-line {background:none; border:none}"
//		"QScrollBar::add-line {background:none; border:none}").arg(themeColor.at(0));
//	QString savePathButtonStyleSheet = QString(
//		"QPushButton {border: none}");
//	
//	HugouClass->ui.searchLineEdit->setStyleSheet(searchLineEditStyleSheet);
//	HugouClass->ui.settingTreeWidget->setStyleSheet(settingTreeWidgetStyleSheet);
//	HugouClass->ui.settingTreeWidget->verticalScrollBar()->setStyleSheet(settingTreeWidgetScrollBarStyleSheet);
//	HugouClass->ui.settingContentListWidget->verticalScrollBar()->setStyleSheet(settingContentListWidgetScrollBarStyleSheet);
//	HugouClass->ui.savePathButton->setStyleSheet(savePathButtonStyleSheet);
//}
