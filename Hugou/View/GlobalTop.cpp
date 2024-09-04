#include "GlobalTop.h"

GlobalTop::GlobalTop(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);
    mainWindow = parent;
    effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(0);
    this->setGraphicsEffect(effect);
}

void GlobalTop::fadeIn()
{
    this->setHidden(false);
    QPropertyAnimation* animation = new QPropertyAnimation(effect, "opacity", this);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setDuration(500);
    connect(animation, &QPropertyAnimation::finished, [&]() { emit fadeInFinished(); });
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void GlobalTop::fadeOut()
{
    QPropertyAnimation* animation = new QPropertyAnimation(effect, "opacity", this);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setDuration(500);
    connect(animation, &QPropertyAnimation::finished, [&]() {
        this->setHidden(true);
        removeSource();
        });
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void GlobalTop::switchTop()
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

void GlobalTop::setSource(QString filename)
{
    ui.globalTopQuickWidget->setSource(QUrl(filename));
    ui.globalTopQuickWidget->show();
}

void GlobalTop::setHint(QString hint)
{
    ui.globalTopHint->setText(hint);
}

void GlobalTop::removeSource()
{
    ui.globalTopQuickWidget->setSource(QUrl("qrc:/qml/empty.qml"));
}

void GlobalTop::updateUi(QWidget* Hugou)
{
    this->setGeometry(0, 0, Hugou->width(), Hugou->height());
}