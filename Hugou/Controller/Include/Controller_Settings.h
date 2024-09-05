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
    bool m_userChanged = true;

signals:
    void SignalApplyTheme(QString theme = "");

protected slots:
    void settingsTreeItemExpandOrCollapseRequest(QTreeWidgetItem* item, int column);
    void settingsContentListWidgetSrollRequest(QTreeWidgetItem* item, int column);
    void applyThemeRequest(QString theme);

private:
    SettingsView* m_settingsView;
    SettingsModel* m_settingsModel;
};