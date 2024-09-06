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
#include "SettingsHelper.h"
#include "Model_Settings.h"
#include "Const_DefaultTheme.h"

extern FloatingNoteManager floatingNoteManager;

class HugouController;

class HugouModel : public QObject
{

    Q_OBJECT

public:
    HugouModel();
    ~HugouModel();
    inline void setTheme(QString theme) { m_theme = theme; };
    QString getTheme();

private:
    QString m_theme = "";
    friend class HugouController;
    struct ThemeResource
    {
        QString generalStyleSheet;
        QString asideBarStyleSheet;
        QString settingsStyleSheet;
    };
    QStringList styleFileNameList = { "general", "asideBar", "settings" };
    ThemeResource loadThemeResource(QString theme);
    ThemeResource getDefaultThemeResource();

    SettingsModel* m_settingsModel;
};