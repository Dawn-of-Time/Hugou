#include "Controller_Schedule.h"

ScheduleController::ScheduleController(ScheduleView* scheduleView, ScheduleModel* scheduleModel)
	:QObject(), m_scheduleView(scheduleView), m_scheduleModel(scheduleModel)
{
	readAndGenerateMemos();
	connect(m_scheduleView->m_monthViewSwitchButton, &QPushButton::clicked, m_scheduleView, &ScheduleView::switchToMonthView);
	connect(m_scheduleView, &ScheduleView::SignalAddMemoRequest, m_scheduleView, &ScheduleView::showMemoSetting);
}

ScheduleController::~ScheduleController()
{
	delete m_scheduleModel;
}

void ScheduleController::readAndGenerateMemos()
{
	m_scheduleModel->readMemoDatabase();
	m_scheduleView->generateMemos(m_scheduleModel->m_memoList);
}
