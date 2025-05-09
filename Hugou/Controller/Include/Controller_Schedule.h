#pragma once
#include <QObject>
#include "View/Include/View_Schedule.h"
#include "Model/Include/Model_Schedule.h"
#include "Controller/Include/Controller_MemoSetting.h"

class ScheduleController :
    public QObject
{
    Q_OBJECT

public:
    ScheduleController(ScheduleView* scheduleView, ScheduleModel* scheduleModel, QObject* parent);
    ~ScheduleController();
    void readAndGenerateMemos();

private:
    ScheduleView* m_scheduleView;
    ScheduleModel* m_scheduleModel;
    MemoSettingController* m_memoSettingController;
	QList<MemoSettingController*> m_memoSettingControllerList;
};

