#pragma once

#include "Var.h"
#include "SettingsHelper.h"
#include "View_Hugou.h"
#include "Model_Hugou.h"
#include "Controller_Settings.h"

extern FloatingNoteManager floatingNoteManager;

class HugouController : public QObject
{
    Q_OBJECT

public:
    HugouController(HugouView* hugouView, HugouModel* hugouModel);
    ~HugouController();

protected slots:
    void openPDFEditFunction();
    void changeStackedWidgetRequest(int index);
    void applyThemeRequest(bool startup, QString theme = "");

private:
    HugouView* m_hugouView;
    HugouModel* m_hugouModel;
    SettingsController* m_settingsController;
};