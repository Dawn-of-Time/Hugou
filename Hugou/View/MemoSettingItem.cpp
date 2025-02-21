#include "MemoSettingItem.h"

MemoSettingItem::MemoSettingItem(QWidget* parent)
	:QWidget(parent)
{
	setupUi();
}

void MemoSettingItem::setupUi()
{
	// 字体清单
	QFont titleFont = QFont("NeverMind", 14, QFont::Medium);

	setFixedWidth(304);
	m_itemLayout = new QVBoxLayout(this);
	m_itemLayout->setContentsMargins(0, 0, 0, 0);
	m_itemLayout->setSpacing(5);
	m_itemLayout->setAlignment(Qt::AlignLeft);

	m_titleWidget = new QWidget(this);
	m_titleWidget->setFixedHeight(25);
	m_titleLayout = new QHBoxLayout(m_titleWidget);
	m_titleLayout->setContentsMargins(0, 0, 0, 0);
	m_titleLayout->setSpacing(0);

	m_title = new QLabel(m_titleWidget);
	m_title->setFont(titleFont);
	m_title->setFixedHeight(25);

	m_titleLayout->addWidget(m_title);
	m_titleLayout->addStretch();

	m_content = new QWidget(this);

	m_itemLayout->addWidget(m_titleWidget);
	m_itemLayout->addWidget(m_content);
}

MemoTypeItem::MemoTypeItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
	connect(m_addTypeButton, &QPushButton::clicked, this, &MemoTypeItem::showMemoTypeConfigView);
}

void MemoTypeItem::setupUi()
{
	// 字体清单
	QFont labelFont = QFont("NeverMind", 10, QFont::Normal);

	setFixedHeight(110);
	m_title->setText("Type");
	m_content->setFixedHeight(80);
	m_contentLayout = new QHBoxLayout(m_content);
	m_contentLayout->setContentsMargins(10, 10, 10, 10);
	m_contentLayout->setSpacing(10);
	m_contentLayout->setAlignment(Qt::AlignLeft);
	m_typeListWidget = new QWidget(m_content);
	m_typeListWidgetLayout = new QHBoxLayout(m_typeListWidget);
	m_typeListWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_typeListWidgetLayout->setSpacing(10);

	QWidget* spacer = new QWidget(m_content);
	spacer->setFixedSize(2, 45);
	spacer->setStyleSheet("background-color: black");

	m_addTypeButton = new QPushButton(m_content);
	m_addTypeButton->setFixedSize(40, 60);
	m_addTypeButton->setCursor(Qt::PointingHandCursor);
	QVBoxLayout* addTypeButtonLayout = new QVBoxLayout(m_addTypeButton);
	addTypeButtonLayout->setContentsMargins(0, 0, 0, 0);
	addTypeButtonLayout->setSpacing(4);
	QPushButton* icon = new QPushButton(m_addTypeButton);
	icon->setFixedSize(36, 36);
	icon->setStyleSheet("background-color: #EAF9FE; border-radius: 5px; border: none");
	icon->setIcon(QIcon(":/icon/preference_default.ico"));
	icon->setIconSize(QSize(16, 16));
	icon->setAttribute(Qt::WA_TransparentForMouseEvents);
	QLabel* label = new QLabel("Config", m_addTypeButton);
	label->setAlignment(Qt::AlignHCenter);
	label->setFixedSize(40, 20);
	label->setFont(labelFont);

	addTypeButtonLayout->setAlignment(Qt::AlignHCenter);
	addTypeButtonLayout->addWidget(icon);
	addTypeButtonLayout->addWidget(label);

	m_contentLayout->addWidget(m_typeListWidget);
	m_contentLayout->addWidget(spacer);
	m_contentLayout->addWidget(m_addTypeButton);
}

void MemoTypeItem::addMemoType(MemoType memoType)
{
	// 字体清单
	QFont labelFont = QFont("NeverMind", 10, QFont::Normal);

	if (m_count <= 4)
	{
		QPushButton* memoTypeWidget = new QPushButton(m_content);
		memoTypeWidget->setFixedSize(36, 60);
		QVBoxLayout* memoTypeWidgetLayout = new QVBoxLayout(memoTypeWidget);
		memoTypeWidgetLayout->setContentsMargins(0, 0, 0, 0);
		memoTypeWidgetLayout->setSpacing(4);
		QLabel* icon = new QLabel(memoTypeWidget);
		icon->setAlignment(Qt::AlignCenter);
		icon->setFixedSize(36, 36);
		icon->setStyleSheet(QString("background-color: %1; border-radius: 5px").arg(memoType.color.name()));
		QLabel* label = new QLabel(memoType.name, memoTypeWidget);
		label->setAlignment(Qt::AlignHCenter);
		label->setFixedSize(36, 20);
		label->setFont(labelFont);

		memoTypeWidgetLayout->setAlignment(Qt::AlignHCenter);
		memoTypeWidgetLayout->addWidget(icon);
		memoTypeWidgetLayout->addWidget(label);

		m_typeListWidgetLayout->addWidget(memoTypeWidget);
		m_count++;
	}
}

void MemoTypeItem::showMemoTypeConfigView()
{
	MemoTypeConfigView* view = new MemoTypeConfigView();
	view->show();
}

MemoTimeItem::MemoTimeItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
	m_animationGroup = new QParallelAnimationGroup(this);
	connect(m_animationGroup, &QParallelAnimationGroup::finished, this, &MemoTimeItem::disableGraphicsEffect);
	connect(m_reminderButton, &QPushButton::clicked, this, &MemoTimeItem::switchReminder);
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
	m_moreButton->setIconSize(QSize(25, 25));
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
	m_dateWidget->setObjectName("dateWidget");
	m_dateWidget->setStyleSheet("QWidget #dateWidget{background-color: rgba(255, 255, 255, 0.5); border-radius: 10px}");
	m_dateWidget->setFixedSize(300, 250);
	m_dateWidgetLayout = new QVBoxLayout(m_dateWidget);
	m_dateWidgetLayout->setContentsMargins(10, 10, 10, 10);
	m_dateWidgetLayout->setSpacing(10);
	m_dateTitleWidget = new QWidget(m_dateWidget);
	m_dateTitleWidget->setFixedHeight(20);
	m_dateTitleWidgetLayout = new QHBoxLayout(m_dateTitleWidget);
	m_dateTitleWidgetLayout->setContentsMargins(0, 0, 0, 0);
	QDate date = QDate::currentDate();
	m_dateTitle = new QLabel(m_monthNameList[date.month() - 1] + " " + QString::number(date.year()), m_dateTitleWidget);
	m_dateTitle->setFont(titleFont);
	m_actionWidget = new QWidget(m_dateTitleWidget);
	m_actionWidget->setFixedWidth(46);
	m_actionWidgetLayout = new QHBoxLayout(m_actionWidget);
	m_actionWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_actionWidgetLayout->setSpacing(0);
	m_backButton = new QPushButton(m_actionWidget);
	m_backButton->setObjectName("backButton");
	m_backButton->setFixedSize(20, 20);
	m_backButton->setIcon(QIcon(":/icon/back.ico"));
	m_backButton->setIconSize(QSize(12, 12));
	m_forwardButton = new QPushButton(m_actionWidget);
	m_forwardButton->setObjectName("forwardButton");
	m_forwardButton->setFixedSize(20, 20);
	m_forwardButton->setIcon(QIcon(":/icon/forward.ico"));
	m_forwardButton->setIconSize(QSize(12, 12));
	m_actionWidgetLayout->addWidget(m_backButton);
	m_actionWidgetLayout->addStretch();
	m_actionWidgetLayout->addWidget(m_forwardButton);
	m_dateTitleWidgetLayout->addWidget(m_dateTitle);
	m_dateTitleWidgetLayout->addStretch();
	m_dateTitleWidgetLayout->addWidget(m_actionWidget);

	m_monthWidget = new QWidget(m_dateWidget);
	m_monthWidgetLayout = new QVBoxLayout(m_monthWidget);
	m_monthWidgetLayout->setAlignment(Qt::AlignHCenter);
	m_monthWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_monthWidgetLayout->setSpacing(10);
	// 星期
	QStringList weekdays = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
	m_weekdaysBar = new QWidget(m_dateWidget);
	m_weekdaysBar->setFixedSize(280, 20);
	m_weekdaysBarLayout = new QHBoxLayout(m_weekdaysBar);
	m_weekdaysBarLayout->setContentsMargins(0, 0, 0, 0);
	m_weekdaysBarLayout->setSpacing(0);
	for (int weekdayIndex = 0; weekdayIndex < 7; weekdayIndex++)
	{
		QLabel* weekday = new QLabel(weekdays[weekdayIndex], m_weekdaysBar);
		weekday->setFixedSize(40, 20);
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
		week->setFixedSize(280, 20);
		QHBoxLayout* weekLayout = new QHBoxLayout(week);
		weekLayout->setContentsMargins(0, 0, 0, 0);
		weekLayout->setSpacing(0);
		for (int dayIndex = 1; dayIndex <= 7; dayIndex++)
		{
			// 天网格
			QPushButton* day = new QPushButton(week);
			day->setObjectName("day");
			day->setFont(monthContentFont);
			day->setFixedSize(40, 20);
			weekLayout->addWidget(day);
			m_dayListForAMonth.append(day);
		}
		m_monthWidgetLayout->addWidget(week);
		m_weekListForAMonth.append(week);
	}
	m_dateWidgetLayout->addWidget(m_dateTitleWidget);
	m_dateWidgetLayout->addWidget(m_monthWidget);
	m_dateWidgetLayout->addStretch();
	loadMonthView(date);

	m_timeWidget = new QWidget(m_content);
	m_timeWidget->setObjectName("timeWidget");
	m_timeWidget->setFixedHeight(55);
	m_timeWidget->setStyleSheet("QWidget #timeWidget {border: 2px dotted #377FED}");
	m_timeWidgetLayout = new QHBoxLayout(m_timeWidget);
	m_timeWidgetLayout->setContentsMargins(3, 0, 3, 0);
	m_timeWidgetLayout->setSpacing(5);

	m_startTimeWidget = new QWidget(m_timeWidget);
	m_startTimeWidget->setFixedSize(134, 55);
	m_startTimeWidgetLayout = new QVBoxLayout(m_startTimeWidget);
	m_startTimeWidgetLayout->setContentsMargins(5, 5, 5, 5);
	m_startTimeWidgetLayout->setSpacing(5);
	m_startTimeYYYYMMDDWidget = new QWidget(m_startTimeWidget);
	m_startTimeYYYYMMDDWidget->setFixedSize(124, 20);
	m_startTimeYYYYMMDDWidget->setStyleSheet("border-bottom: 1px solid #377FED");
	m_startTimeYYYYMMDDWidgetLayout = new QHBoxLayout(m_startTimeYYYYMMDDWidget);
	m_startTimeYYYYMMDDWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_startTimeYYYYMMDDWidgetLayout->setSpacing(3);
	m_startTimeYearButton = new QPushButton(m_startTimeYYYYMMDDWidget);
	m_startTimeYearButton->setFixedSize(29, 20);
	m_startTimeYearButton->setFont(timeFont);
	m_startTimeYearButton->setText("Year");
	QLabel* startYearMonthSeparator = new QLabel("-", m_startTimeYYYYMMDDWidget);
	startYearMonthSeparator->setFixedSize(7, 20);
	startYearMonthSeparator->setFont(timeFont);
	m_startTimeMonthButton = new QPushButton(m_startTimeYYYYMMDDWidget);
	m_startTimeMonthButton->setFixedSize(43, 20);
	m_startTimeMonthButton->setFont(timeFont);
	m_startTimeMonthButton->setText("Month");
	QLabel* startMonthDaySeparator = new QLabel("-", m_startTimeYYYYMMDDWidget);
	startMonthDaySeparator->setFixedSize(7, 20);
	startMonthDaySeparator->setFont(timeFont);
	m_startTimeDayButton = new QPushButton(m_startTimeYYYYMMDDWidget);
	m_startTimeDayButton->setFixedSize(26, 20);
	m_startTimeDayButton->setFont(timeFont);
	m_startTimeDayButton->setText("Day");
	m_startTimeYYYYMMDDWidgetLayout->addStretch();
	m_startTimeYYYYMMDDWidgetLayout->addWidget(m_startTimeYearButton);
	m_startTimeYYYYMMDDWidgetLayout->addWidget(startYearMonthSeparator);
	m_startTimeYYYYMMDDWidgetLayout->addWidget(m_startTimeMonthButton);
	m_startTimeYYYYMMDDWidgetLayout->addWidget(startMonthDaySeparator);
	m_startTimeYYYYMMDDWidgetLayout->addWidget(m_startTimeDayButton);
	m_startTimeYYYYMMDDWidgetLayout->addStretch();
	m_startTimeHHMMWidget = new QWidget(m_startTimeWidget);
	m_startTimeHHMMWidget->setFixedSize(124, 20);
	m_startTimeHHMMWidget->setStyleSheet("border-bottom: 1px solid #377FED");
	m_startTimeHHMMWidgetLayout = new QHBoxLayout(m_startTimeHHMMWidget);
	m_startTimeHHMMWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_startTimeHHMMWidgetLayout->setSpacing(3);
	m_startTimeHourButton = new QPushButton(m_startTimeHHMMWidget);
	m_startTimeHourButton->setFixedSize(32, 20);
	m_startTimeHourButton->setFont(timeFont);
	m_startTimeHourButton->setText("Hour");
	QLabel* startHourMinuteSeparator = new QLabel(":", m_startTimeHHMMWidget);
	startHourMinuteSeparator->setFixedSize(4, 20);
	startHourMinuteSeparator->setFont(timeFont);
	m_startTimeMinuteButton = new QPushButton(m_startTimeHHMMWidget);
	m_startTimeMinuteButton->setFixedSize(48, 20);
	m_startTimeMinuteButton->setFont(timeFont);
	m_startTimeMinuteButton->setText("Minute");
	m_startTimeHHMMWidgetLayout->addStretch();
	m_startTimeHHMMWidgetLayout->addWidget(m_startTimeHourButton);
	m_startTimeHHMMWidgetLayout->addWidget(startHourMinuteSeparator);
	m_startTimeHHMMWidgetLayout->addWidget(m_startTimeMinuteButton);
	m_startTimeHHMMWidgetLayout->addStretch();
	
	m_startTimeWidgetLayout->addWidget(m_startTimeYYYYMMDDWidget);
	m_startTimeWidgetLayout->addWidget(m_startTimeHHMMWidget);

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
	m_endTimeYYYYMMDDWidget->setFixedSize(124, 20);
	m_endTimeYYYYMMDDWidget->setStyleSheet("border-bottom: 1px solid #377FED");
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
	m_endTimeHHMMWidget->setFixedSize(124, 20);
	m_endTimeHHMMWidget->setStyleSheet("border-bottom: 1px solid #377FED");
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

	m_startTimeYearButton->setStyleSheet("color: #ACB1C6");
	m_startTimeMonthButton->setStyleSheet("color: #ACB1C6");
	m_startTimeDayButton->setStyleSheet("color: #ACB1C6");
	m_startTimeHourButton->setStyleSheet("color: #ACB1C6");
	m_startTimeMinuteButton->setStyleSheet("color: #ACB1C6");
	m_endTimeYearButton->setStyleSheet("color: #ACB1C6");
	m_endTimeMonthButton->setStyleSheet("color: #ACB1C6");
	m_endTimeDayButton->setStyleSheet("color: #ACB1C6");
	m_endTimeHourButton->setStyleSheet("color: #ACB1C6");
	m_endTimeMinuteButton->setStyleSheet("color: #ACB1C6");

	m_timeWidgetLayout->addWidget(m_startTimeWidget);
	m_timeWidgetLayout->addWidget(m_toLabel);
	m_timeWidgetLayout->addWidget(m_endTimeWidget);

	m_contentLayout->addWidget(m_dateWidget);
	m_contentLayout->addWidget(m_timeWidget);
}

void MemoTimeItem::loadMonthView(QDate date)
{
	// 日期
	int year = date.year();
	int month = date.month();
	int firstDayOfWeek = QDate(year, month, 1).dayOfWeek();
	int daysNum = date.daysInMonth();

	// 在网格中填充日期
	// 本月
	for (int dayIndex = 1; dayIndex <= daysNum; dayIndex++)
		m_dayListForAMonth[firstDayOfWeek + dayIndex - 2]->setText(QString::number(dayIndex));
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
		m_dayListForAMonth[firstDayOfWeek + date.day() - 2]->setObjectName("today");
		m_dayListForAMonth[firstDayOfWeek + date.day() - 2]->setStyleSheet("QWidget #today {background-color: #AEE4FD}");
	}
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
		moveAnimation->setDuration(200);
		QPropertyAnimation* fadeOutAnimation = new QPropertyAnimation(m_moreButtonEffect, "opacity", this);
		fadeOutAnimation->setStartValue(1);
		fadeOutAnimation->setEndValue(0);
		fadeOutAnimation->setDuration(200);
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
		moveAnimation->setDuration(200);
		QPropertyAnimation* fadeInAnimation = new QPropertyAnimation(m_moreButtonEffect, "opacity", this);
		fadeInAnimation->setStartValue(0);
		fadeInAnimation->setEndValue(1);
		fadeInAnimation->setDuration(200);
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

MemoImportanceAndUrgencyItem::MemoImportanceAndUrgencyItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
	connect(m_topLeftButton, &QPushButton::clicked, this, &MemoImportanceAndUrgencyItem::select);
	connect(m_topRightButton, &QPushButton::clicked, this, &MemoImportanceAndUrgencyItem::select);
	connect(m_bottomLeftButton, &QPushButton::clicked, this, &MemoImportanceAndUrgencyItem::select);
	connect(m_bottomRightButton, &QPushButton::clicked, this, &MemoImportanceAndUrgencyItem::select);
}

void MemoImportanceAndUrgencyItem::setupUi()
{
	// 字体清单
	QFont labelFont = QFont("NeverMind", 10, QFont::Medium);

	setFixedHeight(160);
	m_title->setText("Importance & Urgency");

	m_content->setFixedHeight(130);
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(2, 0, 2, 0);
	m_contentLayout->setSpacing(0);

	m_topWidget = new QWidget(m_content);
	m_topWidget->setFixedSize(300, 20);
	m_importantLabel = new QLabel("Important", m_topWidget);
	m_importantLabel->setFixedSize(76, 20);
	m_importantLabel->move(112, 0);
	m_importantLabel->setFont(labelFont);

	m_middleWidget = new QWidget(m_content);
	m_middleWidget->setFixedSize(300, 90);

	m_leftWidget = new QWidget(m_middleWidget);
	m_leftWidget->setFixedSize(55, 90);
	m_leftWidget->move(0, 0);
	m_notUrgentLabel = new QLabel("Not\nUrgent", m_leftWidget);
	m_notUrgentLabel->setFixedSize(55, 40);
	m_notUrgentLabel->move(0, 25);
	m_notUrgentLabel->setFont(labelFont);
	m_notUrgentLabel->setAlignment(Qt::AlignHCenter);
	
	m_matrixWidget = new QWidget(m_middleWidget);
	m_matrixWidget->setFixedSize(190, 90);
	m_matrixWidget->move(55, 0);

	m_topLeftButton = new QPushButton(m_matrixWidget);
	m_topLeftButton->resize(90, 40);
	m_topLeftButton->setStyleSheet("background-color: rgba(168, 229, 159, 0.5); border: none");
	m_topLeftButton->move(0, 0);
	m_topLine = new QWidget(m_matrixWidget);
	m_topLine->resize(10, 40);
	m_topLine->move(90, 0);
	m_topRightButton = new QPushButton(m_matrixWidget);
	m_topRightButton->resize(90, 40);
	m_topRightButton->setStyleSheet("background-color: rgba(236, 164, 164, 0.5); border: none");
	m_topRightButton->move(100, 0);

	m_leftLine = new QWidget(m_matrixWidget);
	m_leftLine->resize(90, 10);
	m_leftLine->move(0, 40);
	m_centralLine = new QWidget(m_matrixWidget);
	m_centralLine->resize(10, 10);
	m_centralLine->move(90, 40);
	m_rightLine = new QWidget(m_matrixWidget);
	m_rightLine->resize(90, 10);
	m_rightLine->move(100, 40);

	m_bottomLeftButton = new QPushButton(m_matrixWidget);
	m_bottomLeftButton->resize(90, 40);
	m_bottomLeftButton->setStyleSheet("background-color: rgba(139, 205, 246, 0.5); border: none");
	m_bottomLeftButton->move(0, 50);
	m_bottomLine = new QWidget(m_matrixWidget);
	m_bottomLine->resize(10, 40);
	m_bottomLine->move(90, 50);
	m_bottomRightButton = new QPushButton(m_matrixWidget);
	m_bottomRightButton->resize(90, 40);
	m_bottomRightButton->setStyleSheet("background-color: rgba(231, 240, 149, 0.5); border: none");
	m_bottomRightButton->move(100, 50);

	m_rightWidget = new QWidget(m_middleWidget);
	m_rightWidget->setFixedSize(55, 90);
	m_rightWidget->move(245, 0);
	m_urgentLabel = new QLabel("Urgent", m_rightWidget);
	m_urgentLabel->setFixedSize(55, 20);
	m_urgentLabel->move(0, 35);
	m_urgentLabel->setFont(labelFont);

	m_bottomWidget = new QWidget(m_content);
	m_bottomWidget->setFixedSize(300, 20);
	m_notImportantLabel = new QLabel("Not Important", m_bottomWidget);
	m_notImportantLabel->setFixedSize(120, 20);
	m_notImportantLabel->move(90, 0);
	m_notImportantLabel->setFont(labelFont);

	QString labelStyleSheet = "color: #ACB1C6";
	m_importantLabel->setAlignment(Qt::AlignCenter);
	m_notImportantLabel->setAlignment(Qt::AlignCenter);
	m_urgentLabel->setAlignment(Qt::AlignCenter);
	m_notUrgentLabel->setAlignment(Qt::AlignCenter);
	m_importantLabel->setStyleSheet(labelStyleSheet);
	m_notImportantLabel->setStyleSheet(labelStyleSheet);
	m_urgentLabel->setStyleSheet(labelStyleSheet);
	m_notUrgentLabel->setStyleSheet(labelStyleSheet);

	m_contentLayout->addWidget(m_topWidget);
	m_contentLayout->addWidget(m_middleWidget);
	m_contentLayout->addWidget(m_bottomWidget);
}

void MemoImportanceAndUrgencyItem::select()
{
	QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
	bool isTop = false;
	bool isLeft = false;
	if (senderButton == m_topLeftButton) { isTop = true; isLeft = true; }
	if (senderButton == m_topRightButton) isTop = true;
	if (senderButton == m_bottomLeftButton) isLeft = true;
	QParallelAnimationGroup* group = new QParallelAnimationGroup;
	QPropertyAnimation* topLeftAnimation = new QPropertyAnimation(m_topLeftButton, "geometry");
	QPropertyAnimation* topAnimation = new QPropertyAnimation(m_topLine, "geometry");
	QPropertyAnimation* topRightAnimation = new QPropertyAnimation(m_topRightButton, "geometry");
	QPropertyAnimation* leftAnimation = new QPropertyAnimation(m_leftLine, "geometry");
	QPropertyAnimation* centralAnimation = new QPropertyAnimation(m_centralLine, "geometry");
	QPropertyAnimation* rightAnimation = new QPropertyAnimation(m_rightLine, "geometry");
	QPropertyAnimation* bottomLeftAnimation = new QPropertyAnimation(m_bottomLeftButton, "geometry");
	QPropertyAnimation* bottomAnimation = new QPropertyAnimation(m_bottomLine, "geometry");
	QPropertyAnimation* bottomRightAnimation = new QPropertyAnimation(m_bottomRightButton, "geometry");
	
	QString labelDefaultStyleSheet = "color: #ACB1C6";
	QString labelCurrentStyleSheet = "color: #468DFA";
	QString topLeftDefaultStyleSheet = "background-color: rgba(168, 229, 159, 0.5); border: none";
	QString topLeftCurrentStyleSheet = "background-color: rgb(168, 229, 159); border: none";
	QString topRightDefaultStyleSheet = "background-color: rgba(236, 164, 164, 0.5); border: none";
	QString topRightCurrentStyleSheet = "background-color: rgb(236, 164, 164); border: none";
	QString bottomLeftDefaultStyleSheet = "background-color: rgba(139, 205, 246, 0.5); border: none";
	QString bottomLeftCurrentStyleSheet = "background-color: rgb(139, 205, 246); border: none";
	QString bottomRightDefaultStyleSheet = "background-color: rgba(231, 240, 149, 0.5); border: none";
	QString bottomRightCurrentStyleSheet = "background-color: rgb(231, 240, 149); border: none";
	m_importantLabel->setStyleSheet(isTop ? labelCurrentStyleSheet : labelDefaultStyleSheet);
	m_notImportantLabel->setStyleSheet(isTop ? labelDefaultStyleSheet : labelCurrentStyleSheet);
	m_urgentLabel->setStyleSheet(isLeft ? labelDefaultStyleSheet : labelCurrentStyleSheet);
	m_notUrgentLabel->setStyleSheet(isLeft ? labelCurrentStyleSheet : labelDefaultStyleSheet);
	m_topLeftButton->setStyleSheet((isLeft && isTop) ? topLeftCurrentStyleSheet : topLeftDefaultStyleSheet);
	m_topRightButton->setStyleSheet((!isLeft && isTop) ? topRightCurrentStyleSheet : topRightDefaultStyleSheet);
	m_bottomLeftButton->setStyleSheet((isLeft && !isTop) ? bottomLeftCurrentStyleSheet : bottomLeftDefaultStyleSheet);
	m_bottomRightButton->setStyleSheet((!isLeft && !isTop) ? bottomRightCurrentStyleSheet : bottomRightDefaultStyleSheet);
	
	topLeftAnimation->setEndValue(QRect(0, 0, isLeft ? 147 : 33, isTop ? 60 : 20));
	topLeftAnimation->setDuration(300);
	topLeftAnimation->setEasingCurve(QEasingCurve::OutQuad);
	topAnimation->setEndValue(QRect(isLeft ? 147 : 33, 0, 10, isTop ? 60 : 20));
	topAnimation->setDuration(300);
	topAnimation->setEasingCurve(QEasingCurve::OutQuad);
	topRightAnimation->setEndValue(QRect(isLeft ? 157 : 43, 0, isLeft ? 33 : 147, isTop ? 60 : 20));
	topRightAnimation->setDuration(300);
	topRightAnimation->setEasingCurve(QEasingCurve::OutQuad);
	leftAnimation->setEndValue(QRect(0, isTop? 60 : 20, isLeft ? 147 : 33, 10));
	leftAnimation->setDuration(300);
	leftAnimation->setEasingCurve(QEasingCurve::OutQuad);
	centralAnimation->setEndValue(QRect(isLeft ? 20 : 180, isTop ? 60 : 20, 10, 10));
	centralAnimation->setDuration(300);
	centralAnimation->setEasingCurve(QEasingCurve::OutQuad);
	rightAnimation->setEndValue(QRect(isLeft ? 157 : 43, isTop ? 60 : 20, isLeft ? 33 : 147, 10));
	rightAnimation->setDuration(300);
	rightAnimation->setEasingCurve(QEasingCurve::OutQuad);
	bottomLeftAnimation->setEndValue(QRect(0, isTop ? 70 : 30, isLeft ? 147 : 33, isTop ? 20 : 60));
	bottomLeftAnimation->setDuration(300);
	bottomLeftAnimation->setEasingCurve(QEasingCurve::OutQuad);
	bottomAnimation->setEndValue(QRect(isLeft ? 147 : 33, 0, 10, isTop ? 20 : 60));
	bottomAnimation->setDuration(300);
	bottomAnimation->setEasingCurve(QEasingCurve::OutQuad);
	bottomRightAnimation->setEndValue(QRect(isLeft ? 157 : 43, isTop ? 70 : 30, isLeft ? 33 : 147, isTop ? 20 : 60));
	bottomRightAnimation->setDuration(300);
	bottomRightAnimation->setEasingCurve(QEasingCurve::OutQuad);
	group->addAnimation(topLeftAnimation);
	group->addAnimation(topAnimation);
	group->addAnimation(topRightAnimation);
	group->addAnimation(leftAnimation);
	group->addAnimation(centralAnimation);
	group->addAnimation(rightAnimation);
	group->addAnimation(bottomLeftAnimation);
	group->addAnimation(bottomAnimation);
	group->addAnimation(bottomRightAnimation);
	connect(group, &QParallelAnimationGroup::finished, group, &QParallelAnimationGroup::clear);
	group->start(QParallelAnimationGroup::DeleteWhenStopped);
}

MemoDetailItem::MemoDetailItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
}

void MemoDetailItem::setupUi()
{
	// 字体清单
	QFont detailFont = QFont("NeverMind", 12, QFont::Normal);

	resize(304, 80);
	setMinimumHeight(80);

	m_title->setText("Detail");
	m_content->setStyleSheet("border-radius: 10px; background-color: rgba(255, 255, 255, 0.5)");
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(12, 5, 12, 5);
	m_contentLayout->setSpacing(0);

	m_detail = new QTextEdit(m_content);
	m_detail->setAcceptRichText(false);
	m_detail->setUndoRedoEnabled(true);
	m_detail->setFont(detailFont);
	m_detail->setStyleSheet("background-color: transparent");

	m_contentLayout->addWidget(m_detail);
}

MemoSubMemoItem::MemoSubMemoItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
}

void MemoSubMemoItem::setupUi()
{
	// 字体清单
	QFont numberFont = QFont("NeverMind", 10, QFont::Medium);
	QFont contentFont = QFont("NeverMind", 12, QFont::Normal);

	resize(304, 60);
	setMinimumHeight(60);

	m_title->setText("SubMemo");
	m_content->setObjectName("subMemoContent");
	m_content->setStyleSheet("QWidget #subMemoContent {border-radius: 10px; background-color: rgba(255, 255, 255, 0.5)}");
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(12, 5, 12, 5);
	m_contentLayout->setSpacing(10);

	m_addSubMemoWidget = new QWidget(m_content);
	m_addSubMemoWidget->setFixedHeight(20);
	m_addSubMemoWidgetLayout = new QHBoxLayout(m_addSubMemoWidget);
	m_addSubMemoWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_addSubMemoWidgetLayout->setSpacing(8);

	m_subMemoNumber = new QLabel(QString::number(m_count + 1), m_addSubMemoWidget);
	m_subMemoNumber->setFixedSize(18, 18);
	m_subMemoNumber->setFont(numberFont);
	m_subMemoNumber->setAlignment(Qt::AlignCenter);
	m_subMemoNumber->setStyleSheet("background-color: #AEE4FD; border-radius: 9px");
	m_subMemoContent = new QLineEdit(m_addSubMemoWidget);
	m_subMemoContent->setFixedHeight(20);
	m_subMemoContent->setPlaceholderText("Click to add subMemo.");
	m_subMemoContent->setFont(numberFont);
	m_subMemoContent->setStyleSheet("border: none; background-color: transparent");
	m_addSubMemoWidgetLayout->addWidget(m_subMemoNumber);
	m_addSubMemoWidgetLayout->addWidget(m_subMemoContent);
	m_contentLayout->addWidget(m_addSubMemoWidget);
}


MemoAwardItem::MemoAwardItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
}

void MemoAwardItem::setupUi()
{
	// 字体清单
	QFont addAwardContentFont = QFont("NeverMind", 10, QFont::Medium);
	QFont addAwardSubContentFont = QFont("NeverMind", 8, QFont::Normal);

	resize(304, 80);

	m_title->setText("Award");
	m_content->setObjectName("awardContent");
	m_content->setStyleSheet("QWidget #awardContent {border-radius: 10px; background-color: rgba(255, 255, 255, 0.5)}");
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(12, 5, 12, 5);
	m_contentLayout->setSpacing(0);

	m_addAwardContent = new QLabel(tr("How to motivate yourself?"), m_content);
	m_addAwardContent->setFixedHeight(20);
	m_addAwardContent->setFont(addAwardContentFont);
	m_addAwardContent->setStyleSheet("color: #4F5E71");

	m_addAwardSubContent = new QLabel(tr("Click to add awards from the award repo."), m_content);
	m_addAwardSubContent->setFixedHeight(20);
	m_addAwardSubContent->setFont(addAwardSubContentFont);
	m_addAwardSubContent->setStyleSheet("color: #ACB1C6");

	m_contentLayout->addWidget(m_addAwardContent);
	m_contentLayout->addWidget(m_addAwardSubContent);
}

MemoReferenceItem::MemoReferenceItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
}

void MemoReferenceItem::setupUi()
{
	// 字体清单
	QFont addReferenceContentFont = QFont("NeverMind", 10, QFont::Medium);
	QFont addReferenceSubContentFont = QFont("NeverMind", 8, QFont::Normal);

	resize(304, 80);

	m_title->setText("Reference");
	m_content->setObjectName("referenceContent");
	m_content->setStyleSheet("QWidget #referenceContent {border-radius: 10px; background-color: rgba(255, 255, 255, 0.5)}");
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(12, 5, 12, 5);
	m_contentLayout->setSpacing(0);

	m_addReferenceContent = new QLabel(tr("What references are needed?"), m_content);
	m_addReferenceContent->setFixedHeight(20);
	m_addReferenceContent->setFont(addReferenceContentFont);
	m_addReferenceContent->setStyleSheet("color: #4F5E71");

	m_addReferenceSubContent = new QLabel(tr("Click to add References from the Reference repo."), m_content);
	m_addReferenceSubContent->setFixedHeight(20);
	m_addReferenceSubContent->setFont(addReferenceSubContentFont);
	m_addReferenceSubContent->setStyleSheet("color: #ACB1C6");

	m_contentLayout->addWidget(m_addReferenceContent);
	m_contentLayout->addWidget(m_addReferenceSubContent);
}


void MemoSettingItem::paintEvent(QPaintEvent* event) {
	QStyleOption opt;
	opt.initFrom(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
