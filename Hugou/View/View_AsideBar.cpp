#include "View_AsideBar.h"
#include "Var.h"

extern FloatingNoteManager floatingNoteManager;

AsideBarView::AsideBarView(QWidget* parent) :
	QWidget(parent)
{
	setupUi();
	// ÐÅºÅÓë²Û
    connect(m_scheduleButton, &QPushButton::clicked, [&]() {switchOverStackedWidget(0); });
    connect(m_settingButton, &QPushButton::clicked, [&]() {switchOverStackedWidget(1); });
    m_asideBarButtonList = { m_scheduleButton,  m_settingButton };
}

void AsideBarView::setupUi()
{
    this->setObjectName("asideBarView");
    this->setMinimumHeight(asideBarHeight);
    this->setFixedWidth(asideBarWidth);
    m_asideBarLayout = new QVBoxLayout(this);
    m_asideBarLayout->setContentsMargins(30, 0, 30, 0);
    m_asideBarLayout->setSpacing(5);
    m_userLabel = new QLabel(this);
    m_userLabel->setObjectName("userLabel");
    m_userLabel->setFixedHeight(asideUserLabelHeight);
    m_planLabel = new QLabel("PLAN", this);
    m_planLabel->setFixedHeight(asideTitleHeight);
    m_planLabel->setFont(asideTitleFont);
    m_scheduleButton = new IconTextButton(QPixmap(":/icon/schedule_blu.png"), "Schedule", asideButtonFont, this);
    m_scheduleButton->setObjectName("scheduleButton");
    m_scheduleButton->setFixedHeight(asideButtonHeight);
    m_settingButton = new IconTextButton(QPixmap(":/icon/setting_b.png"), "Settings", asideButtonFont, this);
    m_settingButton->setObjectName("settingButton");
    m_settingButton->setFixedHeight(asideButtonHeight);
    m_asideBarLayout->addWidget(m_userLabel, Qt::AlignLeft);
    m_asideBarLayout->addWidget(m_planLabel, Qt::AlignLeft);
    m_asideBarLayout->addWidget(m_scheduleButton, Qt::AlignLeft);
    m_asideBarLayout->addWidget(m_settingButton, Qt::AlignLeft);
    m_asideBarLayout->addStretch();

    m_scheduleButton->setProperty("status", "current");
    m_settingButton->setProperty("status", "default");
}

void AsideBarView::switchOverStackedWidget(int index)
{
    for (int buttonIndex = 0; buttonIndex < m_asideBarButtonList.size(); ++buttonIndex)
    {
        if (buttonIndex == index)
        {
            m_asideBarButtonList[buttonIndex]->setIcon(QPixmap(m_asideBarButtonIconList[buttonIndex].at(1)), QSize(18, 18));
            m_asideBarButtonList[buttonIndex]->setProperty("status", "current");
        }
        else
        {
            m_asideBarButtonList[buttonIndex]->setIcon(QPixmap(m_asideBarButtonIconList[buttonIndex].at(0)), QSize(18, 18));
            m_asideBarButtonList[buttonIndex]->setProperty("status", "default");
        }
    }
    this->setStyleSheet(this->styleSheet());
    emit SignalChangeStackedWidget(index);
}