#include "Controller_Hugou.h"

HugouController::HugouController(HugouView* hugouView, HugouModel* hugouModel)
    : QObject(), m_hugouView(hugouView), m_hugouModel(hugouModel)
{
    m_preferenceController = new PreferenceController(hugouView->m_preferenceView, hugouModel->m_preferenceModel);
    m_scheduleController = new ScheduleController(hugouView->m_scheduleView, hugouModel->m_scheduleModel);

    // 为preferenceHelper指定Hugou。
    preferenceHelper::getHelper()->setHugou(m_hugouView);

    m_themeManager = new ThemeManager(m_hugouView, m_hugouView->m_asideBarView, m_hugouView->m_preferenceView, m_hugouView->m_globalTopView);
    
    // 信号与槽
    connect(m_hugouView->m_titleBarView, &TitleBarView::SignalFloatingNotePanelButtonClicked, m_hugouView->m_floatingNotePanel, &FloatingNotePanel::darkenOrBrightenRequest);
    connect(m_hugouView->m_titleBarView, &TitleBarView::SignalMinimizeButtonClicked, m_hugouView, &HugouView::showMinimized);
    connect(m_hugouView->m_titleBarView, &TitleBarView::SignalScaleButtonClicked, m_hugouView, &HugouView::scale);
    connect(m_hugouView->m_titleBarView, &TitleBarView::SignalCloseButtonClicked, m_hugouView, &HugouView::closeHugou);
    connect(m_hugouView->m_floatingNotePanel, &FloatingNotePanel::SignalDarkenBackground, m_hugouView, &HugouView::darken);
    connect(m_hugouView->m_floatingNotePanel, &FloatingNotePanel::SignalBrightenBackground, m_hugouView, &HugouView::brighten);
    connect(m_hugouView->m_asideBarView, &AsideBarView::SignalChangeStackedWidget, m_hugouView, &HugouView::changeStackedWidget);
    connect(m_preferenceController, &PreferenceController::SignalApplyTheme, m_themeManager, &ThemeManager::loadThemeResource);
    connect(m_themeManager, &ThemeManager::SignalUpdateThemeComboboxValue, m_preferenceController, &PreferenceController::updateThemeComboboxValue);

    m_themeManager->loadThemeResource();
}

HugouController::~HugouController()
{
    delete m_preferenceController;
	delete m_scheduleController;
    delete m_themeManager;
}


void HugouController::openPDFEditFunction()
{
    //FileImportDialog* fileImportDialog = new FileImportDialog(this);
    //fileImportDialog->show();
    //connect(fileImportDialog, &FileImportDialog::uploadSuccessed, [&](QString fileName) 
    //    {
    //        pdfEdit = new PDFEdit(fileName);
    //    });
}