#include "Menu/Include/MenuItem.h"

MenuItem::MenuItem(const QString& title, QWidget* parent)
	:QWidget(parent), m_title(title)
{
	setupUi();
	m_titleLabel->setText(title);
	connect(m_recallButton, &QPushButton::clicked, this, &MenuItem::recall);
}

void MenuItem::setupUi()
{
	// ×ÖÌåÇåµ¥
	QFont titleFont = QFont("NeverMind", 12, QFont::Medium);

	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(5);

	m_titleWidget = new QWidget(this);
	m_titleWidgetLayout = new QHBoxLayout(m_titleWidget);
	m_titleWidgetLayout->setContentsMargins(0, 0, 0, 0);

	m_titleLabel = new QLabel(m_titleWidget);
	m_titleLabel->setFont(titleFont);
	m_recallButton = new QPushButton(m_titleWidget);
	m_recallButton->setFixedSize(24, 24);
	m_recallButton->setIcon(QIcon(":/icon/recall.ico"));
	m_recallButton->setIconSize(QSize(16, 16));
	m_recallButton->setStyleSheet("border: none");

	m_titleWidgetLayout->addWidget(m_titleLabel);
	m_titleWidgetLayout->addWidget(m_recallButton, Qt::AlignRight);
	
	m_layout->addWidget(m_titleWidget);
}

void MenuItem::setCentralWidget(QWidget* widget)
{
	m_layout->addWidget(widget);
}