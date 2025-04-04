#include "Widgets/Include/MemoSettingItem/MemoImportanceAndUrgencyItem.h"

MemoImportanceAndUrgencyItem::MemoImportanceAndUrgencyItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
	adjust(m_topRightButton);
	connect(m_topLeftButton, &QPushButton::clicked, this, &MemoImportanceAndUrgencyItem::select);
	connect(m_topRightButton, &QPushButton::clicked, this, &MemoImportanceAndUrgencyItem::select);
	connect(m_bottomLeftButton, &QPushButton::clicked, this, &MemoImportanceAndUrgencyItem::select);
	connect(m_bottomRightButton, &QPushButton::clicked, this, &MemoImportanceAndUrgencyItem::select);
}

void MemoImportanceAndUrgencyItem::setupUi()
{
	// ×ÖÌåÇåµ¥
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
	m_topLeftButton->setCursor(Qt::PointingHandCursor);
	m_topLine = new QWidget(m_matrixWidget);
	m_topLine->resize(10, 40);
	m_topLine->move(90, 0);
	m_topRightButton = new QPushButton(m_matrixWidget);
	m_topRightButton->resize(90, 40);
	m_topRightButton->setStyleSheet("background-color: rgba(236, 164, 164, 0.5); border: none");
	m_topRightButton->move(100, 0);
	m_topRightButton->setCursor(Qt::PointingHandCursor);

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
	m_bottomLeftButton->setCursor(Qt::PointingHandCursor);
	m_bottomLine = new QWidget(m_matrixWidget);
	m_bottomLine->resize(10, 40);
	m_bottomLine->move(90, 50);
	m_bottomRightButton = new QPushButton(m_matrixWidget);
	m_bottomRightButton->resize(90, 40);
	m_bottomRightButton->setStyleSheet("background-color: rgba(231, 240, 149, 0.5); border: none");
	m_bottomRightButton->move(100, 50);
	m_bottomRightButton->setCursor(Qt::PointingHandCursor);

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
	if (senderButton == m_topLeftButton) m_memoImportanceAndUrgency = NotUrgentButImportant;
	else if (senderButton == m_topRightButton) m_memoImportanceAndUrgency = UrgentAndImportant;
	else if (senderButton == m_bottomLeftButton) m_memoImportanceAndUrgency = NotUrgentAndNotImportant;
	else m_memoImportanceAndUrgency = UrgentButNotImportant;
	adjust(senderButton);
}

void MemoImportanceAndUrgencyItem::adjust(QPushButton* button)
{
	bool isTop = false;
	bool isLeft = false;
	if (button == m_topLeftButton) { isTop = true; isLeft = true; }
	else if (button == m_topRightButton) isTop = true;
	else if (button == m_bottomLeftButton) isLeft = true;
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
	leftAnimation->setEndValue(QRect(0, isTop ? 60 : 20, isLeft ? 147 : 33, 10));
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