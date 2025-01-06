#pragma once
#include <QObject>
#include "View_Schedule.h"
#include "Model_Schedule.h"
class ScheduleController :
    public QObject
{
    Q_OBJECT

public:
    ScheduleController(ScheduleView* scheduleView, ScheduleModel* scheduleModel);

private:
    ScheduleView* m_scheduleView;
    ScheduleModel* m_scheduleModel;
};

