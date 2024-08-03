#include "themeLoadThread.h"

ThemeLoadThread::ThemeLoadThread(QString theme)
{
    this->theme = theme;
}

void ThemeLoadThread::run() {
    QFile generalStyleFile(QString("res/theme/%1/general.qss").arg(theme));
    QFile asideBarStyleFile(QString("res/theme/%1/asideBar.qss").arg(theme));
    QFile settingsStyleFile(QString("res/theme/%1/settings.qss").arg(theme));
    if (!generalStyleFile.exists() || !asideBarStyleFile.exists() || !settingsStyleFile.exists())
    {
        // 硬编码Default主题
        SettingsHelper helper;
        emit helper.triggerError(10100);
        theme = "Default";
    }

    if (generalStyleFile.open(QIODeviceBase::ReadOnly) &&
        asideBarStyleFile.open(QIODeviceBase::ReadOnly) &&
        settingsStyleFile.open(QIODeviceBase::ReadOnly))
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        emit themeResourcePrepared(generalStyleFile.readAll(), asideBarStyleFile.readAll(), settingsStyleFile.readAll());
        generalStyleFile.close();
        asideBarStyleFile.close();
        settingsStyleFile.close();
    }
    else 
    {
        // 硬编码Default主题
        SettingsHelper helper;
        emit helper.triggerError(10101);
    }
}