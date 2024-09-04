#include "View_AsideBar.h"
#include "Var.h"

extern FloatingNoteManager floatingNoteManager;

AsideBarView::AsideBarView(QWidget* parent) :
	QWidget(parent)
{
	setupUi();
	// 信号与槽
    connect(m_workSpaceButton, &QPushButton::clicked, [&]() {switchOverStackedWidget(0); });
    connect(m_settingButton, &QPushButton::clicked, [&]() {switchOverStackedWidget(1); });
    m_asideBarButtonList = { m_workSpaceButton,  m_settingButton };
}

void AsideBarView::setupUi()
{
    this->setMinimumHeight(asideFrameHeight);
    this->setFixedWidth(150);
    //m_asideFrame = new QFrame(this);
    //m_asideFrame->setObjectName("asideFrame");
    m_asideFrameLayout = new QVBoxLayout(this);
    m_asideFrameLayout->setContentsMargins(5, 0, 5, 0);
    m_asideFrameLayout->setSpacing(5);
    m_userLabel = new QLabel(this);
    m_userLabel->setObjectName("userLabel");
    m_userLabel->setFixedSize(userLabelWidth, userLabelHeight);
    m_workSpaceButton = new IconTextButton(QPixmap(":/icon/workSpace_b.png"), "WorkSpace", asideFont, this);
    m_workSpaceButton->setObjectName("workSpaceButton");
    m_workSpaceButton->setFixedSize(asideButtonWidth, asideButtonHeight);
    m_workSpaceButton->setEnabled(false);
    m_settingButton = new IconTextButton(QPixmap(":/icon/setting_w.png"), "Settings", asideFont, this);
    m_settingButton->setObjectName("settingButton");
    m_settingButton->setFixedSize(asideButtonWidth, asideButtonHeight);
    m_asideFrameLayout->addWidget(m_userLabel, Qt::AlignLeft);
    m_asideFrameLayout->addWidget(m_workSpaceButton, Qt::AlignLeft);
    m_asideFrameLayout->addWidget(m_settingButton, Qt::AlignLeft);
    m_asideFrameLayout->addStretch();

    m_workSpaceButton->setProperty("status", "current");
    m_settingButton->setProperty("status", "default");
}
// 子控件位置在Ui结束后才能被正确获取
void AsideBarView::showEvent(QShowEvent* event)
{
    m_workSpaceButtonHoverWatcher = new ButtonHoverWatcher(m_workSpaceButton->pos(), QPoint(m_workSpaceButton->pos().x() + 5, m_workSpaceButton->pos().y()), ButtonHoverWatcher::Direction::Horizontal);
    m_workSpaceButton->installEventFilter(m_workSpaceButtonHoverWatcher);
    m_settingButtonHoverWatcher = new ButtonHoverWatcher(m_settingButton->pos(), QPoint(m_settingButton->pos().x() + 5, m_settingButton->pos().y()), ButtonHoverWatcher::Direction::Horizontal);
    m_settingButton->installEventFilter(m_settingButtonHoverWatcher);
}

void AsideBarView::switchOverStackedWidget(int index)
{
    for (int buttonIndex = 0; buttonIndex < m_asideBarButtonList.size(); ++buttonIndex)
    {
        if (buttonIndex == index)
        {
            m_asideBarButtonList[buttonIndex]->setEnabled(false);
            m_asideBarButtonList[buttonIndex]->setIcon(QPixmap(m_asideBarButtonIconList[buttonIndex].at(1)), QSize(18, 18));
            m_asideBarButtonList[buttonIndex]->setProperty("status", "current");
        }
        else
        {
            m_asideBarButtonList[buttonIndex]->setEnabled(true);
            m_asideBarButtonList[buttonIndex]->setIcon(QPixmap(m_asideBarButtonIconList[buttonIndex].at(0)), QSize(18, 18));
            m_asideBarButtonList[buttonIndex]->setProperty("status", "default");
        }
    }
    this->setStyleSheet(this->styleSheet());
    emit SignalChangeStackedWidget(index);
}