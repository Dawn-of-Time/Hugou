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
    m_tempTheme = theme;    // m_tempTheme��Ŀ�����⣨�û�ϣ����)
    LoadThemeResourceThread* loadThemeResourceThread = new LoadThemeResourceThread(theme);
    connect(loadThemeResourceThread, &LoadThemeResourceThread::SignalThemeResourcePreparedInThread, [&](ThemeResource* themeResource, bool consistentFlag)
        {
            // �����ϣ��Ӧ�õ������������Դһ�£���ThemeManager��m_theme���Ϊm_tempTheme�����򲻱䡣
            if (consistentFlag) m_theme = m_tempTheme;
            emit SignalThemeResourcePrepared(themeResource);
        });
    connect(loadThemeResourceThread, &LoadThemeResourceThread::finished, loadThemeResourceThread, &LoadThemeResourceThread::deleteLater);
    // �����߳�һ���ܹ��õ����е�������Դ��
    loadThemeResourceThread->start();
}

// ��������Ӧ������ĺ����ֱ����ڵ�һ�μ��غͺ����ֶ�������������
// ���Ƕ�����ThemeManager��SignalThemeResourcePrepared�źŴ�����
// ThemeManagerһ�����Եõ����е����⣬�����������������Ҫ����ʧ�ܵ��ж���ThemeManager��ͨ��getTheme�õ�������һ�����뵱ǰ������Դƥ������⡣
// consistentFlag--ϣ��Ӧ�õ�����ͼ��ص�������Դ�Ƿ�һ�¡������һ�£�����Ҫ��preferenceComboboxMap["themeBox"]��
// * ����ǵ�һ�μ��ص��������ΪDefault��
// * ����Ǻ����ֶ��������������ΪThemeManager��ͨ��getTheme�õ����������ơ�
void ThemeManager::applyThemeForStartup(ThemeResource* themeResource)
{
    // ��Ϊ��һ�μ��أ���ô���貥�Ŷ�����������������ThemeManager���źźͲۡ�
    applyThemeResource(themeResource);
    disconnect();
    connect(this, &ThemeManager::SignalThemeResourcePrepared, this, &ThemeManager::applyTheme);
}

void ThemeManager::applyTheme(ThemeResource* themeResource)
{
    // ����Ϊ��һ�μ��أ���ô��Ҫִ�ж�����
    // ��ȡGlobalTop������ʹ��Ȩ��
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
    // У�������
    if (!isExisted)
    {
        // Default�����ļ��Ƿ���ں��Ƿ���Ч���������������������ݱ�Ӳ���뵽�����С����ǣ�����и�������ļ�����ʹ�ø������ļ������ݡ�
        if (m_theme != "Default")
        {
            emit MessegeHelper::getHelper()->trigger(FloatingNote::Error, 10100);
            m_theme = "Default";
            m_themeResource = getDefaultThemeResource();
            m_isConsistent = false;
        }
    }
    // У����ȷ��
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
        // У���Ƿ�Ϊ��
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
    // Ĭ������
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