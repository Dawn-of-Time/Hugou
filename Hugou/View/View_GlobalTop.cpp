#include "View_GlobalTop.h"

GlobalTopView::GlobalTopView(QWidget* parent) :
	QWidget(parent)
{
    setupUi();
    m_effect = new QGraphicsOpacityEffect(this);
    m_effect->setOpacity(0);
    this->setGraphicsEffect(m_effect);
}

void GlobalTopView::setupUi()
{
    this->setObjectName("globalTop");
    this->setGeometry(0, 0, mainWindowWidth, mainWindowHeight);
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
    QPropertyAnimation* animation = new QPropertyAnimation(m_effect, "opacity", this);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setDuration(500);
    connect(animation, &QPropertyAnimation::finished, [&]() { emit fadeInFinished(); });
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void GlobalTopView::fadeOut()
{
    QPropertyAnimation* animation = new QPropertyAnimation(m_effect, "opacity", this);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setDuration(500);
    connect(animation, &QPropertyAnimation::finished, [&]() {
        this->setHidden(true);
        removeSource();
        emit fadeOutFinished();
        });
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void GlobalTopView::switchTop()
{
    if (!isTopShown)
    {
        this->setHidden(false);
        isTopShown = true;
    }
    else
    {
        this->setHidden(true);
        isTopShown = false;
    }
}

void GlobalTopView::setSource(QString filename)
{
    m_globalTopQuickWidget->setSource(QUrl(filename));
    m_globalTopQuickWidget->show();
}

void GlobalTopView::setHint(QString hint)
{
    m_globalTopHint->setText(hint);
}

void GlobalTopView::removeSource()
{
    m_globalTopQuickWidget->setSource(QUrl("qrc:/qml/empty.qml"));
}

void GlobalTopView::updateUi(QWidget* Hugou)
{
    this->setGeometry(0, 0, Hugou->width(), Hugou->height());
}