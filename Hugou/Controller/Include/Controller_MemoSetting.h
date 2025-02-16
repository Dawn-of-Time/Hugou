#pragma once
#include <QObject>
#include "Model_MemoSetting.h"
#include "View_MemoSetting.h"

class MemoSettingController :
    public QObject
{
    Q_OBJECT

public:
    MemoSettingController(MemoSettingView* memoSettingView, MemoSettingModel* memoSettingModel);
    ~MemoSettingController();
    void applyTemplate(MemoTemplate memoTemplate);

private:
    MemoSettingView* m_memoSettingView;
    MemoSettingModel* m_memoSettingModel;
};

