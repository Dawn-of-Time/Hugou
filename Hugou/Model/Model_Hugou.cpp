#include "Model_Hugou.h"

HugouModel::HugouModel()
    : QObject()
{
    m_preferenceModel = new PreferenceModel();
    m_scheduleModel = new ScheduleModel();
}

HugouModel::~HugouModel()
{
    delete m_preferenceModel;
    delete m_scheduleModel;
}