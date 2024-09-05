#pragma once

#include <QString>
#include <QFont>
#include <QSize>
#include <QPoint>
#include <QList>
#include <QMap>

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
const int asideBarWidth = 200;
const int asideBarHeight = mainWindowHeight - titleFrameHeight;
const int asideUserLabelHeight = 40;
const int asideTitleHeight = 20;
const int asideButtonHeight = 35;
const QSize asideButtonIconSize = QSize(18, 18);
// 主页
const int stackedWidgetWidth = titleFrameWidth;
const int stackedWidgetHeight = asideBarHeight - titleFrameHeight;
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
const QFont buttonFont = QFont("Roboto", 12);
const QFont tableHeaderFont = QFont("Roboto", 14, QFont::Bold);
const QFont tableContentFont = QFont("Roboto", 12, QFont::Medium);
const QFont tableSubcontentFont = QFont("Roboto", 10);
// 侧边栏
const QFont asideTitleFont = QFont("Roboto", 12, QFont::Normal);
const QFont asideButtonFont = QFont("Hind Siliguri", 13, QFont::Normal);
// 浮动消息
const QFont signFont = QFont("Hind Siliguri", 16);
const QFont timekeepingLabelFont = QFont("Hind Siliguri", 16);
const QFont floatingNoteButtonFont = QFont("Roboto", 12, QFont::Bold);
// 浮动消息面板
const QFont floatingNotePanelButtonFont = QFont("Roboto", 14, QFont::Bold);

// 全局顶层
const QFont hintFont = QFont("Roboto", 18, QFont::Normal);

// 提示性文字
const QString operationText = QString(
	"<span style='font-weight: bold;'>DROP</span> the PDF file here or "
	"<span style='font-weight: bold;'>CLICK</span> here to search from Explorer.");
const QString searchText = QString("Search item.");

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

// 默认主题
const QString defaultGeneralStyleSheet =
QString("HugouView#hugou { background-color: #F0F4FD; }")
+ QString("QWidget#asideBarAndStackedWidget { background-color: transparent; }")
+ QString("QStackedWidget#stackedWidget { border-radius: 10px; background-color: rgba(255, 255, 255, 0.8);}");

const QString defaultAsideBarStyleSheet = 
QString("QLabel#userLabel { background-color: transparent; }")
+ QString("QPushButton[status=\"default\"]{border-radius: 10px;}")
+ QString("QPushButton[status=\"default\"] > QLabel { color: #434343; background-color: transparent; }")
+ QString("QPushButton[status=\"current\"] { border-radius: 10px;}")
+ QString("QPushButton[status=\"current\"] > QLabel { color: #377FED; background-color: transparent; }");

const QString defaultSettingsStyleSheet =
QString("QStackedWidget { background-color: transparent; border: none }")
+ QString("QTreeWidget { background-color: transparent; border: none }")
+ QString("QListWidget { background-color: transparent; border: none; outline: none; margin-left: 20px; margin-right: 12px; margin-top: 2px; margin-bottom: 2px }")
+ QString("QListWidget::item:hover { background-color: transparent }")
+ QString("QPushButton { border: none }")
+ QString("QComboBox { border: none; border-radius: 5px; padding: 3px; background-color: #A2CBEE; }")
+ QString("QComboBox:hover { background-color: #5591DC; }")
+ QString("QComboBox QAbstractItemView { outline: none; margin-top: 5px; border-radius: 5px; background-color: #A2CBEE; }")
+ QString("QComboBox QAbstractItemView::item:hover { padding: 3px; color: black; border-radius: 5px; background-color: #5591DC; }")
+ QString("QComboBox QAbstractItemView::item:selected { padding: 3px; color: white; border-radius: 5px; background-color: #5591DC; }")
+ QString("QComboBox::down-arrow { image: url(\":/icon/down_bla.png\"); width: 20px; }")
+ QString("QComboBox::drop-down { border: none; }");
