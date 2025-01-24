#pragma once
#include <QObject>
#include "View_TaskSetting.h"
#include "Model_TaskSetting.h"

class TaskSettingController :
    public QObject
{
    Q_OBJECT

public:
    TaskSettingController(TaskSettingView* taskSettingView, TaskSettingModel* taskSettingModel);
    void close();

signals:
    void SignalClose(TaskSettingController* taskSettingController);

private:
    TaskSettingView* m_taskSettingView;
    TaskSettingModel* m_taskSettingModel;
};

