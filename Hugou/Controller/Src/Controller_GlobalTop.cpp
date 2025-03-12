#include "Controller/Include/Controller_GlobalTop.h"

GlobalTopController::GlobalTopController()
{

}

GlobalTopController* GlobalTopController::getController()
{
    static GlobalTopController controller;
    return &controller;
}

void GlobalTopController::fadeInView(GlobalTopView::ResourceBinding* binding)
{
    m_globalTopView->loadResourceBinding(binding);
    m_globalTopView->fadeIn();
}

void GlobalTopController::fadeOutView()
{
    m_globalTopView->fadeOut();
}

void GlobalTopController::setView(GlobalTopView* globalTopView)
{
    m_globalTopView = globalTopView;
    connect(m_globalTopView, &GlobalTopView::SignalFadeInFinished, this, &GlobalTopController::SignalFadeInFinished);
    connect(m_globalTopView, &GlobalTopView::SignalFadeOutFinished, this, &GlobalTopController::SignalFadeOutFinished);
}

void GlobalTopController::startUsing()
{
    QMutexLocker locker(&m_mutex);
    m_refCount++;
}
void GlobalTopController::stopUsing()
{
    QMutexLocker locker(&m_mutex);
    m_refCount--;
    this->disconnect();
}