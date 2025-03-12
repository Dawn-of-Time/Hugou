#include "Widgets/Include/FadeEffectButton.h"

FadeEffectButton::FadeEffectButton(QWidget* parent) :
	QPushButton(parent)
{
	setGeneralStyle();
}

FadeEffectButton::FadeEffectButton(const QIcon& icon, const QSize& iconSize, const QString& text, const QFont& font, QWidget* parent) :
	QPushButton(parent)
{
	setGeneralStyle();
	addIconZone(icon, iconSize);
	addTextZone(text, font);
}

FadeEffectButton::FadeEffectButton(const QIcon& icon, const QSize& iconSize, QWidget* parent) :
	QPushButton(parent)
{
	setGeneralStyle();
	addIconZone(icon, iconSize);
}

FadeEffectButton::FadeEffectButton(const QString& text, const QFont& font, QWidget* parent) :
	QPushButton(parent)
{
	setGeneralStyle();
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
	disableGraphicsEffect();
}

void FadeEffectButton::setGeneralLayout()
{
	m_buttonLayout = new QHBoxLayout(this);
	m_buttonLayout->setContentsMargins(20, 10, 20, 10);
	m_buttonLayout->setSpacing(10);
	m_buttonLayout->setAlignment(Qt::AlignVCenter);
}

void FadeEffectButton::addTextZone(const QString& text, const QFont& font)
{
	if (!m_buttonLayout) setGeneralLayout();
	m_textZone = new QLabel(text, this);
	m_textZone->setFont(font);
	m_textZone->setContentsMargins(5, 0, 0, 0);
	m_buttonLayout->addWidget(m_textZone);
}

void FadeEffectButton::addIconZone(const QIcon& icon, const QSize& iconSize)
{
	if (!m_buttonLayout) setGeneralLayout();
	m_iconZone = new QPushButton(this);
	m_iconZone->setFixedSize(iconSize);
	m_iconZone->setIconSize(iconSize);
	m_iconZone->setIcon(icon);
	m_iconZone->setAttribute(Qt::WA_TransparentForMouseEvents);
	m_iconZone->setStyleSheet("border: none; background-color: transparent");
	m_buttonLayout->addWidget(m_iconZone);
}

QString FadeEffectButton::text() 
{ 
	if (m_textZone)
		return m_textZone->text();
	else return "";
}

void FadeEffectButton::setIcon(const QIcon& icon)
{
	if (m_iconZone) m_iconZone->setIcon(icon);
};

void FadeEffectButton::setIconSize(const QSize& iconSize)
{
	if (m_iconZone) m_iconZone->setIconSize(iconSize);
};

void FadeEffectButton::setText(const QString& text)
{
	if (m_textZone)
	{
		m_textZone->setText(text);
		m_textZone->adjustSize();
		this->adjustSize();
	}
	else addTextZone(text, QFont());
}

void FadeEffectButton::setTextAlignment(Qt::Alignment alignment)
{
	if (m_textZone)
		m_textZone->setAlignment(alignment);
}

void FadeEffectButton::setFont(const QFont& font)
{
	if (m_textZone) m_textZone->setFont(font); 
	else addTextZone("", font);
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

void FadeEffectButton::resizeEvent(QResizeEvent* event) {
	QPushButton::resizeEvent(event);
	m_backgroundWidget->resize(this->size());
}