#include "View/Include/MemoTypeWidget.h"


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
	this->setStyleSheet(
		"QWidget { background-color: transparent; border: none }"
		"QToolTip { padding: 0px 2px 0px 2px; color: white; background-color: #3F3F3F}"
	);
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
	if (QFontMetrics(typeFont).horizontalAdvance(m_memoType.name) > 40) this->setToolTip(m_memoType.name);
	else this->setToolTip("");
	m_type->setAlignment(Qt::AlignHCenter);
	m_type->setFixedSize(40, 20);
	m_type->setFont(typeFont);
	m_type->setAttribute(Qt::WA_TransparentForMouseEvents);

	m_layout->addWidget(m_icon);
	m_layout->addWidget(m_type);
}

void MemoTypeWidget::updateUi(const MemoType& newType)
{
	// 字体清单
	QFont typeFont = QFont("NeverMind", 10, QFont::Normal);

	m_icon->setStyleSheet(QString("background-color: %1; border-radius: 5px").arg(newType.color.name()));
	m_type->setText(QFontMetrics(typeFont).elidedText(newType.name, Qt::ElideRight, 40));
	if (QFontMetrics(typeFont).horizontalAdvance(newType.name) > 40) this->setToolTip(newType.name);
	else this->setToolTip("");
	this->setStyleSheet(
		"QWidget { background-color: transparent; border: none }"
		"QToolTip { padding: 0px 2px 0px 2px; color: white; background-color: #3F3F3F}"
	);
	m_memoType = newType;
	update();
}