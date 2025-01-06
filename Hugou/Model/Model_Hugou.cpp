#include "Model_Hugou.h"

HugouModel::HugouModel()
    : QObject()
{
    m_settingsModel = new SettingsModel();
    m_scheduleModel = new ScheduleModel();
}

HugouModel::~HugouModel()
{
    delete m_settingsModel;
    delete m_scheduleModel;
}