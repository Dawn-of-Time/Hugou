#include "CheckBox.h"

CheckBox::CheckBox(QWidget* parent, Status status)
	:QPushButton(parent), m_status(status)
{
	setFixedSize(20, 20);

	setStyleSheet("border-radius: 3px; border: 2px solid #4F5E71");

	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);
	m_layout->setAlignment(Qt::AlignCenter);
	
	m_icon = new QLabel(this);
	m_icon->setFixedSize(20, 20);
	m_icon->setStyleSheet("background-color: #4F5E71");
	m_icon->setPixmap(QPixmap(":/icon/tick_white.png"));
	m_icon->setAlignment(Qt::AlignCenter);

	m_effect = new QGraphicsOpacityEffect(m_icon);
	if (m_status == Status::Checked)
		m_effect->setOpacity(1);
	else
		m_effect->setOpacity(0);
	m_icon->setGraphicsEffect(m_effect);
	disableGraphicsEffect();

	m_layout->addWidget(m_icon);

    m_animation = new QPropertyAnimation(m_effect, "opacity", this);
	m_animation->setDuration(200);
	connect(m_animation, &QPropertyAnimation::finished, this, &CheckBox::disableGraphicsEffect);
	connect(this, &QPushButton::clicked, this, &CheckBox::changeStatus);
}

void CheckBox::changeStatus()
{
	enableGraphicsEffect();
	if (m_status == Status::Checked)
	{
		m_animation->setStartValue(1);
		m_animation->setEndValue(0);
		m_animation->start();
		m_status = Status::Unchecked;
	}
	else
	{
		m_animation->setStartValue(0);
		m_animation->setEndValue(1);
		m_animation->start();
		m_status = Status::Checked;
	}
}

void CheckBox::enableGraphicsEffect()
{
	m_effect->setEnabled(true);
	m_icon->setVisible(true);
}

void CheckBox::disableGraphicsEffect()
{
	m_effect->setEnabled(false);
	if (m_status == Status::Unchecked)
		m_icon->setVisible(false);
}
