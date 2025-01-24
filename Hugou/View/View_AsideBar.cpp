#include "View_AsideBar.h"

AsideBarView::AsideBarView(QWidget* parent) :
	QWidget(parent)
{
	setupUi();
	// 信号与槽
    connect(m_scheduleButton, &QPushButton::clicked, [&]() {switchOverStackedWidget(0); });
    connect(m_settingButton, &QPushButton::clicked, [&]() {switchOverStackedWidget(1); });
}

void AsideBarView::setupUi()
{
    // 字体清单
    const QFont asideNicknameFont = QFont("Hind Siliguri", 13, QFont::DemiBold);
    const QFont asideIDFont = QFont("Hind Siliguri", 8, QFont::Thin);
    const QFont asideTitleFont = QFont("Work Sans", 10, QFont::DemiBold);
    const QFont asideButtonFont = QFont("Hind Siliguri", 13, QFont::Medium);

    this->setObjectName("asideBarView");
    this->setMinimumHeight(asideBarHeight);
    this->setFixedWidth(asideBarWidth);

    m_asideBarLayout = new QVBoxLayout(this);
    m_asideBarLayout->setContentsMargins(30, 10, 30, 0);
    m_userWidget = new QWidget(this);
    m_userWidget->setObjectName("userLabel");
    m_userWidget->setFixedHeight(asideUserWidgetHeight);
    m_userWidgetLayout = new QHBoxLayout(m_userWidget);
    m_userWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_userWidgetLayout->setSpacing(10);
    m_userAvatar = new QLabel(m_userWidget);
    m_userAvatar->setObjectName("userAvatar");
    m_userAvatar->setFixedSize(asideUserAvaterSide, asideUserAvaterSide);
    QPixmap avatarRes(":/icon/Hugou_48.png");
    m_userAvatar->setPixmap(cropPixmapIntoCircle(avatarRes, 48));
    m_userAvatar->setAlignment(Qt::AlignCenter);
    m_userNicknameAndIDWidget = new QWidget(m_userWidget);
    m_userNicknameAndIDWidgetLayout = new QVBoxLayout(m_userNicknameAndIDWidget);
    m_userNicknameAndIDWidgetLayout->setContentsMargins(0, 3, 0, 3);
    m_userNicknameAndIDWidgetLayout->setSpacing(0);
    m_userNickname = new QLabel("Hugou", m_userNicknameAndIDWidget);
    m_userNickname->setObjectName("userNickname");
    m_userNickname->setFont(asideNicknameFont);
    m_userNickname->setAlignment(Qt::AlignLeft);
    m_userID = new QLabel("ID:00000000", m_userNicknameAndIDWidget);
    m_userID->setObjectName("userID");
    m_userID->setFont(asideIDFont);
    m_userID->setAlignment(Qt::AlignLeft);
    m_userNicknameAndIDWidgetLayout->addWidget(m_userNickname, Qt::AlignLeft);
    m_userNicknameAndIDWidgetLayout->addWidget(m_userID, Qt::AlignLeft);
    m_userWidgetLayout->addWidget(m_userAvatar);
    m_userWidgetLayout->addWidget(m_userNicknameAndIDWidget);

    QSpacerItem* spacer1 = new QSpacerItem(0, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_planLabel = new QLabel(tr("PLAN"), this);
    m_planLabel->setFixedHeight(asideTitleHeight);
    m_planLabel->setFont(asideTitleFont);
    m_planLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_scheduleButton = new IconTextButton(QPixmap(":/icon/schedule_current_16.png"), tr("Schedule"), asideButtonFont, this);
    m_scheduleButton->setObjectName("scheduleButton");
    m_scheduleButton->setFixedSize(asideButtonWidth, asideButtonHeight);
    m_scheduleButton->setBackgroundWidgetStyleSheet("background-color: rgba(0, 0, 255, 0.1); border-radius: 10px;");
    QSpacerItem* spacer2 = new QSpacerItem(0, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_dataBaseLabel = new QLabel(tr("DATABASE"), this);
    m_dataBaseLabel->setFixedHeight(asideTitleHeight);
    m_dataBaseLabel->setFont(asideTitleFont);
    m_dataBaseLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_settingButton = new IconTextButton(QPixmap(":/icon/document_default_16.png"), tr("Document"), asideButtonFont, this);
    m_settingButton->setObjectName("settingButton");
    m_settingButton->setFixedSize(asideButtonWidth, asideButtonHeight);
    m_settingButton->setBackgroundWidgetStyleSheet("background-color: rgba(0, 0, 255, 0.1); border-radius: 10px;");
    m_asideBarLayout->addWidget(m_userWidget, Qt::AlignLeft);
    m_asideBarLayout->addSpacerItem(spacer1);
    m_asideBarLayout->addWidget(m_planLabel, Qt::AlignLeft);
    m_asideBarLayout->addWidget(m_scheduleButton, Qt::AlignLeft);
    m_asideBarLayout->addSpacerItem(spacer2);
    m_asideBarLayout->addWidget(m_dataBaseLabel, Qt::AlignLeft);
    m_asideBarLayout->addWidget(m_settingButton, Qt::AlignLeft);
    m_asideBarLayout->addStretch();

    m_asideBarButtonList = { m_scheduleButton,  m_settingButton };

    switchOverStackedWidget(0);
}

void AsideBarView::switchOverStackedWidget(int index)
{
    for (int buttonIndex = 0; buttonIndex < m_asideBarButtonList.size(); ++buttonIndex)
    {
        if (buttonIndex == index)
        {
            m_asideBarButtonList[buttonIndex]->setIcon(QPixmap(m_asideBarButtonIconList[buttonIndex].at(1)));
            m_asideBarButtonList[buttonIndex]->setProperty("status", "current");
            m_asideBarButtonList[buttonIndex]->setStatus(false);
        }
        else
        {
            m_asideBarButtonList[buttonIndex]->setIcon(QPixmap(m_asideBarButtonIconList[buttonIndex].at(0)));
            m_asideBarButtonList[buttonIndex]->setProperty("status", "default");
            m_asideBarButtonList[buttonIndex]->setStatus(true);
        }
    }
    this->setStyleSheet(this->styleSheet());
    emit SignalChangeStackedWidget(index);
}