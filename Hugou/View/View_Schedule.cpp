#include "View_Schedule.h"

ScheduleView::ScheduleView(QWidget* parent) :
	QWidget(parent)
{
	setupUi();
    /*QTime currentTime = QTime::currentTime();
    if (currentTime.hour() >= 0 && currentTime.hour() < 12) { ui.workSpaceLabel->setText("Good Morning!"); }
    else if (currentTime.hour() >= 12 && currentTime.hour() < 18) { ui.workSpaceLabel->setText("Good Afternoon!"); }
    else { ui.workSpaceLabel->setText("Good Evening!"); }*/
}

void ScheduleView::setupUi()
{
    m_scheduleLayout = new QVBoxLayout(this);
    m_viewSwitchBar = new QWidget(this);
    m_viewSwitchBar->setFixedHeight(60);
    m_viewSwitchBarLayout = new QHBoxLayout(m_viewSwitchBar);
    m_dayViewSwitchButton = new QPushButton("Day", m_viewSwitchBar);
    m_dayViewSwitchButton->setFont(viewSwitchButtonFont);
    m_weekViewSwitchButton = new QPushButton("Week", m_viewSwitchBar);
    m_weekViewSwitchButton->setFont(viewSwitchButtonFont);
    m_monthViewSwitchButton = new QPushButton("Month", m_viewSwitchBar);
    m_monthViewSwitchButton->setFont(viewSwitchButtonFont);
    m_viewSwitchBarLayout->addWidget(m_dayViewSwitchButton);
    m_viewSwitchBarLayout->addWidget(m_weekViewSwitchButton);
    m_viewSwitchBarLayout->addWidget(m_monthViewSwitchButton);

    m_scheduleWidget = new QWidget(this);
    m_scheduleWidgetLayout = new QVBoxLayout(m_scheduleWidget);
    m_scheduleWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_scheduleWidgetLayout->setSpacing(0);

    m_scheduleLayout->addWidget(m_viewSwitchBar);
    m_scheduleLayout->addWidget(m_scheduleWidget);

    QStringList weekdays = { "Mon", "Tue", "Wed", "Thur", "Fri", "Sat", "Sun" };
    m_weekdaysBar = new QWidget(m_scheduleWidget);
    m_weekdaysBarLayout = new QHBoxLayout(m_weekdaysBar);
    m_weekdaysBarLayout->setContentsMargins(0, 0, 0, 0);
    m_weekdaysBarLayout->setSpacing(0);
    for (int weekdayIndex = 0; weekdayIndex < 7; weekdayIndex++)
    {
        QLabel* weekday = new QLabel(weekdays[weekdayIndex], m_weekdaysBar);
        weekday->setStyleSheet("QLabel { border: 1px solid black }");
        m_weekdaysBarLayout->addWidget(weekday);
    }
    m_scheduleWidgetLayout->addWidget(m_weekdaysBar);

    QDate date = QDate::currentDate();
    int year = date.year();
    int month = date.month();
    int firstDayOfWeek = QDate(year, month, 1).dayOfWeek();
    int daysNum = date.daysInMonth();
    int weeksNum = (int)ceil(double(daysNum + (firstDayOfWeek - 1)) / 7);
    QList<QList<QLabel*>> monthList = {};
    for (int weekIndex = 1; weekIndex <= weeksNum; weekIndex++)
    {
        QList<QLabel*> weekList = {};
        QWidget* week = new QWidget(m_scheduleWidget);
        QHBoxLayout* weekLayout = new QHBoxLayout(week);
        weekLayout->setContentsMargins(0, 0, 0, 0);
        weekLayout->setSpacing(0);
        for (int weekdayIndex = 1; weekdayIndex <= 7; weekdayIndex++)
        {
            QLabel* weekday = new QLabel(week);
            weekday->setStyleSheet("QLabel { border: 1px solid black }");
            weekday->setMinimumHeight(15);
            weekLayout->addWidget(weekday);
            weekList.append(weekday);
        }
        m_scheduleWidgetLayout->addWidget(week);
        monthList.append(weekList);
    }

    int weekIndex = 1;
    for (int dayIndex = 1; dayIndex <= daysNum; dayIndex++)
    {
        int weekday = QDate(year, month, dayIndex).dayOfWeek();
        monthList[weekIndex - 1][weekday - 1]->setText(QString::number(dayIndex));
        if (weekday == 7) weekIndex++;
    }
    QFile styleFile(":/theme/Global/schedule.qss");
    styleFile.open(QIODeviceBase::ReadOnly);
    this->setStyleSheet(styleFile.readAll());
    styleFile.close();
}