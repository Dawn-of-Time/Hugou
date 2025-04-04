#include "Widgets/Include/YearAndMonthSelector.h"

YearAndMonthSelector::YearAndMonthSelector(int selectedYear, int selectedMonth, QWidget* parent)
	:CloseWhenLeaveWidget(parent)
{
	m_selectedYear = selectedYear;
	setupUi();
	connect(m_backButton, &QPushButton::clicked, [this]() { changeYear(m_yearLineEdit->text().toInt() - 1); });
	connect(m_forwardButton, &QPushButton::clicked, [this]() { changeYear(m_yearLineEdit->text().toInt() + 1); });
	connect(m_yearLineEdit, &QLineEdit::editingFinished, [this]() { changeYear(m_yearLineEdit->text().toInt()); });
	connect(this, &YearAndMonthSelector::SignalClose, [=]() { emit SignalSelected(m_yearLineEdit->text().toInt(), selectedMonth); });
}

void YearAndMonthSelector::setupUi()
{
	// ×ÖÌåÇåµ¥
	QFont yearFont = QFont("NeverMind", 14, QFont::DemiBold);
	QFont monthFont = QFont("NeverMind", 12, QFont::Light);

	this->setFixedSize(255, 195);
	this->setObjectName("yearAndMonthSelector");
	this->setStyleSheet("QWidget #yearAndMonthSelector { background-color: rgba(255, 255, 255, 0.98);  border-radius: 10px }");

	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(15, 15, 15, 15);
	m_layout->setSpacing(15);
	m_layout->setAlignment(Qt::AlignHCenter);

	m_titleWidget = new QWidget(this);
	m_titleWidget->setFixedHeight(30);
	m_titleWidgetLayout = new QHBoxLayout(m_titleWidget);
	m_titleWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_titleWidgetLayout->setSpacing(0);
	m_backButton = new QPushButton(m_titleWidget);
	m_backButton->setFixedSize(20, 20);
	m_backButton->setIcon(QIcon(":/icon/back.ico"));
	m_backButton->setIconSize(QSize(12, 12));
	m_backButton->setCursor(Qt::PointingHandCursor);
	m_backButton->setStyleSheet("background-color: #AEE4FD; border-radius: 10px");
	m_yearLineEdit = new QLineEdit(m_titleWidget);
	m_yearLineEdit->setFixedSize(135, 30);
	m_yearLineEdit->setAlignment(Qt::AlignCenter);
	m_yearLineEdit->setFont(yearFont);
	m_yearLineEdit->setStyleSheet("border-bottom: 1px solid #AEE4FD");
	m_yearLineEdit->setValidator(new QIntValidator(0, 5000, m_yearLineEdit));
	m_forwardButton = new QPushButton(m_titleWidget);
	m_forwardButton->setFixedSize(20, 20);
	m_forwardButton->setIcon(QIcon(":/icon/forward.ico"));
	m_forwardButton->setIconSize(QSize(12, 12));
	m_forwardButton->setCursor(Qt::PointingHandCursor);
	m_forwardButton->setStyleSheet("background-color: #AEE4FD; border-radius: 10px");
	m_titleWidgetLayout->addWidget(m_backButton);
	m_titleWidgetLayout->addWidget(m_yearLineEdit);
	m_titleWidgetLayout->addWidget(m_forwardButton);

	m_monthWidget = new QWidget(this);
	m_monthWidgetLayout = new QGridLayout(m_monthWidget);
	m_monthWidgetLayout->setHorizontalSpacing(15);
	m_monthWidgetLayout->setVerticalSpacing(3);
	int monthIndex = 1;
	for (int row = 0; row < 3; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			FadeEffectButton* button = new FadeEffectButton(m_monthNameList[row * 4 + column].left(3), monthFont, m_monthWidget);
			button->setFixedSize(45, 30);
			button->layout()->setContentsMargins(0, 0, 0, 0);
			button->setTextAlignment(Qt::AlignCenter);
			button->setBackgroundWidgetStyleSheet("background-color: rgba(0, 0, 255, 0.1); border-radius: 5px");
			m_monthWidgetLayout->addWidget(button, row, column);
			connect(button, &FadeEffectButton::clicked, [this, button]()
				{
					emit SignalSelected(m_yearLineEdit->text().toInt(), m_monthMap[button->text()]);
					this->blockSignals(true);
					this->close();
				});
		}
	}
	m_currentMonthbutton = qobject_cast<FadeEffectButton*>(m_monthWidgetLayout->itemAtPosition(QDate::currentDate().month() / 4, (QDate::currentDate().month() - 1) % 4)->widget());
	m_yearLineEdit->setText(QString::number(m_selectedYear));
	if (m_selectedYear == QDate::currentDate().year()) m_currentMonthbutton->setStyleSheet("QWidget #currentMonth{background-color: rgba(0, 0, 255, 0.1); border-radius: 5px}");
	else m_currentMonthbutton->setStyleSheet("QWidget #currentMonth{background-color: transparent; border-radius: 5px}");

	m_layout->addWidget(m_titleWidget);
	m_layout->addWidget(m_monthWidget);

	QGraphicsDropShadowEffect* dropShadowEffect = new QGraphicsDropShadowEffect(this);
	dropShadowEffect->setBlurRadius(20);
	dropShadowEffect->setXOffset(0);
	dropShadowEffect->setYOffset(6);
	this->setGraphicsEffect(dropShadowEffect);

	QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(this);
	opacityEffect->setOpacity(0);
	this->setGraphicsEffect(opacityEffect);

	QPropertyAnimation* animation = new QPropertyAnimation(opacityEffect, "opacity");
	animation->setStartValue(0);
	animation->setEndValue(1);
	animation->setDuration(200);
	connect(animation, &QPropertyAnimation::finished, [=]()
		{
			opacityEffect->setEnabled(false);
		});
	animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void YearAndMonthSelector::changeYear(int year)
{
	m_yearLineEdit->setText(QString::number(year));
	if (year == QDate::currentDate().year()) m_currentMonthbutton->setStyleSheet("QWidget #currentMonth{background-color: rgba(0, 0, 255, 0.1); border-radius: 5px}");
	else m_currentMonthbutton->setStyleSheet("QWidget #currentMonth{background-color: transparent; border-radius: 5px}");
}