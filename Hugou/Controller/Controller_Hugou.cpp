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
    connect(m_settingsController, &SettingsController::SignalApplyTheme, [&](QString theme) { applyThemeRequest(theme); });

    applyThemeRequestForStartup();
    SettingsHelper* helper = SettingsHelper::getHelper();
    helper->setHugou(m_hugouView);
}

HugouController::~HugouController()
{
    delete m_settingsController;
}

void HugouController::applyThemeRequestForStartup()
{
    // 若为第一次加载，那么就从hugouModel中获取主题（getTheme会在第一次加载主题时从设置中读取主题）。
    // 应用主题成功-hugouModel的成员变量m_theme设置为对应主题；
    // 应用主题失败-hugouModel的成员变量m_theme设置为默认主题，并将设置页的themeBox的当前文字替代为Default。
    QString theme = m_hugouModel->getTheme();
    HugouModel::ThemeResource themeResource = m_hugouModel->loadThemeResource(theme);
    if (m_hugouView->applyThemeResource(themeResource.generalStyleSheet, themeResource.asideBarStyleSheet, themeResource.settingsStyleSheet))
        m_hugouModel->setTheme(theme);
    else
    {
        m_hugouModel->setTheme("Default");
        m_settingsController->m_userChanged = false;
        settingsComboboxMap["themeBox"]->setCurrentText("Default");
        m_settingsController->m_userChanged = true;
    }
}

void HugouController::applyThemeRequest(QString theme)
{
    // 若不为第一次加载，那么一定是用户对主题进行变更，此时执行动画。
    // 应用主题成功-hugouModel的成员变量m_theme设置为对应主题，然后写入配置；
    // 应用主题失败-hugouModel的成员变量m_theme不变更，并将设置页的themeBox的当前文字恢复为变更前的主题名。
    m_hugouView->m_globalTopView->disconnect();
    connect(m_hugouView->m_globalTopView, &GlobalTopView::fadeInFinished, [=]()
        {
            HugouModel::ThemeResource themeResource = m_hugouModel->loadThemeResource(theme);
            if (m_hugouView->applyThemeResource(themeResource.generalStyleSheet, themeResource.asideBarStyleSheet, themeResource.settingsStyleSheet))
            {
                m_hugouModel->setTheme(theme);
                SettingsHelper* helper = SettingsHelper::getHelper();
                helper->writeSettings("theme", theme);
            }
            else
            {
                m_settingsController->m_userChanged = false;
                settingsComboboxMap["themeBox"]->setCurrentText(m_hugouModel->getTheme());
                m_settingsController->m_userChanged = true;
            }
            m_hugouView->endToApplyThemeResourceFinished();
        });
    connect(m_hugouView->m_globalTopView, &GlobalTopView::fadeOutFinished, [=]()
        {
            floatingNoteManager.raiseFloatingNote(m_hugouView, FloatingNote::Type::Success, successNoteMap["10000"] + theme + ".");
        });
    m_hugouView->startToApplyThemeResource(theme);
}

void HugouController::changeStackedWidgetRequest(int index)
{
    m_hugouView->changeStackedWidget(index);
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