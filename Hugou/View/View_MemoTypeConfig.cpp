#include "View/Include/View_MemoTypeConfig.h"

MemoTypeConfigView::MemoTypeConfigView(QMap<MemoType*, MemoType*>& oldNewPriorityDisplayMemoTypeMap)
	:PopupWidget("Memo Type"), m_oldNewPriorityDisplayMemoTypeMap(oldNewPriorityDisplayMemoTypeMap)
{
	setupUi();
	connect(m_closeButton, &QPushButton::clicked, this, &MemoTypeConfigView::close);
}

MemoTypeConfigView::~MemoTypeConfigView()
{
	
}

void MemoTypeConfigView::setupUi()
{
	// �����嵥
	QFont titleFont = QFont("NeverMind", 20, QFont::Normal);

	m_centralWidget = new QWidget(this);
	m_centralWidget->setFixedHeight(480);
	this->setCentralWidget(m_centralWidget);
	m_layout = new QVBoxLayout(m_centralWidget);
	m_layout->setContentsMargins(30, 10, 30, 10);
	m_layout->setSpacing(20);
	m_layout->setAlignment(Qt::AlignTop);

	m_priorityDisplayWidget = new QWidget(m_centralWidget);
	m_priorityDisplayWidget->setFixedSize(780, 130);
	m_priorityDisplayWidgetLayout = new QVBoxLayout(m_priorityDisplayWidget);
	m_priorityDisplayWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_priorityDisplayWidgetLayout->setSpacing(10);
	m_priorityDisplayTitle = new QLabel("Priority Display", m_priorityDisplayWidget);
	m_priorityDisplayTitle->setFixedHeight(30);
	m_priorityDisplayTitle->setFont(titleFont);
	m_priorityDisplayContent = new QWidget(m_centralWidget);
	m_priorityDisplayContent->setObjectName("priorityDisplayContent");
	m_priorityDisplayContent->setFixedHeight(90);
	m_priorityDisplayContent->setStyleSheet("QWidget #priorityDisplayContent {background-color: #AEE4FD; border-radius: 5px}");
	m_priorityDisplayContentLayout = new QHBoxLayout(m_priorityDisplayContent);
	m_priorityDisplayContentLayout->setContentsMargins(50, 15, 50, 15);
	m_priorityDisplayContentLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_priorityDisplayContentLayout->setSpacing(120);
	m_priorityDisplayWidgetLayout->addWidget(m_priorityDisplayTitle);
	m_priorityDisplayWidgetLayout->addWidget(m_priorityDisplayContent);

	m_typeRepoWidget = new QWidget(m_centralWidget);
	m_typeRepoWidget->setFixedSize(780, 300);
	m_typeRepoWidgetLayout = new QVBoxLayout(m_typeRepoWidget);
	m_typeRepoWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_typeRepoWidgetLayout->setSpacing(10);
	m_typeRepoTitle = new QLabel("Type Repo", m_typeRepoWidget);
	m_typeRepoTitle->setFixedHeight(30);
	m_typeRepoTitle->setFont(titleFont);
	m_typeRepoContent = new QWidget(m_centralWidget);
	m_typeRepoContent->setFixedHeight(260);
	m_typeRepoContentLayout = new QVBoxLayout(m_typeRepoContent);
	m_typeRepoContentLayout->setContentsMargins(0, 0, 0, 0);
	m_typeRepoContentLayout->setSpacing(10);
	m_typeRepoContentLayout->setAlignment(Qt::AlignLeft);
	m_typeRepoWidgetLayout->addWidget(m_typeRepoTitle);
	m_typeRepoWidgetLayout->addWidget(m_typeRepoContent);

	m_layout->addWidget(m_priorityDisplayWidget);
	m_layout->addWidget(m_typeRepoWidget);
}

void MemoTypeConfigView::close()
{
	// �������������裺
	// ����һ����MemoTypeMenu�ر�ʱ����ʱ��Ҫ����
	//       1.�б��Ƿ���Ҫ����Ui������Ҫ��������漰����MemoTypeWidget��Ui��
	//       2.���޸ļ�¼������m_oldNewMemoTypeMap�У�����Ѿ����޸ļ�¼����Ҫ�б𱾴��޸Ľ���Ƿ�����ԭ����MemoType��ͬ������ͬ��ɾ���˼�¼��������´˼�¼����
	// ���������MemoTypeConfigView�ر�ʱ����ʱ��Ҫ����
	//       1.�����漰����MemoSetting��Ui��
	//       2.�����ݿ�����޸�MemoType��
	for (MemoType* oldType : m_oldNewMemoTypeMap.keys())
	{
		MemoType* newType = m_oldNewMemoTypeMap[oldType];
		QSqlQuery updateQuery;
		updateQuery.prepare(
			"UPDATE memotype "
			"SET Name = :Name, Color = :Color, Label = :Label, Priority = :Priority "
			"WHERE ID = :ID; "
		);
		updateQuery.bindValue(":Name", newType->name);
		updateQuery.bindValue(":Color", newType->color.name());
		updateQuery.bindValue(":Label", newType->label.ID);
		updateQuery.bindValue(":Priority", newType->priority);
		updateQuery.bindValue(":ID", newType->ID);
		Database::exec(updateQuery);
	}
	qDeleteAll(m_oldNewMemoTypeMap);
	m_oldNewMemoTypeMap.clear();
	emit SignalClose();
	PopupWidget::close();
}

void MemoTypeConfigView::addPriorityType(MemoType& memoType)
{
	// �����嵥
	QFont labelFont = QFont("NeverMind", 10, QFont::Normal);

	MemoTypeWidget* priorityDisplayMemoTypeWidget = new MemoTypeWidget(memoType, m_priorityDisplayContent);
	connect(priorityDisplayMemoTypeWidget, &QPushButton::clicked, [this, priorityDisplayMemoTypeWidget, &memoType]()
		{
			QPoint shownPos = priorityDisplayMemoTypeWidget->mapToGlobal(QPoint(0, 0)) + QPoint(priorityDisplayMemoTypeWidget->width(), 0);
			showMemoTypeMenu(priorityDisplayMemoTypeWidget, shownPos);
		});
	m_priorityDisplayContentLayout->addWidget(priorityDisplayMemoTypeWidget);
	m_priorityDisplayMemoTypeWidgetMap.insert(&memoType, priorityDisplayMemoTypeWidget);
}

void MemoTypeConfigView::addTypeLabelAndType(const QString& labelName, QList<MemoType*>& typeList)
{
	// �����嵥
	QFont labelFont = QFont("NeverMind", 14, QFont::Normal);
	QFont typeFont = QFont("NeverMind", 10, QFont::Normal);
	
	QWidget* widget = new QWidget(m_typeRepoContent);
	widget->setFixedHeight(80);
	widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QHBoxLayout* widgetLayout = new QHBoxLayout(widget);
	widgetLayout->setContentsMargins(10, 0, 10, 0);
	widgetLayout->setSpacing(10);
	widgetLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	QLabel* label = new QLabel(QFontMetrics(labelFont).elidedText(labelName, Qt::ElideRight, 128), widget);
	label->setFixedSize(128, 24);
	label->setStyleSheet("border-right: 2px solid black");
	label->setFont(labelFont);

	widgetLayout->addWidget(label);
	for (MemoType* memoType : typeList)
	{
		MemoTypeWidget* memoTypeWidget = new MemoTypeWidget(*memoType, widget);
		widgetLayout->addWidget(memoTypeWidget);
		m_memoTypeWidgetMap.insert(memoType, memoTypeWidget);
	}
	m_typeRepoContentLayout->addWidget(widget);
}

void MemoTypeConfigView::showMemoTypeMenu(MemoTypeWidget* memoTypeWidget, const QPoint& shownPos)
{
	memoTypeWidget->blockSignals(true);
	MemoType& memoType = memoTypeWidget->getMemo();
	Menu* menu = new Menu(this);
	LineEditMenuItem* lineEditMenuItem = new LineEditMenuItem("Name", menu);
	lineEditMenuItem->setText(memoType.name);
	ColorPaletteMenuItem* colorPaletteMenuItem = new ColorPaletteMenuItem("Color", menu);
	colorPaletteMenuItem->setColor(memoType.color.name());
	// �������������裺
	// ����һ����MemoTypeMenu�ر�ʱ����ʱ��Ҫ����
	//       1.�б��Ƿ���Ҫ����Ui������Ҫ��������漰����MemoTypeWidget��Ui��
	//       2.���޸ļ�¼������m_oldNewMemoTypeMap�У�����Ѿ����޸ļ�¼����Ҫ�б𱾴��޸Ľ���Ƿ�����ԭ����MemoType��ͬ������ͬ��ɾ���˼�¼��������´˼�¼����
	// ���������MemoTypeConfigView�ر�ʱ����ʱ��Ҫ����
	//       1.�����漰����MemoSetting��Ui��
	//       2.�����ݿ�����޸�MemoType��
	// �����ǲ���һ��
	connect(menu, &Menu::SignalSaved, [&](QMap<QString, QString> resultMap)
		{
			MemoType* newType = new MemoType{ memoType.ID, memoType.name, memoType.color, memoType.label, memoType.priority };
			newType->name = resultMap["Name"];
			newType->color = QColor(resultMap["Color"]);
			if (newType != &memoType)
			{
				if (memoType.priority) m_priorityDisplayMemoTypeWidgetMap[&memoType]->updateUi(*newType);
				m_memoTypeWidgetMap[&memoType]->updateUi(*newType);
				// �޸ļ�¼��
				if (memoType.priority)
				{
					MemoType* newPriorityType = new MemoType{ newType->ID, newType->name, newType->color, newType->label, newType->priority };
					if (m_oldNewPriorityDisplayMemoTypeMap.contains(&memoType)) m_oldNewPriorityDisplayMemoTypeMap[&memoType] = newPriorityType;
					else m_oldNewPriorityDisplayMemoTypeMap.insert(&memoType, newPriorityType);
				}
				if (m_oldNewMemoTypeMap.contains(&memoType)) m_oldNewMemoTypeMap[&memoType] = newType;
				else m_oldNewMemoTypeMap.insert(&memoType, newType);
			}
			else
			{
				if (memoType.priority) if (m_oldNewPriorityDisplayMemoTypeMap.contains(&memoType)) m_oldNewPriorityDisplayMemoTypeMap.remove(&memoType);
				if (m_oldNewMemoTypeMap.contains(&memoType)) m_oldNewMemoTypeMap.remove(&memoType);
			}
			memoTypeWidget->blockSignals(false);
		});
	menu->addMenuItem(lineEditMenuItem);
	menu->addMenuItem(colorPaletteMenuItem);
	menu->move(shownPos);
	menu->show();
	menu->raise();
}