#include "Controller/Include/Controller_Hugou.h"

HugouController::HugouController(HugouView* hugouView, HugouModel* hugouModel)
    : QObject(), m_hugouView(hugouView), m_hugouModel(hugouModel)
{
    m_preferenceController = new PreferenceController(hugouView->m_preferenceView, hugouModel->m_preferenceModel, this);
    m_scheduleController = new ScheduleController(hugouView->m_scheduleView, hugouModel->m_scheduleModel, this);

    // 为GlobalTopController指定视图。
    GlobalTopController::getController()->setView(hugouView->m_globalTopView);
    // 为MessegeHelper指定模式。
    MessegeHelper::getHelper()->setMode(MessegeHelper::UIPreparedMode);
    //FloatingNoteManager::getManager()->setParent(this);

    ThemeManager::getManager();
    
    // 信号与槽
    connect(m_hugouView->m_titleBarView, &TitleBarView::SignalMinimizeButtonClicked, m_hugouView, &HugouView::showMinimized);
    connect(m_hugouView->m_titleBarView, &TitleBarView::SignalScaleButtonClicked, m_hugouView, &HugouView::scale);
    connect(m_hugouView->m_titleBarView, &TitleBarView::SignalCloseButtonClicked, m_hugouView, &HugouView::closeHugou);
    connect(m_hugouView->m_asideBarView, &AsideBarView::SignalChangeStackedWidget, m_hugouView, &HugouView::changeStackedWidget);
    connect(m_preferenceController, &PreferenceController::SignalApplyTheme, ThemeManager::getManager(), &ThemeManager::loadThemeResource);
    connect(ThemeManager::getManager(), &ThemeManager::SignalApplyThemeResource, m_hugouView, &HugouView::applyThemeResource);
    connect(m_hugouView, &HugouView::SignalApplyThemeResourceFinished, []() { emit ThemeManager::getManager()->SignalApplyThemeResourceFinished(); });
}