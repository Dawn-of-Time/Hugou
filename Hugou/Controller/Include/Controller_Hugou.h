#pragma once
#include "Utils/Include/Utils_ConfigurationHelper.h"
#include "Utils/Include/Utils_MessegeHelper.h"
#include "Utils/Include/Utils_ThemeManager.h"
#include "Controller_Preference.h"
#include "Controller_Schedule.h"
#include "Controller_GlobalTop.h"
#include "Utils/Include/Utils_FloatingNoteManager.h"
#include "Model/Include/Model_Hugou.h"
#include "View/Include/View_Hugou.h"

class HugouController : public QObject
{
    Q_OBJECT

public:
    HugouController(HugouView* hugouView, HugouModel* hugouModel);
    
private:
    HugouView* m_hugouView;
    HugouModel* m_hugouModel;
    PreferenceController* m_preferenceController;
    ScheduleController* m_scheduleController;
};