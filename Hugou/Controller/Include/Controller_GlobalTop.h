#pragma once
#include <QObject>
#include <QMutex>
#include "View/Include/View_GlobalTop.h"

class GlobalTopController :
    public QObject
{
    Q_OBJECT

public:
    static GlobalTopController* getController();

    void setView(GlobalTopView* globalTopView);
    void fadeInView(GlobalTopView::ResourceBinding* binding);
    void fadeOutView();

    bool isAvailable()
    {
        QMutexLocker locker(&m_mutex);
        return m_refCount == 0;
    }

signals:
    void SignalFadeInFinished();
    void SignalFadeOutFinished();

private:
    QMutex m_mutex;
    int m_refCount = 0;
    GlobalTopView* m_globalTopView;
    GlobalTopController();
    GlobalTopController(const GlobalTopController&) = delete;
    GlobalTopController& operator=(const GlobalTopController&) = delete;
    void startUsing();
    void stopUsing();

public:
    class UsageGuard
    {
    public:
        UsageGuard(GlobalTopController* controller) : m_controller(controller)
        {
            if (m_controller) m_controller->startUsing();
        }

        ~UsageGuard()
        {
            if (m_controller) m_controller->stopUsing();
        }

    private:
        GlobalTopController* m_controller;
    };

    UsageGuard* use()
    {
        return new UsageGuard(this);
    }

    friend class UsageGuard;
};



