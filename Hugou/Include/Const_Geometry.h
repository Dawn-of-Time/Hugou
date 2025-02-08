#pragma once

#include <QSize>

// 几何参数
// 窗口
const int minimumMainWindowWidth = 960;
const int minimumMainWindowHeight = 540;
const int mainWindowWidth = 1440;
const int mainWindowHeight = 810;
const int edgeWidth = 5;

// 标题栏
const int titleFrameWidth = mainWindowWidth;
const int titleFrameHeight = 56;
const int titleButtonWidth = 72;
const int titleButtonHeight = titleFrameHeight;
const QSize titleButtonIconSize = QSize(16, 16);
// 侧边栏
const int asideBarWidth = 246;
const int minimumAsideBarHeight = minimumMainWindowHeight - titleFrameHeight;
const int asideTitleHeight = 30;
const int asideButtonWidth = 226;
const int asideButtonHeight = 36;
const QSize asideButtonIconSize = QSize(18, 18);
// 主页
const int stackedWidgetWidth = titleFrameWidth;
const int stackedWidgetHeight = minimumAsideBarHeight - titleFrameHeight;
const int cardWidgetWidth = 310;

// 浮动消息
const int floatingNoteWidth = 350;
const QSize floatingNoteButtonIconSize = QSize(18, 18);