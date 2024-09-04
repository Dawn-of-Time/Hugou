#pragma once

#include "Var.h"
#include "View_Settings.h"
#include "Model_Settings.h"
#include "SettingsHelper.h"

class SettingsController : public QObject
{

    Q_OBJECT

public:
    SettingsController(SettingsView* settingsView, SettingsModel* settingsModel);

signals:
    void SignalApplyTheme(QString theme = "");

private:
    SettingsView* m_settingsView;
    SettingsModel* m_settingsModel;
};