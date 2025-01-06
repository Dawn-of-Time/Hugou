#include "IconTextButton.h"

IconTextButton::IconTextButton(QPixmap icon, QString text, QFont font, QWidget* parent) :
	QPushButton(parent)
{
	m_backgroundWidget = new QWidget(this);
	m_backgroundWidget->setFixedSize(asideButtonWidth, asideButtonHeight);
	m_backgroundWidget->setStyleSheet("background-color: rgba(0, 0, 255, 0.1); border-radius: 5px;");
	m_backgroundWidgetOpacityEffect = new QGraphicsOpacityEffect();
	m_backgroundWidgetOpacityEffect->setOpacity(0);
	m_backgroundWidget->setGraphicsEffect(m_backgroundWidgetOpacityEffect);
	m_backgroundWidgetOpacityEffectAnimation = new QPropertyAnimation(m_backgroundWidgetOpacityEffect, "opacity");

	m_buttonLayout = new QHBoxLayout(this);
	m_buttonLayout->setContentsMargins(0, 0, 0, 0);
	m_buttonLayout->setSpacing(0);
	m_iconZone = new QLabel(this);
	m_iconZone->setFixedSize(16, 16);
	m_textZone = new QLabel(this);
	
	// ��͸�ӿؼ���ʹ��괥���¼��Ķ����Ǹ��ؼ�
	m_iconZone->setAttribute(Qt::WA_TransparentForMouseEvents);
	m_textZone->setAttribute(Qt::WA_TransparentForMouseEvents);

	m_buttonLayout->setContentsMargins(10, 0, 10, 0);
	m_buttonLayout->setSpacing(12);

	this->setIcon(icon);
	this->setText(text, font);

	m_buttonLayout->addWidget(m_iconZone, Qt::AlignVCenter);
	m_buttonLayout->addWidget(m_textZone, Qt::AlignVCenter);
	m_buttonLayout->addStretch();
}

void IconTextButton::enterEvent(QEnterEvent* event)
{
	QPushButton::enterEvent(event);
	if (m_status)
	{
		this->setCursor(Qt::PointingHandCursor);
		if (m_backgroundWidgetOpacityEffectAnimation->state() == QPropertyAnimation::Running)
		{
			m_backgroundWidgetOpacityEffectAnimation->stop();
		}
		m_backgroundWidgetOpacityEffectAnimation->setStartValue(m_backgroundWidgetOpacityEffect->opacity());
		m_backgroundWidgetOpacityEffectAnimation->setEndValue(1);
		m_backgroundWidgetOpacityEffectAnimation->setDuration(200);
		m_backgroundWidgetOpacityEffectAnimation->start();
	}
}

void IconTextButton::leaveEvent(QEvent* event)
{
	QPushButton::leaveEvent(event);
	this->setCursor(Qt::ArrowCursor);
	if (m_backgroundWidgetOpacityEffectAnimation->state() == QPropertyAnimation::Running)
	{
		m_backgroundWidgetOpacityEffectAnimation->stop();
	}
	m_backgroundWidgetOpacityEffectAnimation->setStartValue(m_backgroundWidgetOpacityEffect->opacity());
	m_backgroundWidgetOpacityEffectAnimation->setEndValue(0);
	m_backgroundWidgetOpacityEffectAnimation->setDuration(200);
	m_backgroundWidgetOpacityEffectAnimation->start();
}