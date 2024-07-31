#include "FloatingNote.h"

FloatingNote::FloatingNote(QWidget* HugouClass) :
	QWidget(HugouClass)
{
	ui.setupUi(this);
	floatingNoteHiddenPos = QPoint(HugouClass->width(), titleFrameHeight);
	floatingNoteShownPos = QPoint(HugouClass->width() - floatingNoteWidth - 20, titleFrameHeight);
	this->move(floatingNoteHiddenPos); // 初始位置

	// 时长标签
	timer = new QElapsedTimer();
	timer->start();
	updateTimer = new QTimer();
	connect(updateTimer, &QTimer::timeout, this, &FloatingNote::SlotTimekeeping);
	updateTimer->start(1000);

	// 按钮事件
	connect(ui.yesButton, &QPushButton::clicked, this, [=]() {SlotButtonClicked(Feedback::Yes); });
	connect(ui.noButton, &QPushButton::clicked, this, [=]() {SlotButtonClicked(Feedback::No); });
	connect(ui.dealLaterButton, &QPushButton::clicked, this, [=]() {SlotButtonClicked(Feedback::DealLater); });
}

FloatingNote::~FloatingNote()
{}

void FloatingNote::updateUI()
{
	ui.sign->setIcon(typeIcon.at(type));
	ui.sign->setText(typeText.at(type));
	ui.noButton->setVisible(false);
	ui.noButton->setEnabled(false);
	ui.dealLaterButton->setVisible(true);
	ui.dealLaterButton->setEnabled(true);
	// Dialog
	if (type == Type::Dialog) {
		ui.noButton->setVisible(true);
		ui.noButton->setEnabled(true);
		ui.dealLaterButton->setVisible(false);
		ui.dealLaterButton->setEnabled(false);
	}
	// 根据内容调整控件大小
	ui.sign->adjustSize();
	ui.contentZone->setText(content);
	ui.contentZone->adjustSize();
	this->adjustSize();
	this->setFixedWidth(floatingNoteWidth);
}

void FloatingNote::setType(Type type) { this->type = type;}

void FloatingNote::setContent(QString content) { this->content = content; }

QPropertyAnimation* FloatingNote::moveNote(QPoint startValue, QPoint endValue)
{
	this->setEnabled(false); // 动画执行期间，不允许点击
	QPropertyAnimation* animation = new QPropertyAnimation(this, "pos");
	double distance = sqrt(QPoint::dotProduct(endValue - startValue, endValue - startValue));
	animation->setDuration(distance / 100);
	animation->setStartValue(startValue);
	animation->setEndValue(endValue);
	return animation;
}

QPropertyAnimation* FloatingNote::raiseNote()
{
	this->setEnabled(false); // 动画执行期间，不允许点击
	QPropertyAnimation* animation = new QPropertyAnimation(this, "pos");
	animation->setDuration(1000);
	animation->setStartValue(pos());
	animation->setEndValue(floatingNoteShownPos);
	animation->setEasingCurve(QEasingCurve::OutQuint);
	return animation;
}

QPropertyAnimation* FloatingNote::dropNote()
{
	this->setEnabled(false);
	QPropertyAnimation* animation = new QPropertyAnimation(this, "pos");
	animation->setDuration(1000);
	animation->setStartValue(pos());
	animation->setEndValue(floatingNoteHiddenPos);
	animation->setEasingCurve(QEasingCurve::OutQuint);
	return animation;
}

// 槽函数
void FloatingNote::SlotTimekeeping()
{
	qint64 elapsed = timer->elapsed();
	int hours = elapsed / 3600000;
	int minutes = (elapsed % 3600000) / 60000;
	if (hours == 0 && minutes >= 1) ui.timekeepingLabel->setText(QString("%1min ago").arg(minutes, 0, 10));
	else if (hours > 0) ui.timekeepingLabel->setText(QString("%1h%2min ago").arg(hours).arg(minutes, 0, 10));
}

void FloatingNote::SlotButtonClicked(Feedback feedback)
{
	// 一次分类：立即处理/稍后处理
	if (feedback == Feedback::DealLater) emit SignalDealLater(this);
	else
	{
		emit SignalDealNow(this);
		//emit SignalButtonClicked(feedback); // 二次分类：是/否
	}
}