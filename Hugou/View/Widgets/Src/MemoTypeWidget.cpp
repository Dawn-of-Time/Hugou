#include "View/Widgets/Include/MemoTypeWidget.h"


MemoTypeWidget::MemoTypeWidget(MemoType& memoType, QWidget* parent)
	:QPushButton(parent), m_memoType(memoType)
{
	setupUi();
	setCursor(Qt::PointingHandCursor);
}

void MemoTypeWidget::setupUi()
{
	// 字体清单
	QFont typeFont = QFont("NeverMind", 10, QFont::Normal);

	this->setFixedSize(40, 60);
	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);
	m_layout->setAlignment(Qt::AlignHCenter);
	m_icon = new QLabel(this);
	m_icon->setAlignment(Qt::AlignCenter);
	m_icon->setFixedSize(40, 40);
	m_icon->setStyleSheet(QString("background-color: %1; border-radius: 5px").arg(m_memoType.color.name()));
	m_icon->setAttribute(Qt::WA_TransparentForMouseEvents);
	m_type = new QLabel(QFontMetrics(typeFont).elidedText(m_memoType.name, Qt::ElideRight, 40), this);
	m_type->setAlignment(Qt::AlignHCenter);
	m_type->setFixedSize(40, 20);
	m_type->setFont(typeFont);
	m_type->setAttribute(Qt::WA_TransparentForMouseEvents);
	m_mask = new QWidget(this);
	m_mask->setStyleSheet("background-color: rgba(255, 255, 255, 0.6); border-radius: 5px");
	m_mask->setAttribute(Qt::WA_TransparentForMouseEvents);
	m_mask->setFixedSize(40, 40);
	m_mask->move(0, 0);
	m_maskEffect = new QGraphicsOpacityEffect(m_mask);
	m_maskEffect->setOpacity(1);
	m_mask->setGraphicsEffect(m_maskEffect);
	m_maskEffect->setEnabled(false);
	m_mask->hide();

	m_tooltip = new ToolTip(m_memoType.name, this);

	m_layout->addWidget(m_icon);
	m_layout->addWidget(m_type);

	this->setStyleSheet(
		"QWidget { background-color: transparent; border: none }"
	);
}

void MemoTypeWidget::setStatus(bool status) 
{ 
	m_status = status; 
	if (!m_status)
	{
		m_mask->show();
		m_type->setStyleSheet("color: rgba(0, 0, 0, 0.4)");
	}
	else
	{
		m_mask->hide();
		m_type->setStyleSheet("color: rgba(0, 0, 0, 1)");
	}
}

void MemoTypeWidget::updateUi(const MemoType& newType)
{
	// 字体清单
	QFont typeFont = QFont("NeverMind", 10, QFont::Normal);

	m_icon->setStyleSheet(QString("background-color: %1; border-radius: 5px").arg(newType.color.name()));
	m_type->setText(QFontMetrics(typeFont).elidedText(newType.name, Qt::ElideRight, 40));
	m_memoType = newType;
	update();
}

void MemoTypeWidget::showEvent(QShowEvent* event)
{
	QWidget::showEvent(event);
	if (!m_status)
	{
		m_mask->show();
		m_type->setStyleSheet("color: rgba(0, 0, 0, 0.3)");
	}
}

void MemoTypeWidget::enterEvent(QEnterEvent* event)
{
	QWidget::enterEvent(event);
	m_tooltip->show();
	if (!m_status)
	{
		m_maskEffect->setEnabled(true);
		m_type->setStyleSheet("color: rgba(0, 0, 0, 1)");
		QPropertyAnimation* animation = new QPropertyAnimation(m_maskEffect, "opacity");
		animation->setDuration(100);
		animation->setEndValue(0);
		connect(animation, &QPropertyAnimation::finished, [this]() { m_mask->hide(); m_maskEffect->setEnabled(false);  });
		animation->start(QPropertyAnimation::DeleteWhenStopped);
	}
}

void MemoTypeWidget::leaveEvent(QEvent* event)
{
	QWidget::leaveEvent(event);
	m_tooltip->hide();
	if (!m_status)
	{
		m_mask->show();
		m_maskEffect->setEnabled(true);
		m_type->setStyleSheet("color: rgba(0, 0, 0, 0.3)");
		QPropertyAnimation* animation = new QPropertyAnimation(m_maskEffect, "opacity");
		animation->setDuration(100);
		animation->setEndValue(1);
		connect(animation, &QPropertyAnimation::finished, [this]() { m_maskEffect->setEnabled(false); });
		animation->start(QPropertyAnimation::DeleteWhenStopped);
	}
}