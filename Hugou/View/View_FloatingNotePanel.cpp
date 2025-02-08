#include "View_FloatingNotePanel.h"

FloatingNotePanel::FloatingNotePanel(QWidget* parent) :
	QWidget(parent)
{
	setupUi();
    this->setHidden(true);
    connect(m_allFloatingNoteButton, &QPushButton::clicked, [&]() {moveSlider(0); });
    connect(m_successFloatingNoteButton, &QPushButton::clicked, [&]() {moveSlider(1); });
    connect(m_informationFloatingNoteButton, &QPushButton::clicked, [&]() {moveSlider(2); });
    connect(m_warningFloatingNoteButton, &QPushButton::clicked, [&]() {moveSlider(3); });
    connect(m_errorFloatingNoteButton, &QPushButton::clicked, [&]() {moveSlider(4); });
}

void FloatingNotePanel::setupUi()
{
    this->setObjectName("floatingNotePanel");
    this->setGeometry(0, titleFrameHeight, mainWindowWidth, mainWindowHeight - titleFrameHeight);
    m_floatingNotePanelLayout = new QVBoxLayout(this);
    m_floatingNotePanelLayout->setSpacing(10);
    m_floatingNotePanelLayout->setContentsMargins(50, 50, 50, 50);
    m_floatingNotePanelTitle = new QLabel("Notification Center", this);
    m_floatingNotePanelTitle->setObjectName("floatingNotePanelTitle");
    //floatingNotePanelTitle->setFixedHeight(50);
    m_floatingNotePanelTitle->setFont(QFont("Hind", 24));

    m_floatingNotePanelTabBar = new QWidget(this);
    m_floatingNotePanelTabBar->setObjectName("floatingNotePanelTabBar");
    m_floatingNotePanelTabBarLayout = new QHBoxLayout(m_floatingNotePanelTabBar);
    m_floatingNotePanelTabBarLayout->setContentsMargins(0, 0, 0, 0);
    m_floatingNotePanelTabBarLayout->setSpacing(50);
    m_allFloatingNoteButton = new QPushButton("All", m_floatingNotePanelTabBar);
    m_allFloatingNoteButton->setObjectName("allFloatingNoteButton");
    m_allFloatingNoteButton->setFont(floatingNotePanelButtonFont);
    m_allFloatingNoteButton->setFixedHeight(30);
    m_successFloatingNoteButton = new QPushButton("Success", m_floatingNotePanelTabBar);
    m_successFloatingNoteButton->setObjectName("successFloatingNoteButton");
    m_successFloatingNoteButton->setFont(floatingNotePanelButtonFont);
    m_successFloatingNoteButton->setFixedHeight(30);
    m_informationFloatingNoteButton = new QPushButton("Information", m_floatingNotePanelTabBar);
    m_informationFloatingNoteButton->setObjectName("informationFloatingNoteButton");
    m_informationFloatingNoteButton->setFont(floatingNotePanelButtonFont);
    m_informationFloatingNoteButton->setFixedHeight(30);
    m_warningFloatingNoteButton = new QPushButton("Warning", m_floatingNotePanelTabBar);
    m_warningFloatingNoteButton->setObjectName("warningFloatingNoteButton");
    m_warningFloatingNoteButton->setFont(floatingNotePanelButtonFont);
    m_warningFloatingNoteButton->setFixedHeight(30);
    m_errorFloatingNoteButton = new QPushButton("Error", m_floatingNotePanelTabBar);
    m_errorFloatingNoteButton->setObjectName("errorFloatingNoteButton");
    m_errorFloatingNoteButton->setFont(floatingNotePanelButtonFont);
    m_errorFloatingNoteButton->setFixedHeight(30);
    m_floatingNoteButtonList = {
        m_allFloatingNoteButton,
        m_successFloatingNoteButton,
        m_informationFloatingNoteButton,
        m_warningFloatingNoteButton,
        m_errorFloatingNoteButton
    };

    m_floatingNotePanelTabBarLayout->addWidget(m_allFloatingNoteButton);
    m_floatingNotePanelTabBarLayout->addWidget(m_successFloatingNoteButton);
    m_floatingNotePanelTabBarLayout->addWidget(m_informationFloatingNoteButton);
    m_floatingNotePanelTabBarLayout->addWidget(m_warningFloatingNoteButton);
    m_floatingNotePanelTabBarLayout->addWidget(m_errorFloatingNoteButton);

    m_floatingNotePanelTabBarSlider = new QWidget(this);
    m_floatingNotePanelTabBarSlider->setObjectName("floatingNotePanelTabBarSlider");
    m_floatingNotePanelTabBarSlider->setFixedHeight(6);

    m_floatingNoteButtonSlider = new QWidget(m_floatingNotePanelTabBarSlider);
    m_floatingNoteButtonSlider->setObjectName("floatingNoteButtonSlider");
    m_floatingNoteButtonSlider->setFixedHeight(6);

    m_floatingNoteContent = new QWidget(this);
    m_floatingNoteContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_floatingNotePanelLayout->addWidget(m_floatingNotePanelTitle);
    m_floatingNotePanelLayout->addWidget(m_floatingNotePanelTabBar);
    m_floatingNotePanelLayout->addWidget(m_floatingNotePanelTabBarSlider);
    m_floatingNotePanelLayout->addWidget(m_floatingNoteContent);
    updateProperty(0);

    // 样式表设置
    QFile styleFile(":/theme/Global/floatingNotePanel.qss");
    styleFile.open(QIODeviceBase::ReadOnly);
    this->setStyleSheet(styleFile.readAll());
    styleFile.close();
}

void FloatingNotePanel::updateProperty(int buttonIndex)
{
    m_floatingNoteButtonList[buttonIndex]->setProperty("status", "current");
    for (QPushButton* button : m_floatingNoteButtonList)
    {
        if (button == m_floatingNoteButtonList[buttonIndex]) continue;
        button->setProperty("status", "default");
    }
}

void FloatingNotePanel::moveSlider(int buttonIndex)
{
    updateProperty(buttonIndex);
    this->setStyleSheet(this->styleSheet());

    QPropertyAnimation* animation = new QPropertyAnimation(m_floatingNoteButtonSlider, "pos");
    int startX = m_floatingNoteButtonSlider->x();
    int endX = m_floatingNoteButtonList[buttonIndex]->x();
    animation->setDuration(abs(endX - startX));
    animation->setStartValue(QPoint(m_floatingNoteButtonSlider->x(), 0));
    animation->setEndValue(QPoint(m_floatingNoteButtonList[buttonIndex]->x(), 0));
    animation->setEasingCurve(QEasingCurve::OutQuint);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void FloatingNotePanel::darkenOrBrightenRequest()
{
    if (this->isHidden())
    {
        emit SignalDarkenBackground();
    }
    else
    {
        emit SignalBrightenBackground();
    }
}

void FloatingNotePanel::switchPanel()
{
    this->updateUi();
    this->setHidden(!this->isHidden());
}

void FloatingNotePanel::updateUi()
{
    this->setGeometry(0, titleFrameHeight, this->parentWidget()->width(), this->parentWidget()->height() - titleFrameHeight);
    m_floatingNoteButtonSlider->setFixedWidth(m_allFloatingNoteButton->width());
}
