#include "View/Include/View_AsideBar.h"
#include <QEvent>
#include <QApplication>

AsideBarView::AsideBarView(QWidget* parent) :
	QWidget(parent) 
{
	setupUi();
}

void AsideBarView::setupUi()
{
    this->setObjectName("asideBarView");
    this->setMinimumHeight(minimumAsideBarHeight);
    this->setFixedWidth(246);

    m_asideBarLayout = new QVBoxLayout(this);
    m_asideBarLayout->setContentsMargins(10, 10, 10, 10);
    m_asideBarLayout->setSpacing(6);

    for (const QString& s : asideBarList)
    {
        if (s.isEmpty())
            m_asideBarLayout->addSpacing(24);
        else
        {
            switch (m_asideBarItemIconMap[s].first)
            {
            case ItemType::AsideTitle:
                m_asideBarLayout->addWidget(generateTitle(s));
                break;
            case ItemType::AsideButton:
                m_asideBarLayout->addWidget(generateButton(s));
                break;
            case ItemType::Stretch:
                m_asideBarLayout->addStretch();
                break;
            default:
                break;
            }
        }
    }
    m_asideBarButtonList[0]->setIcon(QPixmap(m_asideBarItemIconMap["Schedule"].second[1]));
    m_asideBarButtonList[0]->setProperty("status", "current");
    QLinearGradient gradient(m_asideBarButtonList[0]->rect().topLeft(), m_asideBarButtonList[0]->rect().topRight());
    gradient.setColorAt(0, QColor("#104FB9"));
    gradient.setColorAt(1, QColor("#468DFA"));
    m_asideBarButtonList[0]->setGradient(gradient);
    m_asideBarButtonList[0]->setStatus(false);
}

QLabel* AsideBarView::generateTitle(const QString& titleText)
{
    // 字体清单
    QFont asideBarTitleFont = QFont("NeverMind", 10, QFont::Normal);
    
    QLabel* title = new QLabel(titleText, this);
    title->setObjectName("asideBarTitle");
    title->setFixedHeight(30);
    title->setFont(asideBarTitleFont);
    return title;
}

FadeEffectButton* AsideBarView::generateButton(const QString& titleText)
{
    // 字体清单
    QFont asideBarButtonFont = QFont("NeverMind", 11, QFont::Normal);

    FadeEffectButton* button = new FadeEffectButton(QIcon(m_asideBarItemIconMap[titleText].second[0]), QSize(16, 16), titleText, asideBarButtonFont, this);
    button->setFixedSize(226, 36);
    button->setBackgroundWidgetStyleSheet("background-color: rgba(0, 0, 255, 0.1); border-radius: 10px;");
    button->setContentsMargins(20, 10, 20, 10);
    button->setTextAlignment(Qt::AlignLeft);
    button->setProperty("status", "default");
    QPainterPath path;
    path.addRoundedRect(button->rect(), 10, 10);
    button->setPainterPath(path);
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
            button->setIcon(QIcon(m_asideBarItemIconMap[button->text()].second[1]));
            button->setProperty("status", "current");
            QLinearGradient gradient(button->rect().topLeft(), button->rect().topRight());
            gradient.setColorAt(0, QColor("#104FB9"));
            gradient.setColorAt(1, QColor("#468DFA"));
            button->setGradient(gradient);
            button->setStatus(false);
            stackedWidgetIndex = index;
        }
        else
        {
            button->setIcon(QIcon(m_asideBarItemIconMap[button->text()].second[0]));
            button->setProperty("status", "default");
            button->setGradient(QGradient());
            button->setStatus(true);
            index++;
        }
    }
    this->setStyleSheet(ThemeManager::getManager()->getStyleSheet(ThemeRole::AsideBar));
    emit SignalChangeStackedWidget(stackedWidgetIndex);
}

void AsideBarView::paintEvent(QPaintEvent* event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}