#include "View_MemoTypeConfig.h"

MemoTypeConfigView::MemoTypeConfigView(QWidget* parent)
	:PopupWidget("Memo Type", parent)
{
	setupUi();
}

void MemoTypeConfigView::setupUi()
{
	// 字体清单
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
	m_priorityDisplayContent->setFixedHeight(90);
	m_priorityDisplayContent->setStyleSheet("background-color: #AEE4FD; border-radius: 5px");
	m_priorityDisplayContentLayout = new QHBoxLayout(m_priorityDisplayContent);
	m_priorityDisplayContentLayout->setContentsMargins(50, 15, 50, 15);
	m_priorityDisplayWidgetLayout->addWidget(m_priorityDisplayTitle);
	m_priorityDisplayWidgetLayout->addWidget(m_priorityDisplayContent);

	m_typeRepoWidget = new QWidget(m_centralWidget);
	m_typeRepoWidget->setFixedSize(780, 130);
	m_typeRepoWidgetLayout = new QVBoxLayout(m_typeRepoWidget);
	m_typeRepoWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_typeRepoWidgetLayout->setSpacing(10);
	m_typeRepoTitle = new QLabel("Type Repo", m_typeRepoWidget);
	m_typeRepoTitle->setFixedHeight(30);
	m_typeRepoTitle->setFont(titleFont);
	m_typeRepoContent = new QWidget(m_centralWidget);
	m_typeRepoContent->setFixedHeight(90);
	m_typeRepoContentLayout = new QVBoxLayout(m_typeRepoContent);
	m_typeRepoContentLayout->setContentsMargins(50, 15, 50, 15);
	m_typeRepoWidgetLayout->addWidget(m_typeRepoTitle);
	m_typeRepoWidgetLayout->addWidget(m_typeRepoContent);

	m_layout->addWidget(m_priorityDisplayWidget);
	m_layout->addWidget(m_typeRepoWidget);
}

void MemoTypeConfigView::addPriorityType(MemoType* memoType)
{
	// 字体清单
	QFont labelFont = QFont("NeverMind", 10, QFont::Normal);

	QWidget* priorityDisplayMemoTypeWidget = new QWidget(m_priorityDisplayContent);
	priorityDisplayMemoTypeWidget->setFixedSize(36, 60);
	QVBoxLayout* priorityDisplayMemoTypeWidgetLayout = new QVBoxLayout(priorityDisplayMemoTypeWidget);
	priorityDisplayMemoTypeWidgetLayout->setContentsMargins(0, 0, 0, 0);
	priorityDisplayMemoTypeWidgetLayout->setSpacing(4);
	QLabel* icon = new QLabel(priorityDisplayMemoTypeWidget);
	icon->setAlignment(Qt::AlignCenter);
	icon->setFixedSize(36, 36);
	icon->setStyleSheet(QString("background-color: %1; border-radius: 5px").arg(memoType->color.name()));
	QLabel* label = new QLabel(memoType->name, priorityDisplayMemoTypeWidget);
	label->setAlignment(Qt::AlignHCenter);
	label->setFixedSize(36, 20);
	label->setFont(labelFont);

	priorityDisplayMemoTypeWidgetLayout->setAlignment(Qt::AlignHCenter);
	priorityDisplayMemoTypeWidgetLayout->addWidget(icon);
	priorityDisplayMemoTypeWidgetLayout->addWidget(label);

	m_priorityDisplayContentLayout->addWidget(priorityDisplayMemoTypeWidget);
}

void MemoTypeConfigView::addTypeLabelAndType(QString labelName, QList<MemoType>* typeList)
{

}