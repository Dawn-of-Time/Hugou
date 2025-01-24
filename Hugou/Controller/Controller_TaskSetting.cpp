#include "Controller_TaskSetting.h"


TaskSettingController::TaskSettingController(TaskSettingView* taskSettingView, TaskSettingModel* taskSettingModel)
	:m_taskSettingView(taskSettingView), m_taskSettingModel(taskSettingModel)
{
	connect(m_taskSettingView->m_closeButton, &QPushButton::clicked, [&]() {emit SignalClose(this); });
}

void TaskSettingController::close()
{
	m_taskSettingView->slideOut();
	delete m_taskSettingModel;
}