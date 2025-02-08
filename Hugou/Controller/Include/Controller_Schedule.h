#pragma once
#include <QObject>
#include "View_Schedule.h"
#include "Model_Schedule.h"
#include "Controller_MemoSetting.h"

class ScheduleController :
    public QObject
{
    Q_OBJECT

public:
    ScheduleController(ScheduleView* scheduleView, ScheduleModel* scheduleModel);
    ~ScheduleController();
    void readAndGenerateMemos();

private:
    ScheduleView* m_scheduleView;
    ScheduleModel* m_scheduleModel;
    MemoSettingController* m_memoSettingController;
};

