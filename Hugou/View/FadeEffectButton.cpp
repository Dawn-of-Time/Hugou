#include "FadeEffectButton.h"

FadeEffectButton::FadeEffectButton(QWidget* parent) :
	QPushButton(parent)
{
	setGeneralStyle();
}

FadeEffectButton::FadeEffectButton(QPixmap icon, QSize iconSize, QString text, QFont font, QWidget* parent) :
	QPushButton(parent)
{
	setGeneralStyle();
	setGeneralLayout();
	addIconZone(icon, iconSize);
	addTextZone(text, font);
}

FadeEffectButton::FadeEffectButton(QPixmap icon, QSize iconSize, QWidget* parent) :
	QPushButton(parent)
{
	setGeneralStyle();
	setGeneralLayout();
	addIconZone(icon, iconSize);
}

FadeEffectButton::FadeEffectButton(QString text, QFont font, QWidget* parent) :
	QPushButton(parent)
{
	setGeneralStyle();
	setGeneralLayout();
	addTextZone(text, font);
}

void FadeEffectButton::setGeneralStyle()
{
	m_backgroundWidget = new QWidget(this);
	m_backgroundWidgetOpacityEffect = new QGraphicsOpacityEffect(m_backgroundWidget);
	m_backgroundWidgetOpacityEffect->setOpacity(0);
	m_backgroundWidget->setGraphicsEffect(m_backgroundWidgetOpacityEffect);
	m_backgroundWidgetOpacityEffectAnimation = new QPropertyAnimation(m_backgroundWidgetOpacityEffect, "opacity", m_backgroundWidget);
	connect(m_backgroundWidgetOpacityEffectAnimation, &QPropertyAnimation::finished, this, &FadeEffectButton::disableGraphicsEffect);
}

void FadeEffectButton::setGeneralLayout()
{
	m_buttonLayout = new QHBoxLayout(this);
	m_buttonLayout->setContentsMargins(20, 10, 20, 10);
	m_buttonLayout->setSpacing(10);
	m_buttonLayout->setAlignment(Qt::AlignVCenter);
}

void FadeEffectButton::addTextZone(QString text, QFont font)
{
	m_textZone = new QLabel(this);
	this->setText(text, font);
	m_buttonLayout->addWidget(m_textZone);
}

void FadeEffectButton::addIconZone(QPixmap icon, QSize iconSize)
{
	m_iconZone = new QLabel(this);
	m_iconZone->setFixedSize(iconSize);
	this->setIcon(icon);
	m_buttonLayout->addWidget(m_iconZone);
}

QString FadeEffectButton::text() 
{ 
	if (m_textZone)
		return m_textZone->text();
	else return "";
}

void FadeEffectButton::setIcon(QPixmap icon)
{
	//icon.setDevicePixelRatio(getScale());
	if (m_iconZone) m_iconZone->setPixmap(icon);
};

void FadeEffectButton::setIconSize(QSize size)
{
	if (m_iconZone) m_iconZone->setFixedSize(size);
};

void FadeEffectButton::setText(QString text, QFont font)
{
	if (m_textZone)
	{
		m_textZone->setText(text);
		m_textZone->setFont(font);
		m_textZone->adjustSize();
		this->adjustSize();
	}
}

void FadeEffectButton::setFixedSize(int w, int h)
{
	QPushButton::setFixedSize(w, h);
	m_backgroundWidget->setFixedSize(w, h);
}

void FadeEffectButton::setFixedHeight(int h)
{
	QPushButton::setFixedHeight(h);
	m_backgroundWidget->setFixedHeight(h);
}

void FadeEffectButton::enableGraphicsEffect()
{
	m_backgroundWidgetOpacityEffect->setEnabled(true);
	m_backgroundWidget->show();
}

void FadeEffectButton::disableGraphicsEffect()
{
	m_backgroundWidgetOpacityEffect->setEnabled(false);
	if (!m_isMouseOver)
		m_backgroundWidget->hide();
}

void FadeEffectButton::enterEvent(QEnterEvent* event)
{
	QPushButton::enterEvent(event);
	if (m_status)
	{
		m_isMouseOver = true;
		this->setCursor(Qt::PointingHandCursor);
		if (m_backgroundWidgetOpacityEffectAnimation->state() == QPropertyAnimation::Running)
			m_backgroundWidgetOpacityEffectAnimation->stop();
		enableGraphicsEffect();
		m_backgroundWidgetOpacityEffectAnimation->setStartValue(m_backgroundWidgetOpacityEffect->opacity());
		m_backgroundWidgetOpacityEffectAnimation->setEndValue(1.0);
		m_backgroundWidgetOpacityEffectAnimation->setDuration(200);
		m_backgroundWidgetOpacityEffectAnimation->start();
	}
}

void FadeEffectButton::leaveEvent(QEvent* event)
{
	QPushButton::leaveEvent(event);
	m_isMouseOver = false;
	this->setCursor(Qt::ArrowCursor);
	if (m_backgroundWidgetOpacityEffectAnimation->state() == QPropertyAnimation::Running)
		m_backgroundWidgetOpacityEffectAnimation->stop();
	enableGraphicsEffect();
	m_backgroundWidgetOpacityEffectAnimation->setStartValue(m_backgroundWidgetOpacityEffect->opacity());
	m_backgroundWidgetOpacityEffectAnimation->setEndValue(0.0);
	m_backgroundWidgetOpacityEffectAnimation->setDuration(200);
	m_backgroundWidgetOpacityEffectAnimation->start();
}

void FadeEffectButton::paintEvent(QPaintEvent* event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FadeEffectButton::showEvent(QShowEvent* event) {
	m_backgroundWidget->resize(this->size());
}