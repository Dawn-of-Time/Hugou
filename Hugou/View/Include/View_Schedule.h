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
#include <QCheckBox>
#include "Controller_TaskSetting.h"
#include "Card_MonthOverview.h"
#include "View_MemoSetting.h"
#include "Struct_Memo.h"
#include "CheckBox.h"

class ScheduleView : public QWidget
{
    Q_OBJECT
public:
    ScheduleView(QWidget* parent);
    void switchToMonthView();
    void switchToWeekView();
    void switchToDayView();

signals:
    void SignalDarkenBackground();
    void SignalBrightenBackground();
    void SignalAddMemoRequest();

private:
    friend class ScheduleController;
    enum ViewMode {
        Day,
        Week,
        Month
    };
    QHBoxLayout* m_scheduleLayout;
    QWidget* m_centralWidget;
    QWidget* m_cardWidget;
    QVBoxLayout* m_centralWidgetLayout;
    QVBoxLayout* m_cardWidgetLayout;
    QWidget* m_viewSwitchBar;
    QHBoxLayout* m_viewSwitchBarLayout;
    QPushButton* m_monthViewSwitchButton;
    QLabel* m_monthToWeekForward;
    QPushButton* m_weekViewSwitchButton;
    QLabel* m_weekToDayForward;
    QPushButton* m_dayViewSwitchButton;
    //QAnimationGroup* m_switchViewAnimationGroup;
    QWidget* m_memoGeneralWidget;
    QVBoxLayout* m_memoGeneralWidgetLayout;
    QWidget* m_memoGeneralTitleWidget;
    QHBoxLayout* m_memoGeneralTitleWidgetLayout;
    QLabel* m_memoGeneralTitle;
    QWidget* m_memoListWidget;
    QVBoxLayout* m_memoListWidgetLayout;

    QWidget* m_addMemoWidget;
    QVBoxLayout* m_addMemoWidgetLayout;
    FadeEffectButton* m_addMemoBriefWidget;
    QHBoxLayout* m_addMemoBriefWidgetLayout;
    QPushButton* m_dropDownButton;
    CheckBox* m_checkBox;
    QWidget* m_memoContentWidget;
    QVBoxLayout* m_memoContentWidgetLayout;
    QLabel* m_memoContent;
    QLabel* m_memoSubContent;
    ViewMode m_currentView;
    
    QList<QGraphicsOpacityEffect*> m_weekOpacityEffectListForAMonth = {};
    QList<QString> m_monthNameList = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    QMap<QWidget*, Memo> m_memoButtonMap = {};
    QMap<FadeEffectButton*, MemoSettingView*> m_memoSettingMap = {};
    int m_currentWeekIndex;
    enum AnimationFlag {
        NoSwitch, MonthToWeek, WeekToDay, DayToMonth,
        WeekToMonth, DayToWeek, MonthToDay,
    }; // 指示m_switchViewAnimationGroup中运行的动画是从何视图到何视图
    AnimationFlag m_animationFlag = NoSwitch;
    void setupUi();
    void generateMemos(QList<Memo> memoList);
    void showMemoSetting(FadeEffectButton* memoBriefWidget);

    // 当播放与GraphicsEffect有关的动画时，下述两函数需要依次在播放前和播放后调用。
    // enableGraphicsEffect函数用于启用这些效果。
    // disableGraphicsEffect函数用于禁用这些效果，以免与父控件的效果冲突，引发painter唯一性错误。
    void enableGraphicsEffect();
    void disableGraphicsEffect();

    void hideOtherWeeks();
    void showOtherWeeks();

    void resizeEvent(QResizeEvent* event) override;
};