#include "View/Include/View_MemoSetting.h"

MemoSettingView::MemoSettingView(QWidget* parent, Memo* memo)
	:QWidget(parent), m_memo(memo)
{
	setupUi();
	m_templateWidget->hide();
	m_contentWidget->hide();
	setMinimumHeight(0);
}

void MemoSettingView::setupUi()
{
	// 字体清单
	QFont templateTitleFont = QFont("NeverMind", 12, QFont::Medium);
	QFont templateButtonFont = QFont("NeverMind", 10, QFont::DemiBold);

	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(41, 0, 5, 0);

	m_baseWidget = new QWidget(this);
	m_layout->addWidget(m_baseWidget);

	m_baselayout = new QVBoxLayout(m_baseWidget);
	m_baselayout->setSpacing(5);
	m_baselayout->setContentsMargins(20, 0, 20, 0);
	m_templateWidget = new QWidget(m_baseWidget);
	m_templateWidget->setFixedHeight(25);
	m_templateWidgetEffect = new QGraphicsOpacityEffect(m_templateWidget);
	m_templateWidgetEffect->setOpacity(0);
	m_templateWidget->setGraphicsEffect(m_templateWidgetEffect);
	m_templateWidgetEffect->setEnabled(false);
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
	m_saveButton = new QPushButton("Save", m_templateWidget);
	m_saveButton->setFixedHeight(24);
	m_saveButton->setFont(templateButtonFont);
	m_saveButton->setCursor(Qt::PointingHandCursor);

	m_templateWidgetLayout->addWidget(m_templateTitle);
	m_templateWidgetLayout->addWidget(m_templateButton);
	m_templateWidgetLayout->addStretch();
	m_templateWidgetLayout->addWidget(m_saveButton);

	m_contentWidget = new QWidget(m_baseWidget);
	m_contentWidgetLayout = new QHBoxLayout(m_contentWidget);
	m_contentWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_contentWidgetLayout->setSpacing(20);
	m_contentWidgetLayout->setAlignment(Qt::AlignLeft);
	m_contentWidgetEffect = new QGraphicsOpacityEffect(m_contentWidget);
	m_contentWidgetEffect->setOpacity(0);
	m_contentWidget->setGraphicsEffect(m_contentWidgetEffect);
	m_contentWidgetEffect->setEnabled(false);

	m_baselayout->setAlignment(Qt::AlignLeft);
	m_baselayout->addWidget(m_templateWidget);
	m_baselayout->addWidget(m_contentWidget);
}

void MemoSettingView::applyGeneralStyle(const MemoTemplate& memoTemplate)
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
	m_saveButton->setStyleSheet(m_templateButton->styleSheet());
}

void MemoSettingView::addMemoSettingItemToLayout(QWidget* widget)
{
	int height = widget->height();  // 即将加入的控件的高度
	// 将当前页面已经占用的高度拟加上即将加入的控件的高度：
	// 如果超过了当前页面的最大高度，则生成新的页面；
	// 否则，将控件加入当前页面。
	if (m_occupiedHeight + height > m_maxPageHeight)
	{
		m_occupiedHeight = 20 + height;
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

void MemoSettingView::generateNewPage()
{
	m_pageNum++;
	QWidget* newPage = new QWidget(m_contentWidget);
	newPage->setFixedWidth(330);
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
	m_templateWidgetEffect->setEnabled(true);
	m_contentWidgetEffect->setEnabled(true);
}

void MemoSettingView::disableGraphicEffect()
{
	m_templateWidgetEffect->setEnabled(false);
	m_contentWidgetEffect->setEnabled(false);
}

QParallelAnimationGroup* MemoSettingView::fadeIn()
{
	m_baselayout->setContentsMargins(20, 10, 20, 10);
	m_templateWidget->show();
	m_contentWidget->show();
	enableGraphicEffect();
	QParallelAnimationGroup* group = new QParallelAnimationGroup;
	QPropertyAnimation* templateWidgetFadeInAnimation = new QPropertyAnimation(m_templateWidgetEffect, "opacity", m_templateWidget);
	templateWidgetFadeInAnimation->setStartValue(0);
	templateWidgetFadeInAnimation->setEndValue(1);
	templateWidgetFadeInAnimation->setDuration(100);
	QPropertyAnimation* contentWidgetFadeInAnimation = new QPropertyAnimation(m_contentWidgetEffect, "opacity", m_contentWidget);
	contentWidgetFadeInAnimation->setStartValue(0);
	contentWidgetFadeInAnimation->setEndValue(1);
	contentWidgetFadeInAnimation->setDuration(100);
	group->addAnimation(templateWidgetFadeInAnimation);
	group->addAnimation(contentWidgetFadeInAnimation);
	connect(group, &QParallelAnimationGroup::finished, this, &MemoSettingView::disableGraphicEffect);
	return group;
}

QParallelAnimationGroup* MemoSettingView::fadeOut()
{
	enableGraphicEffect();
	QParallelAnimationGroup* group = new QParallelAnimationGroup;
	QPropertyAnimation* templateWidgetFadeOutAnimation = new QPropertyAnimation(m_templateWidgetEffect, "opacity", m_templateWidget);
	templateWidgetFadeOutAnimation->setStartValue(1);
	templateWidgetFadeOutAnimation->setEndValue(0);
	templateWidgetFadeOutAnimation->setDuration(100);
	QPropertyAnimation* contentWidgetFadeOutAnimation = new QPropertyAnimation(m_contentWidgetEffect, "opacity", m_contentWidget);
	contentWidgetFadeOutAnimation->setStartValue(1);
	contentWidgetFadeOutAnimation->setEndValue(0);
	contentWidgetFadeOutAnimation->setDuration(100);
	group->addAnimation(templateWidgetFadeOutAnimation);
	group->addAnimation(contentWidgetFadeOutAnimation);
	connect(group, &QParallelAnimationGroup::finished, [this]()
		{
			m_baselayout->setContentsMargins(20, 0, 20, 0);
			m_templateWidget->hide();
			m_contentWidget->hide();
		});
	return group;
}

void MemoSettingView::check()
{

}

void MemoSettingView::paintEvent(QPaintEvent* event) {
	QStyleOption opt;
	opt.initFrom(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}