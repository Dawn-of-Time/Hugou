#include "Utils/Include/Utils_ThemeManager.h"

ThemeManager::ThemeManager(QList<QWidget*> objectList, QObject* parent)
    : QObject(parent)
{
    m_hugou = objectList[0];
    m_asideBarView = objectList[1];
    m_preferenceView = objectList[2];

    QString theme;
    if (ConfigurationHelper::getHelper()->getPreferenceValue("theme", theme)) m_theme = theme;
    else m_theme = "Default";

    connect(this, &ThemeManager::SignalThemeResourcePrepared, this, &ThemeManager::applyThemeForStartup);

    loadThemeResource(m_theme);
}

ThemeManager::~ThemeManager()
{
}

void ThemeManager::loadThemeResource(QString theme)
{
    m_tempTheme = theme;    // m_tempTheme是目标主题（用户希望的)
    LoadThemeResourceThread* loadThemeResourceThread = new LoadThemeResourceThread(theme);
    connect(loadThemeResourceThread, &LoadThemeResourceThread::SignalThemeResourcePreparedInThread, [&](ThemeResource* themeResource, bool consistentFlag)
        {
            // 如果所希望应用的主题和主题资源一致，则将ThemeManager的m_theme变更为m_tempTheme。否则不变。
            if (consistentFlag) m_theme = m_tempTheme;
            emit SignalThemeResourcePrepared(themeResource);
        });
    connect(loadThemeResourceThread, &LoadThemeResourceThread::finished, loadThemeResourceThread, &LoadThemeResourceThread::deleteLater);
    // 下述线程一定能够得到可行的主题资源。
    loadThemeResourceThread->start();
}

// 下面两个应用主题的函数分别用于第一次加载和后续手动变更两种情况。
// 它们都经由ThemeManager的SignalThemeResourcePrepared信号触发。
// ThemeManager一定可以得到可行的主题，因此两个函数都不需要进行失败的判定。ThemeManager中通过getTheme得到的主题一定是与当前主题资源匹配的主题。
// consistentFlag--希望应用的主题和加载的主题资源是否一致。如果不一致，则需要将preferenceComboboxMap["themeBox"]：
// * 如果是第一次加载的情况，改为Default；
// * 如果是后续手动变更的情况，则改为ThemeManager中通过getTheme得到的主题名称。
void ThemeManager::applyThemeForStartup(ThemeResource* themeResource)
{
    // 若为第一次加载，那么无需播放动画，并且重新连接ThemeManager的信号和槽。
    applyThemeResource(themeResource);
    disconnect();
    connect(this, &ThemeManager::SignalThemeResourcePrepared, this, &ThemeManager::applyTheme);
}

void ThemeManager::applyTheme(ThemeResource* themeResource)
{
    // 若不为第一次加载，那么需要执行动画。
    // 获取GlobalTop控制器使用权。
    GlobalTopController* controller = GlobalTopController::getController();
    if (controller->isAvailable())
    {
        m_globalTopUsagePermission = controller->use();
        connect(controller, &GlobalTopController::SignalFadeInFinished, [this, themeResource]()
            {
                applyThemeResource(themeResource);
            });
        connect(this, &ThemeManager::SignalApplyThemeResourceFinished, controller, &GlobalTopController::fadeOutView);
        connect(controller, &GlobalTopController::SignalFadeOutFinished, [this]()
            {
                ConfigurationHelper::getHelper()->setPreferenceValue("theme", m_theme);
                emit MessegeHelper::getHelper()->trigger(FloatingNote::Success, 10000, m_theme + ".");
                // 归还GlobalTop控制器使用权。
                delete m_globalTopUsagePermission;
            });
        GlobalTopView::ResourceBinding* binding = new GlobalTopView::ResourceBinding();
        binding->qmlFileName = "qrc:/qml/themeApplyMedia.qml";
        binding->hint = tr("Upcoming theme: ") + m_theme;
        controller->fadeInView(binding);
    }
    else qDebug() << "[HUGOU] ThemeManager: Can not use GlobalTopController.";
}

void ThemeManager::applyThemeResource(ThemeResource* themeResource)
{
    QString generalStyleSheet = themeResource->generalStyleSheet;
    QString asideBarStyleSheet = themeResource->asideBarStyleSheet;
    QString preferenceStyleSheet = themeResource->preferenceStyleSheet;
    m_hugou->setStyleSheet(generalStyleSheet);
    m_asideBarView->setStyleSheet(asideBarStyleSheet);
    m_preferenceView->setStyleSheet(preferenceStyleSheet);
    emit SignalApplyThemeResourceFinished();
    delete themeResource;
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
            emit MessegeHelper::getHelper()->trigger(FloatingNote::Error, 10100);
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
            emit MessegeHelper::getHelper()->trigger(FloatingNote::Error, 10101);
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
                emit MessegeHelper::getHelper()->trigger(FloatingNote::Error, 10103);
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
    // 默认主题
    const QString defaultGeneralStyleSheet =
        QString("HugouView#hugou { background-color: #F0F4FD; }")
        + QString("QWidget#asideBarAndStackedWidget { background-color: transparent; }")
        + QString("QStackedWidget#stackedWidget { margin-bottom: 10px; margin-right: 10px; border-radius: 10px; background-color: rgba(255, 255, 255, 0.8);}");

    const QString defaultAsideBarStyleSheet =
        QString("QLabel { padding-left: 6px; color:#666666; background-color: transparent; }")
        + QString("QLabel#userAvatar { padding: 0px; border-radius: 24px; border: none; color: balck; background-color: transparent;} ")
        + QString("QLabel#userNickname { border: none; color: balck; background-color: transparent;} ")
        + QString("QLabel#userID { border: none; color: balck; background-color: transparent;} ")
        + QString("QPushButton[status=\"default\"] { border-radius: 10px; }")
        + QString("QPushButton[status=\"default\"] > QLabel { padding: 0px; margin :0px; color: #434343; background-color: transparent; }")
        + QString("QPushButton[status=\"current\"] { border-radius: 10px;}")
        + QString("QPushButton[status=\"current\"] > QLabel { padding: 0px; margin :0px; color: #377FED; background-color: transparent; }");

    const QString defaultpreferenceStyleSheet =
        QString("QStackedWidget { background-color: transparent; border: none }")
        + QString("QTreeWidget { background-color: transparent; border: none }")
        + QString("QListWidget { background-color: transparent; border: none; outline: none; margin-left: 20px; margin-right: 12px; margin-top: 2px; margin-bottom: 2px }")
        + QString("QListWidget::item:hover { background-color: transparent }")
        + QString("QPushButton { border: none }")
        + QString("QComboBox { border: none; border-radius: 5px; padding: 3px; background-color: #A2CBEE; }")
        + QString("QComboBox:hover { background-color: #5591DC; }")
        + QString("QComboBox QAbstractItemView { outline: none; margin-top: 5px; border-radius: 5px; background-color: #A2CBEE; }")
        + QString("QComboBox QAbstractItemView::item:hover { padding: 3px; color: black; border-radius: 5px; background-color: #5591DC; }")
        + QString("QComboBox QAbstractItemView::item:selected { padding: 3px; color: white; border-radius: 5px; background-color: #5591DC; }")
        + QString("QComboBox::down-arrow { image: url(\":/icon/down_bla.ico\"); width: 20px; }")
        + QString("QComboBox::drop-down { border: none; }");

    themeResource->generalStyleSheet = defaultGeneralStyleSheet;
    themeResource->asideBarStyleSheet = defaultAsideBarStyleSheet;
    themeResource->preferenceStyleSheet = defaultpreferenceStyleSheet;
    return themeResource;
}