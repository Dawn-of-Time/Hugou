#include "Widgets/Include/MemoSettingItem/MemoTypeItem.h"

extern QWidget* globalHugou;

MemoTypeItem::MemoTypeItem(const QList<MemoTypeLabel*>& typeLabelList, QMap<int, QList<MemoType*>>& typeLabelMap, QList<MemoType*>& typeList, QWidget* parent)
	:MemoSettingItem(parent), m_typeLabelList(typeLabelList), m_typeLabelMap(typeLabelMap), m_typeList(typeList)
{
	for (MemoType* memoType : typeList)
		if (memoType->priority) m_priorityTypeList.append(memoType);
	std::sort(m_priorityTypeList.begin(), m_priorityTypeList.end(), [](MemoType* m1, MemoType* m2) {
		return std::tie(m1->priority) < std::tie(m2->priority);
		});
	setupUi();
	connect(m_addTypeButton, &QPushButton::clicked, this, &MemoTypeItem::showMemoTypeConfigView);
}

void MemoTypeItem::setupUi()
{
	// 字体清单
	QFont labelFont = QFont("NeverMind", 10, QFont::Normal);

	setFixedHeight(110);
	m_title->setText("Type");
	m_content->setFixedHeight(80);
	m_contentLayout = new QHBoxLayout(m_content);
	m_contentLayout->setContentsMargins(10, 10, 10, 10);
	m_contentLayout->setSpacing(10);
	m_contentLayout->setAlignment(Qt::AlignLeft);
	m_typeListWidget = new QWidget(m_content);
	m_typeListWidgetLayout = new QHBoxLayout(m_typeListWidget);
	m_typeListWidgetLayout->setContentsMargins(5, 0, 0, 0);
	m_typeListWidgetLayout->setSpacing(10);

	for (MemoType* memoType : m_priorityTypeList)
		addMemoType(*memoType);

	QWidget* spacer = new QWidget(m_content);
	spacer->setFixedSize(1, 60);
	spacer->setStyleSheet("background-color: black");

	m_addTypeButton = new QPushButton(m_content);
	m_addTypeButton->setFixedSize(40, 60);
	m_addTypeButton->setCursor(Qt::PointingHandCursor);
	QVBoxLayout* addTypeButtonLayout = new QVBoxLayout(m_addTypeButton);
	addTypeButtonLayout->setContentsMargins(0, 0, 0, 0);
	addTypeButtonLayout->setSpacing(0);
	addTypeButtonLayout->setAlignment(Qt::AlignHCenter);
	QPushButton* icon = new QPushButton(m_addTypeButton);
	icon->setFixedSize(40, 40);
	icon->setStyleSheet("background-color: #EAF9FE; border-radius: 5px; border: none");
	icon->setIcon(QIcon(":/icon/preference_default.ico"));
	icon->setIconSize(QSize(16, 16));
	icon->setAttribute(Qt::WA_TransparentForMouseEvents);
	QLabel* label = new QLabel("Config", m_addTypeButton);
	label->setAlignment(Qt::AlignHCenter);
	label->setFixedSize(40, 20);
	label->setFont(labelFont);
	label->setAttribute(Qt::WA_TransparentForMouseEvents);

	addTypeButtonLayout->addWidget(icon);
	addTypeButtonLayout->addWidget(label);

	m_contentLayout->addWidget(m_typeListWidget);
	m_contentLayout->addWidget(spacer);
	m_contentLayout->addWidget(m_addTypeButton);
}

void MemoTypeItem::addMemoType(MemoType& memoType)
{
	// 字体清单
	QFont labelFont = QFont("NeverMind", 10, QFont::Normal);

	if (m_count < 5)
	{
		MemoTypeWidget* memoTypeWidget = new MemoTypeWidget(memoType, m_content);
		m_typeListWidgetLayout->addWidget(memoTypeWidget);
		m_count++;
		m_memoTypeWidgetMap.insert(&memoType, memoTypeWidget);
		connect(memoTypeWidget, &MemoTypeWidget::clicked, [this, memoTypeWidget]()
			{
				for (QMap<MemoType*, MemoTypeWidget*>::iterator it = m_memoTypeWidgetMap.begin(); it != m_memoTypeWidgetMap.end(); it++)
				{
					if (it.value() == memoTypeWidget)
					{
						it.value()->setStatus(true);
						m_selectedMemoType = it.key();
						m_isSelected = true;
					}
					else it.value()->setStatus(false);
				}
			});
	}
}

void MemoTypeItem::showMemoTypeConfigView()
{
	MemoTypeConfigView* view = new MemoTypeConfigView(m_oldNewPriorityDisplayMemoTypeMap);
	for (MemoType* memoType : m_priorityTypeList)
		view->addPriorityType(*memoType);
	for (MemoTypeLabel* memoTypeLabel : m_typeLabelList)
		view->addTypeLabelAndType(memoTypeLabel->name, m_typeLabelMap[memoTypeLabel->ID]);

	connect(view, &MemoTypeConfigView::SignalClose, [&]()
		{
			for (QMap<MemoType*, MemoType*>::iterator it = m_oldNewPriorityDisplayMemoTypeMap.begin(); it != m_oldNewPriorityDisplayMemoTypeMap.end(); it++)
			{
				m_memoTypeWidgetMap[it.key()]->updateUi(*it.value());
				it.key()->name = it.value()->name;
				it.key()->color = it.value()->color;
			}
			qDeleteAll(m_oldNewPriorityDisplayMemoTypeMap);
			m_oldNewPriorityDisplayMemoTypeMap.clear();
		});
	view->show();
	view->move(globalHugou->pos() + QPoint((globalHugou->width() - view->width()) / 2, (globalHugou->height() - view->height()) / 2));
}

bool MemoTypeItem::getResult(MemoType* memoType)
{
	if (m_isSelected)
	{
		memoType = m_selectedMemoType;
		return true;
	}
	else return false;
}