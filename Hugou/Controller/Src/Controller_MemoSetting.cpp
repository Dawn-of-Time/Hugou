#include "Controller/Include/Controller_MemoSetting.h"

MemoSettingController::MemoSettingController(MemoSettingView* memoSettingView, MemoSettingModel* memoSettingModel)
	:QObject(), m_memoSettingView(memoSettingView), m_memoSettingModel(memoSettingModel)
{
	applyTemplate(m_memoSettingView->m_memo->memoTemplate);
}

MemoSettingController::~MemoSettingController()
{
}

void MemoSettingController::applyTemplate(const MemoTemplate& memoTemplate)
{
	m_memoSettingView->applyGeneralStyle(memoTemplate);
	m_memoSettingView->generateNewPage();
	for (const MemoSettingItemType& itemType : memoTemplate.templateContent)
		addMemoSettingItem(itemType);
	m_memoSettingView->setMaximumHeight(m_memoSettingView->getSuitableHeight());
}

void MemoSettingController::addMemoSettingItem(const MemoSettingItemType& itemType)
{
	MemoSettingItem* widget = nullptr;
	switch (itemType)
	{
	case MemoSettingItemType::Type:
	{
		widget = new MemoTypeItem(m_memoSettingModel->m_typeLabelList, m_memoSettingModel->m_typeLabelMap, m_memoSettingModel->m_typeList);
		break;
	}
	case MemoSettingItemType::Time:
		widget = new MemoTimeItem();
		break;
	case MemoSettingItemType::ImportanceAndUrgency:
		widget = new MemoImportanceAndUrgencyItem();
		break;
	case MemoSettingItemType::Detail:
		widget = new MemoDetailItem();
		break;
	case MemoSettingItemType::SubMemo:
		widget = new MemoSubMemoItem();
		break;
	case MemoSettingItemType::Award:
		widget = new MemoAwardItem();
		break;
	case MemoSettingItemType::Reference:
		widget = new MemoReferenceItem();
		break;
	default:
		break;
	}
	if (widget) m_memoSettingView->addMemoSettingItemToLayout(widget);
}