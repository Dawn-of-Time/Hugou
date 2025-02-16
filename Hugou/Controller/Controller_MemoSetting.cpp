#include "Controller_MemoSetting.h"

MemoSettingController::MemoSettingController(MemoSettingView* memoSettingView, MemoSettingModel* memoSettingModel)
	:QObject(), m_memoSettingView(memoSettingView), m_memoSettingModel(memoSettingModel)
{
	applyTemplate(m_memoSettingView->m_memo.memoTemplate);
}

MemoSettingController::~MemoSettingController()
{
}

void MemoSettingController::applyTemplate(MemoTemplate memoTemplate)
{
	m_memoSettingView->applyGeneralStyle(memoTemplate);
	for (MemoSettingItemType itemType : memoTemplate.templateContent)
	{
		QWidget* widget = m_memoSettingView->m_memoContentMap.value(itemType);
		switch (itemType)
		{
		case MemoSettingItemType::Type:
		{
			MemoTypeItem* item = qobject_cast<MemoTypeItem*>(widget);
			for (MemoType memoType : m_memoSettingModel->m_typeList)
				item->addMemoType(memoType);
			break;
		}
		case MemoSettingItemType::Time:
			break;
		case MemoSettingItemType::ImportanceAndUrgency:
			break;
		case MemoSettingItemType::Detail:
			break;
		case MemoSettingItemType::SubMemo:
			break;
		case MemoSettingItemType::Award:
			break;
		case MemoSettingItemType::Reference:
			break;
		default:
			break;
		}
	}
}