#pragma once
#include <QLabel>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include "Struct_Task.h"

class TaskSettingView :
    public QWidget
{
    Q_OBJECT

public:
    explicit TaskSettingView(QWidget* parent);

signals:
    void SignalTaskPrepared(Task task);

private:
    QLabel* m_generalTitle;
    QWidget* m_list;
    QVBoxLayout* m_listLayout;
    QLabel* m_sketchTitle;
    QLineEdit* m_sketch;
    QLabel* m_taskTypeTitle;
    QWidget* m_taskTypeWidget;
    QWidget* m_briefTaskTypeWidget;
    QHBoxLayout* m_briefTaskTypeWidgetLayout;
    QWidget* m_detailedTaskTypeWidget;
    QVBoxLayout* m_detailedTaskTypeWidgetLayout;
    QWidget* m_timeTitle;
    QWidget* m_time;
    QPushButton* m_showOrHideButton;
    QWidget* m_postpone;
    QWidget* m_importance;
    QLabel* m_detailTitle;
    QLineEdit* m_detail;
    QLabel* m_awardTitle;
    QLineEdit* m_award;
    QWidget* m_planPanel;

    void setupUi();
};