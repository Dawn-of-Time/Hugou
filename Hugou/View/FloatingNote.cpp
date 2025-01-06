#include "FloatingNote.h"

FloatingNote::FloatingNote(QWidget* HugouClass) :
	QWidget(HugouClass)
{
	setupUi();
	m_floatingNoteHiddenPos = QPoint(HugouClass->width(), titleFrameHeight);
	m_floatingNoteShownPos = QPoint(HugouClass->width() - floatingNoteWidth - 20, titleFrameHeight);
	this->move(m_floatingNoteHiddenPos); // 初始位置

	// 时长标签
	m_timer = new QElapsedTimer();
	m_timer->start();
	m_updateTimer = new QTimer();
	connect(m_updateTimer, &QTimer::timeout, this, &FloatingNote::SlotTimekeeping);
	m_updateTimer->start(1000);

	// 按钮事件
	connect(m_yesButton, &QPushButton::clicked, this, [&]() {SlotButtonClicked(Feedback::Yes); });
	connect(m_noButton, &QPushButton::clicked, this, [&]() {SlotButtonClicked(Feedback::No); });
	connect(m_dealLaterButton, &QPushButton::clicked, this, [&]() {SlotButtonClicked(Feedback::DealLater); });
}

FloatingNote::~FloatingNote()
{}

void FloatingNote::setupUi()
{
	// 主体
	this->setFixedWidth(floatingNoteWidth);
	this->setObjectName("floatingNote");
	m_floatingNoteLayout = new QVBoxLayout(this);
	m_floatingNoteLayout->setContentsMargins(0, 0, 0, 0);
	m_floatingNoteLayout->setSpacing(0);

	m_floatingNoteFrame = new QFrame(this);
	m_floatingNoteFrame->setObjectName("floatingNoteFrame");
	m_floatingNoteFrame->setFixedWidth(floatingNoteWidth);
	m_floatingNoteFrameLayout = new QVBoxLayout(m_floatingNoteFrame);
	m_floatingNoteFrameLayout->setObjectName("floatingNoteFrameLayout");
	m_floatingNoteFrameLayout->setContentsMargins(10, 10, 10, 10);
	m_floatingNoteFrameLayout->setSpacing(10);

	// 标志域
	m_signZone = new QWidget(m_floatingNoteFrame);
	m_signZone->setObjectName("signZone");
	m_signLayout = new QHBoxLayout(m_signZone);
	m_signLayout->setObjectName("signLayout");
	m_signLayout->setSpacing(10);
	m_signLayout->setContentsMargins(0, 0, 0, 0);
	// 标志图标与文字
	m_signIcon = new QLabel(m_signZone);
	m_signIcon->setObjectName("signIcon");
	m_signIcon->setFixedSize(QSize(25, 25));
	m_signTitle = new QLabel(m_signZone);
	m_signTitle->setObjectName("signTitle");
	m_signTitle->setFont(signFont);
	// 时长标签
	m_timekeepingLabel = new QLabel("Now", m_signZone);
	m_timekeepingLabel->setObjectName("timekeepingLabel");
	m_timekeepingLabel->setFont(timekeepingLabelFont);
	m_signLayout->addWidget(m_signIcon);
	m_signLayout->addWidget(m_signTitle);
	m_signLayout->addWidget(m_timekeepingLabel);
	m_signLayout->addStretch();

	// 内容域
	m_contentZone = new QLabel(m_floatingNoteFrame);
	m_contentZone->setObjectName("contentZone");
	m_contentZone->setFont(contentFont);
	m_contentZone->setWordWrap(true);
	m_contentZone->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	m_subcontentZone = new QLabel(m_floatingNoteFrame);
	m_subcontentZone->setObjectName("subcontentZone");
	m_subcontentZone->setFont(contentFont);
	m_subcontentZone->setWordWrap(true);
	m_subcontentZone->setHidden(true);
	m_subcontentZone->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	// 按钮域
	m_buttonZone = new QWidget(m_floatingNoteFrame);
	m_buttonZone->setObjectName("buttonZone");
	m_buttonZone->setFixedHeight(40);
	m_buttonLayout = new QHBoxLayout(m_buttonZone);
	m_buttonLayout->setObjectName("buttonLayout");
	m_buttonLayout->setSpacing(10);
	m_buttonLayout->setContentsMargins(5, 5, 5, 5);
	// 确认按钮
	m_yesButton = new QPushButton("Checked!", m_buttonZone);
	m_yesButton->setObjectName("yesButton");
	m_yesButton->setFont(floatingNoteButtonFont);
	m_yesButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_yesButton->setCursor(QCursor(Qt::PointingHandCursor));
	// 取消按钮
	m_noButton = new QPushButton("No", m_buttonZone);
	m_noButton->setObjectName("noButton");
	m_noButton->setFont(floatingNoteButtonFont);
	m_noButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_noButton->setCursor(QCursor(Qt::PointingHandCursor));
	// 稍后处理按钮
	m_dealLaterButton = new QPushButton("Defer", m_buttonZone);
	m_dealLaterButton->setObjectName("dealLaterButton");
	m_dealLaterButton->setFont(floatingNoteButtonFont);
	m_dealLaterButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_dealLaterButton->setCursor(QCursor(Qt::PointingHandCursor));
	m_buttonLayout->addStretch(1);
	m_buttonLayout->addWidget(m_yesButton, 10);
	m_buttonLayout->addWidget(m_noButton, 10);
	m_buttonLayout->addWidget(m_dealLaterButton, 10);
	m_buttonLayout->addStretch(1);
	// 框架布局
	m_floatingNoteFrameLayout->addWidget(m_signZone);
	m_floatingNoteFrameLayout->addWidget(m_contentZone);
	m_floatingNoteFrameLayout->addWidget(m_subcontentZone);
	m_floatingNoteFrameLayout->addWidget(m_buttonZone);

	m_floatingNoteLayout->addWidget(m_floatingNoteFrame);

	// 样式表设置
	QFile styleFile(":/theme/Global/floatingNote.qss");
	styleFile.open(QIODeviceBase::ReadOnly);
	this->setStyleSheet(styleFile.readAll());
	styleFile.close();
}

void FloatingNote::updateUI()
{
	m_signIcon->setPixmap(m_typeIcon.at(m_type).scaled(QSize(25, 25), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	m_signTitle->setText(m_typeText.at(m_type));
	m_contentZone->setText(m_content);
	if (!m_subcontent.isEmpty())
	{
		m_subcontentZone->setHidden(false);
		m_subcontentZone->setText(m_subcontent);
	}
	m_noButton->setHidden(true);
	m_dealLaterButton->setHidden(true);
	// Dialog
	if (m_type == Type::Dialog) {
		m_noButton->setHidden(false);
	}
	// 根据内容调整控件大小
	this->adjustSize();
}

QPropertyAnimation* FloatingNote::raiseNote()
{
	this->setEnabled(false); // 动画执行期间，不允许点击
	QPropertyAnimation* animation = new QPropertyAnimation(this, "pos");
	animation->setDuration(1000);
	animation->setStartValue(pos());
	animation->setEndValue(m_floatingNoteShownPos);
	animation->setEasingCurve(QEasingCurve::OutQuint);
	return animation;
}

QPropertyAnimation* FloatingNote::dropNote()
{
	this->setEnabled(false);
	QPropertyAnimation* animation = new QPropertyAnimation(this, "pos");
	animation->setDuration(1000);
	animation->setStartValue(pos());
	animation->setEndValue(m_floatingNoteHiddenPos);
	animation->setEasingCurve(QEasingCurve::OutQuint);
	return animation;
}

// 槽函数
void FloatingNote::SlotTimekeeping()
{
	qint64 elapsed = m_timer->elapsed();
	int hours = elapsed / 3600000;
	int minutes = (elapsed % 3600000) / 60000;
	if (hours == 0 && minutes >= 1) m_timekeepingLabel->setText(QString("%1min ago").arg(minutes, 0, 10));
	else if (hours > 0) m_timekeepingLabel->setText(QString("%1h%2min ago").arg(hours).arg(minutes, 0, 10));
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