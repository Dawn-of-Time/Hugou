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
    m_tempTheme = theme;    // m_tempTheme��Ŀ�����⣨�û�ϣ����
    LoadThemeResourceThread* loadThemeResourceThread = new LoadThemeResourceThread;
    connect(loadThemeResourceThread, &LoadThemeResourceThread::SignalThemeResourcePreparedInThread, [&](ThemeResource* themeResource, bool consistentFlag)
        {
            // �����ϣ��Ӧ�õ������������Դһ�£���ThemeManager��m_theme���Ϊm_tempTheme�����򲻱䡣
            if (consistentFlag) m_theme = m_tempTheme;
            emit SignalThemeResourcePrepared(themeResource, consistentFlag);
        });
    connect(loadThemeResourceThread, &LoadThemeResourceThread::finished, loadThemeResourceThread, &LoadThemeResourceThread::deleteLater);
    loadThemeResourceThread->setTheme(theme);
    // �����߳�һ���ܹ��õ����е�������Դ��
    loadThemeResourceThread->start();
}

// ��������Ӧ������ĺ����ֱ����ڵ�һ�μ��غͺ����ֶ�������������
// ���Ƕ�����ThemeManager��SignalThemeResourcePrepared�źŴ�����
// ThemeManagerһ�����Եõ����е����⣬�����������������Ҫ����ʧ�ܵ��ж���ThemeManager��ͨ��getTheme�õ�������һ�����뵱ǰ������Դƥ������⡣
// consistentFlag--ϣ��Ӧ�õ�����ͼ��ص�������Դ�Ƿ�һ�¡������һ�£�����Ҫ��preferenceComboboxMap["themeBox"]��
// * ����ǵ�һ�μ��ص��������ΪDefault��
// * ����Ǻ����ֶ��������������ΪThemeManager��ͨ��getTheme�õ����������ơ�
void ThemeManager::applyThemeForStartup(ThemeResource* themeResource, bool consistentFlag)
{
    // ��Ϊ��һ�μ��أ���ô���貥�Ŷ�����������������ThemeManager���źźͲۡ�
    if (!consistentFlag) emit SignalUpdateThemeComboboxValue("Default");
    applyThemeResource(themeResource);
    disconnect();
    connect(this, &ThemeManager::SignalThemeResourcePrepared, this, &ThemeManager::applyTheme);
}

void ThemeManager::applyTheme(ThemeResource* themeResource, bool consistentFlag)
{
    // ����Ϊ��һ�μ��أ���ô��Ҫִ�ж�����
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
    // У�������
    if (!isExisted)
    {
        // Default�����ļ��Ƿ���ں��Ƿ���Ч���������������������ݱ�Ӳ���뵽�����С����ǣ�����и�������ļ�����ʹ�ø������ļ������ݡ�
        if (m_theme != "Default")
        {
            preferenceHelper* helper = preferenceHelper::getHelper();
            emit helper->triggerError("10100");
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
        // У���Ƿ�Ϊ��
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