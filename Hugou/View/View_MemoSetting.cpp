#include "View_MemoSetting.h"

MemoSettingView::MemoSettingView(QWidget* parent, Memo memo)
	:QWidget(parent)
{
	setupUi();
	applyTemplate(memo.memoTemplate);
}

void MemoSettingView::setupUi()
{
	// 字体清单
	QFont templateTitleFont = QFont("NeverMind", 14, QFont::Medium);
	QFont templateButtonFont = QFont("NeverMind", 12, QFont::DemiBold);
	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(20, 10, 20, 10);
	m_layout->setSpacing(5);

	m_templateWidget = new QWidget(this);
	m_templateWidget->setFixedHeight(30);
	m_templateWidgetLayout = new QHBoxLayout(m_templateWidget);
	m_templateWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_templateWidgetLayout->setSpacing(10);
	m_templateTitle = new QLabel("Current Template:", m_templateWidget);
	m_templateTitle->setFont(templateTitleFont);
	m_templateButton = new QPushButton(m_templateWidget);
	m_templateButton->setFixedHeight(30);
	m_templateButton->setFont(templateButtonFont);
	m_templateWidgetLayout->addWidget(m_templateTitle);
	m_templateWidgetLayout->addWidget(m_templateButton);

	m_contentWidget = new QWidget(this);
	m_contentWidgetLayout = new QHBoxLayout(m_contentWidget);
	m_contentWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_contentWidgetLayout->setSpacing(20);

	m_layout->setAlignment(Qt::AlignLeft);
	m_layout->addWidget(m_templateWidget);
	m_layout->addWidget(m_contentWidget);
}

void MemoSettingView::applyTemplate(MemoTemplate memoTemplate)
{
	QColor color = memoTemplate.color;
	QString colorRGBAString = QString("rgba(%1, %2, %3, 0.2)").arg(color.red()).arg(color.green()).arg(color.blue());

	m_templateButton->setText(memoTemplate.name);
	this->setObjectName(memoTemplate.name);
	this->setStyleSheet(QString(
		"QWidget #%1 {border-left: 4px solid %2; background-color: %3}"
	).arg(memoTemplate.name).arg(color.name()).arg(colorRGBAString));
	m_templateButton->setStyleSheet(QString(
		"border-radius: 15px; background-color: %1; color:white; padding-left: 10px; padding-right: 10px"
	).arg(color.name()));
	for (MemoSettingItemType itemType : memoTemplate.templateContent)
		addMemoSettingItem(itemType);
}

void MemoSettingView::addMemoSettingItem(MemoSettingItemType itemType)
{
	QWidget* widget = nullptr;
	switch (itemType)
	{
	case MemoSettingItemType::Type:
		widget = new MemoTypeItem(this);
		break;
	case MemoSettingItemType::Time:
		break;
	case MemoSettingItemType::Importance:
		break;
	case MemoSettingItemType::Detail:
		break;
	case MemoSettingItemType::SubMemo:
		break;
	case MemoSettingItemType::Award:
		break;
	case MemoSettingItemType::Reference:
		break;
	default:
		break;
	}
	if (widget)
	{
		m_memoContentMap.insert(itemType, widget);
		m_contentWidgetLayout->addWidget(widget);
	}
}

MemoSettingView::MemoSettingItem::MemoSettingItem(QWidget* parent)
	:QWidget(parent)
{
	setupUi();
}

void MemoSettingView::MemoSettingItem::setupUi()
{
	// 字体清单
	QFont titleFont = QFont("NeverMind", 14, QFont::Medium);

	m_itemLayout = new QVBoxLayout(this);
	m_itemLayout->setContentsMargins(0, 0, 0, 0);
	m_itemLayout->setSpacing(4);
	m_itemLayout->setAlignment(Qt::AlignLeft);

	m_title = new QLabel(this);
	m_title->setFont(titleFont);

	m_content = new QWidget(this);

	m_itemLayout->addWidget(m_title);
}

void MemoSettingView::MemoSettingItem::setTitle(QString title)
{
	m_title->setText(title);
}

void MemoSettingView::MemoSettingItem::setContent(QWidget* content)
{
	m_itemLayout->addWidget(content);
}

MemoSettingView::MemoTypeItem::MemoTypeItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
}

void MemoSettingView::MemoTypeItem::setupUi()
{
	setTitle("Type");

	m_content->setFixedHeight(76);
	m_contentLayout = new QHBoxLayout(m_content);
	m_contentLayout->setContentsMargins(10, 10, 10, 10);
	m_contentLayout->setSpacing(10);

	setContent(m_content);
}

void MemoSettingView::MemoTypeItem::addMemoType(MemoType memoType)
{
	// 字体清单
	QFont labelFont = QFont("NeverMind", 12, QFont::Medium);

	QWidget* memoTypeWidget = new QWidget(m_content);
	memoTypeWidget->setFixedSize(36, 56);
	QVBoxLayout* memoTypeWidgetLayout = new QVBoxLayout(memoTypeWidget);
	memoTypeWidgetLayout->setContentsMargins(0, 0, 0, 0);
	memoTypeWidgetLayout->setSpacing(0);
	QWidget* icon = new QWidget(memoTypeWidget);
	icon->setFixedSize(36, 36);
	icon->setStyleSheet(QString("{background-color: %1; border-radius: 5}").arg(memoType.color.name()));
	QLabel* label = new QLabel(memoType.name, memoTypeWidget);
	label->setFont(labelFont);

	memoTypeWidgetLayout->setAlignment(Qt::AlignHCenter);
	memoTypeWidgetLayout->addWidget(icon);
	memoTypeWidgetLayout->addWidget(label);
}