#include "Widgets/Include/Menu/SingleSelectionMenuItem.h"

SingleSelectionMenuItem::SingleSelectionMenuItem(const QString& title, const QList<QString>& selectionList, QWidget* menu)
	:MenuItem(title, menu)
{
	m_selectionList = selectionList;
	setupUi();
	disableRecallFunction();
	setCentralWidget(m_centralWidget);
	connect(m_buttonGroup, &QButtonGroup::buttonClicked, [this](QAbstractButton* selectedButton)
		{
			m_selected = QString::number(m_buttonGroup->id(selectedButton));
			emit SignalSelected(m_selected);
		});
}

void SingleSelectionMenuItem::setupUi()
{
	// ×ÖÌåÇåµ¥
	QFont radioButtonFont = QFont("NeverMind", 10, QFont::Normal);

	m_centralWidget = new QWidget(this);
	m_centralWidgetLayout = new QVBoxLayout(m_centralWidget);
	m_centralWidgetLayout->setContentsMargins(10, 0, 0, 0);
	m_centralWidgetLayout->setSpacing(5);
	m_buttonGroup = new QButtonGroup(this);
	for (const QString& s : m_selectionList)
	{
		QRadioButton* button = new QRadioButton(s, m_centralWidget);
		button->setFont(radioButtonFont);
		button->setContentsMargins(5, 0, 0, 0);
		m_buttonGroup->addButton(button);
		m_centralWidgetLayout->addWidget(button);
	}
}

QString SingleSelectionMenuItem::save()
{
	return m_selected;
}