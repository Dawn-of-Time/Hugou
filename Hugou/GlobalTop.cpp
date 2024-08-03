#include "GlobalTop.h"

GlobalTop::GlobalTop(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);
}

void GlobalTop::blurOrClearBlurRequest()
{
    if (!isTopShown)
    {
        emit blurBackground();
    }
    else
    {
        emit clearBackground();
    }
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

void GlobalTop::setSource(QUrl url)
{
    ui.globalTopQuickWidget->setSource(url);
}

void GlobalTop::setHint(QString hint)
{
    ui.globalTopHint->setText(hint);
}

void GlobalTop::removeSource()
{
    ui.globalTopQuickWidget->setSource(QUrl("res/qml/empty.qml"));
}

void GlobalTop::updateUi(QWidget* Hugou)
{
    this->setGeometry(0, 0, Hugou->width(), Hugou->height());
}