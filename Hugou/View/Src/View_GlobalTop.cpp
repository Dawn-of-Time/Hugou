#include "View/Include/View_GlobalTop.h"

GlobalTopView::GlobalTopView(QWidget* parent) :
	QWidget(parent)
{
    setupUi();
}

GlobalTopView::~GlobalTopView()
{
    removeSource();
}

void GlobalTopView::setupUi()
{
    // ×ÖÌåÇåµ¥
    const QFont hintFont = QFont("Roboto", 18, QFont::Normal);

    this->setObjectName("globalTop");
    m_effect = new QGraphicsOpacityEffect(this);
    m_effect->setOpacity(0);
    this->setGraphicsEffect(m_effect);
    m_effect->setEnabled(false);

    m_globalTopLayout = new QVBoxLayout(this);
    m_globalTopLayout->setSpacing(0);
    m_globalTopQuickWidget = new QQuickWidget(this);
    m_globalTopQuickWidget->setObjectName("globalTopQuickWidget");
    m_globalTopQuickWidget->setFixedSize(360, 360);
    QSizePolicy globalTopQuickWidgetSizePolicy = m_globalTopQuickWidget->sizePolicy();
    globalTopQuickWidgetSizePolicy.setRetainSizeWhenHidden(true);
    m_globalTopQuickWidget->setSizePolicy(globalTopQuickWidgetSizePolicy);

    m_globalTopHint = new QLabel(this);
    m_globalTopHint->setFont(hintFont);
    m_globalTopHint->setAlignment(Qt::AlignCenter);
    QSizePolicy globalTopHintSizePolicy = m_globalTopHint->sizePolicy();
    globalTopHintSizePolicy.setRetainSizeWhenHidden(true);
    m_globalTopHint->setSizePolicy(globalTopHintSizePolicy);

    m_globalTopLayout->addStretch(1);
    m_globalTopLayout->addWidget(m_globalTopQuickWidget, 0, Qt::AlignHCenter);
    m_globalTopLayout->addWidget(m_globalTopHint, 0, Qt::AlignHCenter);
    m_globalTopLayout->addStretch(1);

    this->setHidden(true);
}

void GlobalTopView::fadeIn()
{
    this->setHidden(false);
    m_effect->setEnabled(true);
    QPropertyAnimation* animation = new QPropertyAnimation(m_effect, "opacity", this);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setDuration(700);
    connect(animation, &QPropertyAnimation::finished, [&]() { emit SignalFadeInFinished(); m_effect->setEnabled(false); });
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void GlobalTopView::fadeOut()
{
    m_effect->setEnabled(true);
    QPropertyAnimation* animation = new QPropertyAnimation(m_effect, "opacity", this);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setDuration(700);
    connect(animation, &QPropertyAnimation::finished, [&]() {
        this->setHidden(true);
        m_effect->setEnabled(false);
        removeSource();
        emit SignalFadeOutFinished();
        });
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void GlobalTopView::switchTop()
{
    if (!m_isTopShown)
    {
        this->setHidden(false);
        m_isTopShown = true;
    }
    else
    {
        this->setHidden(true);
        m_isTopShown = false;
    }
}

void GlobalTopView::loadResourceBinding(ResourceBinding* binding)
{
    m_binding = binding;
    setSource(binding->qmlFileName);
    setHint(binding->hint);
}

void GlobalTopView::setSource(const QString& filename)
{
    m_globalTopQuickWidget->engine()->clearComponentCache();
    m_globalTopQuickWidget->setSource(QUrl(filename));
    m_globalTopQuickWidget->show();
}

void GlobalTopView::setHint(const QString& hint)
{
    m_globalTopHint->setText(hint);
}

void GlobalTopView::removeSource()
{
    m_globalTopQuickWidget->setSource(QUrl());
    delete m_binding;
    m_binding = nullptr;
}