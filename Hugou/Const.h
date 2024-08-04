#pragma once

#include <QString>
#include <QFont>
#include <QSize>
#include <QPoint>
#include <map>

// 几何参数
// 窗口
const int mainWindowWidth = 750;
const int mainWindowHeight = 500;
const int edgeWidth = 5;

// 标题栏
const int titleFrameWidth = mainWindowWidth;
const int titleFrameHeight = 35;
const int titleButtonWidth = 60;
const int titleButtonHeight = titleFrameHeight;
const QSize titleButtonIconSize = QSize(15, 15);
// 侧边栏
const int asideFrameWidth = 150;
const int asideFrameHeight = mainWindowHeight - titleFrameHeight;
const int userLabelWidth = 150;
const int userLabelHeight = 80;
const int asideButtonWidth = 135;
const int asideButtonHeight = 40;
const QSize asideButtonIconSize = QSize(18, 18);
// 主页
const int stackedWidgetWidth = titleFrameWidth;
const int stackedWidgetHeight = asideFrameHeight - titleFrameHeight;
const int stackedTitleHeight = 50;
const int functionSubwidgetWidth = stackedWidgetWidth;
const int functionSubwidgetHeight = stackedWidgetHeight - stackedTitleHeight;
const int functionGridRowCount = 1;
const int functionGridColumnCount = 7;
const int functionGridRowHeight = 90;
const int functionGridColumnWidth = 120;
const int functionDialogWidth = 720;
const int functionDialogHeight = 360;
// 浮动消息
const int floatingNoteWidth = 350;
const QSize floatingNoteButtonIconSize = QSize(18, 18);

// 字体
// 通用
const QFont title1 = QFont("Roboto", 16, QFont::Bold);
const QFont title2 = QFont("Roboto", 14);
const QFont contentFont = QFont("Hind Siliguri Light", 12);
const QFont subcontentFont = QFont("Roboto", 8);
const QFont buttonFont = QFont("Roboto", 10);
const QFont tableHeaderFont = QFont("Roboto", 14, QFont::Bold);
const QFont tableContentFont = QFont("Roboto", 12, QFont::Medium);
const QFont tableSubcontentFont = QFont("Roboto", 10);
// 侧边栏
const QFont asideFont = QFont("Roboto", 12, QFont::Medium);
// 浮动消息
const QFont signFont = QFont("Roboto", 16);
const QFont timekeepingLabelFont = QFont("Hind Siliguri Light", 12);
const QFont floatingNoteButtonFont = QFont("Hind Siliguri Light", 12);

// 全局顶层
const QFont hintFont = QFont("Roboto", 18, QFont::Thin);

// 提示性文字
const QString operationText = QString(
	"<span style='font-weight: bold;'>DROP</span> the PDF file here or "
	"<span style='font-weight: bold;'>CLICK</span> here to search from Explorer.");
const QString searchText = QString("Search item.");
const QString readingSettingErrorHint = QString(
	"Failed to read the configuration file. ");
const QString savingSettingErrorHint = QString(
	"Failed to save configuration. ");
// 	"<br>"
//"● Settings - Restore:<br> "
//"&nbsp;&nbsp; Restore the configuration to restore point.<br>"

// 设置项。
//const QStringList settingCatalogueList = {
//		"Common",
//			"Appearance",
//				"Theme",
//			"Country/Region",
//				"Language",
//		"Export",
//			"Save",
//				"Default Save Path" };

const QStringList settingsGroupList = {
	"Common",
	"Export"
};

const QStringList settingsKeyList = {
	{"theme", "language", "defaultSavePath"}
};

// "invalid"不能是值。
const std::map<QString, QStringList> settingValueMap = {
	{"theme", {"Default", "Spring", "Summer", "Autumn", "Winter"}},
	{"language", {"English"}}
};