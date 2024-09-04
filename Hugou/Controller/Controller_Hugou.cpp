#include "Controller_Hugou.h"

HugouController::HugouController(HugouView* hugouView, HugouModel* hugouModel)
    : QObject(), m_hugouView(hugouView), m_hugouModel(hugouModel)
{
    m_settingsController = new SettingsController(hugouView->m_settingsView, hugouModel->m_settingsModel);
    m_hugouModel = hugouModel;

    // 信号与槽
    connect(m_hugouView->m_titleBarView, &TitleBarView::floatingNotePanelButtonClicked, m_hugouView->m_floatingNotePanel, &FloatingNotePanel::blurOrClearBlurRequest);
    connect(m_hugouView->m_floatingNotePanel, &FloatingNotePanel::blurBackground, m_hugouView, &HugouView::blur);
    connect(m_hugouView->m_floatingNotePanel, &FloatingNotePanel::clearBackground, m_hugouView, &HugouView::clearBlur);
    connect(m_hugouView->m_asideBarView, &AsideBarView::SignalChangeStackedWidget, this, &HugouController::changeStackedWidgetRequest);
    connect(m_settingsController, &SettingsController::SignalApplyTheme, [&](QString theme) { applyThemeRequest(false, theme); });

    applyThemeRequest(true);
}

HugouController::~HugouController()
{
    delete m_settingsController;
}

void HugouController::applyThemeRequest(bool startup, QString theme)
{
    // 获取或从设置中（如果是首次）加载主题
    if (theme.isEmpty())
        theme = m_hugouModel->getTheme();
    if (startup)
    {
        HugouModel::ThemeResource themeResource = m_hugouModel->loadThemeResource(theme);
        if (m_hugouView->applyThemeResource(themeResource.generalStyleSheet, themeResource.asideBarStyleSheet, themeResource.settingsStyleSheet))
            m_hugouModel->setTheme(theme);
    }
    else
    {
        connect(m_hugouView->m_globalTop, &GlobalTop::fadeInFinished, [=]()
            {
                HugouModel::ThemeResource themeResource = m_hugouModel->loadThemeResource(theme);
                if (m_hugouView->applyThemeResource(themeResource.generalStyleSheet, themeResource.asideBarStyleSheet, themeResource.settingsStyleSheet))
                    m_hugouModel->setTheme(theme);
                m_hugouView->endToApplyThemeResourceFinished();
            });
        m_hugouView->startToApplyThemeResource(theme);
    }
}

void HugouController::changeStackedWidgetRequest(int index)
{
    m_hugouView->changeStackedWidgetRequest(index);
}

// 槽函数
void HugouController::openPDFEditFunction()
{
    //FileImportDialog* fileImportDialog = new FileImportDialog(this);
    //fileImportDialog->show();
    //connect(fileImportDialog, &FileImportDialog::uploadSuccessed, [&](QString fileName) 
    //    {
    //        pdfEdit = new PDFEdit(fileName);
    //    });
}