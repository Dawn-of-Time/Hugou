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
    FloatingNoteManager::getManager()->setParent(this);

    m_themeManager = new ThemeManager(QList<QWidget*>({ m_hugouView, m_hugouView->m_asideBarView, m_hugouView->m_preferenceView }), this);
    
    // 信号与槽
    //connect(m_hugouView->m_titleBarView, &TitleBarView::SignalFloatingNotePanelButtonClicked, m_hugouView->m_floatingNotePanel, &FloatingNotePanel::darkenOrBrightenRequest);
    connect(m_hugouView->m_titleBarView, &TitleBarView::SignalMinimizeButtonClicked, m_hugouView, &HugouView::showMinimized);
    connect(m_hugouView->m_titleBarView, &TitleBarView::SignalScaleButtonClicked, m_hugouView, &HugouView::scale);
    connect(m_hugouView->m_titleBarView, &TitleBarView::SignalCloseButtonClicked, m_hugouView, &HugouView::closeHugou);
    //connect(m_hugouView->m_floatingNotePanel, &FloatingNotePanel::SignalDarkenBackground, m_hugouView, &HugouView::darken);
    //connect(m_hugouView->m_floatingNotePanel, &FloatingNotePanel::SignalBrightenBackground, m_hugouView, &HugouView::brighten);
    connect(m_hugouView->m_asideBarView, &AsideBarView::SignalChangeStackedWidget, m_hugouView, &HugouView::changeStackedWidget);
    connect(m_preferenceController, &PreferenceController::SignalApplyTheme, m_themeManager, &ThemeManager::loadThemeResource);
}