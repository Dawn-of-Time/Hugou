#pragma once

#include <QWidget>
#include <QPainter>
#include <QSettings>
#include <windowsx.h>
#include <Windows.h>
#include <dwmapi.h>
#include <thread>
#include <chrono>
#include "Var.h"
#include "Assistance_SettingsHelper.h"
#include "Model_Schedule.h"
#include "Model_Settings.h"

class HugouController;

class HugouModel : public QObject
{

    Q_OBJECT

public:
    HugouModel();
    ~HugouModel();

private:
    friend class HugouController;
    struct ThemeResource
    {
        QString generalStyleSheet;
        QString asideBarStyleSheet;
        QString settingsStyleSheet;
    };
    QStringList styleFileNameList = { "general", "asideBar", "settings" };

    SettingsModel* m_settingsModel;
    ScheduleModel* m_scheduleModel;
};