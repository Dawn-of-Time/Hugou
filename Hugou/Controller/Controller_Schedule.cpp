#include "Controller_Schedule.h"

ScheduleController::ScheduleController(ScheduleView* scheduleView, ScheduleModel* scheduleModel)
	:QObject(), m_scheduleView(scheduleView), m_scheduleModel(scheduleModel)
{
	readAndGenerateMemos();
	connect(m_scheduleView->m_monthViewSwitchButton, &QPushButton::clicked, m_scheduleView, &ScheduleView::switchToMonthView);
	connect(m_scheduleView->m_addMemoBriefWidget, &QPushButton::clicked, this, &ScheduleController::addMemo);
}

ScheduleController::~ScheduleController()
{
	delete m_scheduleModel;
	for (MemoSettingController* memoSettingController : m_memoSettingControllerList)
		delete memoSettingController;
}

void ScheduleController::readAndGenerateMemos()
{
	m_scheduleModel->readMemoDatabase();
	m_scheduleView->generateMemos(m_scheduleModel->m_memoList);
}

void ScheduleController::addMemo()
{
	FadeEffectButton* memoBriefWidget = qobject_cast<FadeEffectButton*>(sender());
	MemoSettingController* memoSettingController = new MemoSettingController(
		m_scheduleView->m_memoSettingMap[memoBriefWidget], m_scheduleModel->m_memoSettingModel
	);
	m_scheduleView->showMemoSetting(memoBriefWidget);
	m_memoSettingControllerList.append(memoSettingController);
}
