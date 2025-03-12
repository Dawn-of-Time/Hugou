#include "Widgets/Include/ToolTip.h"

ToolTip::ToolTip(const QString& content, QWidget* parent)
	:QWidget(parent), m_content(content)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
	setAttribute(Qt::WA_TranslucentBackground);
	setupUi();
	hide();
}

void ToolTip::setupUi()
{
	this->setFixedHeight(30);
	this->setStyleSheet("background-color: #373D3F; border-radius: 5px");

	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(8, 5, 5, 8);
	m_layout->setSpacing(0);

	m_contentLabel = new QLabel(m_content, this);
	m_contentLabel->setFixedHeight(20);
	m_contentLabel->setFont(QFont("NeverMind", 10, QFont::Medium));
	m_contentLabel->setAlignment(Qt::AlignCenter);
	m_contentLabel->setStyleSheet("background-color: transparent; color: white");
	m_contentLabel->adjustSize();

	m_layout->addWidget(m_contentLabel);
}

void ToolTip::show()
{
	QWidget::show();
	QPoint parentTopLeft = parentWidget()->mapToGlobal(QPoint(0, 0));
	int x = parentTopLeft.x() + (parentWidget()->width() - this->width()) / 2;
	int y = 0;
	if (parentTopLeft.y() <= 35) y = parentTopLeft.y() + parentWidget()->height() + 5;
	else y = parentTopLeft.y() - 35;
	this->move(x, y);
	this->raise();
}

void ToolTip::paintEvent(QPaintEvent* event) {
	QStyleOption opt;
	opt.initFrom(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}