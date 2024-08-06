#include "themeLoadThread.h"

ThemeLoadThread::ThemeLoadThread(QString theme, QWidget* hugou)
    : QThread()
{
    this->theme = theme;
    this->hugou = hugou;
}

void ThemeLoadThread::run() {
    QFile generalStyleFile(QString("res/theme/%1/general.qss").arg(theme));
    QFile asideBarStyleFile(QString("res/theme/%1/asideBar.qss").arg(theme));
    QFile settingsStyleFile(QString("res/theme/%1/settings.qss").arg(theme));
    if (!generalStyleFile.exists() || !asideBarStyleFile.exists() || !settingsStyleFile.exists())
    {
        // Ӳ����Default����
        SettingsHelper helper(hugou);
        emit helper.triggerError(10100);
        theme = "Default";
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
        // Ӳ����Default����
        SettingsHelper helper(hugou);
        emit helper.triggerError(10101);
    }
}