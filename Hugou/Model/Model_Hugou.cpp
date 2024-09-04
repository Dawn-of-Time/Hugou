#include "Model_Hugou.h"

HugouModel::HugouModel()
    : QObject()
{
    m_settingsModel = new SettingsModel();
}

HugouModel::~HugouModel()
{
    delete m_settingsModel;
}

QString HugouModel::getTheme()
{
    if (m_theme.isEmpty())
    {
        SettingsHelper* helper = SettingsHelper::getHelper();
        m_theme = helper->settingsMap["theme"];
    }
    return m_theme;
}

HugouModel::ThemeResource HugouModel::loadThemeResource(QString theme)
{
    // 当不为默认主题时，尝试加载主题文件
    if (theme != "Default")
    {
        QFile generalStyleFile(QString(":/theme/%1/general.qss").arg(theme));
        QFile asideBarStyleFile(QString(":/theme/%1/asideBar.qss").arg(theme));
        QFile settingsStyleFile(QString(":/theme/%1/settings.qss").arg(theme));
        // 校验存在性
        if (!generalStyleFile.exists() || !asideBarStyleFile.exists() || !settingsStyleFile.exists())
        {
            SettingsHelper* helper = SettingsHelper::getHelper();
            emit helper->triggerError(10100);
            theme = "Default";
            return getDefaultThemeResource();
        }
        // 校验完整性
        if (!generalStyleFile.open(QIODeviceBase::ReadOnly) ||
            !asideBarStyleFile.open(QIODeviceBase::ReadOnly) ||
            !settingsStyleFile.open(QIODeviceBase::ReadOnly))
        {
            SettingsHelper* helper = SettingsHelper::getHelper();
            emit helper->triggerError(10101);
            theme = "Default";
            return getDefaultThemeResource();
        }
        ThemeResource themeResource;
        themeResource.generalStyleSheet = QTextStream(&generalStyleFile).readAll();
        themeResource.asideBarStyleSheet = QTextStream(&asideBarStyleFile).readAll();
        themeResource.settingsStyleSheet = QTextStream(&settingsStyleFile).readAll();
        //std::this_thread::sleep_for(std::chrono::seconds(2));
        generalStyleFile.close();
        asideBarStyleFile.close();
        settingsStyleFile.close();
        return themeResource;
    }
    return getDefaultThemeResource();
}

HugouModel::ThemeResource HugouModel::getDefaultThemeResource()
{
    ThemeResource themeResource;
    themeResource.generalStyleSheet = defaultGeneralStyleSheet;
    themeResource.asideBarStyleSheet = defaultAsideBarStyleSheet;
    themeResource.settingsStyleSheet = defaultSettingsStyleSheet;
    return themeResource;
}