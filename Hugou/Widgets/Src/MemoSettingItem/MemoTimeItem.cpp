#include "Widgets/Include/MemoSettingItem/MemoTimeItem.h"

MemoTimeItem::MemoTimeItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	m_lastMonth = DayAttribution{ false, 0, 0 };
	m_thisMonth = DayAttribution{ true, 0, 0 };
	m_nextMonth = DayAttribution{ false, 0, 41 };
	m_reminder = Reminder{ false, QDateTime() };
	setupUi();
	m_beginDateTime = m_endDateTime = QDateTime::currentDateTime();
	loadMonthView(QDate::currentDate());
	m_animationGroup = new QParallelAnimationGroup(this);
	connect(m_animationGroup, &QParallelAnimationGroup::finished, this, &MemoTimeItem::disableGraphicsEffect);
	connect(m_reminderButton, &QPushButton::clicked, this, &MemoTimeItem::switchReminder);
	connect(m_moreButton, &QPushButton::clicked, this, &MemoTimeItem::setReminder);
	connect(m_dateTitle, &QPushButton::clicked, this, &MemoTimeItem::setYearAndMonth);
	connect(m_backButton, &QPushButton::clicked, this, &MemoTimeItem::goBackAMonth);
	connect(m_forwardButton, &QPushButton::clicked, this, &MemoTimeItem::goForwardAMonth);
	connect(m_backToTodayButton, &QPushButton::clicked, this, &MemoTimeItem::goBackToToday);
	connect(m_reminderModeSelectionMenuItem, &SingleSelectionMenuItem::SignalSelected, this, &MemoTimeItem::switchReminderMode);
	connect(m_reminderMenu, &Menu::SignalSaved, [&](QMap<QString, QString> resultMap)
		{
			m_reminder.mode = static_cast<ReminderMode>(resultMap["Remind Mode"].toInt());
			m_reminder.reminderDateTime = QDateTime::fromString(resultMap["Reminder Time"], "yyyy MM dd hh mm");
			switch (m_reminder.mode)
			{
			case ReminderMode::Once: break;
			case ReminderMode::Repeat:
			{
				m_reminder.repeateMode = static_cast<ReminderRepeatMode>(resultMap["Repeat Mode"].toInt());
				break;
			}
			default: break;
			}
			m_reminderMenu->close();
		});
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
	QFont backToTodayFont = QFont("NeverMind", 10, QFont::Bold);
	QFont toFont = QFont("NeverMind", 10, QFont::Bold);

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
	m_moreButton->setCursor(Qt::PointingHandCursor);
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
	m_dateTitle->setBackgroundWidgetStyleSheet("background-color: rgba(0, 0, 255, 0.1); border-radius: 5px");
	m_dateTitle->setTextAlignment(Qt::AlignLeft);
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
	int buttonID = 0;
	// 绘制网格
	m_dayGroup = new QButtonGroup(this);
	for (int weekIndex = 1; weekIndex <= 6; weekIndex++)
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
			FadeEffectButton* day = new FadeEffectButton("", monthContentFont, week);
			day->setAutoFillBackground(true);
			day->setBackgroundWidgetStyleSheet("background-color: rgba(174, 228, 253, 0.5)");
			day->setFixedSize(36, 20);
			day->setTextAlignment(Qt::AlignCenter);
			day->setCursor(Qt::PointingHandCursor);
			connect(day, &FadeEffectButton::clicked, this, &MemoTimeItem::setBeginOrEnd);
			weekLayout->addWidget(day);
			m_dayListForAMonth.append(day);
			m_dayGroup->addButton(day, buttonID);
			buttonID++;
		}
		m_monthWidgetLayout->addWidget(week);
		m_weekListForAMonth.append(week);
	}

	m_beginAndEndLabel = new QLabel("Begin | End", m_content);
	m_beginAndEndLabel->setContentsMargins(3, 0, 3, 0);
	m_beginAndEndLabel->setFixedHeight(25);
	m_beginAndEndLabel->setFont(QFont("NeverMind", 10, QFont::Bold));
	m_beginAndEndLabel->setAlignment(Qt::AlignCenter);
	m_beginAndEndLabel->setStyleSheet("background-color: rgba(55, 61, 63, 0.7); border-radius: 3px; color: white");
	m_beginAndEndLabel->adjustSize();

	m_beginLabel = new QLabel("Begin", m_content);
	m_beginLabel->setContentsMargins(3, 0, 3, 0);
	m_beginLabel->setFixedHeight(25);
	m_beginLabel->setFont(QFont("NeverMind", 10, QFont::Bold));
	m_beginLabel->setAlignment(Qt::AlignCenter);
	m_beginLabel->setStyleSheet("background-color: rgba(55, 61, 63, 0.7); border-radius: 3px; color: white");
	m_beginLabel->adjustSize();
	m_beginLabel->hide();

	m_endLabel = new QLabel("End", m_content);
	m_endLabel->setContentsMargins(3, 0, 3, 0);
	m_endLabel->setFixedHeight(25);
	m_endLabel->setFont(QFont("NeverMind", 10, QFont::Bold));
	m_endLabel->setAlignment(Qt::AlignCenter);
	m_endLabel->setStyleSheet("background-color: rgba(55, 61, 63, 0.7); border-radius: 3px; color: white");
	m_endLabel->adjustSize();
	m_endLabel->hide();

	m_dateWidgetLayout->addWidget(m_dateTitleWidget);
	m_dateWidgetLayout->addWidget(m_monthWidget);

	m_timeWidget = new QWidget(m_content);
	m_timeWidget->setFixedHeight(55);
	m_timeWidgetLayout = new QHBoxLayout(m_timeWidget);
	m_timeWidgetLayout->setContentsMargins(3, 0, 3, 0);
	m_timeWidgetLayout->setSpacing(3);

	m_beginDateTimeSelector = new DateTimeSelector(m_timeWidget);
	m_beginDateTimeSelector->setDateTime(QDateTime::currentDateTime());
	m_toLabel = new QLabel("To", m_timeWidget);
	m_toLabel->setFixedSize(20, 20);
	m_toLabel->setStyleSheet("color: white; background-color: #468DFA; border-radius: 3px");
	m_toLabel->setAlignment(Qt::AlignCenter);
	m_toLabel->setFont(toFont);
	m_endDateTimeSelector = new DateTimeSelector(m_timeWidget);
	m_endDateTimeSelector->setDateTime(QDateTime::currentDateTime().addMSecs(3600000));

	m_timeWidgetLayout->addWidget(m_beginDateTimeSelector);
	m_timeWidgetLayout->addWidget(m_toLabel);
	m_timeWidgetLayout->addWidget(m_endDateTimeSelector);

	m_contentLayout->addWidget(m_dateWidget);
	m_contentLayout->addWidget(m_timeWidget);

	m_reminderMenu = new Menu(this);
	m_reminderModeSelectionMenuItem = new SingleSelectionMenuItem("Remind Mode", { tr("Once"), tr("Repeat") }, m_reminderMenu);
	m_reminderDateTimeMenuItem = new DateTimeMenuItem("Reminder Time", m_reminderMenu);
	m_repeatModeSelectionMenuItem = new SingleSelectionMenuItem("Repeat Mode", { tr("Every day"), tr("Every week"), tr("Every month"), tr("Every year"), tr("Custom")}, m_reminderMenu);
	m_reminderMenu->addMenuItem(m_reminderModeSelectionMenuItem);
	m_reminderMenu->addMenuItem(m_reminderDateTimeMenuItem);
	m_reminderMenu->addMenuItem(m_repeatModeSelectionMenuItem);
	m_reminderMenu->hide();
}

void MemoTimeItem::setBeginOrEnd()
{
	FadeEffectButton* button = qobject_cast<FadeEffectButton*>(sender());
	int day = button->text().toInt();
	QDate selectedDate = QDate(m_selectedDate.year(), m_selectedDate.month(), day);
	if (m_lastMonth.isExisted && m_dayGroup->id(button) <= m_lastMonth.upperBound)
	{
		goBackAMonth();
		selectedDate = QDate(m_selectedDate.year(), m_selectedDate.month(), day);
		button = m_dayListForAMonth[m_startDate.daysTo(selectedDate)];
	}
	else if (m_nextMonth.isExisted && m_dayGroup->id(button) >= m_nextMonth.lowerBound)
	{
		goForwardAMonth();
		selectedDate = QDate(m_selectedDate.year(), m_selectedDate.month(), day);
		button = m_dayListForAMonth[m_startDate.daysTo(selectedDate)];
	}

	setUpdatesEnabled(false);

	m_todayButton->setBaseColor(Qt::transparent);
	if (m_timeSelectMode == TimeSelectMode::EndMode && m_beginDateTime.date() > selectedDate)
		m_timeSelectMode = TimeSelectMode::BeginMode;

	switch (m_timeSelectMode)
	{
	case TimeSelectMode::DefaultMode:
	case TimeSelectMode::BeginMode:
	{
		for (int index = 0; index <= 41; index++)
			m_dayListForAMonth[index]->setBaseColor(Qt::transparent);
		m_beginButton = button;
		m_endDateTime = QDateTime();
		m_endLabel->hide();
		m_beginAndEndLabel->hide();
		m_beginLabel->show();
		m_beginLabel->move(getLabelPos(m_beginLabel, button));
		m_beginButton->setBaseColor(QColor("#AEE4FD"));
		m_beginDateTime.setDate(selectedDate);
		m_beginDateTimeSelector->setDate(m_beginDateTime.date());
		m_timeSelectMode = TimeSelectMode::EndMode;
		break;
	}
	case TimeSelectMode::EndMode:
	{
		m_endButton = button;
		m_endDateTime.setDate(selectedDate);
		if (m_beginDateTime.date() == m_endDateTime.date())
		{
			m_endLabel->hide();
			m_beginLabel->hide();
			m_beginAndEndLabel->show();
			m_beginAndEndLabel->move(getLabelPos(m_beginAndEndLabel, button));
		}
		else
		{
			m_endLabel->show();
			m_endLabel->move(getLabelPos(m_endLabel, m_endButton));
			m_endDateTime.setDate(selectedDate);
			int index = m_dayGroup->id(m_beginButton);
			if (m_endDateTime.date().month() != m_beginDateTime.date().month())
			{
				if (m_beginDateTime.date() < m_startDate)
				{
					index = 0;
					m_beginLabel->hide();
				}
				else
				{
					m_beginButton = m_dayListForAMonth[m_startDate.daysTo(m_beginDateTime.date())];
					m_beginLabel->show();
					m_beginLabel->move(getLabelPos(m_beginLabel, m_beginButton));
				}
			}
			for (; index <= m_dayGroup->id(m_endButton); index++)
			{
				m_dayListForAMonth[index]->setBaseColor(QColor("#AEE4FD"));
			}
		}
		m_endDateTimeSelector->setDate(m_endDateTime.date());
		m_timeSelectMode = TimeSelectMode::BeginMode;
		break;
	}
	default: break;
	}
	setUpdatesEnabled(true);
}

void MemoTimeItem::loadMonthView(const QDate& date)
{
	int year = date.year();
	int month = date.month();
	if (year == m_selectedDate.year() && month == m_selectedDate.month()) return;

	int firstDayOfWeek = QDate(year, month, 1).dayOfWeek();
	int day = date.day();
	int daysNum = date.daysInMonth();
	setUpdatesEnabled(false);
	// 月份标题
	m_dateTitle->setText(m_monthNameList[month - 1] + " " + QString::number(year));

	// 月份日期范围
	m_startDate = QDate(year, month, 1);
	// 在网格中填充日期
	// 本月（下标从 firstDayOfWeek - 1 到 firstDayOfWeek + daysNum - 2）
	m_thisMonth.lowerBound = firstDayOfWeek - 1;
	m_thisMonth.upperBound = firstDayOfWeek + daysNum - 2;
	for (int dayIndex = 1; dayIndex <= daysNum; dayIndex++)
	{
		FadeEffectButton* button = m_dayListForAMonth[firstDayOfWeek + dayIndex - 2];
		button->setText(QString::number(dayIndex));
		button->setBaseColor(Qt::transparent);
		button->setTextColor(Qt::black);
	}
	// 上月（下标从 0 到 firstDayOfWeek - 2）
	if (m_thisMonth.lowerBound > 0)
	{
		m_lastMonth.isExisted = true;
		m_lastMonth.upperBound = firstDayOfWeek - 2;
		int lastMonthDays = date.addMonths(-1).daysInMonth();
		for (int dayIndex = firstDayOfWeek - 2; dayIndex >= 0; dayIndex--)
		{
			FadeEffectButton* button = m_dayListForAMonth[dayIndex];
			button->setText(QString::number(lastMonthDays));
			button->setBaseColor(Qt::transparent);
			button->setTextColor(QColor("#ACB1C6"));
			lastMonthDays--;
		}
		m_startDate = QDate(date.addMonths(-1).year(), date.addMonths(-1).month(), lastMonthDays + 1);
	}
	else
	{
		m_lastMonth.isExisted = false;
	}
	m_finishDate = m_startDate.addDays(41);
	// 下月（下标从 firstDayOfWeek + daysNum - 1 到 41）
	if (m_thisMonth.upperBound < 41)
	{
		m_nextMonth.isExisted = true;
		m_nextMonth.lowerBound = firstDayOfWeek + daysNum - 1;
		int nextMonthDay = 1;
		for (int dayIndex = m_thisMonth.upperBound + 1; dayIndex <= 41; dayIndex++, nextMonthDay++)
		{
			FadeEffectButton* button = m_dayListForAMonth[dayIndex];
			button->setText(QString::number(nextMonthDay));
			button->setTextColor(QColor("#ACB1C6"));
			button->setBaseColor(Qt::transparent);
		}
	}
	else
	{
		m_nextMonth.isExisted = false;
	}
	// 今日和跳转至今日（当且仅当默认模式下显示今日）
	QDate currentDate = QDate::currentDate();
	if (year == currentDate.year() && month == currentDate.month())
	{
		if (m_timeSelectMode == TimeSelectMode::DefaultMode)
		{
			m_todayButton = m_dayListForAMonth[firstDayOfWeek + day - 2];
			m_todayButton->setTextColor(Qt::black);
			m_todayButton->setBaseColor(QColor("#AEE4FD"));
			m_beginButton = m_endButton = m_todayButton;
		}
		m_backToTodayButton->hide();
	}
	else
	{
		m_backToTodayButton->show();
	}

	// 检测当前月历是否包含了起始/结束日期及其之间的日期。
	// 确认起始点
	int startPoint = -1, finishPoint = -1; 
	m_beginAndEndLabel->hide();
	if (m_beginDateTime.isNull()) m_beginLabel->hide();
	else
	{
		// 起始日期在当前月历
		if (m_beginDateTime.date() >= m_startDate && m_beginDateTime.date() <= m_finishDate)
		{
			m_beginButton = m_dayListForAMonth[m_startDate.daysTo(m_beginDateTime.date())];
			m_beginButton->setBaseColor(QColor("#AEE4FD"));
			startPoint = finishPoint = m_startDate.daysTo(m_beginDateTime.date());
			m_beginLabel->show();
			m_beginLabel->move(getLabelPos(m_beginLabel, m_beginButton));
		}
		// 起始日期早于当前月历
		else if (m_beginDateTime.date() < m_startDate)
		{
			startPoint = 0;
			m_beginLabel->hide();
		}
		// 起始日期晚于当前月历
		else
		{
			m_beginLabel->hide();
		}

		// 确认结束点
		if (m_endDateTime.isNull()) m_endLabel->hide();
		else
		{
			// 结束日期在当前月历
			if (m_endDateTime.date() >= m_startDate && m_endDateTime.date() <= m_finishDate)
			{
				m_endButton = m_dayListForAMonth[m_startDate.daysTo(m_endDateTime.date())];
				finishPoint = m_startDate.daysTo(m_endDateTime.date());
				m_endLabel->show();
				m_endLabel->move(getLabelPos(m_endLabel, m_endButton));
				if (startPoint == finishPoint)
				{
					m_beginLabel->hide();
					m_endLabel->hide();
					m_beginAndEndLabel->show();
					m_beginAndEndLabel->move(getLabelPos(m_beginAndEndLabel, m_beginButton));
				}
			}
			// 结束日期晚于当前月历
			else if(m_endDateTime.date() > m_finishDate)
			{
				finishPoint = 41;
				m_endLabel->hide();
			}
			// 结束日期早于当前月历
			else
			{
				m_endLabel->hide();
			}

			if(startPoint != -1 && finishPoint != -1)
				for (int index = startPoint; index <= finishPoint; index++)
					m_dayListForAMonth[index]->setBaseColor(QColor("#AEE4FD"));
		}
	}
	setUpdatesEnabled(true);
	m_selectedDate.setDate(year, month, day);
}

void MemoTimeItem::goBackAMonth()
{
	loadMonthView(m_selectedDate.addMonths(-1));
}

void MemoTimeItem::goForwardAMonth()
{
	loadMonthView(m_selectedDate.addMonths(1));
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
	YearAndMonthSelector* selector = new YearAndMonthSelector(m_selectedDate.year(), m_selectedDate.month(), m_content);
	selector->move(21, 36);
	selector->show();
	connect(m_dateTitle, &QPushButton::clicked, selector, &YearAndMonthSelector::close);
	connect(selector, &YearAndMonthSelector::SignalSelected, [this](int year, int month)
		{
			loadMonthView(QDate(year, month, m_selectedDate.day()));
			m_dateTitle->disconnect();
			connect(m_dateTitle, &FadeEffectButton::clicked, this, &MemoTimeItem::setYearAndMonth);
		}
	);
}

void MemoTimeItem::switchReminder()
{
	if (m_animationGroup->state() == QAbstractAnimation::Running)
		m_animationGroup->stop();
	m_animationGroup->clear();
	enableGraphicsEffect();
	if (m_reminder.hasReminder)
	{
		m_reminder.hasReminder = false;
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
		m_reminder.hasReminder = true;
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

void MemoTimeItem::setReminder()
{
	if (m_reminder.reminderDateTime.isNull())
	{
		m_reminderDateTimeMenuItem->setDateTime(m_beginDateTime);
		m_reminder.reminderDateTime = m_beginDateTime;
	}
	m_reminderMenu->move(m_reminderWidget->mapToGlobal(QPoint(0, 0) + QPoint(m_reminderWidget->width(), 0)));
	m_reminderMenu->show();
}

void MemoTimeItem::switchReminderMode(const QString& mode)
{
	if (mode == "Once")
	{
		m_repeatModeSelectionMenuItem->setEnabled(false);
	}
	else if (mode == "Repeat")
	{
		m_repeatModeSelectionMenuItem->setEnabled(true);
	}
}

void MemoTimeItem::enableGraphicsEffect()
{
	m_moreButtonEffect->setEnabled(true);
	m_moreButton->show();
}

void MemoTimeItem::disableGraphicsEffect()
{
	m_moreButtonEffect->setEnabled(false);
	if (!m_reminder.hasReminder)
		m_moreButton->hide();
}

QPoint MemoTimeItem::getLabelPos(QLabel* label, QPushButton* dayButton)
{
	QPoint buttonTopLeft = dayButton->mapTo(m_content, QPoint(0, 0));
	int x = buttonTopLeft.x() + (dayButton->width() - label->width()) / 2;
	int y = buttonTopLeft.y() - 30;
	return QPoint(x, y);
}

void MemoTimeItem::showEvent(QShowEvent* event)
{
	MemoSettingItem::show();
	m_beginAndEndLabel->move(getLabelPos(m_beginAndEndLabel, m_todayButton));
}