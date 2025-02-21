#include "View_TitleBar.h"

TitleBarView::TitleBarView(QWidget* parent) :
    QWidget(parent)
{
	setupUi();
    connect(m_minimizeButton, &QPushButton::clicked, [&]() {emit SignalMinimizeButtonClicked(); });
    connect(m_scaleButton, &QPushButton::clicked, [&]() {emit SignalScaleButtonClicked(); });
	connect(m_closeButton, &QPushButton::clicked, [&]() {emit SignalCloseButtonClicked(); });
}

void TitleBarView::setupUi()
{
    // 字体清单
    QFont appNameFont = QFont("NeverMind", 14, QFont::Bold);
    QFont AIChatLineEditFont = QFont("NeverMind", 12, QFont::Normal);

    this->setObjectName("titleBar");

    m_titleLayout = new QHBoxLayout(this);
    m_titleLayout->setContentsMargins(16, 0, 0, 16);
    m_titleLayout->setSpacing(0);

    // 软件图标和名字
    m_appIcon = new QPushButton(this);
    m_appIcon->setFixedSize(48, 48);
    m_appIcon->setIcon(QIcon(":/icon/Hugou.ico"));
    m_appIcon->setIconSize(QSize(48, 48));
    m_appIcon->setStyleSheet("border: none; background-color: transparent");

    m_appName = new QLabel("Hugou", this);
    m_appName->setFixedWidth(80);
    m_appName->setFont(appNameFont);

    // 左拖拽区域
    m_leftDragZone = new QLabel(this);
    m_leftDragZone->setObjectName("leftDragZone");
    m_leftDragZone->setFixedHeight(titleFrameHeight);

    // AI 聊天
    m_AIChatWidget = new QWidget(this);
    m_AIChatWidget->setObjectName("AIChatWidget");
    m_AIChatWidget->setFixedHeight(40);
    m_AIChatWidgetLayout = new QHBoxLayout(m_AIChatWidget);
    m_AIChatWidgetLayout->setSpacing(5);
    m_AIChatIcon = new QPushButton(m_AIChatWidget);
    m_AIChatIcon->setFixedSize(16, 16);
    m_AIChatIcon->setIcon(QIcon(":/icon/AI_chat_default.ico"));
    m_AIChatIcon->setIconSize(QSize(16, 16));
    m_AIChatIcon->setStyleSheet("border: none; background-color: transparent");
    m_AIChatLineEdit = new QLineEdit(m_AIChatWidget);
    m_AIChatLineEdit->setObjectName("AIChatLineEdit");
    m_AIChatLineEdit->setPlaceholderText("Chat");
    m_AIChatLineEdit->setFont(AIChatLineEditFont);

    m_AIChatWidgetLayout->setAlignment(Qt::AlignVCenter);
    m_AIChatWidgetLayout->addWidget(m_AIChatIcon);
    m_AIChatWidgetLayout->addWidget(m_AIChatLineEdit);

    // 右拖拽区域
    m_rightDragZone = new QLabel(this);
    m_rightDragZone->setObjectName("leftDragZone");
    m_rightDragZone->setFixedHeight(titleFrameHeight);

    // 用户区域
    m_userWidget = new QWidget(this);
    m_userWidget->setFixedSize(56, 56);
    m_userWidgetLayout = new QHBoxLayout(m_userWidget);
    m_userWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_userWidgetLayout->setSpacing(0);
    m_userButton = new QPushButton(m_userWidget);
    m_userButton->setObjectName("userButton");
    m_userButton->setFixedSize(36, 36);
    m_userButton->setIcon(QIcon(":/icon/Hugou.ico"));
    m_userButton->setIconSize(QSize(36, 36));
    m_userWidgetLayout->setAlignment(Qt::AlignCenter);
    m_userWidgetLayout->addWidget(m_userButton);

    // 最小化按钮
    m_minimizeButton = new QPushButton(this);
    m_minimizeButton->setObjectName("minimizeButton");
    m_minimizeButton->setIcon(QIcon(":/icon/minimum_black.ico"));
    m_minimizeButton->setFixedSize(titleButtonWidth, titleButtonHeight);

    // 最大化/还原按钮
    m_scaleButton = new QPushButton(this);
    m_scaleButton->setObjectName("scaledButton");
    m_scaleButton->setIcon(QIcon(":/icon/maximum_black.ico"));
    m_scaleButton->setFixedSize(titleButtonWidth, titleButtonHeight);

    // 关闭按钮
    m_closeButton = new QPushButton(this);
    m_closeButton->setObjectName("closeButton");
    m_closeButton->setIcon(QIcon(":/icon/close_black.ico"));
    m_closeButton->setFixedSize(titleButtonWidth, titleButtonHeight);
    m_closeButtonHoverWatcher = new ButtonHoverWatcher(QString(":/icon/close_black.ico"), QString(":/icon/close_white.ico"), this);
    m_closeButton->installEventFilter(m_closeButtonHoverWatcher);

    m_titleLayout->setAlignment(Qt::AlignVCenter);
    m_titleLayout->addWidget(m_appIcon);
    m_titleLayout->addWidget(m_appName);
    m_titleLayout->addWidget(m_leftDragZone, 1);
    m_titleLayout->addWidget(m_AIChatWidget, 1);
    m_titleLayout->addWidget(m_rightDragZone, 1);
    m_titleLayout->addWidget(m_userWidget);
    m_titleLayout->addWidget(m_minimizeButton);
    m_titleLayout->addWidget(m_scaleButton);
    m_titleLayout->addWidget(m_closeButton);

    // 样式表设置
    QFile styleFile(":/theme/Global/titleBar.qss");
    styleFile.open(QIODeviceBase::ReadOnly);
    this->setStyleSheet(styleFile.readAll());
    styleFile.close();
}

bool TitleBarView::isOnMaxButton(QPoint windowPos)
{
    return QRect(m_scaleButton->mapTo(this->parentWidget(), QPoint(0, 0)), m_scaleButton->size()).contains(windowPos);
}

bool TitleBarView::isOnDragZone(QPoint windowPos)
{
    return QRect(m_leftDragZone->mapTo(this->parentWidget(), QPoint(0, 0)), m_leftDragZone->size()).contains(windowPos) ||
        QRect(m_rightDragZone->mapTo(this->parentWidget(), QPoint(0, 0)), m_rightDragZone->size()).contains(windowPos);
}

//void TitleBarView::paintEvent(QPaintEvent* event) {
//    QStyleOption opt;
//    opt.initFrom(this);
//    QPainter painter(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
//}