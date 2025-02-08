#include "Card_MonthOverview.h"

MonthOverviewCard::MonthOverviewCard(QWidget* parent)
    :Card(parent)
{
    setupUi();
}

void MonthOverviewCard::setupUi()
{
    // 字体清单
    QFont titleFont = QFont("NeverMind", 16, QFont::DemiBold);
    QFont monthContentFont = QFont("NeverMind", 11, QFont::Normal);

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(13, 16, 13, 16);
    m_layout->setSpacing(10);

    m_titleWidget = new QWidget(this);
    m_titleWidget->setFixedHeight(30);
    m_titleWidgetLayout = new QHBoxLayout(m_titleWidget);
    m_titleWidgetLayout->setContentsMargins(8, 0, 8, 0);
    QDate date = QDate::currentDate();
    m_title = new QLabel(m_monthNameList[date.month() - 1] + " " + QString::number(date.year()), m_titleWidget);
    m_title->setFont(titleFont);
    m_actionWidget = new QWidget(m_titleWidget);
    m_actionWidget->setFixedWidth(46);
    m_actionWidgetLayout = new QHBoxLayout(m_actionWidget);
    m_actionWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_actionWidgetLayout->setSpacing(0);
    m_backButton = new QPushButton(m_actionWidget);
    m_backButton->setObjectName("backButton");
    m_backButton->setFixedSize(20, 20);
    m_backButton->setIcon(QIcon(":/icon/back.png"));
    m_backButton->setIconSize(QSize(12, 12));
    m_forwardButton = new QPushButton(m_actionWidget);
    m_forwardButton->setObjectName("forwardButton");
    m_forwardButton->setFixedSize(20, 20);
    m_forwardButton->setIcon(QIcon(":/icon/forward.png"));
    m_forwardButton->setIconSize(QSize(12, 12));
    m_actionWidgetLayout->addWidget(m_backButton);
    m_actionWidgetLayout->addStretch();
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
        weekday->setFixedSize(30, 15);
        weekday->setFont(monthContentFont);
        weekday->setAlignment(Qt::AlignCenter);
        m_weekdaysBarLayout->addWidget(weekday);
    }
    m_monthWidgetLayout->addWidget(m_weekdaysBar);
    // 日期
    loadMonthView(date, monthContentFont);

    m_layout->addWidget(m_titleWidget);
    m_layout->addWidget(m_monthWidget);
}

void MonthOverviewCard::loadMonthView(QDate date, QFont monthContentFont)
{
    m_dayListForAMonth.clear();
    m_weekListForAMonth.clear();
    int year = date.year();
    int month = date.month();
    int firstDayOfWeek = QDate(year, month, 1).dayOfWeek();
    int daysNum = date.daysInMonth();
    int weeksNum = (int)ceil(double(daysNum + firstDayOfWeek - 1) / 7);
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
            day->setFixedSize(30, 20);
            weekLayout->addWidget(day);
            m_dayListForAMonth.append(day);
        }
        m_monthWidgetLayout->addWidget(week);
        m_weekListForAMonth.append(week);
    }
    // 在网格中填充日期
    for (int dayIndex = 1; dayIndex <= daysNum; dayIndex++)
        m_dayListForAMonth[firstDayOfWeek + dayIndex - 2]->setText(QString::number(dayIndex));
    m_dayListForAMonth[date.day() - 1]->setObjectName("today");
}