﻿#pragma once

#include <QtCore/QVariant>
#include <QApplication>
#include <QtWidgets>
#include <QFont>
#include "TitleBar.h"
#include "AsideBar.h"
#include "Const.h"
#include "ButtonHoverWatcher.h"
#include "ComboboxWheelWatcher.h"
#include "WorkSpace.h"
#include "Settings.h"

QT_BEGIN_NAMESPACE

class Ui_HugouClass
{
public:
    QHBoxLayout* generalLayout;
    QWidget* titleBarAndStackedWidget;
    QVBoxLayout* titleBarAndStackedLayout;
    TitleBar* titleBar;
    AsideBar* asideBar;
    QWidget* stackedWidgetContainer;
    QStackedWidget* stackedWidget;
    QHBoxLayout* stackedWidgetLayout;
    WorkSpace* workSpaceWidget;
    Settings* settingsWidget;
    

    void setupUi(QWidget* HugouClass)
    {
        // 1 主窗口
        // --基本属性设置
        HugouClass->setObjectName("HugouClass");
        HugouClass->setMinimumSize(mainWindowWidth, mainWindowHeight);
        HugouClass->resize(960, 640);

        // --无边框窗口
        // 注：使用无边框窗口的一个目标是方便自定义标题栏。事实上，使用Qt::CustomizeWindowHint标志会更方便一些，
        //    因为Qt::FramelessWindowHint标志将会一并移出窗口边缘的拉伸效果，同时并不自带圆角效果。遗憾的是，
        //    使用Qt::CustomizeWindowHint标志后，会在窗口的顶端残留白条，并不美观。因此考虑使用
        //    Qt::FramelessWindowHint标志，其余功能自行实现。
        // --透明背景
        //HugouClass->setAttribute(Qt::WA_TranslucentBackground);


        // 2 主布局
        generalLayout = new QHBoxLayout(HugouClass);
        generalLayout->setSpacing(0);
        generalLayout->setContentsMargins(0, 0, 0, 0);
        // ----侧边栏
        asideBar = new AsideBar(HugouClass);
        // ----标题栏与堆叠控件
        titleBarAndStackedWidget = new QWidget(HugouClass);
        titleBarAndStackedLayout = new QVBoxLayout(titleBarAndStackedWidget);
        titleBarAndStackedLayout->setSpacing(0);
        titleBarAndStackedLayout->setContentsMargins(0, 0, 0, 0);
        // ------标题栏
        titleBar = new TitleBar(titleBarAndStackedWidget);
        // ------堆叠控件
        stackedWidgetContainer = new QWidget(titleBarAndStackedWidget);
        stackedWidgetLayout = new QHBoxLayout(stackedWidgetContainer);
        stackedWidgetLayout->setSpacing(0);
        stackedWidgetLayout->setContentsMargins(5, 0, 5, 5);
        stackedWidget = new QStackedWidget(stackedWidgetContainer);
        stackedWidget->setObjectName("stackedWidget");

        // --------堆叠控件：WorkSpace
        workSpaceWidget = new WorkSpace(stackedWidget);
        // --------堆叠控件：Settings
        settingsWidget = new Settings(stackedWidget);

        stackedWidget->addWidget(workSpaceWidget);
        stackedWidget->addWidget(settingsWidget);
        stackedWidget->setCurrentWidget(workSpaceWidget);

        stackedWidgetLayout->addWidget(stackedWidget);

        titleBarAndStackedLayout->addWidget(titleBar);
        titleBarAndStackedLayout->addWidget(stackedWidgetContainer);

        generalLayout->addWidget(asideBar);
        generalLayout->addWidget(titleBarAndStackedWidget);


        // 全局控件
        top
        retranslateUi(HugouClass);
    } // setupUi

    void retranslateUi(QWidget* HugouClass)
    {
        HugouClass->setWindowTitle(QCoreApplication::translate("HugouClass", "Hugou", nullptr));
    } 
};

QT_END_NAMESPACE
