#include "Controller/Include/Controller_Schedule.h"

ScheduleController::ScheduleController(ScheduleView* scheduleView, ScheduleModel* scheduleModel, QObject* parent)
	:QObject(parent), m_scheduleView(scheduleView), m_scheduleModel(scheduleModel)
{
	readAndGenerateMemos();
	for (QObject* object : m_scheduleView->m_memoListWidget->children())
	{
		if (MemoWidget* memoWidget = qobject_cast<MemoWidget*>(object))
		{
			MemoSettingController* memoSettingController = new MemoSettingController(
				memoWidget->getMemoSettingView(), m_scheduleModel->m_memoSettingModel
			);
			m_memoSettingControllerList.append(memoSettingController);
		}
	}
	connect(m_scheduleView->m_monthViewSwitchButton, &QPushButton::clicked, m_scheduleView, &ScheduleView::switchToMonthView);
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
	for (Memo& memo : m_scheduleModel->m_memoList)
		m_scheduleView->generateMemo(memo);
	m_scheduleView->addAddMemoWidget();
}
