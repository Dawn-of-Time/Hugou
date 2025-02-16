#include "View_MemoSetting.h"

MemoSettingView::MemoSettingView(QWidget* parent, Memo memo)
	:QWidget(parent), m_memo(memo)
{
	setupUi();
	hide();
}

void MemoSettingView::setupUi()
{
	// 字体清单
	QFont templateTitleFont = QFont("NeverMind", 12, QFont::Medium);
	QFont templateButtonFont = QFont("NeverMind", 10, QFont::DemiBold);

	m_effect = new QGraphicsOpacityEffect(this);
	m_effect->setOpacity(0);
	this->setGraphicsEffect(m_effect);
	m_effect->setEnabled(false);

	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(41, 0, 0, 0);

	m_baseWidget = new QWidget(this);
	m_layout->addWidget(m_baseWidget);

	m_baselayout = new QVBoxLayout(m_baseWidget);
	m_baselayout->setContentsMargins(20, 10, 20, 10);
	m_baselayout->setSpacing(5);

	m_templateWidget = new QWidget(m_baseWidget);
	m_templateWidget->setFixedHeight(25);
	m_templateWidgetLayout = new QHBoxLayout(m_templateWidget);
	m_templateWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_templateWidgetLayout->setSpacing(10);
	m_templateTitle = new QLabel("Current Template:", m_templateWidget);
	m_templateTitle->setFont(templateTitleFont);
	m_templateTitle->setStyleSheet("color: #252A31");
	m_templateButton = new QPushButton(m_templateWidget);
	m_templateButton->setFixedHeight(24);
	m_templateButton->setFont(templateButtonFont);
	m_templateButton->setCursor(Qt::PointingHandCursor);

	m_templateWidgetLayout->addWidget(m_templateTitle);
	m_templateWidgetLayout->addWidget(m_templateButton);
	m_templateWidgetLayout->addStretch();

	m_area = new QScrollArea(m_baseWidget);
	m_area->setObjectName("scrollArea");
	m_area->setStyleSheet("QWidget #scrollArea { background-color: transparent}");
	m_area->setWidgetResizable(true);

	m_contentWidget = new QWidget(m_area);
	m_contentWidgetLayout = new QHBoxLayout(m_contentWidget);
	m_contentWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_contentWidgetLayout->setSpacing(20);
	m_contentWidgetLayout->setAlignment(Qt::AlignLeft);
	generateNewPage();
	for (MemoSettingItemType itemType : m_memo.memoTemplate.templateContent)
		addMemoSettingItem(itemType);

	m_area->setWidget(m_contentWidget);
	//m_area->setMaximumHeight(getSuitableHeight());

	m_baselayout->setAlignment(Qt::AlignLeft);
	m_baselayout->addWidget(m_templateWidget);
	m_baselayout->addWidget(m_area);

	setMaximumHeight(25 + getSuitableHeight());
}

void MemoSettingView::applyGeneralStyle(MemoTemplate memoTemplate)
{
	QColor color = memoTemplate.color;
	QString colorRGBAString = QString("rgba(%1, %2, %3, 0.2)").arg(color.red()).arg(color.green()).arg(color.blue());

	m_baseWidget->setObjectName(memoTemplate.name + "Memo");
	m_baseWidget->setStyleSheet(QString(
		"QWidget #%1Memo {"
		"background-color: %2; "
		"border-radius: 10px;"
		"}"
	).arg(memoTemplate.name).arg(colorRGBAString));

	m_contentWidget->setObjectName(memoTemplate.name + "Content");
	m_contentWidget->setStyleSheet(QString(
		"QWidget #%1Content {border-radius: 5px; background-color: rgba(255, 255, 255, 0.4)}"
	).arg(memoTemplate.name)
	);

	m_templateButton->setObjectName(memoTemplate.name + "TemplateButton");
	m_templateButton->setText(memoTemplate.name);
	m_templateButton->setStyleSheet(QString(
		"border-radius: 12px; "
		"background-color: %1; "
		"color:white; "
		"padding-left: 10px; "
		"padding-right: 10px"
	).arg(color.name()));
}

QWidget* MemoSettingView::addMemoSettingItem(MemoSettingItemType itemType)
{
	QWidget* widget = nullptr;
	switch (itemType)
	{
	case MemoSettingItemType::Type:
		widget = new MemoTypeItem();
		break;
	case MemoSettingItemType::Time:
		widget = new MemoTimeItem();
		break;
	case MemoSettingItemType::ImportanceAndUrgency:
		widget = new MemoImportanceAndUrgencyItem();
		break;
	case MemoSettingItemType::Detail:
		widget = new MemoDetailItem();
		break;
	case MemoSettingItemType::SubMemo:
		widget = new MemoSubMemoItem();
		break;
	case MemoSettingItemType::Award:
		widget = new MemoAwardItem();
		break;
	case MemoSettingItemType::Reference:
		widget = new MemoReferenceItem();
		break;
	default:
		break;
	}
	if (widget)
	{
		m_memoContentMap.insert(itemType, widget);
		int height = widget->height();  // 即将加入的控件的高度
		// 将当前页面已经占用的高度拟加上即将加入的控件的高度：
		// 如果超过了当前页面的最大高度，则生成新的页面；
		// 否则，将控件加入当前页面。
		if (m_occupiedHeight + height > m_maxPageHeight)
		{
			m_occupiedHeight = 10 + height;
			generateNewPage();
		}
		else
		{
			m_occupiedHeight = m_occupiedHeight + height + 10;	// 控件之间的间距为10
			if (m_occupiedHeight > m_pageSuitableHeight)
				m_pageSuitableHeight = m_occupiedHeight;
		}
		widget->setParent(m_pageList.last());
		m_pageList.last()->layout()->addWidget(widget);
	}
	return widget;
}

void MemoSettingView::generateNewPage()
{
	m_pageNum++;
	QWidget* newPage = new QWidget(m_contentWidget);
	newPage->setObjectName(QString("page%1").arg(m_pageNum));
	newPage->setFixedWidth(324);
	newPage->setMaximumHeight(m_maxPageHeight);
	QVBoxLayout* newPageLayout = new QVBoxLayout(newPage);
	newPageLayout->setContentsMargins(10, 10, 10, 10);
	newPageLayout->setSpacing(10);
	newPageLayout->setAlignment(Qt::AlignTop);
	m_contentWidgetLayout->addWidget(newPage);
	m_pageList.append(newPage);
}

void MemoSettingView::enableGraphicEffect()
{
	m_effect->setEnabled(true);
}

void MemoSettingView::disableGraphicEffect()
{
	m_effect->setEnabled(false);
}

void MemoSettingView::fadeIn()
{
	enableGraphicEffect();
	QPropertyAnimation* fadeInAnimation = new QPropertyAnimation(m_effect, "opacity", this);
	fadeInAnimation->setStartValue(0);
	fadeInAnimation->setEndValue(1);
	fadeInAnimation->setDuration(500);
	connect(fadeInAnimation, &QPropertyAnimation::finished, this, &MemoSettingView::disableGraphicEffect);
	fadeInAnimation->start(QPropertyAnimation::DeleteWhenStopped);
}

void MemoSettingView::paintEvent(QPaintEvent* event) {
	QStyleOption opt;
	opt.initFrom(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}