#pragma once
#include <QObject>
#include "Model_MemoSetting.h"
#include "View_MemoSetting.h"

class MemoSettingController :
    public QObject
{
public:
    MemoSettingController(MemoSettingView* memoSettingView, MemoSettingModel* memoSettingModel);
    ~MemoSettingController();

private:
    MemoSettingView* m_memoSettingView;
    MemoSettingModel* m_memoSettingModel;
};

