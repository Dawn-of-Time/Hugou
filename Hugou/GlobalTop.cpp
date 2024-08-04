#include "GlobalTop.h"

GlobalTop::GlobalTop(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);
    mainWindow = parent;
    timer = new QTimer(this);
}

void GlobalTop::fadeIn()
{
    timer->disconnect();
    this->setHidden(false);
    ui.globalTopQuickWidget->setHidden(true);
    ui.globalTopHint->setHidden(true);
    connect(timer, &QTimer::timeout, [&]() {
        int newAlpha = color.alpha() + 17;
        if (newAlpha <= 255)
        {
            color.setAlpha(newAlpha);
            update();
        }
        else
        {
            timer->stop();
            ui.globalTopQuickWidget->setHidden(false);
            ui.globalTopHint->setHidden(false);
        }
        });
    timer->start(100);
}

void GlobalTop::fadeOut()
{
    timer->disconnect();
    ui.globalTopQuickWidget->setHidden(true);
    ui.globalTopHint->setHidden(true);
    connect(timer, &QTimer::timeout, [&]() {
        int newAlpha = color.alpha() - 17;
        if (newAlpha >= 0)
        {
            color.setAlpha(newAlpha);
            update();
        }
        else
        {
            timer->stop();
            this->setHidden(true);
            removeSource();
        }
        });
    timer->start(100);
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
    ui.globalTopQuickWidget->setSource(QUrl("res/qml/empty.qml"));
}

void GlobalTop::updateUi(QWidget* Hugou)
{
    this->setGeometry(0, 0, Hugou->width(), Hugou->height());
}