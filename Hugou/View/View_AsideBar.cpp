#include "View_AsideBar.h"

AsideBarView::AsideBarView(QWidget* parent) :
	QWidget(parent)
{
	setupUi();
}

void AsideBarView::setupUi()
{
    this->setObjectName("asideBarView");
    this->setMinimumHeight(minimumAsideBarHeight);
    this->setFixedWidth(asideBarWidth);

    m_asideBarLayout = new QVBoxLayout(this);
    m_asideBarLayout->setContentsMargins(10, 10, 10, 10);
    m_asideBarLayout->setSpacing(6);
   
    int index = 0;
    for (QString s : asideBarList)
    {
        if (s.isEmpty())
            m_asideBarLayout->addSpacing(24);
        else
        {
            switch (m_asideBarItemIconMap[s].first)
            {
            case ItemType::AsideTitle:
            {
                m_asideBarLayout->addWidget(generateTitle(s));
                break;
            }
            case ItemType::AsideButton:
            {
                m_asideBarLayout->addWidget(generateButton(s));
                break;
            }
            case ItemType::Stretch:
            {
                m_asideBarLayout->addStretch();
                break;
            }
            default:
                break;
            }
        }
    }
    m_asideBarButtonList[0]->setIcon(QPixmap(m_asideBarItemIconMap["Schedule"].second[1]));
    m_asideBarButtonList[0]->setProperty("status", "current");
    m_asideBarButtonList[0]->setStatus(false);
}

QLabel* AsideBarView::generateTitle(QString titleText)
{
    // 字体清单
    QFont asideTitleFont = QFont("NeverMind", 10, QFont::Normal);
    
    QLabel* title = new QLabel(titleText, this);
    title->setObjectName("asideTitle");
    title->setFixedHeight(asideTitleHeight);
    title->setFont(asideTitleFont);
    return title;
}

FadeEffectButton* AsideBarView::generateButton(QString titleText)
{
    // 字体清单
    QFont asideButtonFont = QFont("NeverMind", 11, QFont::Normal);

    FadeEffectButton* button = new FadeEffectButton(QIcon(m_asideBarItemIconMap[titleText].second[0]), QSize(16, 16), titleText, asideButtonFont, this);
    button->setFixedSize(asideButtonWidth, asideButtonHeight);
    button->setBackgroundWidgetStyleSheet("background-color: rgba(0, 0, 255, 0.1); border-radius: 18px;");
    button->setProperty("status", "default");
    button->setStatus(true);
    m_asideBarButtonList.append(button);
    connect(button, &QPushButton::clicked, this, &AsideBarView::switchOverStackedWidget);
    return button;
}

void AsideBarView::switchOverStackedWidget()
{
    FadeEffectButton* objectiveButton = (FadeEffectButton*)sender();
    int index = 0;
    int stackedWidgetIndex = 0;
    for(FadeEffectButton* button : m_asideBarButtonList)
    {
        if (button == objectiveButton)
        {
            button->setIcon(QPixmap(m_asideBarItemIconMap[button->text()].second[1]));
            button->setProperty("status", "current");
            button->setStatus(false);
            stackedWidgetIndex = index;
        }
        else
        {
            button->setIcon(QPixmap(m_asideBarItemIconMap[button->text()].second[0]));
            button->setProperty("status", "default");
            button->setStatus(true);
            index++;
        }
    }
    this->setStyleSheet(this->styleSheet());
    emit SignalChangeStackedWidget(stackedWidgetIndex);
}