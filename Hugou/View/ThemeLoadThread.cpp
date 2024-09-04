#include "themeLoadThread.h"

ThemeLoadThread::ThemeLoadThread(QString theme)
    : QThread()
{
    this->m_theme = theme;
}

void ThemeLoadThread::run() {
    QFile generalStyleFile(QString(":/theme/%1/general.qss").arg(m_theme));
    QFile asideBarStyleFile(QString(":/theme/%1/asideBar.qss").arg(m_theme));
    QFile settingsStyleFile(QString(":/theme/%1/settings.qss").arg(m_theme));
    if (!generalStyleFile.exists() || !asideBarStyleFile.exists() || !settingsStyleFile.exists())
    {
        // 硬编码Default主题
        SettingsHelper* helper = SettingsHelper::getHelper();
        emit helper->triggerError(10100);
        m_theme = "Default";
    }

    if (generalStyleFile.open(QIODeviceBase::ReadOnly) &&
        asideBarStyleFile.open(QIODeviceBase::ReadOnly) &&
        settingsStyleFile.open(QIODeviceBase::ReadOnly))
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        emit themeResourcePrepared(generalStyleFile.readAll(), asideBarStyleFile.readAll(), settingsStyleFile.readAll());
        generalStyleFile.close();
        asideBarStyleFile.close();
        settingsStyleFile.close();
    }
    else 
    {
        // 硬编码Default主题
        SettingsHelper* helper = SettingsHelper::getHelper();
        emit helper->triggerError(10101);
    }
}