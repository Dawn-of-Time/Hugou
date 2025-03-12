#include "Widgets/Include/MemoSettingItem/MemoTimeItem.h"

MemoTimeItem::MemoTimeItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
	m_animationGroup = new QParallelAnimationGroup(this);
	connect(m_animationGroup, &QParallelAnimationGroup::finished, this, &MemoTimeItem::disableGraphicsEffect);
	connect(m_reminderButton, &QPushButton::clicked, this, &MemoTimeItem::switchReminder);
	connect(m_dateTitle, &QPushButton::clicked, this, &MemoTimeItem::setYearAndMonth);
	connect(m_backButton, &QPushButton::clicked, this, &MemoTimeItem::goBackAMonth);
	connect(m_forwardButton, &QPushButton::clicked, this, &MemoTimeItem::goForwardAMonth);
	connect(m_backToTodayButton, &QPushButton::clicked, this, &MemoTimeItem::goBackToToday);
}

MemoTimeItem::~MemoTimeItem()
{
	m_animationGroup->clear();
	delete m_animationGroup;
}

void MemoTimeItem::setupUi()
{
	// 字体清单
	QFont titleFont = QFont("NeverMind", 12, QFont::DemiBold);
	QFont monthContentFont = QFont("NeverMind", 10, QFont::Normal);
	QFont timeFont = QFont("NeverMind", 10, QFont::Normal);
	QFont backToTodayFont = QFont("NeverMind", 10, QFont::Bold);
	QFont toFont = QFont("NeverMind", 10, QFont::Medium);

	setFixedHeight(340);

	m_title->setText("Time");
	m_reminderWidget = new QWidget(m_titleWidget);
	m_reminderWidget->setFixedSize(50, 25);
	m_reminderButton = new QPushButton(m_reminderWidget);
	m_reminderButton->setFixedSize(25, 25);
	m_reminderButton->setIconSize(QSize(16, 16));
	m_reminderButton->setIcon(QIcon(":/icon/remind.ico"));
	m_reminderButton->setStyleSheet("border: none; background-color: transparent");
	m_reminderButton->setCursor(Qt::PointingHandCursor);
	m_off = new QPushButton(m_reminderButton);
	m_off->setFixedSize(25, 25);
	m_off->setIcon(QIcon(":/icon/off.ico"));
	m_off->setIconSize(QSize(16, 16));
	m_off->setAttribute(Qt::WA_TransparentForMouseEvents);
	m_moreButton = new QPushButton(m_reminderWidget);
	m_moreButton->setFixedSize(25, 25);
	m_moreButton->setIconSize(QSize(16, 16));
	m_moreButton->setIcon(QIcon(":/icon/more.ico"));
	m_moreButton->setStyleSheet("border: none; background-color: transparent");
	m_moreButtonEffect = new QGraphicsOpacityEffect(m_moreButton);
	m_moreButtonEffect->setOpacity(0);
	m_moreButton->setGraphicsEffect(m_moreButtonEffect);
	m_moreButtonEffect->setEnabled(false);
	m_reminderButton->move(25, 0);
	m_moreButton->move(25, 0);
	m_moreButton->hide();
	m_titleLayout->addWidget(m_reminderWidget);

	m_content->setFixedHeight(310);
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(0, 0, 0, 0);
	m_contentLayout->setSpacing(5);
	m_contentLayout->setAlignment(Qt::AlignHCenter);

	m_dateWidget = new QWidget(m_content);
	m_dateWidget->setFixedSize(300, 250);
	m_dateWidgetLayout = new QVBoxLayout(m_dateWidget);
	m_dateWidgetLayout->setContentsMargins(10, 10, 10, 10);
	m_dateWidgetLayout->setSpacing(10);
	m_dateTitleWidget = new QWidget(m_dateWidget);
	m_dateTitleWidget->setFixedHeight(20);
	m_dateTitleWidgetLayout = new QHBoxLayout(m_dateTitleWidget);
	m_dateTitleWidgetLayout->setContentsMargins(5, 0, 5, 0);
	m_dateTitleWidgetLayout->setSpacing(0);
	m_dateTitle = new FadeEffectButton("", titleFont, m_titleWidget);
	m_dateTitle->setFixedSize(178, 20);
	m_dateTitle->layout()->setContentsMargins(0, 0, 0, 0);
	m_dateTitle->setBackgroundWidgetStyleSheet("background-color: rgba(0, 0, 255, 0.1); border-radius: 5px");
	m_actionWidget = new QWidget(m_dateTitleWidget);
	m_actionWidget->setFixedWidth(92);
	m_actionWidgetLayout = new QHBoxLayout(m_actionWidget);
	m_actionWidgetLayout->setContentsMargins(5, 0, 5, 0);
	m_actionWidgetLayout->setSpacing(5);
	m_backToTodayButton = new QPushButton("T", m_actionWidget);
	m_backToTodayButton->setObjectName("backToTodayButton");
	m_backToTodayButton->setFixedSize(20, 20);
	m_backToTodayButton->setFont(backToTodayFont);
	m_backToTodayButton->setCursor(Qt::PointingHandCursor);
	m_backToTodayButton->setStyleSheet("background-color: #AEE4FD; border-radius: 10px");
	QSizePolicy policy = m_backToTodayButton->sizePolicy();
	policy.setRetainSizeWhenHidden(true);
	m_backToTodayButton->setSizePolicy(policy);
	m_backButton = new QPushButton(m_actionWidget);
	m_backButton->setObjectName("backButton");
	m_backButton->setFixedSize(20, 20);
	m_backButton->setIcon(QIcon(":/icon/back.ico"));
	m_backButton->setIconSize(QSize(12, 12));
	m_backButton->setCursor(Qt::PointingHandCursor);
	m_forwardButton = new QPushButton(m_actionWidget);
	m_forwardButton->setObjectName("forwardButton");
	m_forwardButton->setFixedSize(20, 20);
	m_forwardButton->setIcon(QIcon(":/icon/forward.ico"));
	m_forwardButton->setIconSize(QSize(12, 12));
	m_forwardButton->setCursor(Qt::PointingHandCursor);
	m_actionWidgetLayout->addWidget(m_backToTodayButton);
	m_actionWidgetLayout->addWidget(m_backButton);
	m_actionWidgetLayout->addWidget(m_forwardButton);
	m_dateTitleWidgetLayout->addWidget(m_dateTitle);
	m_dateTitleWidgetLayout->addStretch();
	m_dateTitleWidgetLayout->addWidget(m_actionWidget);

	m_monthWidget = new QWidget(m_dateWidget);
	m_monthWidgetLayout = new QVBoxLayout(m_monthWidget);
	m_monthWidgetLayout->setAlignment(Qt::AlignHCenter);
	m_monthWidgetLayout->setContentsMargins(14, 0, 14, 0);
	m_monthWidgetLayout->setSpacing(10);
	// 星期
	QStringList weekdays = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
	m_weekdaysBar = new QWidget(m_dateWidget);
	m_weekdaysBar->setFixedSize(252, 20);
	m_weekdaysBarLayout = new QHBoxLayout(m_weekdaysBar);
	m_weekdaysBarLayout->setContentsMargins(0, 0, 0, 0);
	m_weekdaysBarLayout->setSpacing(0);
	for (int weekdayIndex = 0; weekdayIndex < 7; weekdayIndex++)
	{
		QLabel* weekday = new QLabel(weekdays[weekdayIndex], m_weekdaysBar);
		weekday->setFixedSize(36, 20);
		weekday->setFont(monthContentFont);
		weekday->setAlignment(Qt::AlignCenter);
		m_weekdaysBarLayout->addWidget(weekday);
	}
	m_monthWidgetLayout->addWidget(m_weekdaysBar);
	int weeksNum = 6;
	// 绘制网格
	for (int weekIndex = 1; weekIndex <= weeksNum; weekIndex++)
	{
		// 周网格
		QWidget* week = new QWidget(m_monthWidget);
		week->setFixedSize(252, 20);
		QHBoxLayout* weekLayout = new QHBoxLayout(week);
		weekLayout->setContentsMargins(0, 0, 0, 0);
		weekLayout->setSpacing(0);
		for (int dayIndex = 1; dayIndex <= 7; dayIndex++)
		{
			// 天网格
			QPushButton* day = new QPushButton(week);
			day->setObjectName("day");
			day->setFont(monthContentFont);
			day->setFixedSize(36, 20);
			day->setCursor(Qt::PointingHandCursor);
			connect(day, &QPushButton::clicked, [this, day]()
				{
					if (m_timeSelectMode == TimeSelectMode::BeginMode)
					{
						m_endWidget->hide();
						m_beginAndEndWidget->hide();
						m_beginWidget->show();
						m_beginWidget->move(getLabelPos(m_beginWidget, day));
						m_beginButton = day;
						m_timeSelectMode = TimeSelectMode::EndMode;
					}
					else
					{
						if (day == m_beginButton)
						{
							m_endWidget->hide();
							m_beginWidget->hide();
							m_beginAndEndWidget->show();
							m_beginAndEndWidget->move(getLabelPos(m_beginAndEndWidget, day));
							m_endButton = day;
						}
						else
						{
							m_endWidget->show();
							m_endWidget->move(getLabelPos(m_endWidget, day));
							m_endButton = day;
						}
						m_timeSelectMode = TimeSelectMode::BeginMode;
					}
				});
			weekLayout->addWidget(day);
			m_dayListForAMonth.append(day);
		}
		m_monthWidgetLayout->addWidget(week);
		m_weekListForAMonth.append(week);
	}
	loadMonthView(QDate::currentDate());

	m_beginAndEndWidget = new QWidget(m_content);
	m_beginAndEndWidget->setFixedHeight(30);
	m_beginAndEndWidget->setStyleSheet("background-color: rgba(55, 61, 63, 0.7); border-radius: 5px");
	m_beginAndEndWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
	QVBoxLayout* beginAndEndWidgetLayout = new QVBoxLayout(m_beginAndEndWidget);
	beginAndEndWidgetLayout->setContentsMargins(8, 5, 5, 8);
	beginAndEndWidgetLayout->setSpacing(0);
	m_beginAndEndLabel = new QLabel("Begin | End", m_beginAndEndWidget);
	m_beginAndEndLabel->setFixedHeight(20);
	m_beginAndEndLabel->setFont(QFont("NeverMind", 10, QFont::Medium));
	m_beginAndEndLabel->setAlignment(Qt::AlignCenter);
	m_beginAndEndLabel->setStyleSheet("background-color: transparent; color: white");
	m_beginAndEndLabel->adjustSize();
	beginAndEndWidgetLayout->addWidget(m_beginAndEndLabel);

	m_beginWidget = new QWidget(m_content);
	m_beginWidget->setFixedHeight(30);
	m_beginWidget->setStyleSheet("background-color: rgba(55, 61, 63, 0.7); border-radius: 5px");
	m_beginWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
	QVBoxLayout* beginWidgetLayout = new QVBoxLayout(m_beginWidget);
	beginWidgetLayout->setContentsMargins(8, 5, 5, 8);
	beginWidgetLayout->setSpacing(0);
	m_beginLabel = new QLabel("Begin", m_beginWidget);
	m_beginLabel->setFixedHeight(20);
	m_beginLabel->setFont(QFont("NeverMind", 10, QFont::Medium));
	m_beginLabel->setAlignment(Qt::AlignCenter);
	m_beginLabel->setStyleSheet("background-color: transparent; color: white");
	m_beginLabel->adjustSize();
	beginWidgetLayout->addWidget(m_beginLabel);
	m_beginWidget->hide();

	m_endWidget = new QWidget(m_content);
	m_endWidget->setFixedHeight(30);
	m_endWidget->setStyleSheet("background-color: rgba(55, 61, 63, 0.7); border-radius: 5px");
	m_endWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
	QVBoxLayout* endWidgetLayout = new QVBoxLayout(m_endWidget);
	endWidgetLayout->setContentsMargins(8, 5, 5, 8);
	endWidgetLayout->setSpacing(0);
	m_endLabel = new QLabel("End", m_endWidget);
	m_endLabel->setFixedHeight(20);
	m_endLabel->setFont(QFont("NeverMind", 10, QFont::Medium));
	m_endLabel->setAlignment(Qt::AlignCenter);
	m_endLabel->setStyleSheet("background-color: transparent; color: white");
	m_endLabel->adjustSize();
	endWidgetLayout->addWidget(m_endLabel);
	m_endWidget->hide();

	m_dateWidgetLayout->addWidget(m_dateTitleWidget);
	m_dateWidgetLayout->addWidget(m_monthWidget);

	m_timeWidget = new QWidget(m_content);
	m_timeWidget->setFixedHeight(55);
	m_timeWidgetLayout = new QHBoxLayout(m_timeWidget);
	m_timeWidgetLayout->setContentsMargins(3, 0, 3, 0);
	m_timeWidgetLayout->setSpacing(5);

	m_beginTimeWidget = new QWidget(m_timeWidget);
	m_beginTimeWidget->setFixedSize(134, 55);
	m_beginTimeWidgetLayout = new QVBoxLayout(m_beginTimeWidget);
	m_beginTimeWidgetLayout->setContentsMargins(5, 5, 5, 5);
	m_beginTimeWidgetLayout->setSpacing(5);
	m_beginTimeYYYYMMDDWidget = new QWidget(m_beginTimeWidget);
	m_beginTimeYYYYMMDDWidget->setObjectName("beginTimeYYYYMMDDWidget");
	m_beginTimeYYYYMMDDWidget->setFixedSize(124, 20);
	m_beginTimeYYYYMMDDWidget->setStyleSheet("QWidget #beginTimeYYYYMMDDWidget { border-bottom: 1px solid #377FED }");
	m_beginTimeYYYYMMDDWidgetLayout = new QHBoxLayout(m_beginTimeYYYYMMDDWidget);
	m_beginTimeYYYYMMDDWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_beginTimeYYYYMMDDWidgetLayout->setSpacing(3);
	m_beginTimeYearButton = new QPushButton(m_beginTimeYYYYMMDDWidget);
	m_beginTimeYearButton->setFixedSize(29, 20);
	m_beginTimeYearButton->setFont(timeFont);
	m_beginTimeYearButton->setText("Year");
	QLabel* beginYearMonthSeparator = new QLabel("-", m_beginTimeYYYYMMDDWidget);
	beginYearMonthSeparator->setFixedSize(7, 20);
	beginYearMonthSeparator->setFont(timeFont);
	m_beginTimeMonthButton = new QPushButton(m_beginTimeYYYYMMDDWidget);
	m_beginTimeMonthButton->setFixedSize(43, 20);
	m_beginTimeMonthButton->setFont(timeFont);
	m_beginTimeMonthButton->setText("Month");
	QLabel* beginMonthDaySeparator = new QLabel("-", m_beginTimeYYYYMMDDWidget);
	beginMonthDaySeparator->setFixedSize(7, 20);
	beginMonthDaySeparator->setFont(timeFont);
	m_beginTimeDayButton = new QPushButton(m_beginTimeYYYYMMDDWidget);
	m_beginTimeDayButton->setFixedSize(26, 20);
	m_beginTimeDayButton->setFont(timeFont);
	m_beginTimeDayButton->setText("Day");
	m_beginTimeYYYYMMDDWidgetLayout->addStretch();
	m_beginTimeYYYYMMDDWidgetLayout->addWidget(m_beginTimeYearButton);
	m_beginTimeYYYYMMDDWidgetLayout->addWidget(beginYearMonthSeparator);
	m_beginTimeYYYYMMDDWidgetLayout->addWidget(m_beginTimeMonthButton);
	m_beginTimeYYYYMMDDWidgetLayout->addWidget(beginMonthDaySeparator);
	m_beginTimeYYYYMMDDWidgetLayout->addWidget(m_beginTimeDayButton);
	m_beginTimeYYYYMMDDWidgetLayout->addStretch();
	m_beginTimeHHMMWidget = new QWidget(m_beginTimeWidget);
	m_beginTimeHHMMWidget->setObjectName("beginTimeHHMMWidget");
	m_beginTimeHHMMWidget->setFixedSize(124, 20);
	m_beginTimeHHMMWidget->setStyleSheet("QWidget #beginTimeHHMMWidget { border-bottom: 1px solid #377FED }");
	m_beginTimeHHMMWidgetLayout = new QHBoxLayout(m_beginTimeHHMMWidget);
	m_beginTimeHHMMWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_beginTimeHHMMWidgetLayout->setSpacing(3);
	m_beginTimeHourButton = new QPushButton(m_beginTimeHHMMWidget);
	m_beginTimeHourButton->setFixedSize(32, 20);
	m_beginTimeHourButton->setFont(timeFont);
	m_beginTimeHourButton->setText("Hour");
	QLabel* beginHourMinuteSeparator = new QLabel(":", m_beginTimeHHMMWidget);
	beginHourMinuteSeparator->setFixedSize(4, 20);
	beginHourMinuteSeparator->setFont(timeFont);
	m_beginTimeMinuteButton = new QPushButton(m_beginTimeHHMMWidget);
	m_beginTimeMinuteButton->setFixedSize(48, 20);
	m_beginTimeMinuteButton->setFont(timeFont);
	m_beginTimeMinuteButton->setText("Minute");
	m_beginTimeHHMMWidgetLayout->addStretch();
	m_beginTimeHHMMWidgetLayout->addWidget(m_beginTimeHourButton);
	m_beginTimeHHMMWidgetLayout->addWidget(beginHourMinuteSeparator);
	m_beginTimeHHMMWidgetLayout->addWidget(m_beginTimeMinuteButton);
	m_beginTimeHHMMWidgetLayout->addStretch();

	m_beginTimeWidgetLayout->addWidget(m_beginTimeYYYYMMDDWidget);
	m_beginTimeWidgetLayout->addWidget(m_beginTimeHHMMWidget);

	m_toLabel = new QLabel("To", m_timeWidget);
	m_toLabel->setFixedSize(20, 20);
	m_toLabel->setStyleSheet("color: white; background-color: #468DFA; border-radius: 5px");
	m_toLabel->setAlignment(Qt::AlignCenter);
	m_toLabel->setFont(toFont);

	m_endTimeWidget = new QWidget(m_timeWidget);
	m_endTimeWidget->setFixedSize(134, 55);
	m_endTimeWidgetLayout = new QVBoxLayout(m_endTimeWidget);
	m_endTimeWidgetLayout->setContentsMargins(5, 5, 5, 5);
	m_endTimeWidgetLayout->setSpacing(5);
	m_endTimeYYYYMMDDWidget = new QWidget(m_endTimeWidget);
	m_endTimeYYYYMMDDWidget->setObjectName("endTimeYYYYMMDDWidget");
	m_endTimeYYYYMMDDWidget->setFixedSize(124, 20);
	m_endTimeYYYYMMDDWidget->setStyleSheet("QWidget #endTimeYYYYMMDDWidget { border-bottom: 1px solid #377FED }");
	m_endTimeYYYYMMDDWidgetLayout = new QHBoxLayout(m_endTimeYYYYMMDDWidget);
	m_endTimeYYYYMMDDWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_endTimeYYYYMMDDWidgetLayout->setSpacing(3);
	m_endTimeYearButton = new QPushButton(m_endTimeYYYYMMDDWidget);
	m_endTimeYearButton->setFixedSize(29, 20);
	m_endTimeYearButton->setFont(timeFont);
	m_endTimeYearButton->setText("Year");

	QLabel* endYearMonthSeparator = new QLabel("-", m_endTimeYYYYMMDDWidget);
	endYearMonthSeparator->setFixedSize(7, 20);
	endYearMonthSeparator->setFont(timeFont);
	m_endTimeMonthButton = new QPushButton(m_endTimeYYYYMMDDWidget);
	m_endTimeMonthButton->setFixedSize(43, 20);
	m_endTimeMonthButton->setFont(timeFont);
	m_endTimeMonthButton->setText("Month");
	QLabel* endMonthDaySeparator = new QLabel("-", m_endTimeYYYYMMDDWidget);
	endMonthDaySeparator->setFixedSize(7, 20);
	endMonthDaySeparator->setFont(timeFont);
	m_endTimeDayButton = new QPushButton(m_endTimeYYYYMMDDWidget);
	m_endTimeDayButton->setFixedSize(26, 20);
	m_endTimeDayButton->setFont(timeFont);
	m_endTimeDayButton->setText("Day");
	m_endTimeYYYYMMDDWidgetLayout->addStretch();
	m_endTimeYYYYMMDDWidgetLayout->addWidget(m_endTimeYearButton);
	m_endTimeYYYYMMDDWidgetLayout->addWidget(endYearMonthSeparator);
	m_endTimeYYYYMMDDWidgetLayout->addWidget(m_endTimeMonthButton);
	m_endTimeYYYYMMDDWidgetLayout->addWidget(endMonthDaySeparator);
	m_endTimeYYYYMMDDWidgetLayout->addWidget(m_endTimeDayButton);
	m_endTimeYYYYMMDDWidgetLayout->addStretch();

	m_endTimeHHMMWidget = new QWidget(m_endTimeWidget);
	m_endTimeHHMMWidget->setObjectName("endTimeHHMMWidget");
	m_endTimeHHMMWidget->setFixedSize(124, 20);
	m_endTimeHHMMWidget->setStyleSheet("QWidget #endTimeHHMMWidget { border-bottom: 1px solid #377FED }");
	m_endTimeHHMMWidgetLayout = new QHBoxLayout(m_endTimeHHMMWidget);
	m_endTimeHHMMWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_endTimeHHMMWidgetLayout->setSpacing(3);
	m_endTimeHHMMWidgetLayout->setAlignment(Qt::AlignCenter);
	m_endTimeHourButton = new QPushButton(m_endTimeHHMMWidget);
	m_endTimeHourButton->setFixedSize(32, 20);
	m_endTimeHourButton->setFont(timeFont);
	m_endTimeHourButton->setText("Hour");
	QLabel* endHourMinuteSeparator = new QLabel(":", m_endTimeHHMMWidget);
	endHourMinuteSeparator->setFixedSize(4, 20);
	endHourMinuteSeparator->setFont(timeFont);
	m_endTimeMinuteButton = new QPushButton(m_endTimeHHMMWidget);
	m_endTimeMinuteButton->setFixedSize(48, 20);
	m_endTimeMinuteButton->setFont(timeFont);
	m_endTimeMinuteButton->setText("Minute");
	m_endTimeHHMMWidgetLayout->addStretch();
	m_endTimeHHMMWidgetLayout->addWidget(m_endTimeHourButton);
	m_endTimeHHMMWidgetLayout->addWidget(endHourMinuteSeparator);
	m_endTimeHHMMWidgetLayout->addWidget(m_endTimeMinuteButton);
	m_endTimeHHMMWidgetLayout->addStretch();
	m_endTimeWidgetLayout->addWidget(m_endTimeYYYYMMDDWidget);
	m_endTimeWidgetLayout->addWidget(m_endTimeHHMMWidget);

	m_beginTimeYearButton->setStyleSheet("color: #ACB1C6");
	m_beginTimeMonthButton->setStyleSheet("color: #ACB1C6");
	m_beginTimeDayButton->setStyleSheet("color: #ACB1C6");
	m_beginTimeHourButton->setStyleSheet("color: #ACB1C6");
	m_beginTimeMinuteButton->setStyleSheet("color: #ACB1C6");
	m_endTimeYearButton->setStyleSheet("color: #ACB1C6");
	m_endTimeMonthButton->setStyleSheet("color: #ACB1C6");
	m_endTimeDayButton->setStyleSheet("color: #ACB1C6");
	m_endTimeHourButton->setStyleSheet("color: #ACB1C6");
	m_endTimeMinuteButton->setStyleSheet("color: #ACB1C6");

	m_timeWidgetLayout->addWidget(m_beginTimeWidget);
	m_timeWidgetLayout->addWidget(m_toLabel);
	m_timeWidgetLayout->addWidget(m_endTimeWidget);

	m_contentLayout->addWidget(m_dateWidget);
	m_contentLayout->addWidget(m_timeWidget);
}

void MemoTimeItem::loadMonthView(const QDate& date)
{
	int year = date.year();
	int month = date.month();
	if (year == m_currentDate.year() && month == m_currentDate.month()) return;
	int firstDayOfWeek = QDate(year, month, 1).dayOfWeek();
	int daysNum = date.daysInMonth();

	m_dateTitle->setText(m_monthNameList[month - 1] + " " + QString::number(year));

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
		m_todayButton->setStyleSheet("background-color: #AEE4FD");
		m_backToTodayButton->hide();
	}
	else
	{
		m_todayButton->setStyleSheet("background-color: transparent");
		m_backToTodayButton->show();
	}
	m_currentDate.setDate(year, month, date.day());
}

void MemoTimeItem::goBackAMonth()
{
	loadMonthView(m_currentDate.addMonths(-1));
}

void MemoTimeItem::goForwardAMonth()
{
	loadMonthView(m_currentDate.addMonths(1));
}

void MemoTimeItem::goBackToToday()
{
	loadMonthView(QDate::currentDate());
}

void MemoTimeItem::setYearAndMonth()
{
	// 字体清单
	QFont yearFont = QFont("NeverMind", 14, QFont::DemiBold);
	QFont monthFont = QFont("NeverMind", 12, QFont::Light);

	m_dateTitle->disconnect();
	CloseWhenLeaveWidget* settingWidget = new CloseWhenLeaveWidget(m_content);
	settingWidget->setFixedSize(255, 195);
	settingWidget->move(21, 36);
	settingWidget->setObjectName("yearAndMonthSettingWidget");
	settingWidget->setStyleSheet("QWidget #yearAndMonthSettingWidget { background-color: rgba(255, 255, 255, 0.98);  border-radius: 10px }");
	connect(m_dateTitle, &QPushButton::clicked, settingWidget, &CloseWhenLeaveWidget::close);

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
					m_dateTitle->disconnect();
					connect(m_dateTitle, &FadeEffectButton::clicked, this, &MemoTimeItem::setYearAndMonth);
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
			m_dateTitle->disconnect();
			connect(m_dateTitle, &QPushButton::clicked, this, &MemoTimeItem::setYearAndMonth);
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

void MemoTimeItem::switchReminder()
{
	if (m_animationGroup->state() == QAbstractAnimation::Running)
		m_animationGroup->stop();
	m_animationGroup->clear();
	enableGraphicsEffect();
	if (m_hasReminder)
	{
		m_hasReminder = false;
		m_off->show();
		QPropertyAnimation* moveAnimation = new QPropertyAnimation(m_reminderButton, "pos", this);
		moveAnimation->setStartValue(m_reminderButton->pos());
		moveAnimation->setEndValue(QPoint(25, 0));
		moveAnimation->setDuration(400);
		QPropertyAnimation* fadeOutAnimation = new QPropertyAnimation(m_moreButtonEffect, "opacity", this);
		fadeOutAnimation->setStartValue(1);
		fadeOutAnimation->setEndValue(0);
		fadeOutAnimation->setDuration(400);
		m_animationGroup->addAnimation(fadeOutAnimation);
		m_animationGroup->addAnimation(moveAnimation);
	}
	else
	{
		m_hasReminder = true;
		m_off->hide();
		QPropertyAnimation* moveAnimation = new QPropertyAnimation(m_reminderButton, "pos", this);
		moveAnimation->setStartValue(m_reminderButton->pos());
		moveAnimation->setEndValue(QPoint(0, 0));
		moveAnimation->setDuration(400);
		QPropertyAnimation* fadeInAnimation = new QPropertyAnimation(m_moreButtonEffect, "opacity", this);
		fadeInAnimation->setStartValue(0);
		fadeInAnimation->setEndValue(1);
		fadeInAnimation->setDuration(400);
		m_animationGroup->addAnimation(moveAnimation);
		m_animationGroup->addAnimation(fadeInAnimation);
	}
	m_animationGroup->start();
}

void MemoTimeItem::enableGraphicsEffect()
{
	m_moreButtonEffect->setEnabled(true);
	m_moreButton->show();
}

void MemoTimeItem::disableGraphicsEffect()
{
	m_moreButtonEffect->setEnabled(false);
	if (!m_hasReminder)
		m_moreButton->hide();
}

QPoint MemoTimeItem::getLabelPos(QWidget* label, QPushButton* dayButton)
{
	QPoint buttonTopLeft = dayButton->mapTo(m_content, QPoint(0, 0));
	int x = buttonTopLeft.x() + (dayButton->width() - label->width()) / 2;
	int y = buttonTopLeft.y() - 35;
	return QPoint(x, y);
}

void MemoTimeItem::showEvent(QShowEvent* event)
{
	MemoSettingItem::show();
	m_beginAndEndWidget->adjustSize();
	m_beginWidget->adjustSize();
	m_endWidget->adjustSize();
	m_beginAndEndWidget->move(getLabelPos(m_beginAndEndWidget, m_todayButton));
}