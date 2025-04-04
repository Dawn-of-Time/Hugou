#include "Widgets/Include/Menu/LineEditMenuItem.h"

LineEditMenuItem::LineEditMenuItem(const QString& title, QWidget* menu)
	:MenuItem(title, menu)
{
	setupUi();
}

void LineEditMenuItem::setupUi()
{
	// ×ÖÌåÇåµ¥
	QFont lineEditFont = QFont("NeverMind", 12, QFont::Normal);

	m_lineEdit = new QLineEdit(this);
	m_lineEdit->setFixedHeight(30);
	m_lineEdit->setFont(lineEditFont);
	this->setCentralWidget(m_lineEdit);
}

void LineEditMenuItem::recall()
{
	m_lineEdit->setText(m_oldName);
}

QString LineEditMenuItem::save()
{
	return m_lineEdit->text();
}