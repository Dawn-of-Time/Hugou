#include "View_Schedule.h"

ScheduleView::ScheduleView(QWidget* parent) :
	QWidget(parent)
{
    m_currentView = ViewMode::Month;
    m_switchViewAnimationGroup = new QSequentialAnimationGroup(this);
	setupUi();
}

void ScheduleView::setupUi()
{
    // 字体清单
    const QFont viewSwitchButtonFont = QFont("Hind Siliguri", 13);
    const QFont weekdayFont = QFont("Hind Siliguri", 11, QFont::Medium);

    m_scheduleLayout = new QVBoxLayout(this);
    m_viewSwitchBar = new QWidget(this);
    m_viewSwitchBar->setFixedHeight(60);
    m_viewSwitchBarLayout = new QHBoxLayout(m_viewSwitchBar);
    m_monthViewSwitchButton = new QPushButton(m_viewSwitchBar);
    m_monthViewSwitchButton->setFont(viewSwitchButtonFont);
    m_weekViewSwitchButton = new QPushButton(m_viewSwitchBar);
    m_weekViewSwitchButton->setFont(viewSwitchButtonFont);
    m_dayViewSwitchButton = new QPushButton(m_viewSwitchBar);
    m_dayViewSwitchButton->setFont(viewSwitchButtonFont);
    m_addTaskButton = new QPushButton("ADD", m_viewSwitchBar);
    m_addTaskButton->setFont(viewSwitchButtonFont);
    m_viewSwitchBarLayout->addWidget(m_monthViewSwitchButton);
    m_viewSwitchBarLayout->addWidget(m_weekViewSwitchButton);
    m_viewSwitchBarLayout->addWidget(m_dayViewSwitchButton);
    m_viewSwitchBarLayout->addWidget(m_addTaskButton);
    m_viewSwitchBarLayout->addStretch();

    m_scheduleWidget = new QWidget(this);
    m_scheduleWidgetLayout = new QVBoxLayout(m_scheduleWidget);
    m_scheduleWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_scheduleWidgetLayout->setSpacing(0);

    m_scheduleLayout->addWidget(m_viewSwitchBar);
    m_scheduleLayout->addWidget(m_scheduleWidget);

    QStringList weekdays = { "MON", "TUE", "WED", "THUR", "FRI", "SAT", "SUN" };
    m_weekdaysBar = new QWidget(m_scheduleWidget);
    m_weekdaysBar->setFixedHeight(15);
    m_weekdaysBarLayout = new QHBoxLayout(m_weekdaysBar);
    m_weekdaysBarLayout->setContentsMargins(0, 0, 0, 0);
    m_weekdaysBarLayout->setSpacing(0);
    QWidget* placeholder = new QWidget(m_weekdaysBar);
    placeholder->setFixedWidth(50);
    m_weekdaysBarLayout->addWidget(placeholder);
    for (int weekdayIndex = 0; weekdayIndex < 7; weekdayIndex++)
    {
        QLabel* weekday = new QLabel(weekdays[weekdayIndex], m_weekdaysBar);
        weekday->setFixedHeight(15);
        weekday->setStyleSheet("QLabel { border: 1px solid white }");
        weekday->setFont(weekdayFont);
        weekday->setAlignment(Qt::AlignCenter);
        m_weekdaysBarLayout->addWidget(weekday);
    }
    m_scheduleWidgetLayout->addWidget(m_weekdaysBar);

    loadMonthView(QDate::currentDate());
    QFile styleFile(":/theme/Global/schedule.qss");
    styleFile.open(QIODeviceBase::ReadOnly);
    this->setStyleSheet(styleFile.readAll());
    styleFile.close();
}

void ScheduleView::loadMonthView(QDate date)
{
    m_dayListForAMonth.clear();
    m_weekListForAMonth.clear();
    m_weekOpacityEffectListForAMonth.clear();
    int year = date.year();
    int month = date.month();
    int firstDayOfWeek = QDate(year, month, 1).dayOfWeek();
    int daysNum = date.daysInMonth();
    int weeksNum = (int)ceil(double(daysNum + firstDayOfWeek - 1) / 7);
    m_monthViewSwitchButton->setText(m_monthNameList[month - 1]);
    // 绘制网格
    for (int weekIndex = 1; weekIndex <= weeksNum; weekIndex++)
    {
        // 周网格
        QWidget* week = new QWidget(m_scheduleWidget);
        QHBoxLayout* weekLayout = new QHBoxLayout(week);
        weekLayout->setContentsMargins(0, 0, 0, 0);
        weekLayout->setSpacing(0);
        QGraphicsOpacityEffect* weekOpacity = new QGraphicsOpacityEffect;
        weekOpacity->setOpacity(1);
        weekOpacity->setEnabled(false);
        week->setGraphicsEffect(weekOpacity);
        // 周序号
        QPushButton* weekIndexButton = new QPushButton(QString::number(weekIndex), week);
        weekIndexButton->setStyleSheet("QPushButton { background-color: rgba(0, 0, 255, 0.3); border: 1px solid white; border-radius: 5px }");
        weekIndexButton->setFont(QFont("Roboto", 13, QFont::Normal));
        weekIndexButton->setFixedWidth(50);
        weekIndexButton->setMinimumHeight(15);
        weekIndexButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        weekIndexButton->setCursor(Qt::PointingHandCursor);
        weekLayout->addWidget(weekIndexButton);
        connect(weekIndexButton, &QPushButton::clicked, this, &ScheduleView::switchToWeekView);
        m_weekIndexButtonListForAMonth.append(weekIndexButton);
        for (int dayIndex = 1; dayIndex <= 7; dayIndex++)
        {
            // 天网格
            QPushButton* day = new QPushButton(week);
            day->setStyleSheet("QPushButton { text-align: top; background-color: rgba(0, 0, 255, 0.1); border: 1px solid white; border-radius: 5px }");
            day->setFont(QFont("Roboto", 13, QFont::Normal));
            day->setMinimumHeight(15);
            day->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            weekLayout->addWidget(day);
            m_dayListForAMonth.append(day);
        }
        m_scheduleWidgetLayout->addWidget(week);
        m_weekOpacityEffectListForAMonth.append(weekOpacity);
        m_weekListForAMonth.append(week);
    }
    // 在网格中填充日期
    for (int dayIndex = 1; dayIndex <= daysNum; dayIndex++)
        m_dayListForAMonth[firstDayOfWeek + dayIndex - 2]->setText(QString::number(dayIndex));
}

void ScheduleView::switchToMonthView()
{
    enableGraphicsEffect();
    m_weekViewSwitchButton->setHidden(true);
    m_dayViewSwitchButton->setHidden(true);
    if (m_currentView == ViewMode::Week)
    {
        m_switchViewAnimationGroup->clear();
        // 收缩指定周
        QPropertyAnimation* shrinkAnimation = new QPropertyAnimation(m_weekListForAMonth[m_currentWeekIndex - 1], "geometry");
        shrinkAnimation->setStartValue(m_weekListForAMonth[m_currentWeekIndex - 1]->geometry());
        int endHeight = (m_scheduleWidget->height() - 15) / m_weekListForAMonth.length();
        int endY = 15 + (m_currentWeekIndex - 1) * endHeight;
        shrinkAnimation->setEndValue(QRect(0, endY, m_scheduleWidget->width(), endHeight));
        shrinkAnimation->setDuration(300);
        shrinkAnimation->setEasingCurve(QEasingCurve::OutQuint);
        // 显示其余周
        QParallelAnimationGroup* fadeInGroup = new QParallelAnimationGroup;
        for (int weekIndex = 1; weekIndex <= m_weekOpacityEffectListForAMonth.size(); weekIndex++)
        {
            if (weekIndex != m_currentWeekIndex)
            {
                QPropertyAnimation* fadeAnimation = new QPropertyAnimation(m_weekOpacityEffectListForAMonth[weekIndex - 1], "opacity");
                fadeAnimation->setStartValue(0);
                fadeAnimation->setEndValue(1);
                fadeAnimation->setDuration(200);
                fadeInGroup->addAnimation(fadeAnimation);
            }
        }
        m_switchViewAnimationGroup->addAnimation(fadeInGroup);
        m_switchViewAnimationGroup->disconnect();
        connect(m_switchViewAnimationGroup, &QAnimationGroup::finished, this, &ScheduleView::disableGraphicsEffect);
        connect(shrinkAnimation, &QPropertyAnimation::finished, [&]()
            {
                showOtherWeeks();
                m_switchViewAnimationGroup->start();
            });
        this->setEnabled(false);
        shrinkAnimation->start(QPropertyAnimation::DeleteWhenStopped);
    }
}

void ScheduleView::switchToWeekView()
{
    enableGraphicsEffect();
    m_weekViewSwitchButton->setHidden(false);
    m_dayViewSwitchButton->setHidden(true);
    if (m_currentView == ViewMode::Month)
    {
        m_animationFlag = AnimationFlag::MonthToWeek;
        m_currentWeekIndex = m_weekIndexButtonListForAMonth.indexOf(qobject_cast<QWidget*>(sender())) + 1;
        m_weekViewSwitchButton->setText("Week " + QString::number(m_currentWeekIndex));
        m_switchViewAnimationGroup->clear();
        // 隐藏其余周
        QParallelAnimationGroup* fadeOutGroup = new QParallelAnimationGroup;
        for (int weekIndex = 1; weekIndex <= m_weekOpacityEffectListForAMonth.size(); weekIndex++)
        {
            if (weekIndex != m_currentWeekIndex)
            {
                QPropertyAnimation* fadeAnimation = new QPropertyAnimation(m_weekOpacityEffectListForAMonth[weekIndex - 1], "opacity");
                fadeAnimation->setStartValue(1);
                fadeAnimation->setEndValue(0);
                fadeAnimation->setDuration(200);
                fadeOutGroup->addAnimation(fadeAnimation);
            }
        }
        // 延展指定周
        QPropertyAnimation* expandAnimation = new QPropertyAnimation(m_weekListForAMonth[m_currentWeekIndex - 1], "geometry");
        expandAnimation->setStartValue(m_weekListForAMonth[m_currentWeekIndex - 1]->geometry());
        expandAnimation->setEndValue(QRect(0, 15, m_scheduleWidget->width(), m_scheduleWidget->height() - 15));
        expandAnimation->setDuration(400);
        expandAnimation->setEasingCurve(QEasingCurve::OutQuint);
        m_switchViewAnimationGroup->addAnimation(fadeOutGroup);
        m_switchViewAnimationGroup->addAnimation(expandAnimation);
        m_switchViewAnimationGroup->disconnect();
        connect(m_switchViewAnimationGroup, &QAnimationGroup::finished, this, &ScheduleView::hideOtherWeeks);
        // 动画播放期间，禁用视图
        this->setEnabled(false);
        m_switchViewAnimationGroup->start();
    }  
}

void ScheduleView::switchToDayView()
{
    if (m_currentView == ViewMode::Week)
    {
        m_animationFlag = AnimationFlag::WeekToDay;
        m_switchViewAnimationGroup->clear();
        // 隐藏其余天
        QParallelAnimationGroup* fadeOutGroup = new QParallelAnimationGroup;
        for (int weekIndex = 1; weekIndex <= m_weekOpacityEffectListForAMonth.size(); weekIndex++)
        {
            if (weekIndex != 2)
            {
                QPropertyAnimation* fadeAnimation = new QPropertyAnimation(m_weekOpacityEffectListForAMonth[weekIndex - 1], "opacity");
                fadeAnimation->setStartValue(1);
                fadeAnimation->setEndValue(0);
                fadeAnimation->setDuration(300);
                fadeOutGroup->addAnimation(fadeAnimation);
                //m_weekListForAMonth[weekIndex - 1]->setHidden(true);
            }
        }
        // 延展指定天
        QPropertyAnimation* expandAnimation = new QPropertyAnimation(m_weekListForAMonth[1], "geometry");
        expandAnimation->setStartValue(m_weekListForAMonth[1]->geometry());
        expandAnimation->setEndValue(QRect(0, 15, m_scheduleWidget->width(), m_scheduleWidget->height() - 15));
        expandAnimation->setDuration(500);
        expandAnimation->setEasingCurve(QEasingCurve::OutQuint);
        m_switchViewAnimationGroup->addAnimation(fadeOutGroup);
        m_switchViewAnimationGroup->addAnimation(expandAnimation);
        //connect(m_switchViewAnimationGroup, &QAnimationGroup::finished, [&]() {hideOtherWeeks(); });
        m_switchViewAnimationGroup->start();
    }
    m_currentView = ViewMode::Day;
}

void ScheduleView::hideOtherWeeks()
{
    for (int weekIndex = 1; weekIndex <= m_weekListForAMonth.size(); weekIndex++)
    {
        if (weekIndex != m_currentWeekIndex)
            m_weekListForAMonth[weekIndex - 1]->setHidden(true);
    }
    m_currentView = ViewMode::Week;
    this->setEnabled(true);
    m_weekIndexButtonListForAMonth[m_currentWeekIndex - 1]->disconnect();
    connect(m_weekIndexButtonListForAMonth[m_currentWeekIndex - 1], &QPushButton::clicked, this, &ScheduleView::switchToMonthView);
}

void ScheduleView::showOtherWeeks()
{
    for (int weekIndex = 1; weekIndex <= m_weekListForAMonth.size(); weekIndex++)
    {
        if (weekIndex != m_currentWeekIndex)
            m_weekListForAMonth[weekIndex - 1]->setHidden(false);
    }
    m_currentView = ViewMode::Month;
    this->setEnabled(true);
    m_weekIndexButtonListForAMonth[m_currentWeekIndex - 1]->disconnect();
    connect(m_weekIndexButtonListForAMonth[m_currentWeekIndex - 1], &QPushButton::clicked, this, &ScheduleView::switchToWeekView);
}

void ScheduleView::resizeEvent(QResizeEvent* event)
{
    // 一旦有任何变形窗口的操作，都应使动画立即变换到其最终状态。
    if (m_switchViewAnimationGroup->state() == QAnimationGroup::Running)
    {
        m_switchViewAnimationGroup->stop();
        switch (m_animationFlag)
        {
        case ScheduleView::NoSwitch:
            break;
        case ScheduleView::MonthToWeek:
        {
            hideOtherWeeks();
            for (int i = 0; i < m_weekOpacityEffectListForAMonth.size(); i++)
                m_weekOpacityEffectListForAMonth[i]->setOpacity(0);
            disableGraphicsEffect();
            break;
        }
        case ScheduleView::WeekToDay:
            break;
        case ScheduleView::DayToMonth:
            break;
        case ScheduleView::WeekToMonth:
        {
            showOtherWeeks();
            for (int i = 0; i < m_weekOpacityEffectListForAMonth.size(); i++)
                m_weekOpacityEffectListForAMonth[i]->setOpacity(1);
            disableGraphicsEffect();
            break;
        }
        case ScheduleView::DayToWeek:
            break;
        case ScheduleView::MonthToDay:
            break;
        default:
            break;
        }
    }
    if (m_taskSettingView) m_taskSettingView->adjustView();
}

void ScheduleView::disableGraphicsEffect()
{
    for (int i = 0; i < m_weekOpacityEffectListForAMonth.size(); i++)
        m_weekOpacityEffectListForAMonth[i]->setEnabled(false);
}

void ScheduleView::enableGraphicsEffect()
{
    for (int i = 0; i < m_weekOpacityEffectListForAMonth.size(); i++)
        m_weekOpacityEffectListForAMonth[i]->setEnabled(true);
}