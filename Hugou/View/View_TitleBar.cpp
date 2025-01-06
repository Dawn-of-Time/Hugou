#include "View_TitleBar.h"

TitleBarView::TitleBarView(QWidget* parent) :
    QWidget(parent)
{
	setupUi();
    
    connect(m_minimizeButton, &QPushButton::clicked, [&]() {emit SignalMinimizeButtonClicked(); });
    connect(m_scaleButton, &QPushButton::clicked, [&]() {emit SignalScaleButtonClicked(); });
	connect(m_closeButton, &QPushButton::clicked, [&]() {emit SignalCloseButtonClicked(); });
    connect(m_floatingNotePanelButton, &QPushButton::clicked, [&]() {emit SignalFloatingNotePanelButtonClicked(); });
    connect(FloatingNoteManager::getManager(), &FloatingNoteManager::SignalAnimationFinishedToTitleBar, this, &TitleBarView::slideFloatingNotePoint);
}

void TitleBarView::setupUi()
{
    this->setObjectName("titleBar");

    m_titleLayout = new QHBoxLayout(this);
    m_titleLayout->setContentsMargins(0, 0, 0, 0);
    m_titleLayout->setSpacing(0);

    // 拖拽区域
    m_dragZone = new QLabel(this);
    m_dragZone->setObjectName("dragZone");
    m_dragZone->setFixedHeight(titleButtonHeight);

    // 消息中心
    m_floatingNotePanelLabel = new QLabel(this);
    m_floatingNotePanelLabel->setFixedSize(titleButtonWidth, titleButtonHeight);
    m_floatingNotePanelButtonBackground = new QLabel(m_floatingNotePanelLabel);
    m_floatingNotePanelButtonBackground->setObjectName("floatingNotePanelButtonBackground");
    m_floatingNotePanelButtonBackground->setFixedSize(titleButtonWidth, titleButtonHeight);
    m_floatingNotePanelButtonBackgroundLayout = new QVBoxLayout(m_floatingNotePanelButtonBackground);
    m_floatingNotePanelButtonBackgroundLayout->setContentsMargins(0, 0, 0, 0);
    m_floatingNotePanelButtonBackgroundLayout->setSpacing(0);
    m_floatingNotePanelIcon = new QPushButton(m_floatingNotePanelButtonBackground);
    m_floatingNotePanelIcon->setObjectName("floatingNotePanelIcon");
    m_floatingNotePanelIcon->setFixedSize(60, 35);
    m_floatingNotePanelIcon->setIcon(QIcon(":/icon/floatingNoteManager_b.png"));
    m_floatingNotePanelIcon->setIconSize(titleButtonIconSize);
    m_floatingNoteQueue = new QLabel(m_floatingNotePanelButtonBackground);
    m_floatingNoteQueue->setObjectName("floatingNoteQueue");
    m_floatingNoteQueue->setFixedHeight(10);
    m_queueLayout = new QHBoxLayout(m_floatingNoteQueue);
    m_queueLayout->setContentsMargins(5, 0, 0, 0);
    m_queueLayout->setSpacing(0);
    m_firstNotePoint = new QLabel(m_floatingNoteQueue);
    m_firstNotePoint->setObjectName("firstNotePoint");
    m_secondNotePoint = new QLabel(m_floatingNoteQueue);
    m_secondNotePoint->setObjectName("secondNotePoint");
    m_thirdNotePoint = new QLabel(m_floatingNoteQueue);
    m_thirdNotePoint->setObjectName("thirdNotePoint");
    m_forthNotePoint = new QLabel(m_floatingNoteQueue);
    m_forthNotePoint->setObjectName("forthNotePoint");
    m_fifthNotePoint = new QLabel(m_floatingNoteQueue);
    m_fifthNotePoint->setObjectName("fifthNotePoint");
    m_notePointQueue = { m_firstNotePoint, m_secondNotePoint, m_thirdNotePoint, m_forthNotePoint, m_fifthNotePoint };
    for (int i = 0; i < 5; ++i)
    {
        m_notePointQueue[i]->setFixedSize(QSize(10, 10));
        m_queueLayout->addWidget(m_notePointQueue[i]);
    }
    m_floatingNotePanelButtonBackgroundLayout->addWidget(m_floatingNotePanelIcon);
    m_floatingNotePanelButtonBackgroundLayout->addWidget(m_floatingNoteQueue);
    m_floatingNotePanelButton = new QPushButton(m_floatingNotePanelLabel);
    m_floatingNotePanelButton->setObjectName("floatingNotePanelButton");
    m_floatingNotePanelButton->setFixedSize(titleButtonWidth, titleButtonHeight);
    /*floatingNotePanelButtonHoverWatcher = new ButtonHoverWatcher(floatingNotePanelButtonBackground, "transparent", "background: qradialgradient(cx:0.5, cy:0.5, fx:0.5, fy:0.5, radius:0.65, stop:0 rgba(255, 255, 255, 0.5), stop:0.8 rgba(255, 255, 255, 0), stop:1 rgba(255, 255, 255, 0));", titleBar);
    floatingNotePanelButton->installEventFilter(floatingNotePanelButtonHoverWatcher);*/
    m_floatingNotePanelButton->raise();

    // 帮助按钮
    m_helpButton = new QPushButton(this);
    m_helpButton->setObjectName("helpButton");
    m_helpButton->setIcon(QIcon(":/icon/help_b.png"));
    m_helpButton->setIconSize(titleButtonIconSize);
    m_helpButton->setFixedSize(titleButtonWidth, titleButtonHeight);

    // 最小化按钮
    m_minimizeButton = new QPushButton(this);
    m_minimizeButton->setObjectName("minimizeButton");
    m_minimizeButton->setIcon(QIcon(":/icon/minimum.png"));
    m_minimizeButton->setFixedSize(titleButtonWidth, titleButtonHeight);

    // 最大化/还原按钮
    m_scaleButton = new QPushButton(this);
    m_scaleButton->setObjectName("scaledButton");
    m_scaleButton->setIcon(QIcon(":/icon/maximum.png"));
    m_scaleButton->setFixedSize(titleButtonWidth, titleButtonHeight);

    // 关闭按钮
    m_closeButton = new QPushButton(this);
    m_closeButton->setObjectName("closeButton");
    m_closeButton->setIcon(QIcon(":/icon/close.png"));
    m_closeButton->setFixedSize(titleButtonWidth, titleButtonHeight);
    /*closeButtonHoverWatcher = new ButtonHoverWatcher(QString(":/icon/close_bla.png"), QString(":/icon/close_w.png"), titleBar);
    closeButton->installEventFilter(closeButtonHoverWatcher);*/

    m_titleLayout->addWidget(m_dragZone);
    m_titleLayout->addWidget(m_floatingNotePanelLabel);
    m_titleLayout->addWidget(m_helpButton);
    m_titleLayout->addWidget(m_minimizeButton);
    m_titleLayout->addWidget(m_scaleButton);
    m_titleLayout->addWidget(m_closeButton);

    // 样式表设置
    QFile styleFile(":/theme/Global/titleBar.qss");
    styleFile.open(QIODeviceBase::ReadOnly);
    this->setStyleSheet(styleFile.readAll());
    styleFile.close();
}

// 槽函数
void TitleBarView::slideFloatingNotePoint()
{
    QParallelAnimationGroup* parallelGroup = new QParallelAnimationGroup;
    for (int i = 0; i < 5; i++)
    {
        QPropertyAnimation* animation = new QPropertyAnimation(m_notePointQueue[i], "pos", m_floatingNoteQueue);
        animation->setDuration(100);
        animation->setStartValue(QPoint(5 + 10 * i, 0));
        animation->setEndValue(QPoint(5 + 10 * (i + 1), 0));
        parallelGroup->addAnimation(animation);
    }
    connect(parallelGroup, &QParallelAnimationGroup::finished, this, &TitleBarView::floatFloatingNotePoint);
    parallelGroup->start(QParallelAnimationGroup::DeleteWhenStopped);
}

void TitleBarView::floatFloatingNotePoint()
{
    QPropertyAnimation* animation0 = new QPropertyAnimation(m_notePointQueue[4], "pos", m_floatingNoteQueue);
    // 设置消息点必须在移动动画之后
    m_notePointQueue[4]->setPixmap(m_typePixmap[FloatingNoteManager::getManager()->getLatestHiddenFloatingNote()->m_type]);
    animation0->setDuration(100);
    animation0->setStartValue(QPoint(5, 15));
    animation0->setEndValue(QPoint(5, 0));
    connect(animation0, &QPropertyAnimation::finished, this, &TitleBarView::allocateFloatingNotePoint);
    animation0->start(QAbstractAnimation::DeleteWhenStopped);
}

void TitleBarView::allocateFloatingNotePoint()
{
    // 重新分配控件位置
    m_notePointQueue.insert(m_notePointQueue.begin(), m_notePointQueue.back());
    m_notePointQueue.pop_back();
    for (int i = 0; i < 5; ++i) m_queueLayout->removeWidget(m_notePointQueue[i]);
    for (int i = 0; i < 5; ++i) m_queueLayout->addWidget(m_notePointQueue[i]);
    FloatingNoteManager::getManager()->checkPopupQueue();
}

bool TitleBarView::isOnMaxButton(QPoint windowPos)
{
    return QRect(m_scaleButton->mapTo(this->parentWidget(), QPoint(0, 0)), m_scaleButton->size()).contains(windowPos);
}

bool TitleBarView::isOnDragZone(QPoint windowPos)
{
    return QRect(m_dragZone->mapTo(this->parentWidget(), QPoint(0, 0)), m_dragZone->size()).contains(windowPos);
}

//void TitleBarView::paintEvent(QPaintEvent* event) {
//    QStyleOption opt;
//    opt.initFrom(this);
//    QPainter painter(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
//}