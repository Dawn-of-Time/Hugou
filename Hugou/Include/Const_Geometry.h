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
// 侧边栏
const int minimumAsideBarHeight = minimumMainWindowHeight - titleFrameHeight;
// 主页
const int stackedWidgetWidth = titleFrameWidth;
const int stackedWidgetHeight = minimumAsideBarHeight - titleFrameHeight;
// 浮动消息
const int floatingNoteWidth = 400;