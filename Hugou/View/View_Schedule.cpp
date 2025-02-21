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
    m_monthToWeekForward = new QPushButton(m_viewSwitchBar);
    m_monthToWeekForward->setFixedSize(32, 32);
    m_monthToWeekForward->setIcon(QIcon(":/icon/forward_schedule_viewSwitchBar.ico"));
    m_monthToWeekForward->setIconSize(QSize(32, 32));
    m_weekViewSwitchButton = new QPushButton("Week " + QString::number(QDate::currentDate().weekNumber()), m_viewSwitchBar);
    m_weekViewSwitchButton->setFont(viewSwitchButtonFont);
    m_weekToDayForward = new QPushButton(m_viewSwitchBar);
    m_weekToDayForward->setFixedSize(32, 32);
    m_weekToDayForward->setIcon(QIcon(":/icon/forward_schedule_viewSwitchBar.ico"));
    m_weekToDayForward->setIconSize(QSize(32, 32));
    m_dayViewSwitchButton = new QPushButton("Day " + QString::number(QDate::currentDate().day()), m_viewSwitchBar);
    m_dayViewSwitchButton->setFont(viewSwitchButtonFont);
    m_viewSwitchBarLayout->addWidget(m_monthViewSwitchButton);
    m_viewSwitchBarLayout->addWidget(m_monthToWeekForward);
    m_viewSwitchBarLayout->addWidget(m_weekViewSwitchButton);
    m_viewSwitchBarLayout->addWidget(m_weekToDayForward);
    m_viewSwitchBarLayout->addWidget(m_dayViewSwitchButton);
    m_viewSwitchBarLayout->addStretch();

    m_memoGeneralWidget = new QWidget(m_centralWidget);
    m_memoGeneralWidget->setObjectName("memoWidget");
    m_memoGeneralWidgetLayout = new QVBoxLayout(m_memoGeneralWidget);
    m_memoGeneralWidgetLayout->setContentsMargins(36, 16, 36, 16);
    m_memoGeneralWidgetLayout->setSpacing(18);
    m_memoGeneralTitleWidget = new QWidget(m_memoGeneralWidget);
    m_memoGeneralTitleWidgetLayout = new QHBoxLayout(m_memoGeneralTitleWidget);
    m_memoGeneralTitleWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_memoGeneralTitleWidgetLayout->setSpacing(0);
    m_memoGeneralTitle = new QLabel("Memo", m_memoGeneralTitleWidget);
    m_memoGeneralTitle->setFont(memoTitleFont);
    m_memoGeneralTitleWidgetLayout->addWidget(m_memoGeneralTitle, Qt::AlignLeft);

    QScrollArea* m_memoListArea = new QScrollArea(m_memoGeneralWidget);
    m_memoListArea->setWidgetResizable(true);
    m_memoListArea->viewport()->setStyleSheet("background-color: transparent;");
    m_memoListArea->setStyleSheet(
        "QScrollArea{ background-color: transparent; border: none }"
    );
    m_memoListWidget = new QWidget(m_memoListArea);
    m_memoListWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_memoListWidgetLayout = new QVBoxLayout(m_memoListWidget);
    m_memoListWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_memoListWidgetLayout->setSpacing(16);
    m_memoListWidgetLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    m_memoListArea->setWidget(m_memoListWidget);
    m_memoGeneralWidgetLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_memoGeneralWidgetLayout->addWidget(m_memoGeneralTitleWidget);
    m_memoGeneralWidgetLayout->addWidget(m_memoListArea);

    m_centralWidgetLayout->addWidget(m_viewSwitchBar);
    m_centralWidgetLayout->addWidget(m_memoGeneralWidget);

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
    QFont memoContentFont = QFont("NeverMind", 14, QFont::Medium);
    QFont memoSubContentFont = QFont("NeverMind", 12, QFont::Normal);
    for (const Memo memo : memoList)
    {
        QWidget* memoWidget = new QWidget(m_memoListWidget);
        QVBoxLayout* memoWidgetLayout = new QVBoxLayout(memoWidget);
        memoWidgetLayout->setContentsMargins(0, 0, 0, 0);
        memoWidgetLayout->setSpacing(0);

        QPushButton* memoBriefWidget = new QPushButton(m_addMemoWidget);
        //connect(memoBriefWidget, &QPushButton::clicked, this, &ScheduleView::showMemoSetting);
        memoBriefWidget->setFixedHeight(36);
        QHBoxLayout* memoBriefWidgetLayout = new QHBoxLayout(memoBriefWidget);
        memoBriefWidgetLayout->setContentsMargins(0, 0, 0, 0);
        memoBriefWidgetLayout->setSpacing(8);
        QPushButton* dropDownButton = new QPushButton(memoBriefWidget);
        dropDownButton->setFixedSize(12, 12);
        if (memo.hasSubMemo)
        {
            dropDownButton->setIcon(QIcon(":/icon/forward.ico"));
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
    m_addMemoWidgetLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    m_addMemoBriefWidget = new FadeEffectButton(m_addMemoWidget);
    m_addMemoBriefWidget->setFixedHeight(60);
    m_addMemoBriefWidget->setCursor(Qt::PointingHandCursor);
    m_addMemoBriefWidget->setBackgroundWidgetStyleSheet("background-color: #EAF9FE; border-radius: 10px");
    m_addMemoBriefWidgetLayout = new QHBoxLayout(m_addMemoBriefWidget);
    m_addMemoBriefWidgetLayout->setContentsMargins(0, 12, 0, 12);
    m_addMemoBriefWidgetLayout->setSpacing(8);
	
    m_dropDownButton = new QPushButton(m_addMemoBriefWidget);
    m_dropDownButton->setFixedSize(12, 12);
    m_checkBox = new CheckBox(m_addMemoBriefWidget);
    
    m_memoContentWidget = new QWidget(m_addMemoBriefWidget);
    m_memoContentWidgetLayout = new QVBoxLayout(m_memoContentWidget);
    m_memoContentWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_memoContentWidgetLayout->setSpacing(0);

    m_memoContent = new QLabel(tr("What do you want to do?"), m_addMemoBriefWidget);
    m_memoContent->setFixedHeight(20);
    //m_memoContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_memoContent->setFont(memoContentFont);
    m_memoContent->setStyleSheet("color: #4F5E71");

    m_memoSubContent = new QLabel(tr("Click here to add a new memo."), m_addMemoBriefWidget);
    m_memoSubContent->setFixedHeight(20);
    m_memoSubContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_memoSubContent->setFont(memoSubContentFont);
    m_memoSubContent->setStyleSheet("color: #ACB1C6");

    m_memoContentWidgetLayout->addWidget(m_memoContent);
    m_memoContentWidgetLayout->addWidget(m_memoSubContent);

    m_addMemoBriefWidgetLayout->addWidget(m_dropDownButton);
    m_addMemoBriefWidgetLayout->addWidget(m_checkBox);
    m_addMemoBriefWidgetLayout->addWidget(m_memoContentWidget);

    MemoSettingView* memoSetting = new MemoSettingView(m_addMemoWidget, Memo());
    m_memoSettingMap.insert(m_addMemoBriefWidget, memoSetting);

    m_addMemoWidgetLayout->addWidget(m_addMemoBriefWidget);
    m_addMemoWidgetLayout->addWidget(memoSetting);

    m_memoListWidgetLayout->addWidget(m_addMemoWidget);
    m_memoButtonMap.insert(m_addMemoBriefWidget, Memo());
}

void ScheduleView::showMemoSetting(FadeEffectButton* memoBriefWidget)
{
    MemoSettingView* memoSetting = m_memoSettingMap[memoBriefWidget];
    QWidget* memoWidget = memoBriefWidget->parentWidget();
    int availableHeight = m_memoListWidget->height() - m_addMemoWidget->height();
    int memoSettingHeight = memoSetting->getSuitableHeight();
    int heightIncrement = availableHeight < memoSettingHeight ? availableHeight : memoSettingHeight;
    QParallelAnimationGroup* group = new QParallelAnimationGroup;
    QPropertyAnimation* memoWidgetExpandAnimation = new QPropertyAnimation(memoWidget, "geometry");
    memoWidgetExpandAnimation->setStartValue(memoWidget->geometry());
    memoWidgetExpandAnimation->setEndValue(QRect(memoWidget->x(), memoWidget->y(), memoWidget->width(), memoWidget->height() + heightIncrement));
    memoWidgetExpandAnimation->setDuration(200);
    QPropertyAnimation* memoSettingExpandAnimation = new QPropertyAnimation(memoSetting, "geometry");
    memoSettingExpandAnimation->setStartValue(memoSetting->geometry());
    memoSettingExpandAnimation->setEndValue(QRect(memoSetting->x(), memoSetting->y(), memoSetting->width(), memoSetting->height() + heightIncrement));
    memoSettingExpandAnimation->setDuration(200);
    group->addAnimation(memoWidgetExpandAnimation);
    group->addAnimation(memoSettingExpandAnimation);
    connect(group, &QParallelAnimationGroup::finished, [=]()
        {
            memoSetting->fadeIn();
        }
    );
    group->start(QPropertyAnimation::DeleteWhenStopped);
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