#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QGraphicsEffect>
#include <QFile>
#include <QDate>
#include <cmath>
#include "Controller_TaskSetting.h"

class ScheduleView : public QWidget
{
    Q_OBJECT
public:
    ScheduleView(QWidget* parent);
    void loadMonthView(QDate date);
    void switchToMonthView();
    void switchToWeekView();
    void switchToDayView();

signals:
    void SignalDarkenBackground();
    void SignalBrightenBackground();

private:
    friend class ScheduleController;
    enum ViewMode {
        Day,
        Week,
        Month
    };
    QVBoxLayout* m_scheduleLayout;
    QWidget* m_viewSwitchBar;
    QHBoxLayout* m_viewSwitchBarLayout;
    QPushButton* m_monthViewSwitchButton;
    QPushButton* m_weekViewSwitchButton;
    QPushButton* m_dayViewSwitchButton;
    QPushButton* m_addTaskButton;
    QAnimationGroup* m_switchViewAnimationGroup;
    QWidget* m_scheduleWidget;
    QWidget* m_weekdaysBar;
    QHBoxLayout* m_weekdaysBarLayout;
    QVBoxLayout* m_scheduleWidgetLayout;
    TaskSettingView* m_taskSettingView = nullptr;
    ViewMode m_currentView;
    QList<QPushButton*> m_weekIndexButtonListForAMonth = {};
    QList<QPushButton*> m_dayListForAMonth = {};
    QList<QWidget*> m_weekListForAMonth = {};
    QList<QGraphicsOpacityEffect*> m_weekOpacityEffectListForAMonth = {};
    QList<QString> m_monthNameList = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    int m_currentWeekIndex;
    enum AnimationFlag {
        NoSwitch, MonthToWeek, WeekToDay, DayToMonth,
        WeekToMonth, DayToWeek, MonthToDay,
    }; // ָʾm_switchViewAnimationGroup�����еĶ����ǴӺ���ͼ������ͼ
    AnimationFlag m_animationFlag = NoSwitch;
    void setupUi();

    // ��������GraphicsEffect�йصĶ���ʱ��������������Ҫ�����ڲ���ǰ�Ͳ��ź���á�
    // enableGraphicsEffect��������������ЩЧ����
    // disableGraphicsEffect�������ڽ�����ЩЧ���������븸�ؼ���Ч����ͻ������painterΨһ�Դ���
    void enableGraphicsEffect();
    void disableGraphicsEffect();

    void hideOtherWeeks();
    void showOtherWeeks();

    void resizeEvent(QResizeEvent* event) override;
};