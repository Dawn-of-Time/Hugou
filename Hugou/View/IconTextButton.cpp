#include "IconTextButton.h"

IconTextButton::IconTextButton(QPixmap icon, QString text, QFont font, QWidget* parent) :
	QPushButton(parent)
{
	m_backgroundWidget = new QWidget(this);
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
	
	// 穿透子控件，使鼠标触发事件的对象是父控件
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

void IconTextButton::setIcon(QPixmap icon)
{
	icon.setDevicePixelRatio(getScale());
	m_iconZone->setPixmap(icon);
};

void IconTextButton::setIconSize(QSize size)
{
	m_iconZone->setFixedSize(size);
};

void IconTextButton::setText(QString text, QFont font)
{
	m_textZone->setText(text);
	m_textZone->setFont(font);
}

void IconTextButton::setFixedSize(int w, int h)
{
	QPushButton::setFixedSize(w, h);
	m_backgroundWidget->setFixedSize(w, h);
}

void IconTextButton::setFixedHeight(int h)
{
	QPushButton::setFixedHeight(h);
	m_backgroundWidget->setFixedHeight(h);
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

void IconTextButton::paintEvent(QPaintEvent* event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void IconTextButton::showEvent(QShowEvent* event) {
	m_backgroundWidget->resize(this->size());
}