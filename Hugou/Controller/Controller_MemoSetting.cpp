#include "Controller_MemoSetting.h"

MemoSettingController::MemoSettingController(MemoSettingView* memoSettingView, MemoSettingModel* memoSettingModel)
	:QObject(), m_memoSettingView(memoSettingView), m_memoSettingModel(memoSettingModel)
{
	m_memoSettingView->applyTemplate(m_memoSettingModel->m_templateList[0]);
}

MemoSettingController::~MemoSettingController()
{
	delete m_memoSettingModel;
}