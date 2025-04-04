#include "Model/Include/Model_Hugou.h"

HugouModel::HugouModel()
    : QObject()
{
    m_preferenceModel = new PreferenceModel(this);
    m_scheduleModel = new ScheduleModel(this);
}