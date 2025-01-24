#include "Controller_Schedule.h"

ScheduleController::ScheduleController(ScheduleView* scheduleView, ScheduleModel* scheduleModel)
	:QObject(), m_scheduleView(scheduleView), m_scheduleModel(scheduleModel)
{
	connect(m_scheduleView->m_monthViewSwitchButton, &QPushButton::clicked, m_scheduleView, &ScheduleView::switchToMonthView);
	connect(m_scheduleView->m_addTaskButton, &QPushButton::clicked, this, &ScheduleController::showTaskSetting);
}

void ScheduleController::showTaskSetting()
{
	foreach(QWidget* child, m_scheduleView->findChildren<QWidget*>()) child->setEnabled(false);
	TaskSettingModel* taskSettingModel = new TaskSettingModel;
	TaskSettingView* taskSettingView = new TaskSettingView(m_scheduleView);
	m_scheduleView->m_taskSettingView = taskSettingView;
	TaskSettingController* taskeSettingController = new TaskSettingController(taskSettingView, taskSettingModel);
	taskSettingView->raise();
	taskSettingView->move(QPoint(m_scheduleView->width(), 0));
	taskSettingView->show(); 
	taskSettingView->slideIn();
	connect(taskeSettingController, &TaskSettingController::SignalClose, this, &ScheduleController::closeTaskSetting);
}

void ScheduleController::closeTaskSetting(TaskSettingController* taskeSettingController)
{
	taskeSettingController->close();
	delete taskeSettingController;
	m_scheduleView->m_taskSettingView = nullptr;
	foreach(QWidget * child, m_scheduleView->findChildren<QWidget*>()) child->setEnabled(true);
}
