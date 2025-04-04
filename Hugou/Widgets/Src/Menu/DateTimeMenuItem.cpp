#include "Widgets/Include/Menu/DateTimeMenuItem.h"

DateTimeMenuItem::DateTimeMenuItem(const QString& title, QWidget* menu)
	:MenuItem(title, menu)
{
	setupUi();
	setCentralWidget(m_centralWidget);
	m_yearValidator = new QIntValidator(0, 9999, this);
	m_monthValidator = new QIntValidator(1, 12, this);
	m_dayValidator = new QIntValidator(1, 31, this);
	m_hourValidator = new QIntValidator(0, 23, this);
	m_minuteValidator = new QIntValidator(0, 59, this);
	connect(m_yearButton, &FadeEffectButton::clicked, [this]() { edit(m_yearButton, m_yearValidator); });
	connect(m_monthButton, &FadeEffectButton::clicked, [this]() { edit(m_monthButton, m_monthValidator); });
	connect(m_dayButton, &FadeEffectButton::clicked, [this]() { edit(m_dayButton, m_dayValidator); });
	connect(m_hourButton, &FadeEffectButton::clicked, [this]() { edit(m_hourButton, m_hourValidator); });
	connect(m_minuteButton, &FadeEffectButton::clicked, [this]() { edit(m_minuteButton, m_minuteValidator); });
}

void DateTimeMenuItem::setupUi()
{
	// 字体清单
	QFont timeFont = QFont("NeverMind", 10, QFont::Normal);

	QSizePolicy policy = QSizePolicy();
	policy.setRetainSizeWhenHidden(true);

	m_centralWidget = new QWidget(this);
	m_layout = new QHBoxLayout(m_centralWidget);
	m_layout->setContentsMargins(5, 5, 5, 5); 
	m_lineEdit = new QLineEdit(m_centralWidget);
	m_lineEdit->setFont(timeFont);
	m_lineEdit->setContentsMargins(0, 0, 0, 0);
	m_lineEdit->setAlignment(Qt::AlignCenter);
	m_lineEdit->hide();

	m_YYYYMMDDWidget = new QWidget(m_centralWidget);
	m_YYYYMMDDWidget->setObjectName("YYYYMMDDWidget");
	//m_YYYYMMDDWidget->setFixedSize(124, 20);
	m_YYYYMMDDWidget->setStyleSheet("QWidget #YYYYMMDDWidget { border-bottom: 1px solid #377FED }");
	m_YYYYMMDDWidgetLayout = new QHBoxLayout(m_YYYYMMDDWidget);
	m_YYYYMMDDWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_YYYYMMDDWidgetLayout->setSpacing(0);
	m_yearButton = new FadeEffectButton(m_YYYYMMDDWidget);
	m_yearButton->setBackgroundWidgetStyleSheet("background-color: rgba(0, 0, 255, 0.1); border-radius: 5px");
	m_yearButton->setFixedSize(52, 20);
	m_yearButton->setFont(timeFont);
	m_yearButton->setCursor(Qt::PointingHandCursor);
	m_yearButton->setSizePolicy(policy);
	QLabel* yearMonthSeparator = new QLabel("-", m_YYYYMMDDWidget);
	yearMonthSeparator->setFixedSize(4, 20);
	yearMonthSeparator->setFont(timeFont);
	m_monthButton = new FadeEffectButton(m_YYYYMMDDWidget);
	m_monthButton->setBackgroundWidgetStyleSheet("background-color: rgba(0, 0, 255, 0.1); border-radius: 5px");
	m_monthButton->setFixedSize(30, 20);
	m_monthButton->setFont(timeFont);
	m_monthButton->setCursor(Qt::PointingHandCursor);
	m_monthButton->setSizePolicy(policy);
	QLabel* monthDaySeparator = new QLabel("-", m_YYYYMMDDWidget);
	monthDaySeparator->setFixedSize(4, 20);
	monthDaySeparator->setFont(timeFont);
	m_dayButton = new FadeEffectButton(m_YYYYMMDDWidget);
	m_dayButton->setBackgroundWidgetStyleSheet("background-color: rgba(0, 0, 255, 0.1); border-radius: 5px");
	m_dayButton->setFixedSize(30, 20);
	m_dayButton->setFont(timeFont);
	m_dayButton->setCursor(Qt::PointingHandCursor);
	m_dayButton->setSizePolicy(policy);
	m_YYYYMMDDWidgetLayout->addStretch();
	m_YYYYMMDDWidgetLayout->addWidget(m_yearButton);
	m_YYYYMMDDWidgetLayout->addWidget(yearMonthSeparator);
	m_YYYYMMDDWidgetLayout->addWidget(m_monthButton);
	m_YYYYMMDDWidgetLayout->addWidget(monthDaySeparator);
	m_YYYYMMDDWidgetLayout->addWidget(m_dayButton);
	m_YYYYMMDDWidgetLayout->addStretch();
	m_HHMMWidget = new QWidget(m_centralWidget);
	m_HHMMWidget->setObjectName("HHMMWidget");
	//m_HHMMWidget->setFixedSize(124, 20);
	m_HHMMWidget->setStyleSheet("QWidget #HHMMWidget { border-bottom: 1px solid #377FED }");
	m_HHMMWidgetLayout = new QHBoxLayout(m_HHMMWidget);
	m_HHMMWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_HHMMWidgetLayout->setSpacing(0);
	m_hourButton = new FadeEffectButton(m_HHMMWidget);
	m_hourButton->setBackgroundWidgetStyleSheet("background-color: rgba(0, 0, 255, 0.1); border-radius: 5px");
	m_hourButton->setFixedSize(30, 20);
	m_hourButton->setFont(timeFont);
	m_hourButton->setCursor(Qt::PointingHandCursor);
	m_hourButton->setSizePolicy(policy);
	QLabel* hourMinuteSeparator = new QLabel(":", m_HHMMWidget);
	hourMinuteSeparator->setFixedSize(2, 20);
	hourMinuteSeparator->setFont(timeFont);
	m_minuteButton = new FadeEffectButton(m_HHMMWidget);
	m_minuteButton->setBackgroundWidgetStyleSheet("background-color: rgba(0, 0, 255, 0.1); border-radius: 5px");
	m_minuteButton->setFixedSize(30, 20);
	m_minuteButton->setFont(timeFont);
	m_minuteButton->setCursor(Qt::PointingHandCursor);
	m_minuteButton->setSizePolicy(policy);
	m_HHMMWidgetLayout->addWidget(m_hourButton);
	m_HHMMWidgetLayout->addWidget(hourMinuteSeparator);
	m_HHMMWidgetLayout->addWidget(m_minuteButton);

	m_layout->addStretch();
	m_layout->addWidget(m_YYYYMMDDWidget);
	m_layout->addStretch();
	m_layout->addWidget(m_HHMMWidget);
	m_layout->addStretch();
}

void DateTimeMenuItem::setDateTime(const QDateTime& dateTime)
{
	QDate date = dateTime.date();
	QTime time = dateTime.time();
	m_yearButton->setText(QString::number(date.year()));
	m_monthButton->setText(QString("%1").arg(date.month(), 2, 10, QLatin1Char('0')));
	m_dayButton->setText(QString("%1").arg(date.day(), 2, 10, QLatin1Char('0')));
	m_selectedDateTime.setDate(date);
	m_dayValidator->setTop(date.daysInMonth());
	m_hourButton->setText(QString("%1").arg(time.hour(), 2, 10, QLatin1Char('0')));
	m_minuteButton->setText(QString("%1").arg(time.minute(), 2, 10, QLatin1Char('0')));
	m_selectedDateTime.setTime(time);
}

void DateTimeMenuItem::edit(FadeEffectButton* button, const QValidator* validator)
{
	// 字体清单
	QFont timeFont = QFont("NeverMind", 11, QFont::Normal);

	m_lineEdit->move(button->mapTo(m_centralWidget, QPoint(0, 0)));
	m_lineEdit->resize(button->size());
	m_lineEdit->setText(button->text());
	m_lineEdit->setValidator(validator);
	m_lineEdit->raise();
	m_lineEdit->show();
	m_lineEdit->setFocus();
	m_lineEdit->disconnect();
	connect(m_lineEdit, &QLineEdit::editingFinished, [this, button]()
		{
			int result = m_lineEdit->text().toInt();
			// 按钮文字规则
			if (button == m_yearButton) button->setText(m_lineEdit->text());
			else button->setText(QString("%1").arg(result, 2, 10, QLatin1Char('0')));
			// 变更m_selectedDateTime
			if (button == m_yearButton) m_selectedDateTime.setDate(QDate(result, m_selectedDateTime.date().month(), m_selectedDateTime.date().day()));
			else if (button == m_monthButton)
			{
				int days = QDate(m_selectedDateTime.date().year(), result, 1).daysInMonth();
				if (m_selectedDateTime.date().day() > days)
				{
					m_dayButton->setText("01");
					m_selectedDateTime.setDate(QDate(m_selectedDateTime.date().year(), result, 1));
				}
				else m_selectedDateTime.setDate(QDate(m_selectedDateTime.date().year(), result, m_selectedDateTime.date().day()));
			}
			else if (button == m_dayButton) m_selectedDateTime.setDate(QDate(m_selectedDateTime.date().year(), m_selectedDateTime.date().month(), result));
			else if (button == m_hourButton) m_selectedDateTime.setTime(QTime(result, m_selectedDateTime.time().minute()));
			else if (button == m_minuteButton) m_selectedDateTime.setTime(QTime(m_selectedDateTime.time().hour(), result));
			button->show();
			m_lineEdit->hide();
		});
	button->hide();
}

QString DateTimeMenuItem::save()
{
	return m_selectedDateTime.toString("yyyy MM dd hh mm");
}