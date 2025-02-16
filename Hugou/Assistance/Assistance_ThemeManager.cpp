#include "Assistance_ThemeManager.h"

ThemeManager::ThemeManager(QWidget* hugou, QWidget* asideBarView, QWidget* preferenceView, GlobalTopView* globalTopView)
    : QObject(), m_hugou(hugou), m_asideBarView(asideBarView), m_preferenceView(preferenceView), m_globalTopView(globalTopView)
{
    connect(this, &ThemeManager::SignalThemeResourcePrepared, this, &ThemeManager::applyThemeForStartup);
}

ThemeManager::~ThemeManager()
{
}

QString ThemeManager::getTheme()
{
    if (m_theme.isEmpty())
    {
        preferenceHelper* helper = preferenceHelper::getHelper();
        QString theme;
        if (helper->getpreferenceValue("theme", theme))
            m_theme = theme;
        else m_theme = "Default";
    }
    return m_theme;
}

void ThemeManager::loadThemeResource(QString theme)
{
    if (theme.isEmpty()) theme = getTheme();
    m_tempTheme = theme;    // m_tempTheme是目标主题（用户希望的
    LoadThemeResourceThread* loadThemeResourceThread = new LoadThemeResourceThread;
    connect(loadThemeResourceThread, &LoadThemeResourceThread::SignalThemeResourcePreparedInThread, [&](ThemeResource* themeResource, bool consistentFlag)
        {
            // 如果所希望应用的主题和主题资源一致，则将ThemeManager的m_theme变更为m_tempTheme。否则不变。
            if (consistentFlag) m_theme = m_tempTheme;
            emit SignalThemeResourcePrepared(themeResource, consistentFlag);
        });
    connect(loadThemeResourceThread, &LoadThemeResourceThread::finished, loadThemeResourceThread, &LoadThemeResourceThread::deleteLater);
    loadThemeResourceThread->setTheme(theme);
    // 下述线程一定能够得到可行的主题资源。
    loadThemeResourceThread->start();
}

// 下面两个应用主题的函数分别用于第一次加载和后续手动变更两种情况。
// 它们都经由ThemeManager的SignalThemeResourcePrepared信号触发。
// ThemeManager一定可以得到可行的主题，因此两个函数都不需要进行失败的判定。ThemeManager中通过getTheme得到的主题一定是与当前主题资源匹配的主题。
// consistentFlag--希望应用的主题和加载的主题资源是否一致。如果不一致，则需要将preferenceComboboxMap["themeBox"]：
// * 如果是第一次加载的情况，改为Default；
// * 如果是后续手动变更的情况，则改为ThemeManager中通过getTheme得到的主题名称。
void ThemeManager::applyThemeForStartup(ThemeResource* themeResource, bool consistentFlag)
{
    // 若为第一次加载，那么无需播放动画，并且重新连接ThemeManager的信号和槽。
    if (!consistentFlag) emit SignalUpdateThemeComboboxValue("Default");
    applyThemeResource(themeResource);
    disconnect();
    connect(this, &ThemeManager::SignalThemeResourcePrepared, this, &ThemeManager::applyTheme);
}

void ThemeManager::applyTheme(ThemeResource* themeResource, bool consistentFlag)
{
    // 若不为第一次加载，那么需要执行动画。
    if (!consistentFlag)  emit SignalUpdateThemeComboboxValue(m_theme);
    preferenceHelper::getHelper()->setpreferenceValue("theme", m_theme);
    m_globalTopView->disconnect();
    connect(m_globalTopView, &GlobalTopView::fadeInFinished, [=]()
        {
            applyThemeResource(themeResource);
            endToApplyThemeResourceFinished();
        });
    connect(m_globalTopView, &GlobalTopView::fadeOutFinished, [=]()
        {
            FloatingNoteManager::getManager()->raiseFloatingNote(FloatingNote::Type::Success, successNoteMap["10000"] + m_theme + ".");
        });
    startToApplyThemeResource(m_theme);
}

void ThemeManager::startToApplyThemeResource(QString theme)
{
    m_globalTopView->setSource("qrc:/qml/themeApplyMedia.qml");
    m_globalTopView->setHint(tr("Upcoming theme: ") + theme);
    m_globalTopView->fadeIn();
}

void ThemeManager::applyThemeResource(ThemeResource* themeResource)
{

    QString generalStyleSheet = themeResource->generalStyleSheet;
    QString asideBarStyleSheet = themeResource->asideBarStyleSheet;
    QString preferenceStyleSheet = themeResource->preferenceStyleSheet;
    m_hugou->setStyleSheet(generalStyleSheet);
    m_asideBarView->setStyleSheet(asideBarStyleSheet);
    m_preferenceView->setStyleSheet(preferenceStyleSheet);
    delete themeResource;
}

void ThemeManager::endToApplyThemeResourceFinished()
{
    m_globalTopView->fadeOut();
}

void LoadThemeResourceThread::run()
{
    QFile generalStyleFile(QString(":/theme/%1/general.qss").arg(m_theme));
    QFile asideBarStyleFile(QString(":/theme/%1/asideBar.qss").arg(m_theme));
    QFile preferenceStyleFile(QString(":/theme/%1/preference.qss").arg(m_theme));
    bool isExisted = generalStyleFile.exists() && asideBarStyleFile.exists() && preferenceStyleFile.exists();
    bool isCorrect = generalStyleFile.open(QIODeviceBase::ReadOnly) && asideBarStyleFile.open(QIODeviceBase::ReadOnly) &&
        preferenceStyleFile.open(QIODeviceBase::ReadOnly);
    // 校验存在性
    if (!isExisted)
    {
        // Default主题文件是否存在和是否有效都不触发错误。其主题内容被硬编码到程序中。但是，如果有该主题的文件，就使用该主题文件的内容。
        if (m_theme != "Default")
        {
            preferenceHelper* helper = preferenceHelper::getHelper();
            emit helper->triggerError("10100");
            m_theme = "Default";
            m_themeResource = getDefaultThemeResource();
            m_isConsistent = false;
        }
    }
    // 校验正确性
    else if (isExisted && !isCorrect)
    {
        if (m_theme != "Default")
        {
            preferenceHelper* helper = preferenceHelper::getHelper();
            emit helper->triggerError("10101");
            m_theme = "Default";
            m_themeResource = getDefaultThemeResource();
            m_isConsistent = false;
        }
    }
    else
    {
        QString generalStyleSheet = QTextStream(&generalStyleFile).readAll();
        QString asideBarStyleSheet = QTextStream(&asideBarStyleFile).readAll();
        QString preferenceStyleSheet = QTextStream(&preferenceStyleFile).readAll();
        // 校验是否为空
        if (generalStyleSheet.isEmpty() || asideBarStyleSheet.isEmpty() || preferenceStyleSheet.isEmpty())
        {
            if (m_theme != "Default")
            {
                preferenceHelper* helper = preferenceHelper::getHelper();
                emit helper->triggerError("10103");
                m_theme = "Default";
                m_themeResource = getDefaultThemeResource();
                m_isConsistent = false;
            }
        }
        else
        {
            m_themeResource->generalStyleSheet = generalStyleSheet;
            m_themeResource->asideBarStyleSheet = asideBarStyleSheet;
            m_themeResource->preferenceStyleSheet = preferenceStyleSheet;
            m_isConsistent = true;
        }
    }
    generalStyleFile.close();
    asideBarStyleFile.close();
    preferenceStyleFile.close();
    emit SignalThemeResourcePreparedInThread(m_themeResource, m_isConsistent);
}

ThemeResource* LoadThemeResourceThread::getDefaultThemeResource()
{
    ThemeResource* themeResource = new ThemeResource{};
    themeResource->generalStyleSheet = defaultGeneralStyleSheet;
    themeResource->asideBarStyleSheet = defaultAsideBarStyleSheet;
    themeResource->preferenceStyleSheet = defaultpreferenceStyleSheet;
    return themeResource;
}