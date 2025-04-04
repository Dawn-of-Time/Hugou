#include "Utils/Include/Utils_ThemeManager.h"

ThemeManager::ThemeManager()
    : QObject()
{
    QString theme;
    if (ConfigurationHelper::getHelper()->getPreferenceValue("theme", theme)) m_theme = theme;
    else m_theme = "Default";

    connect(this, &ThemeManager::SignalThemeResourcePrepared, this, &ThemeManager::applyThemeForStartup);

    loadThemeResource(m_theme);
}

ThemeManager* ThemeManager::getManager()
{
    static ThemeManager manager;
    return &manager;
}

QString& ThemeManager::getStyleSheet(const ThemeRole& themeRole)
{
    return m_cacheMap[themeRole];
}

void ThemeManager::loadThemeResource(QString theme)
{
    m_tempTheme = theme;    // m_tempTheme是目标主题（用户希望的)
    LoadThemeResourceThread* loadThemeResourceThread = new LoadThemeResourceThread(theme);
    connect(loadThemeResourceThread, &LoadThemeResourceThread::SignalThemeResourcePreparedInThread, [&](QMap<ThemeRole, QString> themeResourceMap, bool consistentFlag, QMap<ThemeRole, QString> cacheMap)
        {
            // 如果所希望应用的主题和主题资源一致，则将ThemeManager的m_theme变更为m_tempTheme。否则改为Default。
            if (consistentFlag) m_theme = m_tempTheme;
            else m_theme = "Default";
            m_themeResourceMap = themeResourceMap;
            m_cacheMap = cacheMap;
            emit SignalThemeResourcePrepared();
        });
    connect(loadThemeResourceThread, &LoadThemeResourceThread::finished, loadThemeResourceThread, &LoadThemeResourceThread::deleteLater);
    // 下述线程一定能够得到可行的主题资源。
    loadThemeResourceThread->start();
}

// 下面两个应用主题的函数分别用于第一次加载和后续手动变更两种情况。
// 它们都经由ThemeManager的SignalThemeResourcePrepared信号触发。
// ThemeManager一定可以得到可行的主题，因此两个函数都不需要进行失败的判定。ThemeManager中的m_theme一定是与当前主题资源匹配的主题。
void ThemeManager::applyThemeForStartup()
{
    // 若为第一次加载，那么无需播放动画，并且重新连接ThemeManager的信号和槽。
    emit SignalApplyThemeResource(m_themeResourceMap);
    disconnect();
    connect(this, &ThemeManager::SignalThemeResourcePrepared, this, &ThemeManager::applyTheme);
}

void ThemeManager::applyTheme()
{
    // 若不为第一次加载，那么需要执行动画。
    // 获取GlobalTop控制器使用权。
    GlobalTopController* controller = GlobalTopController::getController();
    if (controller->isAvailable())
    {
        m_globalTopUsagePermission = controller->use();
        connect(controller, &GlobalTopController::SignalFadeInFinished, [this]()
            {
                emit SignalApplyThemeResource(m_themeResourceMap);
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

void LoadThemeResourceThread::run()
{
    bool isExisted = true;
    bool isCorrect = true;
    bool isEmpty = false;
    QStringList styleSheetList;

    for (const QString& fileName : m_fileNameList)
    {
        QFile file(QString(":/theme/%1/%2.qss").arg(m_theme).arg(fileName));
        // 校验存在性
        if (!file.exists())
        {
            isExisted = false;
            break;
        }
        // 校验正确性
        if (!file.open(QIODeviceBase::ReadOnly))
        {
            isCorrect = false;
            break;
        }
        QString styleSheet = QTextStream(&file).readAll();
        file.close();
        // 校验是否为空
        if (styleSheet.isEmpty())
        {
            isEmpty = true;
            break;
        }
        else 
        {
            if (m_themeResourceLoadModeMap[m_themeRoleMap[fileName]] == ThemeResourceLoadMode::CacheAfterLoading)
                m_cacheMap.insert(m_themeRoleMap[fileName], styleSheet);
            m_themeResourceMap.insert(m_themeRoleMap[fileName], styleSheet);
            styleSheetList.append(styleSheet);
        }
    }

    // 有任何一项不满足，都应用硬编码的默认主题。
    if (!isExisted || !isCorrect || isEmpty)
    {
        if (m_theme != "Default")
        {
            int errorCode = !isExisted ? 10100 : (!isCorrect ? 10101 : 10103);
            emit MessegeHelper::getHelper()->trigger(FloatingNote::Error, errorCode);
            m_theme = "Default";
            m_isConsistent = false;
        }
        m_themeResourceMap.clear();
        for (const QString& fileName : m_fileNameList)
            m_themeResourceMap.insert(m_themeRoleMap[fileName], getDefaultThemeResource(m_themeRoleMap[fileName]));
    }
    else m_isConsistent = true;
    emit SignalThemeResourcePreparedInThread(m_themeResourceMap, m_isConsistent, m_cacheMap);
}

QString LoadThemeResourceThread::getDefaultThemeResource(const ThemeRole& themeRole)
{
    switch (themeRole)
    {
    case ThemeRole::General:
        return QString(
            "HugouView#hugou { background-color: #F0F4FD; }"
            "QWidget#asideBarAndStackedWidget { background-color: transparent; }"
            "QStackedWidget#stackedWidget { margin-bottom: 10px; margin-right: 10px; border-radius: 10px; background-color: rgba(255, 255, 255, 0.8;}"
        );
    case ThemeRole::AsideBar:
        return QString(
            "QLabel { padding-left: 6px; color:#666666; background-color: transparent; }"
            "QLabel#userAvatar { padding: 0px; border-radius: 24px; border: none; color: balck; background-color: transparent;} "
            "QLabel#userNickname { border: none; color: balck; background-color: transparent;} "
            "QLabel#userID { border: none; color: balck; background-color: transparent;} "
            "QPushButton[status=\"default\"] { border-radius: 10px; }"
            "QPushButton[status=\"default\"] > QLabel { padding: 0px; margin :0px; color: #434343; background-color: transparent; }"
            "QPushButton[status=\"current\"] { border-radius: 10px;}"
            "QPushButton[status=\"current\"] > QLabel { padding: 0px; margin :0px; color: #377FED; background-color: transparent; }"
        );
    case ThemeRole::Preference:
        return QString(
            "QStackedWidget { background-color: transparent; border: none }"
            "QTreeWidget { background-color: transparent; border: none }"
            "QListWidget { background-color: transparent; border: none; outline: none; margin-left: 20px; margin-right: 12px; margin-top: 2px; margin-bottom: 2px }"
            "QListWidget::item:hover { background-color: transparent }"
            "QPushButton { border: none }"
            "QComboBox { border: none; border-radius: 5px; padding: 3px; background-color: #A2CBEE; }"
            "QComboBox:hover { background-color: #5591DC; }"
            "QComboBox QAbstractItemView { outline: none; margin-top: 5px; border-radius: 5px; background-color: #A2CBEE; }"
            "QComboBox QAbstractItemView::item:hover { padding: 3px; color: black; border-radius: 5px; background-color: #5591DC; }"
            "QComboBox QAbstractItemView::item:selected { padding: 3px; color: white; border-radius: 5px; background-color: #5591DC; }"
            "QComboBox::down-arrow { image: url(\":/icon/down_bla.ico\"; width: 20px; }"
            "QComboBox::drop-down { border: none; }"
        );
    case ThemeRole::Schedule:
        return QString(
            "ScheduleView QWidget#cardWidget { border-left: 1px solid #A8A8A8; }"
            "ScheduleView QWidget#memoGeneralWidget { background-color: #FFFFFF; border-radius: 12px; }"
            "ScheduleView QPushButton { border: none; background-color: transparent; }"
        );
    default:
        return "";
    }
}