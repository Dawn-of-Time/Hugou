#include "Card_MonthOverview.h"

MonthOverviewCard::MonthOverviewCard(QWidget* parent)
    :Card(parent)
{
    setupUi();
    connect(m_title, &QPushButton::clicked, this, &MonthOverviewCard::setYearAndMonth);
    connect(m_backButton, &QPushButton::clicked, this, &MonthOverviewCard::goBackAMonth);
    connect(m_forwardButton, &QPushButton::clicked, this, &MonthOverviewCard::goForwardAMonth);
    connect(m_backToTodayButton, &QPushButton::clicked, this, &MonthOverviewCard::goBackToToday);
}

void MonthOverviewCard::setupUi()
{
    // 字体清单
    QFont titleFont = QFont("NeverMind", 16, QFont::DemiBold);
    QFont backToTodayFont = QFont("NeverMind", 12, QFont::Bold);
    QFont monthContentFont = QFont("NeverMind", 11, QFont::Normal);

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(13, 16, 13, 16);
    m_layout->setSpacing(10);

    m_titleWidget = new QWidget(this);
    m_titleWidget->setFixedHeight(30);
    m_titleWidgetLayout = new QHBoxLayout(m_titleWidget);
    m_titleWidgetLayout->setContentsMargins(8, 0, 8, 0);
    m_titleWidgetLayout->setSpacing(0);
    m_title = new FadeEffectButton("", titleFont, m_titleWidget);
    m_title->setFixedSize(176, 30);
    m_title->layout()->setContentsMargins(0, 0, 0, 0);
    m_title->setBackgroundWidgetStyleSheet("background-color: rgba(0, 0, 255, 0.1)");
    m_actionWidget = new QWidget(m_titleWidget);
    m_actionWidget->setFixedWidth(92);
    m_actionWidgetLayout = new QHBoxLayout(m_actionWidget);
    m_actionWidgetLayout->setContentsMargins(5, 0, 5, 0);
    m_actionWidgetLayout->setSpacing(5);
    m_backToTodayButton = new QPushButton("T", m_actionWidget);
    m_backToTodayButton->setObjectName("backToTodayButton");
    m_backToTodayButton->setFixedSize(24, 24);
    m_backToTodayButton->setFont(backToTodayFont);
    m_backToTodayButton->setCursor(Qt::PointingHandCursor);
    m_backToTodayButton->setStyleSheet("background-color: #AEE4FD; border-radius: 12px");
    QSizePolicy policy = m_backToTodayButton->sizePolicy();
    policy.setRetainSizeWhenHidden(true);
    m_backToTodayButton->setSizePolicy(policy);
    m_backButton = new QPushButton(m_actionWidget);
    m_backButton->setObjectName("backButton");
    m_backButton->setFixedSize(24, 24);
    m_backButton->setIcon(QIcon(":/icon/back.ico"));
    m_backButton->setIconSize(QSize(12, 12));
    m_backButton->setCursor(Qt::PointingHandCursor);
    m_backButton->setStyleSheet("background-color: #AEE4FD; border-radius: 12px");
    m_forwardButton = new QPushButton(m_actionWidget);
    m_forwardButton->setObjectName("forwardButton");
    m_forwardButton->setFixedSize(24, 24);
    m_forwardButton->setIcon(QIcon(":/icon/forward.ico"));
    m_forwardButton->setIconSize(QSize(12, 12));
    m_forwardButton->setCursor(Qt::PointingHandCursor);
    m_forwardButton->setStyleSheet("background-color: #AEE4FD; border-radius: 12px");
    m_actionWidgetLayout->addWidget(m_backToTodayButton);
    m_actionWidgetLayout->addWidget(m_backButton);
    m_actionWidgetLayout->addWidget(m_forwardButton);
    m_titleWidgetLayout->addWidget(m_title);
    m_titleWidgetLayout->addStretch();
    m_titleWidgetLayout->addWidget(m_actionWidget);

    m_monthWidget = new QWidget(this);
    m_monthWidgetLayout = new QVBoxLayout(m_monthWidget);
    m_monthWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_monthWidgetLayout->setSpacing(10);

    // 星期
    QStringList weekdays = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
    m_weekdaysBar = new QWidget(this);
    m_weekdaysBar->setFixedHeight(20);
    m_weekdaysBarLayout = new QHBoxLayout(m_weekdaysBar);
    m_weekdaysBarLayout->setContentsMargins(0, 0, 0, 0);
    m_weekdaysBarLayout->setSpacing(0);
    for (int weekdayIndex = 0; weekdayIndex < 7; weekdayIndex++)
    {
        QLabel* weekday = new QLabel(weekdays[weekdayIndex], m_weekdaysBar);
        weekday->setFixedSize(30, 20);
        weekday->setFont(monthContentFont);
        weekday->setAlignment(Qt::AlignCenter);
        m_weekdaysBarLayout->addWidget(weekday);
    }
    m_monthWidgetLayout->addWidget(m_weekdaysBar);
    // 日期
    int weeksNum = 6;
    // 绘制网格
    for (int weekIndex = 1; weekIndex <= weeksNum; weekIndex++)
    {
        // 周网格
        QWidget* week = new QWidget(m_monthWidget);
        QHBoxLayout* weekLayout = new QHBoxLayout(week);
        weekLayout->setContentsMargins(0, 0, 0, 0);
        weekLayout->setSpacing(0);
        for (int dayIndex = 1; dayIndex <= 7; dayIndex++)
        {
            // 天网格
            QPushButton* day = new QPushButton(week);
            day->setObjectName("day");
            day->setFont(monthContentFont);
            day->setFixedSize(30, 30);
            day->setStyleSheet("border-radius: 10px");
            weekLayout->addWidget(day);
            m_dayListForAMonth.append(day);
        }
        m_monthWidgetLayout->addWidget(week);
        m_weekListForAMonth.append(week);
    }
    loadMonthView(QDate::currentDate());

    m_layout->addWidget(m_titleWidget);
    m_layout->addWidget(m_monthWidget);
}

void MonthOverviewCard::loadMonthView(const QDate& date)
{
    int year = date.year();
    int month = date.month();
    if (year == m_currentDate.year() && month == m_currentDate.month()) return;
    int firstDayOfWeek = QDate(year, month, 1).dayOfWeek();
    int daysNum = date.daysInMonth();

    m_title->setText(m_monthNameList[month - 1] + " " + QString::number(year));

    // 在网格中填充日期
    // 本月
    for (int dayIndex = 1; dayIndex <= daysNum; dayIndex++)
    {
        m_dayListForAMonth[firstDayOfWeek + dayIndex - 2]->setText(QString::number(dayIndex));
        m_dayListForAMonth[firstDayOfWeek + dayIndex - 2]->setStyleSheet("color: black");
    }
        
    // 上月
    if (firstDayOfWeek > 1)
        for (int dayIndex = 1; dayIndex < firstDayOfWeek; dayIndex++)
        {
            m_dayListForAMonth[dayIndex - 1]->setText(QString::number(date.addMonths(-1).daysInMonth() - firstDayOfWeek + dayIndex + 1));
            m_dayListForAMonth[dayIndex - 1]->setStyleSheet("color: #ACB1C6");
        }
    // 下月
    int lastDayofWeek = QDate(year, month, daysNum).dayOfWeek();
    if (lastDayofWeek < 7)
    {
        for (int dayIndex = 1; dayIndex <= 7 - lastDayofWeek; dayIndex++)
        {
            m_dayListForAMonth[firstDayOfWeek + daysNum - 2 + dayIndex]->setText(QString::number(dayIndex));
            m_dayListForAMonth[firstDayOfWeek + daysNum - 2 + dayIndex]->setStyleSheet("color: #ACB1C6");
        }
        int weeksNum = (int)ceil(double(daysNum + firstDayOfWeek - 1) / 7);
        if (weeksNum < 6)
        {
            int index = 35;
            for (int dayIndex = 7 - lastDayofWeek + 1; dayIndex <= 14 - lastDayofWeek; dayIndex++)
            {
                m_dayListForAMonth[index]->setText(QString::number(dayIndex));
                m_dayListForAMonth[index]->setStyleSheet("color: #ACB1C6");
                index++;
            }
        }
    }

    if (year == QDate::currentDate().year() && month == QDate::currentDate().month())
    {
        m_todayButton = m_dayListForAMonth[QDate(year, month, 1).dayOfWeek() + date.day() - 2];
        m_todayButton->setStyleSheet("background-color: #AEE4FD; border-radius: 10px");
        m_backToTodayButton->hide();
    }
    else
    {
        m_todayButton->setStyleSheet("background-color: transparent; border-radius: 10px");
        m_backToTodayButton->show();
    }  
    m_currentDate.setDate(year, month, date.day());
}

void MonthOverviewCard::goBackAMonth()
{
    loadMonthView(m_currentDate.addMonths(-1));
}

void MonthOverviewCard::goForwardAMonth()
{
    loadMonthView(m_currentDate.addMonths(1));
}

void MonthOverviewCard::goBackToToday()
{
    loadMonthView(QDate::currentDate());
}

void MonthOverviewCard::setYearAndMonth()
{
    // 字体清单
    QFont yearFont = QFont("NeverMind", 14, QFont::DemiBold);
    QFont monthFont = QFont("NeverMind", 12, QFont::Light);

    m_title->disconnect();
    CloseWhenLeaveWidget* settingWidget = new CloseWhenLeaveWidget(this);
    settingWidget->setFixedSize(255, 195);
    settingWidget->move(21, 46);
    settingWidget->setObjectName("yearAndMonthSettingWidget");
    settingWidget->setStyleSheet("QWidget #yearAndMonthSettingWidget { background-color: rgba(255, 255, 255, 0.98);  border-radius: 10px }");
    connect(m_title, &QPushButton::clicked, settingWidget, &CloseWhenLeaveWidget::close);
    
    QVBoxLayout* settingWidgetLayout = new QVBoxLayout(settingWidget);
    settingWidgetLayout->setContentsMargins(15, 15, 15, 15);
    settingWidgetLayout->setSpacing(15);
    settingWidgetLayout->setAlignment(Qt::AlignHCenter);

    QWidget* titleWidget = new QWidget(settingWidget);
    titleWidget->setFixedHeight(30);
    QHBoxLayout* titleWidgetLayout = new QHBoxLayout(titleWidget);
    titleWidgetLayout->setContentsMargins(0, 0, 0, 0);
    titleWidgetLayout->setSpacing(0);
    QPushButton* backButton = new QPushButton(titleWidget);
    backButton->setObjectName("backButton");
    backButton->setFixedSize(20, 20);
    backButton->setIcon(QIcon(":/icon/back.ico"));
    backButton->setIconSize(QSize(12, 12));
    backButton->setCursor(Qt::PointingHandCursor);
    backButton->setStyleSheet("background-color: #AEE4FD; border-radius: 10px");
    QLineEdit* yearLineEdit = new QLineEdit(QString::number(m_currentDate.year()), titleWidget);
    yearLineEdit->setFixedSize(135, 30);
    yearLineEdit->setAlignment(Qt::AlignCenter);
    yearLineEdit->setFont(yearFont);
    yearLineEdit->setStyleSheet("border-bottom: 1px solid #AEE4FD");
    yearLineEdit->setValidator(new QIntValidator(0, 5000, yearLineEdit));
    QPushButton* forwardButton = new QPushButton(titleWidget);
    forwardButton->setObjectName("forwardButton");
    forwardButton->setFixedSize(20, 20);
    forwardButton->setIcon(QIcon(":/icon/forward.ico"));
    forwardButton->setIconSize(QSize(12, 12));
    forwardButton->setCursor(Qt::PointingHandCursor);
    forwardButton->setStyleSheet("background-color: #AEE4FD; border-radius: 10px");
    titleWidgetLayout->addWidget(backButton);
    titleWidgetLayout->addWidget(yearLineEdit);
    titleWidgetLayout->addWidget(forwardButton);

    QWidget* monthWidget = new QWidget(settingWidget);
    QGridLayout* monthWidgetLayout = new QGridLayout(monthWidget);
    monthWidgetLayout->setHorizontalSpacing(15);
    monthWidgetLayout->setVerticalSpacing(3);
    int monthIndex = 1;
    FadeEffectButton* currentMonthbutton;
    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            FadeEffectButton* button = new FadeEffectButton(m_monthNameList[row * 4 + column].left(3), monthFont, monthWidget);
            button->setFixedSize(45, 30);
            button->layout()->setContentsMargins(0, 0, 0, 0);
            button->setTextAlignment(Qt::AlignCenter);
            button->setBackgroundWidgetStyleSheet("background-color: rgba(0, 0, 255, 0.1); border-radius: 5px");
            
            if (row * 4 + column == m_currentDate.month() - 1)  
            {
                currentMonthbutton = button;
                button->setObjectName("currentMonth");
                button->setStyleSheet("QWidget #currentMonth{background-color: rgba(0, 0, 255, 0.1); border-radius: 5px}");
            }
            monthWidgetLayout->addWidget(button, row, column);
            connect(button, &FadeEffectButton::clicked, [=]()
                {
                    loadMonthView(QDate(yearLineEdit->text().toInt(), m_monthMap[button->text()], m_currentDate.day()));
                    settingWidget->blockSignals(true);
                    m_title->disconnect();
                    connect(m_title, &FadeEffectButton::clicked, this, &MonthOverviewCard::setYearAndMonth);
                    settingWidget->close();
                });
        }
    }

    settingWidgetLayout->addWidget(titleWidget);
    settingWidgetLayout->addWidget(monthWidget);
    
    settingWidget->show();

    connect(backButton, &QPushButton::clicked, [=]()
        {
            int year = yearLineEdit->text().toInt() - 1;
            yearLineEdit->setText(QString::number(year));
            if (year == m_currentDate.year()) currentMonthbutton->setStyleSheet("QWidget #currentMonth{background-color: rgba(0, 0, 255, 0.1); border-radius: 5px}");
            else currentMonthbutton->setStyleSheet("QWidget #currentMonth{background-color: transparent; border-radius: 5px}");
        });
    connect(forwardButton, &QPushButton::clicked, [=]()
        {
            int year = yearLineEdit->text().toInt() + 1;
            yearLineEdit->setText(QString::number(year));
            if (year == m_currentDate.year()) currentMonthbutton->setStyleSheet("QWidget #currentMonth{background-color: rgba(0, 0, 255, 0.1); border-radius: 5px}");
            else currentMonthbutton->setStyleSheet("QWidget #currentMonth{background-color: transparent; border-radius: 5px}");
        });
    connect(yearLineEdit, &QLineEdit::editingFinished, [=]()
        {
            int year = yearLineEdit->text().toInt();
            if (year == QDate::currentDate().year()) currentMonthbutton->setStyleSheet("QWidget #currentMonth{background-color: rgba(0, 0, 255, 0.1); border-radius: 5px}");
            else currentMonthbutton->setStyleSheet("QWidget #currentMonth{background-color: transparent; border-radius: 5px}");
            loadMonthView(QDate(year, m_currentDate.month(), m_currentDate.day()));
        });
    connect(settingWidget, &CloseWhenLeaveWidget::SignalClose, [=]() 
        {
            m_title->disconnect();
            connect(m_title, &QPushButton::clicked, this, &MonthOverviewCard::setYearAndMonth);
            loadMonthView(QDate(yearLineEdit->text().toInt(), m_currentDate.month(), m_currentDate.day()));
        });

    QGraphicsDropShadowEffect* dropShadowEffect = new QGraphicsDropShadowEffect(settingWidget);
    dropShadowEffect->setBlurRadius(20);
    dropShadowEffect->setXOffset(0);
    dropShadowEffect->setYOffset(6);
    settingWidget->setGraphicsEffect(dropShadowEffect);

    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(settingWidget);
    opacityEffect->setOpacity(0);
    settingWidget->setGraphicsEffect(opacityEffect);

    QPropertyAnimation* animation = new QPropertyAnimation(opacityEffect, "opacity");
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setDuration(200);
    connect(animation, &QPropertyAnimation::finished, [=]()
        {
            opacityEffect->setEnabled(false);
        });
    animation->start(QParallelAnimationGroup::DeleteWhenStopped);
}