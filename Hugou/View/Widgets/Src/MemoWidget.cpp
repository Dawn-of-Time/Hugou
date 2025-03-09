#include "View/Widgets/Include/MemoWidget.h"

MemoWidget::MemoWidget(Memo* memo, QWidget* parent)
    :QWidget(parent), m_memo(memo)
{
    setupUi();
    connect(m_memoBriefWidget, &FadeEffectButton::clicked, this, &MemoWidget::showMemoSetting);
}

void MemoWidget::setupUi()
{
    // 字体清单
    QFont memoContentFont = QFont("NeverMind", 14, QFont::Medium);
    QFont memoSubContentFont = QFont("NeverMind", 12, QFont::Normal);

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(8);
    m_layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    m_memoBriefWidget = new FadeEffectButton(this);
    m_memoBriefWidget->setFixedHeight(60);
    m_memoBriefWidget->setCursor(Qt::PointingHandCursor);
    m_memoBriefWidget->setBackgroundWidgetStyleSheet("background-color: #EAF9FE; border-radius: 10px");
    m_memoBriefWidgetLayout = new QHBoxLayout(m_memoBriefWidget);
    m_memoBriefWidgetLayout->setContentsMargins(0, 12, 0, 12);
    m_memoBriefWidgetLayout->setSpacing(8);

    m_dropDownButton = new QPushButton(m_memoBriefWidget);
    m_dropDownButton->setFixedSize(12, 12);
    m_checkBox = new CheckBox(m_memoBriefWidget);

    m_memoContentWidget = new QWidget(m_memoBriefWidget);
    m_memoContentWidgetLayout = new QVBoxLayout(m_memoContentWidget);
    m_memoContentWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_memoContentWidgetLayout->setSpacing(0);

    m_memoContent = new QLabel(m_memoContentWidget);
    if (m_memo->ID == -1) m_memoContent->setText(tr("What do you want to do?"));
    m_memoContent->setFixedHeight(20);
    m_memoContent->setFont(memoContentFont);
    m_memoContent->setStyleSheet("color: #4F5E71");

    m_memoSubContent = new QLabel(tr("Click here to add a new memo."), m_memoContentWidget);
    if (m_memo->ID == -1) m_memoSubContent->setText(tr("What do you want to do?"));
    m_memoSubContent->setFixedHeight(20);
    m_memoSubContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_memoSubContent->setFont(memoSubContentFont);
    m_memoSubContent->setStyleSheet("color: #ACB1C6");

    m_memoContentWidgetLayout->addWidget(m_memoContent);
    m_memoContentWidgetLayout->addWidget(m_memoSubContent);

    m_memoBriefWidgetLayout->addWidget(m_dropDownButton);
    m_memoBriefWidgetLayout->addWidget(m_checkBox);
    m_memoBriefWidgetLayout->addWidget(m_memoContentWidget);

    m_memoSetting = new MemoSettingView(this, m_memo);

    m_layout->addWidget(m_memoBriefWidget);
    m_layout->addWidget(m_memoSetting);
}

void MemoWidget::showMemoSetting()
{
    m_memoBriefWidget->blockSignals(true);
    m_memoBriefWidget->disconnect();
    connect(m_memoBriefWidget, &FadeEffectButton::clicked, this, &MemoWidget::hideMemoSetting);
    int memoSettingHeight = m_memoSetting->getSuitableHeight();
    QPropertyAnimation* memoSettingExpandAnimation = new QPropertyAnimation(m_memoSetting, "minimumHeight");
    memoSettingExpandAnimation->setStartValue(0);
    memoSettingExpandAnimation->setEndValue(memoSettingHeight);
    memoSettingExpandAnimation->setDuration(700);
    memoSettingExpandAnimation->setEasingCurve(QEasingCurve::OutQuart);
    connect(memoSettingExpandAnimation, &QPropertyAnimation::finished, [this]()
        {
            QParallelAnimationGroup* group = m_memoSetting->fadeIn();
            connect(group, &QParallelAnimationGroup::finished, m_memoBriefWidget, [this](){ m_memoBriefWidget->blockSignals(false); });
            group->start(QPropertyAnimation::DeleteWhenStopped);
        });
    connect(memoSettingExpandAnimation, &QPropertyAnimation::valueChanged, m_layout, &QVBoxLayout::update);
    memoSettingExpandAnimation->start(QPropertyAnimation::DeleteWhenStopped);
}

void MemoWidget::hideMemoSetting()
{
    m_memoBriefWidget->blockSignals(true);
    m_memoBriefWidget->disconnect();
    connect(m_memoBriefWidget, &FadeEffectButton::clicked, this, &MemoWidget::showMemoSetting);
    QParallelAnimationGroup* group = m_memoSetting->fadeOut();
    connect(group, &QParallelAnimationGroup::finished, [this]()
        {
            QPropertyAnimation* memoSettingCollapseAnimation = new QPropertyAnimation(m_memoSetting, "minimumHeight");
            memoSettingCollapseAnimation->setEndValue(0);
            memoSettingCollapseAnimation->setDuration(700);
            memoSettingCollapseAnimation->setEasingCurve(QEasingCurve::OutQuart);
            connect(memoSettingCollapseAnimation, &QPropertyAnimation::valueChanged, m_layout, &QVBoxLayout::update);
            connect(memoSettingCollapseAnimation, &QPropertyAnimation::valueChanged, [this]() { parentWidget()->update(); });  // 用于消除残影
            connect(memoSettingCollapseAnimation, &QPropertyAnimation::finished, m_memoSetting, &MemoSettingView::disableGraphicEffect);
            connect(memoSettingCollapseAnimation, &QPropertyAnimation::finished, m_memoBriefWidget, [this]() { m_memoBriefWidget->blockSignals(false); });
            memoSettingCollapseAnimation->start(QPropertyAnimation::DeleteWhenStopped);
        });
    group->start(QParallelAnimationGroup::DeleteWhenStopped);
}