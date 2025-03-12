#pragma once
#include "Widgets/Include/MemoSettingItem/MemoSettingItem.h"
#include <QDate>
#include <QPushButton>
#include <QParallelAnimationGroup>
#include <QLineEdit>
#include <QGraphicsOpacityEffect>
#include "Widgets/Include/FadeEffectButton.h"
#include "Widgets/Include/CloseWhenLeaveWidget.h"

class MemoTimeItem :
    public MemoSettingItem
{
    Q_OBJECT
public:
    enum TimeSelectMode
    {
        BeginMode,
        EndMode
    };
    MemoTimeItem(QWidget* parent = nullptr);
    ~MemoTimeItem();
    void loadMonthView(const QDate& date);

private:
    bool m_hasReminder = false;
    TimeSelectMode m_timeSelectMode = TimeSelectMode::BeginMode;
    QDate m_currentDate = QDate();
    QPushButton* m_todayButton;
    QPushButton* m_beginButton;
    QPushButton* m_endButton;
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
    QWidget* m_weekdaysBar;
    QHBoxLayout* m_weekdaysBarLayout;
    QWidget* m_beginWidget;
    QWidget* m_beginAndEndWidget;
    QWidget* m_endWidget;
    QLabel* m_beginLabel;
    QLabel* m_beginAndEndLabel;
    QLabel* m_endLabel;
    QWidget* m_timeWidget;
    QHBoxLayout* m_timeWidgetLayout;
    QWidget* m_beginTimeWidget;
    QVBoxLayout* m_beginTimeWidgetLayout;
    QWidget* m_beginTimeYYYYMMDDWidget;
    QHBoxLayout* m_beginTimeYYYYMMDDWidgetLayout;
    QPushButton* m_beginTimeYearButton;
    QPushButton* m_beginTimeMonthButton;
    QPushButton* m_beginTimeDayButton;
    QWidget* m_beginTimeHHMMWidget;
    QHBoxLayout* m_beginTimeHHMMWidgetLayout;
    QPushButton* m_beginTimeHourButton;
    QPushButton* m_beginTimeMinuteButton;
    QLabel* m_toLabel;
    QWidget* m_endTimeWidget;
    QVBoxLayout* m_endTimeWidgetLayout;
    QWidget* m_endTimeYYYYMMDDWidget;
    QHBoxLayout* m_endTimeYYYYMMDDWidgetLayout;
    QPushButton* m_endTimeYearButton;
    QPushButton* m_endTimeMonthButton;
    QPushButton* m_endTimeDayButton;
    QWidget* m_endTimeHHMMWidget;
    QHBoxLayout* m_endTimeHHMMWidgetLayout;
    QPushButton* m_endTimeHourButton;
    QPushButton* m_endTimeMinuteButton;

    QList<QPushButton*> m_weekIndexButtonListForAMonth = {};
    QList<QPushButton*> m_dayListForAMonth = {};
    QList<QWidget*> m_weekListForAMonth = {};
    QList<QString> m_monthNameList = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    QMap<QString, int> m_monthMap =
    {
        { "Jan", 1},
        { "Feb", 2},
        {"Mar", 3},
        {"Apr", 4},
        {"May", 5},
        {"Jun", 6},
        {"Jul", 7},
        {"Aug", 8},
        {"Sep", 9},
        {"Oct", 10},
        {"Nov", 11},
        {"Dec",  12}
    };

    void setupUi();
    void switchReminder();
    void goBackAMonth();
    void goForwardAMonth();
    void goBackToToday();
    void setYearAndMonth();
    void enableGraphicsEffect();
    void disableGraphicsEffect();
    QPoint getLabelPos(QWidget* label, QPushButton* dayButton);
    void showEvent(QShowEvent* event) override;
};
