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
    }; // 指示m_switchViewAnimationGroup中运行的动画是从何视图到何视图
    AnimationFlag m_animationFlag = NoSwitch;
    void setupUi();

    // 当播放与GraphicsEffect有关的动画时，下述两函数需要依次在播放前和播放后调用。
    // enableGraphicsEffect函数用于启用这些效果。
    // disableGraphicsEffect函数用于禁用这些效果，以免与父控件的效果冲突，引发painter唯一性错误。
    void enableGraphicsEffect();
    void disableGraphicsEffect();

    void hideOtherWeeks();
    void showOtherWeeks();

    void resizeEvent(QResizeEvent* event) override;
};