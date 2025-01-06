#pragma once
#include "Assistance_SettingsHelper.h"
#include "Assistance_ThemeManager.h"
#include "Controller_Settings.h"
#include "Controller_Schedule.h"
#include "Assistance_FloatingNoteManager.h"
#include "Model_Hugou.h"
#include "View_Hugou.h"

class HugouController : public QObject
{
    Q_OBJECT

public:
    HugouController(HugouView* hugouView, HugouModel* hugouModel);
    ~HugouController();
    void openPDFEditFunction();
    
private:
    HugouView* m_hugouView;
    HugouModel* m_hugouModel;
    SettingsController* m_settingsController;
    ScheduleController* m_scheduleController;
    ThemeManager* m_themeManager;
};