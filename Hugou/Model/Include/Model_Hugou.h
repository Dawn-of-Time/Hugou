#pragma once

#include <QWidget>
#include <QPainter>
#include <QSettings>
#include <windowsx.h>
#include <Windows.h>
#include <dwmapi.h>
#include <thread>
#include <chrono>
#include "Utils/Include/Utils_ConfigurationHelper.h"
#include "Model/Include/Model_Schedule.h"
#include "Model/Include/Model_preference.h"

class HugouController;

class HugouModel : public QObject
{

    Q_OBJECT

public:
    HugouModel();

private:
    friend class HugouController;
    struct ThemeResource
    {
        QString generalStyleSheet;
        QString asideBarStyleSheet;
        QString preferenceStyleSheet;
    };
    QStringList styleFileNameList = { "general", "asideBar", "preference" };

    PreferenceModel* m_preferenceModel;
    ScheduleModel* m_scheduleModel;
};