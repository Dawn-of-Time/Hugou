#include "Controller_Schedule.h"

ScheduleController::ScheduleController(ScheduleView* scheduleView, ScheduleModel* scheduleModel)
	:QObject(), m_scheduleView(scheduleView), m_scheduleModel(scheduleModel)
{

}

