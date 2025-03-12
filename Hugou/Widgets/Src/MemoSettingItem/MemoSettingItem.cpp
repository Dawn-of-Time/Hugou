#include "Widgets/Include/MemoSettingItem/MemoSettingItem.h"

MemoSettingItem::MemoSettingItem(QWidget* parent)
	:QWidget(parent)
{
	setupUi();
}

void MemoSettingItem::setupUi()
{
	// 字体清单
	QFont titleFont = QFont("NeverMind", 14, QFont::Medium);

	setFixedWidth(304);
	m_itemLayout = new QVBoxLayout(this);
	m_itemLayout->setContentsMargins(0, 0, 0, 0);
	m_itemLayout->setSpacing(5);
	m_itemLayout->setAlignment(Qt::AlignLeft);

	m_titleWidget = new QWidget(this);
	m_titleWidget->setFixedHeight(25);
	m_titleLayout = new QHBoxLayout(m_titleWidget);
	m_titleLayout->setContentsMargins(0, 0, 0, 0);
	m_titleLayout->setSpacing(0);

	m_title = new QLabel(m_titleWidget);
	m_title->setFont(titleFont);
	m_title->setFixedHeight(25);

	m_titleLayout->addWidget(m_title);
	m_titleLayout->addStretch();

	m_content = new QWidget(this);
	m_content->setObjectName("memoSettingItemContent");
	m_content->setStyleSheet("QWidget #memoSettingItemContent{background-color: rgba(255, 255, 255, 0.5); border-radius: 10px}");

	m_itemLayout->addWidget(m_titleWidget);
	m_itemLayout->addWidget(m_content);
}



MemoImportanceAndUrgencyItem::MemoImportanceAndUrgencyItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
	connect(m_topLeftButton, &QPushButton::clicked, this, &MemoImportanceAndUrgencyItem::select);
	connect(m_topRightButton, &QPushButton::clicked, this, &MemoImportanceAndUrgencyItem::select);
	connect(m_bottomLeftButton, &QPushButton::clicked, this, &MemoImportanceAndUrgencyItem::select);
	connect(m_bottomRightButton, &QPushButton::clicked, this, &MemoImportanceAndUrgencyItem::select);
}

void MemoImportanceAndUrgencyItem::setupUi()
{
	// 字体清单
	QFont labelFont = QFont("NeverMind", 10, QFont::Medium);

	setFixedHeight(160);
	m_title->setText("Importance & Urgency");

	m_content->setFixedHeight(130);
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(2, 0, 2, 0);
	m_contentLayout->setSpacing(0);

	m_topWidget = new QWidget(m_content);
	m_topWidget->setFixedSize(300, 20);
	m_importantLabel = new QLabel("Important", m_topWidget);
	m_importantLabel->setFixedSize(76, 20);
	m_importantLabel->move(112, 0);
	m_importantLabel->setFont(labelFont);

	m_middleWidget = new QWidget(m_content);
	m_middleWidget->setFixedSize(300, 90);

	m_leftWidget = new QWidget(m_middleWidget);
	m_leftWidget->setFixedSize(55, 90);
	m_leftWidget->move(0, 0);
	m_notUrgentLabel = new QLabel("Not\nUrgent", m_leftWidget);
	m_notUrgentLabel->setFixedSize(55, 40);
	m_notUrgentLabel->move(0, 25);
	m_notUrgentLabel->setFont(labelFont);
	m_notUrgentLabel->setAlignment(Qt::AlignHCenter);
	
	m_matrixWidget = new QWidget(m_middleWidget);
	m_matrixWidget->setFixedSize(190, 90);
	m_matrixWidget->move(55, 0);

	m_topLeftButton = new QPushButton(m_matrixWidget);
	m_topLeftButton->resize(90, 40);
	m_topLeftButton->setStyleSheet("background-color: rgba(168, 229, 159, 0.5); border: none");
	m_topLeftButton->move(0, 0);
	m_topLine = new QWidget(m_matrixWidget);
	m_topLine->resize(10, 40);
	m_topLine->move(90, 0);
	m_topRightButton = new QPushButton(m_matrixWidget);
	m_topRightButton->resize(90, 40);
	m_topRightButton->setStyleSheet("background-color: rgba(236, 164, 164, 0.5); border: none");
	m_topRightButton->move(100, 0);

	m_leftLine = new QWidget(m_matrixWidget);
	m_leftLine->resize(90, 10);
	m_leftLine->move(0, 40);
	m_centralLine = new QWidget(m_matrixWidget);
	m_centralLine->resize(10, 10);
	m_centralLine->move(90, 40);
	m_rightLine = new QWidget(m_matrixWidget);
	m_rightLine->resize(90, 10);
	m_rightLine->move(100, 40);

	m_bottomLeftButton = new QPushButton(m_matrixWidget);
	m_bottomLeftButton->resize(90, 40);
	m_bottomLeftButton->setStyleSheet("background-color: rgba(139, 205, 246, 0.5); border: none");
	m_bottomLeftButton->move(0, 50);
	m_bottomLine = new QWidget(m_matrixWidget);
	m_bottomLine->resize(10, 40);
	m_bottomLine->move(90, 50);
	m_bottomRightButton = new QPushButton(m_matrixWidget);
	m_bottomRightButton->resize(90, 40);
	m_bottomRightButton->setStyleSheet("background-color: rgba(231, 240, 149, 0.5); border: none");
	m_bottomRightButton->move(100, 50);

	m_rightWidget = new QWidget(m_middleWidget);
	m_rightWidget->setFixedSize(55, 90);
	m_rightWidget->move(245, 0);
	m_urgentLabel = new QLabel("Urgent", m_rightWidget);
	m_urgentLabel->setFixedSize(55, 20);
	m_urgentLabel->move(0, 35);
	m_urgentLabel->setFont(labelFont);

	m_bottomWidget = new QWidget(m_content);
	m_bottomWidget->setFixedSize(300, 20);
	m_notImportantLabel = new QLabel("Not Important", m_bottomWidget);
	m_notImportantLabel->setFixedSize(120, 20);
	m_notImportantLabel->move(90, 0);
	m_notImportantLabel->setFont(labelFont);

	QString labelStyleSheet = "color: #ACB1C6";
	m_importantLabel->setAlignment(Qt::AlignCenter);
	m_notImportantLabel->setAlignment(Qt::AlignCenter);
	m_urgentLabel->setAlignment(Qt::AlignCenter);
	m_notUrgentLabel->setAlignment(Qt::AlignCenter);
	m_importantLabel->setStyleSheet(labelStyleSheet);
	m_notImportantLabel->setStyleSheet(labelStyleSheet);
	m_urgentLabel->setStyleSheet(labelStyleSheet);
	m_notUrgentLabel->setStyleSheet(labelStyleSheet);

	m_contentLayout->addWidget(m_topWidget);
	m_contentLayout->addWidget(m_middleWidget);
	m_contentLayout->addWidget(m_bottomWidget);
}

void MemoImportanceAndUrgencyItem::select()
{
	QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
	bool isTop = false;
	bool isLeft = false;
	if (senderButton == m_topLeftButton) { isTop = true; isLeft = true; }
	if (senderButton == m_topRightButton) isTop = true;
	if (senderButton == m_bottomLeftButton) isLeft = true;
	QParallelAnimationGroup* group = new QParallelAnimationGroup;
	QPropertyAnimation* topLeftAnimation = new QPropertyAnimation(m_topLeftButton, "geometry");
	QPropertyAnimation* topAnimation = new QPropertyAnimation(m_topLine, "geometry");
	QPropertyAnimation* topRightAnimation = new QPropertyAnimation(m_topRightButton, "geometry");
	QPropertyAnimation* leftAnimation = new QPropertyAnimation(m_leftLine, "geometry");
	QPropertyAnimation* centralAnimation = new QPropertyAnimation(m_centralLine, "geometry");
	QPropertyAnimation* rightAnimation = new QPropertyAnimation(m_rightLine, "geometry");
	QPropertyAnimation* bottomLeftAnimation = new QPropertyAnimation(m_bottomLeftButton, "geometry");
	QPropertyAnimation* bottomAnimation = new QPropertyAnimation(m_bottomLine, "geometry");
	QPropertyAnimation* bottomRightAnimation = new QPropertyAnimation(m_bottomRightButton, "geometry");
	
	QString labelDefaultStyleSheet = "color: #ACB1C6";
	QString labelCurrentStyleSheet = "color: #468DFA";
	QString topLeftDefaultStyleSheet = "background-color: rgba(168, 229, 159, 0.5); border: none";
	QString topLeftCurrentStyleSheet = "background-color: rgb(168, 229, 159); border: none";
	QString topRightDefaultStyleSheet = "background-color: rgba(236, 164, 164, 0.5); border: none";
	QString topRightCurrentStyleSheet = "background-color: rgb(236, 164, 164); border: none";
	QString bottomLeftDefaultStyleSheet = "background-color: rgba(139, 205, 246, 0.5); border: none";
	QString bottomLeftCurrentStyleSheet = "background-color: rgb(139, 205, 246); border: none";
	QString bottomRightDefaultStyleSheet = "background-color: rgba(231, 240, 149, 0.5); border: none";
	QString bottomRightCurrentStyleSheet = "background-color: rgb(231, 240, 149); border: none";
	m_importantLabel->setStyleSheet(isTop ? labelCurrentStyleSheet : labelDefaultStyleSheet);
	m_notImportantLabel->setStyleSheet(isTop ? labelDefaultStyleSheet : labelCurrentStyleSheet);
	m_urgentLabel->setStyleSheet(isLeft ? labelDefaultStyleSheet : labelCurrentStyleSheet);
	m_notUrgentLabel->setStyleSheet(isLeft ? labelCurrentStyleSheet : labelDefaultStyleSheet);
	m_topLeftButton->setStyleSheet((isLeft && isTop) ? topLeftCurrentStyleSheet : topLeftDefaultStyleSheet);
	m_topRightButton->setStyleSheet((!isLeft && isTop) ? topRightCurrentStyleSheet : topRightDefaultStyleSheet);
	m_bottomLeftButton->setStyleSheet((isLeft && !isTop) ? bottomLeftCurrentStyleSheet : bottomLeftDefaultStyleSheet);
	m_bottomRightButton->setStyleSheet((!isLeft && !isTop) ? bottomRightCurrentStyleSheet : bottomRightDefaultStyleSheet);
	
	topLeftAnimation->setEndValue(QRect(0, 0, isLeft ? 147 : 33, isTop ? 60 : 20));
	topLeftAnimation->setDuration(300);
	topLeftAnimation->setEasingCurve(QEasingCurve::OutQuad);
	topAnimation->setEndValue(QRect(isLeft ? 147 : 33, 0, 10, isTop ? 60 : 20));
	topAnimation->setDuration(300);
	topAnimation->setEasingCurve(QEasingCurve::OutQuad);
	topRightAnimation->setEndValue(QRect(isLeft ? 157 : 43, 0, isLeft ? 33 : 147, isTop ? 60 : 20));
	topRightAnimation->setDuration(300);
	topRightAnimation->setEasingCurve(QEasingCurve::OutQuad);
	leftAnimation->setEndValue(QRect(0, isTop? 60 : 20, isLeft ? 147 : 33, 10));
	leftAnimation->setDuration(300);
	leftAnimation->setEasingCurve(QEasingCurve::OutQuad);
	centralAnimation->setEndValue(QRect(isLeft ? 20 : 180, isTop ? 60 : 20, 10, 10));
	centralAnimation->setDuration(300);
	centralAnimation->setEasingCurve(QEasingCurve::OutQuad);
	rightAnimation->setEndValue(QRect(isLeft ? 157 : 43, isTop ? 60 : 20, isLeft ? 33 : 147, 10));
	rightAnimation->setDuration(300);
	rightAnimation->setEasingCurve(QEasingCurve::OutQuad);
	bottomLeftAnimation->setEndValue(QRect(0, isTop ? 70 : 30, isLeft ? 147 : 33, isTop ? 20 : 60));
	bottomLeftAnimation->setDuration(300);
	bottomLeftAnimation->setEasingCurve(QEasingCurve::OutQuad);
	bottomAnimation->setEndValue(QRect(isLeft ? 147 : 33, 0, 10, isTop ? 20 : 60));
	bottomAnimation->setDuration(300);
	bottomAnimation->setEasingCurve(QEasingCurve::OutQuad);
	bottomRightAnimation->setEndValue(QRect(isLeft ? 157 : 43, isTop ? 70 : 30, isLeft ? 33 : 147, isTop ? 20 : 60));
	bottomRightAnimation->setDuration(300);
	bottomRightAnimation->setEasingCurve(QEasingCurve::OutQuad);
	group->addAnimation(topLeftAnimation);
	group->addAnimation(topAnimation);
	group->addAnimation(topRightAnimation);
	group->addAnimation(leftAnimation);
	group->addAnimation(centralAnimation);
	group->addAnimation(rightAnimation);
	group->addAnimation(bottomLeftAnimation);
	group->addAnimation(bottomAnimation);
	group->addAnimation(bottomRightAnimation);
	connect(group, &QParallelAnimationGroup::finished, group, &QParallelAnimationGroup::clear);
	group->start(QParallelAnimationGroup::DeleteWhenStopped);
}

MemoDetailItem::MemoDetailItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
}

void MemoDetailItem::setupUi()
{
	// 字体清单
	QFont detailFont = QFont("NeverMind", 12, QFont::Normal);

	resize(304, 80);
	setMinimumHeight(80);

	m_title->setText("Detail");
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(12, 5, 12, 5);
	m_contentLayout->setSpacing(0);

	m_detail = new QTextEdit(m_content);
	m_detail->setAcceptRichText(false);
	m_detail->setUndoRedoEnabled(true);
	m_detail->setFont(detailFont);
	m_detail->setStyleSheet("background-color: transparent; border: none");

	m_contentLayout->addWidget(m_detail);
}

MemoSubMemoItem::MemoSubMemoItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
}

void MemoSubMemoItem::setupUi()
{
	// 字体清单
	QFont numberFont = QFont("NeverMind", 10, QFont::Medium);
	QFont contentFont = QFont("NeverMind", 12, QFont::Normal);

	resize(304, 60);
	setMinimumHeight(60);

	m_title->setText("SubMemo");
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(12, 5, 12, 5);
	m_contentLayout->setSpacing(10);

	m_addSubMemoWidget = new QWidget(m_content);
	m_addSubMemoWidget->setFixedHeight(20);
	m_addSubMemoWidgetLayout = new QHBoxLayout(m_addSubMemoWidget);
	m_addSubMemoWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_addSubMemoWidgetLayout->setSpacing(8);

	m_subMemoNumber = new QLabel(QString::number(m_count + 1), m_addSubMemoWidget);
	m_subMemoNumber->setFixedSize(18, 18);
	m_subMemoNumber->setFont(numberFont);
	m_subMemoNumber->setAlignment(Qt::AlignCenter);
	m_subMemoNumber->setStyleSheet("background-color: #AEE4FD; border-radius: 9px");
	m_subMemoContent = new QLineEdit(m_addSubMemoWidget);
	m_subMemoContent->setFixedHeight(20);
	m_subMemoContent->setPlaceholderText("Click to add subMemo.");
	m_subMemoContent->setFont(numberFont);
	m_subMemoContent->setStyleSheet("border: none; background-color: transparent");
	m_addSubMemoWidgetLayout->addWidget(m_subMemoNumber);
	m_addSubMemoWidgetLayout->addWidget(m_subMemoContent);
	m_contentLayout->addWidget(m_addSubMemoWidget);
}


MemoAwardItem::MemoAwardItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
}

void MemoAwardItem::setupUi()
{
	// 字体清单
	QFont addAwardContentFont = QFont("NeverMind", 10, QFont::Medium);
	QFont addAwardSubContentFont = QFont("NeverMind", 8, QFont::Normal);

	resize(304, 80);

	m_title->setText("Award");
	m_content->setObjectName("awardContent");
	m_content->setStyleSheet("QWidget #awardContent {border-radius: 10px; background-color: rgba(255, 255, 255, 0.5)}");
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(12, 5, 12, 5);
	m_contentLayout->setSpacing(0);

	m_addAwardContent = new QLabel(tr("How to motivate yourself?"), m_content);
	m_addAwardContent->setFixedHeight(20);
	m_addAwardContent->setFont(addAwardContentFont);
	m_addAwardContent->setStyleSheet("color: #4F5E71");

	m_addAwardSubContent = new QLabel(tr("Click to add awards from the award repo."), m_content);
	m_addAwardSubContent->setFixedHeight(20);
	m_addAwardSubContent->setFont(addAwardSubContentFont);
	m_addAwardSubContent->setStyleSheet("color: #ACB1C6");

	m_contentLayout->addWidget(m_addAwardContent);
	m_contentLayout->addWidget(m_addAwardSubContent);
}

MemoReferenceItem::MemoReferenceItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
}

void MemoReferenceItem::setupUi()
{
	// 字体清单
	QFont addReferenceContentFont = QFont("NeverMind", 10, QFont::Medium);
	QFont addReferenceSubContentFont = QFont("NeverMind", 8, QFont::Normal);

	resize(304, 80);

	m_title->setText("Reference");
	m_content->setObjectName("referenceContent");
	m_content->setStyleSheet("QWidget #referenceContent {border-radius: 10px; background-color: rgba(255, 255, 255, 0.5)}");
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(12, 5, 12, 5);
	m_contentLayout->setSpacing(0);

	m_addReferenceContent = new QLabel(tr("What references are needed?"), m_content);
	m_addReferenceContent->setFixedHeight(20);
	m_addReferenceContent->setFont(addReferenceContentFont);
	m_addReferenceContent->setStyleSheet("color: #4F5E71");

	m_addReferenceSubContent = new QLabel(tr("Click to add References from the Reference repo."), m_content);
	m_addReferenceSubContent->setFixedHeight(20);
	m_addReferenceSubContent->setFont(addReferenceSubContentFont);
	m_addReferenceSubContent->setStyleSheet("color: #ACB1C6");

	m_contentLayout->addWidget(m_addReferenceContent);
	m_contentLayout->addWidget(m_addReferenceSubContent);
}


void MemoSettingItem::paintEvent(QPaintEvent* event) {
	QStyleOption opt;
	opt.initFrom(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
