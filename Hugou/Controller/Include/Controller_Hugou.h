#pragma once
#include "Assistance/Include/Assistance_PreferenceHelper.h"
#include "Assistance/Include/Assistance_MessegeHelper.h"
#include "Assistance/Include/Assistance_ThemeManager.h"
#include "Controller/Include/Controller_Preference.h"
#include "Controller/Include/Controller_Schedule.h"
#include "Assistance/Include/Assistance_FloatingNoteManager.h"
#include "Model/Include/Model_Hugou.h"
#include "View/Include/View_Hugou.h"

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
    PreferenceController* m_preferenceController;
    ScheduleController* m_scheduleController;
    ThemeManager* m_themeManager;
};