#pragma once
#include <QObject>
#include "Model/Include/Model_MemoSetting.h"
#include "View/Include/View_MemoSetting.h"

class MemoSettingController :
    public QObject
{
    Q_OBJECT

public:
    MemoSettingController(MemoSettingView* memoSettingView, MemoSettingModel* memoSettingModel);
    ~MemoSettingController();
    void applyTemplate(const MemoTemplate& memoTemplate);
    void addMemoSettingItem(const MemoSettingItemType& itemType);

private:
    MemoSettingView* m_memoSettingView;
    MemoSettingModel* m_memoSettingModel;
};

