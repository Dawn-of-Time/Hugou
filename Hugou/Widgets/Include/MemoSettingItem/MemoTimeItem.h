#pragma once
#include "Widgets/Include/MemoSettingItem/MemoSettingItem.h"
#include <QDate>
#include <QPushButton>
#include <QParallelAnimationGroup>
#include <QLineEdit>
#include <QButtonGroup>
#include <QGraphicsOpacityEffect>
#include <QStackedWidget>
#include "Widgets/Include/FadeEffectButton.h"
#include "Widgets/Include/DateTimeSelector.h"
#include "Widgets/Include/YearAndMonthSelector.h"
#include "Widgets/Include/Menu/Menu.h"
#include "Widgets/Include/Menu/SingleSelectionMenuItem.h"
#include "Widgets/Include/Menu/DateTimeMenuItem.h"

class MemoTimeItem :
    public MemoSettingItem
{
    Q_OBJECT
public:
    MemoTimeItem(QWidget* parent = nullptr);
    ~MemoTimeItem();
    void loadMonthView(const QDate& date);

private:
    enum TimeSelectMode
    {
        DefaultMode,
        BeginMode,
        EndMode
    };
    enum DayButtonStatus
    {
        NotSelectedAndNotThisMonth,
        NotSelectedAndThisMonth,
        SelectedAndNotThisMonth,
        SelectedAndThisMonth
    };
    struct DayAttribution
    {
        bool isExisted;
        int lowerBound;
        int upperBound;
    };
    enum ReminderMode
    {
        Once,
        Repeat
    };
    enum ReminderRepeatMode
    {
        EveryDay,
        EveryWeek,
        EveryMonth,
        EveryYear,
        Custom
    };
    struct Reminder
    {
        bool hasReminder = false;
        QDateTime reminderDateTime = QDateTime();
        ReminderMode mode = Once;
        ReminderRepeatMode repeateMode = ReminderRepeatMode::EveryDay;
    };
    TimeSelectMode m_timeSelectMode = TimeSelectMode::DefaultMode;
    QDate m_selectedDate = QDate();
    DayAttribution m_lastMonth;
    DayAttribution m_thisMonth;
    DayAttribution m_nextMonth;
    FadeEffectButton* m_todayButton;
    FadeEffectButton* m_beginButton = nullptr;
    FadeEffectButton* m_endButton = nullptr;
    QDateTime m_beginDateTime = QDateTime();
    QDateTime m_endDateTime = QDateTime();
    QDate m_startDate;  // 月历初按钮的日期
    QDate m_finishDate; // 月历末按钮的日期
    Reminder m_reminder;
    QParallelAnimationGroup* m_animationGroup;
    QVBoxLayout* m_contentLayout;
    QWidget* m_reminderWidget;
    QPushButton* m_reminderButton;
    QPushButton* m_off;
    QPushButton* m_moreButton;
    QGraphicsOpacityEffect* m_moreButtonEffect;
    QWidget* m_dateWidget;
    QVBoxLayout* m_dateWidgetLayout;
    QWidget* m_dateTitleWidget;
    QHBoxLayout* m_dateTitleWidgetLayout;
    FadeEffectButton* m_dateTitle;
    QWidget* m_actionWidget;
    QHBoxLayout* m_actionWidgetLayout;
    QPushButton* m_backToTodayButton;
    QPushButton* m_backButton;
    QPushButton* m_forwardButton;
    QWidget* m_monthWidget;
    QVBoxLayout* m_monthWidgetLayout;
    QButtonGroup* m_dayGroup;
    QWidget* m_weekdaysBar;
    QHBoxLayout* m_weekdaysBarLayout;
    QLabel* m_beginLabel;
    QLabel* m_beginAndEndLabel;
    QLabel* m_endLabel;
    QWidget* m_timeWidget;
    QHBoxLayout* m_timeWidgetLayout;
    DateTimeSelector* m_beginDateTimeSelector;
    QLabel* m_toLabel;
    DateTimeSelector* m_endDateTimeSelector;
    
    Menu* m_reminderMenu;
    SingleSelectionMenuItem* m_reminderModeSelectionMenuItem;
    DateTimeMenuItem* m_reminderDateTimeMenuItem;
    SingleSelectionMenuItem* m_repeatModeSelectionMenuItem;

    QList<QPushButton*> m_weekIndexButtonListForAMonth = {};
    QList<QWidget*> m_weekListForAMonth = {};
    QList<FadeEffectButton*> m_dayListForAMonth = {};
    QList<QString> m_monthNameList = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    QMap<QString, int> m_monthMap =
    {
        {"Jan", 1},
        {"Feb", 2},
        {"Mar", 3},
        {"Apr", 4},
        {"May", 5},
        {"Jun", 6},
        {"Jul", 7},
        {"Aug", 8},
        {"Sep", 9},
        {"Oct", 10},
        {"Nov", 11},
        {"Dec", 12}
    };

    void setupUi();
    void switchReminder();
    void switchReminderMode(const QString& mode);
    void goBackAMonth();
    void goForwardAMonth();
    void goBackToToday();
    void setYearAndMonth();
    void setBeginOrEnd();
    void setReminder();
    void enableGraphicsEffect();
    void disableGraphicsEffect();
    QPoint getLabelPos(QLabel* label, QPushButton* dayButton);
    void showEvent(QShowEvent* event) override;
};
