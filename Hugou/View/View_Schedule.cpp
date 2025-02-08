#include "View_Schedule.h"

ScheduleView::ScheduleView(QWidget* parent) :
	QWidget(parent)
{
    //m_currentView = ViewMode::Month;
    //m_switchViewAnimationGroup = new QSequentialAnimationGroup(this);
	setupUi();
}

void ScheduleView::setupUi()
{
    // 字体清单
    const QFont viewSwitchButtonFont = QFont("NeverMind", 36, QFont::DemiBold);
    const QFont memoTitleFont = QFont("NeverMind", 24, QFont::DemiBold);

    m_scheduleLayout = new QHBoxLayout(this);
    m_scheduleLayout->setContentsMargins(0, 0, 0, 0);
    m_scheduleLayout->setSpacing(0);
    m_centralWidget = new QWidget(this);
    m_cardWidget = new QWidget(this);
    m_cardWidget->setObjectName("cardWidget");
    m_cardWidget->setFixedWidth(cardWidgetWidth);
    m_scheduleLayout->addWidget(m_centralWidget);
    m_scheduleLayout->addWidget(m_cardWidget);

    m_centralWidgetLayout = new QVBoxLayout(m_centralWidget);
    m_centralWidgetLayout->setContentsMargins(24, 24, 24, 24);
    m_centralWidgetLayout->setSpacing(0);

    m_viewSwitchBar = new QWidget(m_centralWidget);
    m_viewSwitchBar->setFixedHeight(98);
    m_viewSwitchBarLayout = new QHBoxLayout(m_viewSwitchBar);
    m_viewSwitchBarLayout->setContentsMargins(20, 20, 20, 20);
    m_viewSwitchBarLayout->setSpacing(7);
    m_monthViewSwitchButton = new QPushButton(m_monthNameList[QDate::currentDate().month() - 1], m_viewSwitchBar);
    m_monthViewSwitchButton->setFont(viewSwitchButtonFont);
    m_monthToWeekForward = new QLabel(m_viewSwitchBar);
    m_monthToWeekForward->setFixedSize(32, 32);
    m_monthToWeekForward->setPixmap(QPixmap(":/icon/forward_schedule_viewSwitchBar.png"));
    m_weekViewSwitchButton = new QPushButton("Week " + QString::number(QDate::currentDate().weekNumber()), m_viewSwitchBar);
    m_weekViewSwitchButton->setFont(viewSwitchButtonFont);
    m_weekToDayForward = new QLabel(m_viewSwitchBar);
    m_weekToDayForward->setFixedSize(32, 32);
    m_weekToDayForward->setPixmap(QPixmap(":/icon/forward_schedule_viewSwitchBar.png"));
    m_dayViewSwitchButton = new QPushButton("Day " + QString::number(QDate::currentDate().day()), m_viewSwitchBar);
    m_dayViewSwitchButton->setFont(viewSwitchButtonFont);
    m_viewSwitchBarLayout->addWidget(m_monthViewSwitchButton);
    m_viewSwitchBarLayout->addWidget(m_monthToWeekForward);
    m_viewSwitchBarLayout->addWidget(m_weekViewSwitchButton);
    m_viewSwitchBarLayout->addWidget(m_weekToDayForward);
    m_viewSwitchBarLayout->addWidget(m_dayViewSwitchButton);
    m_viewSwitchBarLayout->addStretch();

    m_memoWidget = new QWidget(m_centralWidget);
    m_memoWidget->setObjectName("memoWidget");
    m_memoWidgetLayout = new QVBoxLayout(m_memoWidget);
    m_memoWidgetLayout->setContentsMargins(36, 16, 36, 16);
    m_memoWidgetLayout->setSpacing(18);
    m_memoTitleWidget = new QWidget(m_memoWidget);
    m_memoTitleWidgetLayout = new QHBoxLayout(m_memoTitleWidget);
    m_memoTitleWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_memoTitleWidgetLayout->setSpacing(0);
    m_memoTitle = new QLabel("Memo", m_memoTitleWidget);
    m_memoTitle->setFont(memoTitleFont);
    m_memoTitleWidgetLayout->addWidget(m_memoTitle, Qt::AlignLeft);

    m_memoListWidget = new QWidget(m_memoWidget);
    m_memoListWidgetLayout = new QVBoxLayout(m_memoListWidget);
    m_memoListWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_memoListWidgetLayout->setSpacing(16);

    m_memoWidgetLayout->setAlignment(Qt::AlignLeft);
    m_memoWidgetLayout->addWidget(m_memoTitleWidget);
    m_memoWidgetLayout->addWidget(m_memoListWidget);

    m_centralWidgetLayout->addWidget(m_viewSwitchBar);
    m_centralWidgetLayout->addWidget(m_memoWidget);
    m_centralWidgetLayout->addStretch();

    m_cardWidgetLayout = new QVBoxLayout(m_cardWidget);
    m_cardWidgetLayout->setContentsMargins(0, 0, 0, 0);

    MonthOverviewCard* monthOverviewCard = new MonthOverviewCard(m_cardWidget);
    m_cardWidgetLayout->addWidget(monthOverviewCard);
    m_cardWidgetLayout->addStretch();
    QFile styleFile(":/theme/Default/schedule.qss");
    styleFile.open(QIODeviceBase::ReadOnly);
    this->setStyleSheet(styleFile.readAll());
    styleFile.close();
}

void ScheduleView::generateMemos(QList<Memo> memoList)
{
    QFont memoContentFont = QFont("NeverMind", 14, QFont::Normal);
    for (const Memo memo : memoList)
    {
        QWidget* memoWidget = new QWidget(m_memoListWidget);
        QVBoxLayout* memoWidgetLayout = new QVBoxLayout(memoWidget);
        memoWidgetLayout->setContentsMargins(0, 0, 0, 0);
        memoWidgetLayout->setSpacing(0);

        QPushButton* memoBriefWidget = new QPushButton(m_addMemoWidget);
        connect(memoBriefWidget, &QPushButton::clicked, this, &ScheduleView::showMemoSetting);
        memoBriefWidget->setFixedHeight(36);
        QHBoxLayout* memoBriefWidgetLayout = new QHBoxLayout(memoBriefWidget);
        memoBriefWidgetLayout->setContentsMargins(0, 0, 0, 0);
        memoBriefWidgetLayout->setSpacing(8);
        QPushButton* dropDownButton = new QPushButton(memoBriefWidget);
        dropDownButton->setFixedSize(12, 12);
        if (memo.hasSubMemo)
        {
            dropDownButton->setIcon(QIcon(":/icon/forward.png"));
            dropDownButton->setIconSize(QSize(9, 9));
        }
        QCheckBox* checkBox = new QCheckBox(memoWidget);
        checkBox->setFixedSize(20, 20);
        QLabel* memoContent = new QLabel(memo.sketch, m_addMemoBriefWidget);
        memoContent->setFixedHeight(20);
        memoContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        memoContent->setFont(memoContentFont);
        
        memoBriefWidgetLayout->addWidget(dropDownButton);
        memoBriefWidgetLayout->addWidget(checkBox);
        

        QWidget* memoDetailedWidget = new QWidget(memoWidget);
        m_memoListWidgetLayout->addWidget(memoWidget);
        m_memoButtonMap.insert(memoBriefWidget, memo);
    }

    m_addMemoWidget = new QWidget(m_memoListWidget);
    m_addMemoWidgetLayout = new QVBoxLayout(m_addMemoWidget);
    m_addMemoWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_addMemoWidgetLayout->setSpacing(8);

    m_addMemoBriefWidget = new QPushButton(m_addMemoWidget);
    connect(m_addMemoBriefWidget, &QPushButton::clicked, this, &ScheduleView::showMemoSetting);
    m_addMemoBriefWidget->setFixedHeight(36);
    m_addMemoBriefWidgetLayout = new QHBoxLayout(m_addMemoBriefWidget);
    m_addMemoBriefWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_addMemoBriefWidgetLayout->setSpacing(8);
    m_dropDownButton = new QPushButton(m_addMemoBriefWidget);
    m_dropDownButton->setFixedSize(12, 12);
    m_addIcon = new QLabel(m_addMemoBriefWidget);
    m_addIcon->setFixedSize(20, 20);
    m_addIcon->setPixmap(QPixmap(":/icon/add_memo.png"));
    m_memoContent = new QLabel("Click here to add a new memo.", m_addMemoBriefWidget);
    m_memoContent->setFixedHeight(20);
    m_memoContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_memoContent->setFont(memoContentFont);

    m_addMemoBriefWidgetLayout->addWidget(m_dropDownButton);
    m_addMemoBriefWidgetLayout->addWidget(m_addIcon);
    m_addMemoBriefWidgetLayout->addWidget(m_memoContent);

    m_addMemoWidgetLayout->addWidget(m_addMemoBriefWidget);

    m_memoListWidgetLayout->addWidget(m_addMemoWidget);
    m_memoButtonMap.insert(m_addMemoBriefWidget, Memo());
}

void ScheduleView::showMemoSetting()
{
    QWidget* memoWidget = qobject_cast<QWidget*>(sender())->parentWidget();
    Memo memo = m_memoButtonMap.value(memoWidget);
    MemoSettingView* memoSetting = new MemoSettingView(memoWidget, memo);
    memoWidget->layout()->addWidget(memoSetting);
}

void ScheduleView::switchToMonthView()
{
    //enableGraphicsEffect();
    //m_weekViewSwitchButton->setHidden(true);
    //m_dayViewSwitchButton->setHidden(true);
    //if (m_currentView == ViewMode::Week)
    //{
    //    m_switchViewAnimationGroup->clear();
    //    // 收缩指定周
    //    QPropertyAnimation* shrinkAnimation = new QPropertyAnimation(m_weekListForAMonth[m_currentWeekIndex - 1], "geometry");
    //    shrinkAnimation->setStartValue(m_weekListForAMonth[m_currentWeekIndex - 1]->geometry());
    //    int endHeight = (m_scheduleWidget->height() - 15) / m_weekListForAMonth.length();
    //    int endY = 15 + (m_currentWeekIndex - 1) * endHeight;
    //    shrinkAnimation->setEndValue(QRect(0, endY, m_scheduleWidget->width(), endHeight));
    //    shrinkAnimation->setDuration(300);
    //    shrinkAnimation->setEasingCurve(QEasingCurve::OutQuint);
    //    // 显示其余周
    //    QParallelAnimationGroup* fadeInGroup = new QParallelAnimationGroup;
    //    for (int weekIndex = 1; weekIndex <= m_weekOpacityEffectListForAMonth.size(); weekIndex++)
    //    {
    //        if (weekIndex != m_currentWeekIndex)
    //        {
    //            QPropertyAnimation* fadeAnimation = new QPropertyAnimation(m_weekOpacityEffectListForAMonth[weekIndex - 1], "opacity");
    //            fadeAnimation->setStartValue(0);
    //            fadeAnimation->setEndValue(1);
    //            fadeAnimation->setDuration(200);
    //            fadeInGroup->addAnimation(fadeAnimation);
    //        }
    //    }
    //    m_switchViewAnimationGroup->addAnimation(fadeInGroup);
    //    m_switchViewAnimationGroup->disconnect();
    //    connect(m_switchViewAnimationGroup, &QAnimationGroup::finished, this, &ScheduleView::disableGraphicsEffect);
    //    connect(shrinkAnimation, &QPropertyAnimation::finished, [&]()
    //        {
    //            showOtherWeeks();
    //            m_switchViewAnimationGroup->start();
    //        });
    //    this->setEnabled(false);
    //    shrinkAnimation->start(QPropertyAnimation::DeleteWhenStopped);
    //}
}

void ScheduleView::switchToWeekView()
{
    //enableGraphicsEffect();
    //m_weekViewSwitchButton->setHidden(false);
    //m_dayViewSwitchButton->setHidden(true);
    //if (m_currentView == ViewMode::Month)
    //{
    //    m_animationFlag = AnimationFlag::MonthToWeek;
    //    m_currentWeekIndex = m_weekIndexButtonListForAMonth.indexOf(qobject_cast<QWidget*>(sender())) + 1;
    //    m_weekViewSwitchButton->setText("Week " + QString::number(m_currentWeekIndex));
    //    m_switchViewAnimationGroup->clear();
    //    // 隐藏其余周
    //    QParallelAnimationGroup* fadeOutGroup = new QParallelAnimationGroup;
    //    for (int weekIndex = 1; weekIndex <= m_weekOpacityEffectListForAMonth.size(); weekIndex++)
    //    {
    //        if (weekIndex != m_currentWeekIndex)
    //        {
    //            QPropertyAnimation* fadeAnimation = new QPropertyAnimation(m_weekOpacityEffectListForAMonth[weekIndex - 1], "opacity");
    //            fadeAnimation->setStartValue(1);
    //            fadeAnimation->setEndValue(0);
    //            fadeAnimation->setDuration(200);
    //            fadeOutGroup->addAnimation(fadeAnimation);
    //        }
    //    }
    //    // 延展指定周
    //    QPropertyAnimation* expandAnimation = new QPropertyAnimation(m_weekListForAMonth[m_currentWeekIndex - 1], "geometry");
    //    expandAnimation->setStartValue(m_weekListForAMonth[m_currentWeekIndex - 1]->geometry());
    //    expandAnimation->setEndValue(QRect(0, 15, m_scheduleWidget->width(), m_scheduleWidget->height() - 15));
    //    expandAnimation->setDuration(400);
    //    expandAnimation->setEasingCurve(QEasingCurve::OutQuint);
    //    m_switchViewAnimationGroup->addAnimation(fadeOutGroup);
    //    m_switchViewAnimationGroup->addAnimation(expandAnimation);
    //    m_switchViewAnimationGroup->disconnect();
    //    connect(m_switchViewAnimationGroup, &QAnimationGroup::finished, this, &ScheduleView::hideOtherWeeks);
    //    // 动画播放期间，禁用视图
    //    this->setEnabled(false);
    //    m_switchViewAnimationGroup->start();
    //}  
}

void ScheduleView::switchToDayView()
{
    //if (m_currentView == ViewMode::Week)
    //{
    //    m_animationFlag = AnimationFlag::WeekToDay;
    //    m_switchViewAnimationGroup->clear();
    //    // 隐藏其余天
    //    QParallelAnimationGroup* fadeOutGroup = new QParallelAnimationGroup;
    //    for (int weekIndex = 1; weekIndex <= m_weekOpacityEffectListForAMonth.size(); weekIndex++)
    //    {
    //        if (weekIndex != 2)
    //        {
    //            QPropertyAnimation* fadeAnimation = new QPropertyAnimation(m_weekOpacityEffectListForAMonth[weekIndex - 1], "opacity");
    //            fadeAnimation->setStartValue(1);
    //            fadeAnimation->setEndValue(0);
    //            fadeAnimation->setDuration(300);
    //            fadeOutGroup->addAnimation(fadeAnimation);
    //            //m_weekListForAMonth[weekIndex - 1]->setHidden(true);
    //        }
    //    }
    //    // 延展指定天
    //    QPropertyAnimation* expandAnimation = new QPropertyAnimation(m_weekListForAMonth[1], "geometry");
    //    expandAnimation->setStartValue(m_weekListForAMonth[1]->geometry());
    //    expandAnimation->setEndValue(QRect(0, 15, m_scheduleWidget->width(), m_scheduleWidget->height() - 15));
    //    expandAnimation->setDuration(500);
    //    expandAnimation->setEasingCurve(QEasingCurve::OutQuint);
    //    m_switchViewAnimationGroup->addAnimation(fadeOutGroup);
    //    m_switchViewAnimationGroup->addAnimation(expandAnimation);
    //    //connect(m_switchViewAnimationGroup, &QAnimationGroup::finished, [&]() {hideOtherWeeks(); });
    //    m_switchViewAnimationGroup->start();
    //}
    //m_currentView = ViewMode::Day;
}

void ScheduleView::hideOtherWeeks()
{
    //for (int weekIndex = 1; weekIndex <= m_weekListForAMonth.size(); weekIndex++)
    //{
    //    if (weekIndex != m_currentWeekIndex)
    //        m_weekListForAMonth[weekIndex - 1]->setHidden(true);
    //}
    //m_currentView = ViewMode::Week;
    //this->setEnabled(true);
    //m_weekIndexButtonListForAMonth[m_currentWeekIndex - 1]->disconnect();
    //connect(m_weekIndexButtonListForAMonth[m_currentWeekIndex - 1], &QPushButton::clicked, this, &ScheduleView::switchToMonthView);
}

void ScheduleView::showOtherWeeks()
{
    //for (int weekIndex = 1; weekIndex <= m_weekListForAMonth.size(); weekIndex++)
    //{
    //    if (weekIndex != m_currentWeekIndex)
    //        m_weekListForAMonth[weekIndex - 1]->setHidden(false);
    //}
    //m_currentView = ViewMode::Month;
    //this->setEnabled(true);
    //m_weekIndexButtonListForAMonth[m_currentWeekIndex - 1]->disconnect();
    //connect(m_weekIndexButtonListForAMonth[m_currentWeekIndex - 1], &QPushButton::clicked, this, &ScheduleView::switchToWeekView);
}

void ScheduleView::resizeEvent(QResizeEvent* event)
{
    // 一旦有任何变形窗口的操作，都应使动画立即变换到其最终状态。
    //if (m_switchViewAnimationGroup->state() == QAnimationGroup::Running)
    //{
    //    m_switchViewAnimationGroup->stop();
    //    switch (m_animationFlag)
    //    {
    //    case ScheduleView::NoSwitch:
    //        break;
    //    case ScheduleView::MonthToWeek:
    //    {
    //        hideOtherWeeks();
    //        for (int i = 0; i < m_weekOpacityEffectListForAMonth.size(); i++)
    //            m_weekOpacityEffectListForAMonth[i]->setOpacity(0);
    //        disableGraphicsEffect();
    //        break;
    //    }
    //    case ScheduleView::WeekToDay:
    //        break;
    //    case ScheduleView::DayToMonth:
    //        break;
    //    case ScheduleView::WeekToMonth:
    //    {
    //        showOtherWeeks();
    //        for (int i = 0; i < m_weekOpacityEffectListForAMonth.size(); i++)
    //            m_weekOpacityEffectListForAMonth[i]->setOpacity(1);
    //        disableGraphicsEffect();
    //        break;
    //    }
    //    case ScheduleView::DayToWeek:
    //        break;
    //    case ScheduleView::MonthToDay:
    //        break;
    //    default:
    //        break;
    //    }
    //}
    //if (m_taskSettingView) m_taskSettingView->adjustView();
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