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
    m_tempTheme = theme;    // m_tempTheme��Ŀ�����⣨�û�ϣ����)
    LoadThemeResourceThread* loadThemeResourceThread = new LoadThemeResourceThread(theme);
    connect(loadThemeResourceThread, &LoadThemeResourceThread::SignalThemeResourcePreparedInThread, [&](QMap<ThemeRole, QString> themeResourceMap, bool consistentFlag, QMap<ThemeRole, QString> cacheMap)
        {
            // �����ϣ��Ӧ�õ������������Դһ�£���ThemeManager��m_theme���Ϊm_tempTheme�������ΪDefault��
            if (consistentFlag) m_theme = m_tempTheme;
            else m_theme = "Default";
            m_themeResourceMap = themeResourceMap;
            m_cacheMap = cacheMap;
            emit SignalThemeResourcePrepared();
        });
    connect(loadThemeResourceThread, &LoadThemeResourceThread::finished, loadThemeResourceThread, &LoadThemeResourceThread::deleteLater);
    // �����߳�һ���ܹ��õ����е�������Դ��
    loadThemeResourceThread->start();
}

// ��������Ӧ������ĺ����ֱ����ڵ�һ�μ��غͺ����ֶ�������������
// ���Ƕ�����ThemeManager��SignalThemeResourcePrepared�źŴ�����
// ThemeManagerһ�����Եõ����е����⣬�����������������Ҫ����ʧ�ܵ��ж���ThemeManager�е�m_themeһ�����뵱ǰ������Դƥ������⡣
void ThemeManager::applyThemeForStartup()
{
    // ��Ϊ��һ�μ��أ���ô���貥�Ŷ�����������������ThemeManager���źźͲۡ�
    emit SignalApplyThemeResource(m_themeResourceMap);
    disconnect();
    connect(this, &ThemeManager::SignalThemeResourcePrepared, this, &ThemeManager::applyTheme);
}

void ThemeManager::applyTheme()
{
    // ����Ϊ��һ�μ��أ���ô��Ҫִ�ж�����
    // ��ȡGlobalTop������ʹ��Ȩ��
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
                // �黹GlobalTop������ʹ��Ȩ��
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
        // У�������
        if (!file.exists())
        {
            isExisted = false;
            break;
        }
        // У����ȷ��
        if (!file.open(QIODeviceBase::ReadOnly))
        {
            isCorrect = false;
            break;
        }
        QString styleSheet = QTextStream(&file).readAll();
        file.close();
        // У���Ƿ�Ϊ��
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

    // ���κ�һ����㣬��Ӧ��Ӳ�����Ĭ�����⡣
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