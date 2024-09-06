#pragma once

#include <QSize>

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
const QSize titleButtonIconSize = QSize(16, 16);
// 侧边栏
const int asideBarWidth = 200;
const int asideBarHeight = mainWindowHeight - titleFrameHeight;
const int asideUserWidgetHeight = 48;
const int asideUserAvaterSide = asideUserWidgetHeight;
const int asideTitleHeight = 10;
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